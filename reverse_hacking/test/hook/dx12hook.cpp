#include "dx12hook.h"
#include <Windows.h>
#include <d3d12.h>
#include <dxgi.h>
#include <dxgi1_4.h>
#include <mutex>
#include <thread>
#include "Detours/detours.h"
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib, "dxgi.lib")
#ifdef _WIN64
#pragma comment(lib, "detours64.lib")
#else
#pragma comment(lib, "detours32.lib")
#endif
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_dx12.h"
#include "../imgui/imgui_impl_win32.h"
#include "../log.h"


extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


namespace Dx12Hook {


typedef HRESULT(STDMETHODCALLTYPE* Dx12Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
Dx12Present g_present = nullptr;

typedef void(STDMETHODCALLTYPE* Dx12ExecuteCommandLists)(ID3D12CommandQueue* queue, UINT NumCommandLists, ID3D12CommandList* const* ppCommandLists);
Dx12ExecuteCommandLists g_executeCommandLists = nullptr;

typedef HRESULT(STDMETHODCALLTYPE* Dx12ResizeBufferHook) (IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);
Dx12ResizeBufferHook g_resizeBufferHook = nullptr;

struct FrameContext 
{
    ID3D12CommandAllocator* commandAllocator;
    ID3D12Resource* resource;
    D3D12_CPU_DESCRIPTOR_HANDLE descriptorHandle;
};

ID3D12Device* g_device = nullptr;
ID3D12CommandQueue* g_commandQueue = nullptr;
FrameContext* g_frameContext = nullptr;
ID3D12DescriptorHeap* g_descriptorHeapBackBuffers = nullptr;
ID3D12DescriptorHeap* g_descriptorHeapRender = nullptr;
ID3D12GraphicsCommandList* g_commandList = nullptr;
IDXGISwapChain3* g_swapChain3 = nullptr;
UINT g_bufferCount = 0;

std::uintptr_t* g_swapChainVtable = nullptr;
std::uintptr_t* g_commandQueueVtable = nullptr;

bool g_init = false;
WNDPROC g_hGameWindowProc;
Dx12Hook::ConfigData g_configData;


LRESULT CALLBACK hookWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    CallWindowProc((WNDPROC)ImGui_ImplWin32_WndProcHandler, hWnd, uMsg, wParam, lParam);

    ImGuiIO& io = ImGui::GetIO();
    if (io.WantCaptureMouse || io.WantCaptureKeyboard)
    {
        return true;
    }

    return CallWindowProc(g_hGameWindowProc, hWnd, uMsg, wParam, lParam);
}

HRESULT WINAPI hookPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
    static std::once_flag onceFlag;
    std::call_once(onceFlag, [&]()
    {
        HWND hGameWindow = (HWND)g_configData.gameWindow;
        if (hGameWindow == nullptr)
        {
            LOG_INFO("hookPresent failed, hGameWindow == nullptr.\n");
            return;
        }

        if (FAILED(pSwapChain->GetDevice(__uuidof(ID3D12Device), (void**)&g_device)))
        {
            LOG_INFO("hookPresent failed, GetDevice failed.\n");
            return;
        }

        // Query SwapChain3 which can be used to get the current backbuffer index
        pSwapChain->QueryInterface(IID_PPV_ARGS(&g_swapChain3));
        if (g_swapChain3 == nullptr)
        {
            LOG_INFO("Could not query SwapChain to SwapChain3");
            return;
        }

        DXGI_SWAP_CHAIN_DESC desc;
        pSwapChain->GetDesc(&desc);
        desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
        desc.OutputWindow = hGameWindow;
        desc.Windowed = ((GetWindowLongPtr(hGameWindow, GWL_STYLE) & WS_POPUP) != 0) ? false : true;

        g_bufferCount = desc.BufferCount;
        g_frameContext = new FrameContext[g_bufferCount];

        D3D12_DESCRIPTOR_HEAP_DESC descriptorImGuiRender = {};
        descriptorImGuiRender.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
        descriptorImGuiRender.NumDescriptors = g_bufferCount;
        descriptorImGuiRender.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

        if (FAILED(g_device->CreateDescriptorHeap(&descriptorImGuiRender, IID_PPV_ARGS(&g_descriptorHeapRender))))
        {
            LOG_INFO("hookPresent failed, CreateDescriptorHeap failed.\n");
            return;
        }           

        ID3D12CommandAllocator* allocator;
        if (FAILED(g_device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&allocator))))
        {
            LOG_INFO("hookPresent failed, CreateCommandAllocator failed.\n");
            return;
        }

        for (UINT i = 0; i < g_bufferCount; i++)
        {
            g_frameContext[i].commandAllocator = allocator;
        }

        if (FAILED(g_device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, allocator, NULL, IID_PPV_ARGS(&g_commandList)))
            || FAILED(g_commandList->Close()))
        {
            LOG_INFO("hookPresent failed, CreateCommandList failed.\n");
            return;
        }

        D3D12_DESCRIPTOR_HEAP_DESC descriptorBackBuffers;
        descriptorBackBuffers.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
        descriptorBackBuffers.NumDescriptors = g_bufferCount;
        descriptorBackBuffers.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
        descriptorBackBuffers.NodeMask = 1;
        if (FAILED(g_device->CreateDescriptorHeap(&descriptorBackBuffers, IID_PPV_ARGS(&g_descriptorHeapBackBuffers))))
        {
            LOG_INFO("hookPresent failed, CreateDescriptorHeap failed.\n");
            return;
        }

        const auto RTVDescriptorSize = g_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
        D3D12_CPU_DESCRIPTOR_HANDLE RTVHandle = g_descriptorHeapBackBuffers->GetCPUDescriptorHandleForHeapStart();
        for (UINT i = 0; i < g_bufferCount; i++)
        {
            ID3D12Resource* pBackBuffer = nullptr;
            pSwapChain->GetBuffer(i, IID_PPV_ARGS(&pBackBuffer));
            g_device->CreateRenderTargetView(pBackBuffer, nullptr, RTVHandle);
            g_frameContext[i].descriptorHandle = RTVHandle;
            g_frameContext[i].resource = pBackBuffer;
            RTVHandle.ptr += RTVDescriptorSize;
        }

        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantTextInput || ImGui::GetIO().WantCaptureKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        ImGui::StyleColorsDark();
        if (!ImGui_ImplWin32_Init(hGameWindow) 
            || !ImGui_ImplDX12_Init(g_device, g_bufferCount,
                DXGI_FORMAT_R8G8B8A8_UNORM, g_descriptorHeapRender,
                g_descriptorHeapRender->GetCPUDescriptorHandleForHeapStart(),
                g_descriptorHeapRender->GetGPUDescriptorHandleForHeapStart()))
        {
            LOG_INFO("hookPresent failed, init imgui failed.\n");
            return;
        }

        g_hGameWindowProc = (WNDPROC)SetWindowLongPtr(hGameWindow, GWLP_WNDPROC, (LONG_PTR)hookWndProc);
        if (g_hGameWindowProc == nullptr)
        {
            LOG_INFO("hookPresent failed, g_hGameWindowProc == nullptr.\n");
            return;
        }

        g_init = true;
    });

    if (!g_init || (g_commandQueue == nullptr))
    {
        return g_present(pSwapChain, SyncInterval, Flags);
    }

    ImGui_ImplDX12_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    if (g_configData.renderFun)
    {
        g_configData.renderFun();
    }

    ImGui::EndFrame();

    FrameContext& currentFrameContext = g_frameContext[g_swapChain3->GetCurrentBackBufferIndex()];
    currentFrameContext.commandAllocator->Reset();

    D3D12_RESOURCE_BARRIER barrier;
    barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    barrier.Transition.pResource = currentFrameContext.resource;
    barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
    barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;

    g_commandList->Reset(currentFrameContext.commandAllocator, nullptr);
    g_commandList->ResourceBarrier(1, &barrier);
    g_commandList->OMSetRenderTargets(1, &currentFrameContext.descriptorHandle, FALSE, nullptr);
    g_commandList->SetDescriptorHeaps(1, &g_descriptorHeapRender);

    ImGui::Render();
    ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), g_commandList);
    barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
    barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
    g_commandList->ResourceBarrier(1, &barrier);
    g_commandList->Close();
    g_commandQueue->ExecuteCommandLists(1, reinterpret_cast<ID3D12CommandList* const*>(&g_commandList));
    return g_present(pSwapChain, SyncInterval, Flags);
}

HRESULT STDMETHODCALLTYPE hookDx12ResizeBuffer(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
{
    if (g_device == nullptr)
    {
        return g_resizeBufferHook(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);
    }

    LOG_INFO("hookDx12ResizeBuffer, window will resize,Width{}, Height:{}.\n", Width, Height);

    // Release the previous resources we will be recreating.
    for (UINT i = 0; i < g_bufferCount; i++)
    {
        g_frameContext[i].resource->Release();
    }

    HRESULT hr = g_resizeBufferHook(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);

    static const auto RTVDescriptorSize = g_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
    D3D12_CPU_DESCRIPTOR_HANDLE RTVHandle = g_descriptorHeapBackBuffers->GetCPUDescriptorHandleForHeapStart();
    for (UINT i = 0; i < g_bufferCount; i++)
    {
        ID3D12Resource* pBackBuffer = nullptr;
        pSwapChain->GetBuffer(i, IID_PPV_ARGS(&pBackBuffer));
        g_device->CreateRenderTargetView(pBackBuffer, nullptr, RTVHandle);
        g_frameContext[i].descriptorHandle = RTVHandle;
        g_frameContext[i].resource = pBackBuffer;
        RTVHandle.ptr += RTVDescriptorSize;
    }

    return hr;
}

void STDMETHODCALLTYPE hookExecuteCommandLists(ID3D12CommandQueue* queue, UINT NumCommandLists, ID3D12CommandList* const* ppCommandLists)
{
    if (g_commandQueue == nullptr)
    {
        g_commandQueue = queue;
    }

    g_executeCommandLists(queue, NumCommandLists, ppCommandLists);
}

LRESULT WINAPI wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

bool threadStart(const ConfigData& config)
{
    if (config.gameWindow == nullptr)
    {
        LOG_INFO("threadStart, config.gameWindow == NULL\n");
        return false;
    }

    g_configData = config;

    WNDCLASSEXA wc = { sizeof(WNDCLASSEX), CS_CLASSDC, wndProc, 0L, 0L, GetModuleHandleA(NULL), NULL, NULL, NULL, NULL, "DX", NULL };
    RegisterClassExA(&wc);

    HWND hWnd = CreateWindowA(wc.lpszClassName, NULL, WS_OVERLAPPEDWINDOW, 100, 100, 300, 300, NULL, NULL, wc.hInstance, NULL);
    IDXGIFactory4* factory = nullptr;
    if (FAILED(CreateDXGIFactory1(IID_PPV_ARGS(&factory))))
    {
        LOG_INFO("threadStart, CreateDXGIFactory1 failed.\n");
        return false;
    }

    IDXGIAdapter* adapter = nullptr;
    if (factory->EnumAdapters(0, &adapter) == DXGI_ERROR_NOT_FOUND)
    {
        LOG_INFO("threadStart, EnumAdapters failed.\n");
        return false;
    }

    ID3D12Device* device = nullptr;
    if (FAILED(D3D12CreateDevice(adapter, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device))))
    {
        LOG_INFO("threadStart, D3D12CreateDevice failed.\n");
        return false;
    }

    D3D12_COMMAND_QUEUE_DESC queueDesc;
    queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    queueDesc.Priority = 0;
    queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    queueDesc.NodeMask = 0;
    ID3D12CommandQueue* commandQueue;
    if (FAILED(device->CreateCommandQueue(&queueDesc, __uuidof(ID3D12CommandQueue), (void**)&commandQueue)))
    {
        LOG_INFO("threadStart, CreateCommandQueue failed.\n");
        return false;
    }

    DXGI_RATIONAL refreshRate;
    refreshRate.Numerator = 60;
    refreshRate.Denominator = 1;

    DXGI_MODE_DESC bufferDesc;
    bufferDesc.Width = 100;
    bufferDesc.Height = 100;
    bufferDesc.RefreshRate = refreshRate;
    bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

    DXGI_SAMPLE_DESC sampleDesc;
    sampleDesc.Count = 1;
    sampleDesc.Quality = 0;

    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
    swapChainDesc.BufferDesc = bufferDesc;
    swapChainDesc.SampleDesc = sampleDesc;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.BufferCount = 2;
    swapChainDesc.OutputWindow = hWnd;
    swapChainDesc.Windowed = 1;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    IDXGISwapChain* swapChain;
    if (FAILED(factory->CreateSwapChain(commandQueue, &swapChainDesc, &swapChain)))
    {
        LOG_INFO("threadStart, CreateSwapChain failed.\n");
        return false;
    }

    // hook
    g_swapChainVtable = (std::uintptr_t*)(*(std::uintptr_t*)swapChain);
    g_resizeBufferHook = (Dx12ResizeBufferHook)g_swapChainVtable[13];
    g_present = (Dx12Present)g_swapChainVtable[8];

    g_commandQueueVtable = (std::uintptr_t*)(*(std::uintptr_t*)commandQueue);
    g_executeCommandLists = (Dx12ExecuteCommandLists)g_commandQueueVtable[10];

    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID&)g_present, hookPresent);
    DetourAttach(&(PVOID&)g_resizeBufferHook, hookDx12ResizeBuffer);
    DetourAttach(&(PVOID&)g_executeCommandLists, hookExecuteCommandLists);
    DetourTransactionCommit();

    LOG_INFO("BaseAddr:              {}\n", (void*)GetModuleHandle(NULL));
    LOG_INFO("g_swapChainVtable:     {}\n", (void*)g_swapChainVtable);
    LOG_INFO("g_commandQueueVtable:  {}\n", (void*)g_commandQueueVtable);

    device->Release();
    commandQueue->Release();
    swapChain->Release();

    while (true)
    {
        Sleep(10);
    }
}

void start(const ConfigData& config)
{
    std::thread thr(&threadStart, config);
    thr.detach();
}

}


/*
you can look up Vtable funtions by add  /d1 reportSingleClassLayoutIDXGISwapChain to VS->C/C++>commandline
IDXGISwapChain  VTable
1> 0	| &IUnknown::QueryInterface
1> 1	| &IUnknown::AddRef
1> 2	| &IUnknown::Release
1> 3	| &IDXGIObject::SetPrivateData
1> 4	| &IDXGIObject::SetPrivateDataInterface
1> 5	| &IDXGIObject::GetPrivateData
1> 6	| &IDXGIObject::GetParent
1> 7	| &IDXGIDeviceSubObject::GetDevice
1> 8	| &IDXGISwapChain::Present
1> 9	| &IDXGISwapChain::GetBuffer
1>10	| &IDXGISwapChain::SetFullscreenState
1>11	| &IDXGISwapChain::GetFullscreenState
1>12	| &IDXGISwapChain::GetDesc
1>13	| &IDXGISwapChain::ResizeBuffers
1>14	| &IDXGISwapChain::ResizeTarget
1>15	| &IDXGISwapChain::GetContainingOutput
1>16	| &IDXGISwapChain::GetFrameStatistics
1>17	| &IDXGISwapChain::GetLastPresentCount


ID3D12CommandQueue  VTable
1> 0	| &IUnknown::QueryInterface
1> 1	| &IUnknown::AddRef
1> 2	| &IUnknown::Release
1> 3	| &ID3D12Object::GetPrivateData
1> 4	| &ID3D12Object::SetPrivateData
1> 5	| &ID3D12Object::SetPrivateDataInterface
1> 6	| &ID3D12Object::SetName
1> 7	| &ID3D12DeviceChild::GetDevice
1> 8	| &ID3D12CommandQueue::UpdateTileMappings
1> 9	| &ID3D12CommandQueue::CopyTileMappings
1>10	| &ID3D12CommandQueue::ExecuteCommandLists
1>11	| &ID3D12CommandQueue::SetMarker
1>12	| &ID3D12CommandQueue::BeginEvent
1>13	| &ID3D12CommandQueue::EndEvent
1>14	| &ID3D12CommandQueue::Signal
1>15	| &ID3D12CommandQueue::Wait
1>16	| &ID3D12CommandQueue::GetTimestampFrequency
1>17	| &ID3D12CommandQueue::GetClockCalibration
1>18	| &ID3D12CommandQueue::GetDesc
*/