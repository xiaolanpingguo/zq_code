//#include "dllloader.h"
//#include "r3/log.h"
//#include "r3/utils.h"
//#include "r3/render_manager.h"
//#include "r3/process_mamager.h"
//#include "r3/imgui/imgui_impl_win32.h"
//#include "r3/imgui/imgui.h"
//
//#include <commdlg.h>
//
//
//DllLoader::DllLoader()
//{
//}
//
//DllLoader::~DllLoader()
//{
//}
//
//void DllLoader::start()
//{
//	std::thread thr(&appThread);
//    //HANDLE h = thr.native_handle();
//    //if (Utils::hideThread(h))
//    //{
//    //    LOG_INFO("hide thead success, thead handle:{}\n", (void*)h);
//    //}
//	thr.detach();
//}
//
//void DllLoader::appThread()
//{
//	DllLoader* loader = new DllLoader();
//	if (!loader->init())
//	{
//		return;
//	}
//
//	loader->run();
//}
//
//bool DllLoader::init()
//{
//	if (!Application::init())
//	{
//        MessageBox(nullptr, TEXT("render manager init failed"), TEXT("error"), MB_OK);
//        return false;
//	}
//
//	return true;
//}
//
//void DllLoader::run()
//{
//	Application::run();
//}
//
//ApplicationConfig DllLoader::getApplicationConfig()
//{
//	return ApplicationConfig{ std::bind(&DllLoader::draw, this), 400, 200, L"test", false, };
//}
//
//void DllLoader::update()
//{
//}
//
//void DllLoader::shutdown()
//{
//	Application::shutdown();
//}
//
//void DllLoader::draw()
//{
//	ImGui::Begin("loader");
//
//	if (ImGui::Button("load"))
//	{
//		loadDll();
//	}
//
//	if (ImGui::Button("unload"))
//	{
//		unloadDll();
//	}
//
//	ImGui::End();
//}
//
//void DllLoader::loadDll()
//{
//	OPENFILENAME ofn = { 0 };
//	TCHAR strFilename[MAX_PATH] = { 0 };
//	ofn.lStructSize = sizeof(OPENFILENAME);
//	ofn.hwndOwner = NULL;
//	ofn.lpstrFilter = TEXT("*.*");
//	ofn.nFilterIndex = 1;
//	ofn.lpstrFile = strFilename;
//	ofn.nMaxFile = sizeof(strFilename);
//	ofn.lpstrInitialDir = TEXT(".");
//	ofn.lpstrTitle = TEXT("Open");
//	ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;
//	if (GetOpenFileName(&ofn))
//	{
//		HMODULE handle = LoadLibrary(strFilename);
//		if (handle)
//		{
//			MessageBox(NULL, TEXT("load success"), TEXT("notice"), 0);
//			m_dllHandls.insert({ std::wstring(strFilename), handle });
//		}
//	}
//}
//
//void DllLoader::unloadDll()
//{
//	if (!m_dllHandls.empty())
//	{
//		FreeLibrary(m_dllHandls.begin()->second);
//		m_dllHandls.erase(m_dllHandls.begin());
//	}
//}
