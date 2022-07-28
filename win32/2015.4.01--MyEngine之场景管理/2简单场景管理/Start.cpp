#include "Start.h"
#include "SceneManager.h"
#include <iostream>
#include <windows.h>

void CStart::Run()
{
	system("cls");
	std::cout<<"Start³¡¾°"<<std::endl;

	if(GetAsyncKeyState(VK_RETURN) & 0x8000)
		CSceneManager::SetCurScene(1);
	if(GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		CSceneManager::Exit();
}