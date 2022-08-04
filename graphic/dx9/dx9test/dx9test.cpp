#include <d3d9.h>
#include <strsafe.h>
#pragma comment(lib, "d3d9.lib")


struct CUSTOMVERTEX
{
    FLOAT x, y, z, rhw; // The transformed position for the vertex
    DWORD color;        // The vertex color
};

// Our custom FVF, which describes our custom vertex structure
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)


LPDIRECT3D9             g_pD3D = NULL; // Used to create the D3DDevice
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL; // Our rendering device
LPDIRECT3DVERTEXBUFFER9 g_pVB = NULL; // Buffer to hold Vertices


HRESULT InitD3D(HWND hWnd)
{
    // Create the D3D object.
    if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
        return E_FAIL;

    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

    if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING,
        &d3dpp, &g_pd3dDevice)))
    {
        return E_FAIL;
    }

    // Device state would normally be set here

    return S_OK;
}

//-----------------------------------------------------------------------------
// Name: InitVB()
// Desc: Creates a vertex buffer and fills it with our Vertices. The vertex
//       buffer is basically just a chuck of memory that holds Vertices. After
//       creating it, we must Lock()/Unlock() it to fill it. For indices, D3D
//       also uses index buffers. The special thing about vertex and index
//       buffers is that they can be created in device memory, allowing some
//       cards to process them in hardware, resulting in a dramatic
//       performance gain.
//-----------------------------------------------------------------------------
HRESULT InitVB()
{
    CUSTOMVERTEX Vertices[] =
    {
        { 150.0f,  50.0f, 0.5f, 1.0f, D3DCOLOR_XRGB(255,0,0), }, // x, y, z, rhw, color
        { 250.0f, 250.0f, 0.5f, 1.0f, D3DCOLOR_XRGB(0,255,0), },
        {  50.0f, 250.0f, 0.5f, 1.0f, D3DCOLOR_XRGB(0,0,255), },
    };

    if (FAILED(g_pd3dDevice->CreateVertexBuffer(3 * sizeof(CUSTOMVERTEX),
        0, D3DFVF_CUSTOMVERTEX,
        D3DPOOL_DEFAULT, &g_pVB, NULL)))
    {
        return E_FAIL;
    }

    VOID* pVertices;
    if (FAILED(g_pVB->Lock(0, sizeof(Vertices), (void**)&pVertices, 0)))
        return E_FAIL;
    memcpy(pVertices, Vertices, sizeof(Vertices));
    g_pVB->Unlock();

    return S_OK;
}

VOID Cleanup()
{
    if (g_pVB != NULL)
        g_pVB->Release();

    if (g_pd3dDevice != NULL)
        g_pd3dDevice->Release();

    if (g_pD3D != NULL)
        g_pD3D->Release();
}

VOID Render()
{
    // Clear the backbuffer to a blue color
    g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

    // Begin the scene
    if (SUCCEEDED(g_pd3dDevice->BeginScene()))
    {
        g_pd3dDevice->SetStreamSource(0, g_pVB, 0, sizeof(CUSTOMVERTEX));
        g_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);

        g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);

        // End the scene
        g_pd3dDevice->EndScene();
    }

    // Present the backbuffer contents to the display
    g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:
        Cleanup();
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, INT)
{
    WNDCLASS wc;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = MsgProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInst;
    wc.hIcon = LoadIcon(0, IDI_APPLICATION);
    wc.hCursor = LoadCursor(0, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
    wc.lpszMenuName = 0;
    wc.lpszClassName = L"D3DWndClassName";

    if (!RegisterClass(&wc))
    {
        MessageBox(0, L"RegisterClass Failed.", 0, 0);
        return false;
    }

    // Compute window rectangle dimensions based on requested client area dimensions.
    RECT R = { 0, 0, 800, 600 };
    AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
    int width = R.right - R.left;
    int height = R.bottom - R.top;

    HWND hWnd = CreateWindow(L"D3DWndClassName", L"test",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, 0, 0, hInst, 0);
    if (!hWnd)
    {
        MessageBox(0, L"CreateWindow Failed.", 0, 0);
        return false;
    }

    // Initialize Direct3D
    if (SUCCEEDED(InitD3D(hWnd)))
    {
        // Create the vertex buffer
        if (SUCCEEDED(InitVB()))
        {
            // Show the window
            ShowWindow(hWnd, SW_SHOWDEFAULT);
            UpdateWindow(hWnd);

            // Enter the message loop
            MSG msg;
            ZeroMemory(&msg, sizeof(msg));
            while (msg.message != WM_QUIT)
            {
                if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
                {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }
                else
                    Render();
            }
        }
    }

    UnregisterClassA("dx9", wc.hInstance);
    return 0;
}