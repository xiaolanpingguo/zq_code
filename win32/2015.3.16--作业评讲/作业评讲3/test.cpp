#include <windows.h>
#include "resource.h"
#include <iostream>

bool begin = false;
int num = 0;
int opr = -1; //0123代表+-*/
bool selectNum = true;//选择数字


void activeNum(HWND hwndDlg,bool b)
{
	for(int i = IDC_BUTTON1 ; i <= IDC_BUTTON10;++i)
	{
		HWND h = GetDlgItem(hwndDlg ,i);
		EnableWindow(h,b);
	}
	for(int i = IDC_BUTTON12 ; i <= IDC_BUTTON15;++i)
	{
		HWND h = GetDlgItem(hwndDlg ,i);
		EnableWindow(h,!b);
	}
}

INT_PTR CALLBACK DiglogProc(HWND hwnddlg,
							UINT uMsg,
							WPARAM wParam,
							LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_INITDIALOG:
		{
			activeNum(hwnddlg,true);
			return 1;
		}
	case WM_COMMAND:
		{
			if(HIWORD(wParam) == BN_CLICKED)
			{
				if(LOWORD(wParam) == IDCANCEL
				||LOWORD(wParam) == IDOK)
					EndDialog(hwnddlg,1);
				else if(LOWORD(wParam) == IDC_BUTTON11)
				{
					begin = false;
					num = 0;
					opr = -1;
					selectNum = true;
					activeNum(hwnddlg,selectNum);
					SetWindowTextA(GetDlgItem(hwnddlg,IDC_EDIT1),"");
				}
				else
				{
					if(selectNum)
					{
						if(!begin)
						{
							num = LOWORD(wParam) - IDC_BUTTON1 + 1;
							begin = true;
						}
						else
						{
							switch(opr)
							{
							case 0:num += ( LOWORD(wParam) - IDC_BUTTON1 + 1);break;
							case 1:num -= ( LOWORD(wParam) - IDC_BUTTON1 + 1);break;
							case 2:num *= ( LOWORD(wParam) - IDC_BUTTON1 + 1);break;
							case 3:num /= ( LOWORD(wParam) - IDC_BUTTON1 + 1);break;
							}
						}
						char buf[32];
						sprintf_s(buf,32,"%d",num);
						SetWindowTextA(GetDlgItem(hwnddlg,IDC_EDIT1),buf);
						activeNum(hwnddlg,selectNum = !selectNum);
					}
					else
					{
						opr = LOWORD(wParam) - IDC_BUTTON12;
						activeNum(hwnddlg,selectNum = !selectNum);
					}
				}
			}
			return 0;
		}
	}
	return 0;
}


//窗口消息函数，本函数将被操作系统调用
__w64 long __stdcall WindowProc(HWND hwnd,//产生消息的窗口
								unsigned int uMsg,//消息类型
								__w64 unsigned int wParam,//消息附加参数1
								__w64 long lParam)//消息附加参数2
{
	switch(uMsg)
	{
	//销毁消息触发方式
	//1)点击系统菜单的关闭菜单项（Alt + F4）
	//2)右上角的X按钮
	case WM_DESTROY:
		{
			//投递一个WM_QUIT消息到本线程的消息队列中
			PostQuitMessage(0);
			//一般我们处理了某个消息都要直接返回0.
			return 0;
		}
	}
	//我们不关心的消息就调用DefWindowProc(windows对所有消息的默认处理函数)来帮助我们处理
	return DefWindowProc(hwnd,uMsg,wParam,lParam);
}

int __stdcall WinMain(HINSTANCE hInstance,//应用程序实例句柄
					  HINSTANCE hPrevInstance,
					  LPSTR lpCmdLine,
					  int nCmdShow)
{
	DialogBox(hInstance,MAKEINTRESOURCE(IDD_DIALOG1),HWND_DESKTOP,DiglogProc);

	return 1;
}