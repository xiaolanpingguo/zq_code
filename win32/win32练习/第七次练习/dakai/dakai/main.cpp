#include <windows.h>
#include"resource.h"
#include<iostream>
#include<vector>

struct ch
{
	char buf[MAX_PATH];
};

std::vector<ch> g_vCh;

int flag =0;

INT_PTR __stdcall f(HWND hwndDlg,
					UINT uMsg,
					WPARAM wParam,
					LPARAM lParam)
{
	switch(uMsg)
	{
	/*case WM_CLOSE:
		{
			EndDialog(hwndDlg,100);
		}*/
	case WM_INITDIALOG:
		{
			if(flag ==1)
			{
				HWND hwnd = GetDlgItem(hwndDlg,IDC_EDIT1);
				if(g_vCh.size()>0)
				{
					std::vector<ch>::iterator i = g_vCh.begin();
					int size = 128;
					char* p = new char[size];
					p[0] = 0;
					int len =0;
					for(;i!=g_vCh.end();i++)
					{
						if(len+(int)(sizeof(i->buf))+3>size)
						{
							size*=2;
							char* q = new char[size];
							strcpy_s(q,len+1,p);
							delete []p;
							p = q;
						}
						strcat_s(p,size,i->buf);
						strcat_s(p,size,"\r\n");
						len= len + sizeof(i->buf)+2;
					}
					
					SetWindowText(hwnd,p);
					delete []p;
				}
				
			}
			return 1;
		}
	case WM_COMMAND:
		{
			if(HIWORD(wParam)==BN_CLICKED)
			{
				if(LOWORD(wParam)==IDC_BUTTON1)
				{
					char buf[MAX_PATH]={};
					OPENFILENAME ofn = {};
					ofn.lStructSize = sizeof(ofn);
					ofn.hwndOwner = hwndDlg;
					ofn.lpstrFile = buf;
					ofn.nMaxFile = MAX_PATH;

					//打开保存文件对话框
					//如果选择确定，则对OPENFILENAME对象的某些项进行了设置
					//if(IDOK == GetSaveFileName(&ofn))
					//{
					//	SetWindowText(hwnd,buf);
					//}
					//打开文件打开对话框
					if(IDOK == GetOpenFileName(&ofn))
					{
						ch lch;
						strcpy_s(lch.buf,MAX_PATH,buf);
						g_vCh.push_back(lch);
					}
					return 1;
				}else
				if(LOWORD(wParam)==IDC_BUTTON2)
				{
					flag =1;
					INT_PTR r =DialogBox(GetModuleHandle(0),
						 MAKEINTRESOURCE(IDD_DIALOG2),
						 hwndDlg,
						 f);
					if(r==100)
					{
						MessageBoxA(hwndDlg,"按确定退出","提示",MB_OK);
					}else
					if(r==101)
					{
						MessageBoxA(hwndDlg,"按取消退出","提示",MB_OK);
					}
					return 1;
				}else
				if(LOWORD(wParam)==IDOK)
				{
					EndDialog(hwndDlg,100);
				}else
				if(LOWORD(wParam)==IDCANCEL)
				{
					EndDialog(hwndDlg,101);
				}else
				if(LOWORD(wParam)==IDC_BUTTON3)
				{
					g_vCh.clear();
					MessageBoxA(hwndDlg,"清空完毕","提示",MB_OK);
				}
			}
			return 1;
		}
	}
	return 0;
}



int __stdcall WinMain(HINSTANCE hInstance,//应用程序实例句柄
					  HINSTANCE hPrevInstance,
					  LPSTR lpCmdLine,
					  int nCmdShow)
{
	
	
	INT_PTR r =DialogBox(hInstance,
						 MAKEINTRESOURCE(IDD_DIALOG1),
						 HWND_DESKTOP,
						 f);
	

	return 1;
}