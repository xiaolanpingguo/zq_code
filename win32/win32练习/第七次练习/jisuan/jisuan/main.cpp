#include <windows.h>
#include"resource.h"
#include<iostream>

#define _INIT 0
#define _CHOSEF 1
#define _CHOSEN 2

#define _UNSIGN 2
#define _ADD 3
#define _SUB 4
#define _MUL 5
#define _DIV 6

int sum=0;
int flag =_INIT;
int fuhao =_UNSIGN;
int ls;
char buf[256];



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
			HWND hwnd =GetDlgItem(hwndDlg,IDC_BUTTON4);
			EnableWindow(hwnd,FALSE);
			HWND hwnd1 =GetDlgItem(hwndDlg,IDC_BUTTON8);
			EnableWindow(hwnd1,FALSE);
			HWND hwnd2 =GetDlgItem(hwndDlg,IDC_BUTTON12);
			EnableWindow(hwnd2,FALSE);
			HWND hwnd3 =GetDlgItem(hwndDlg,IDC_BUTTON9);
			EnableWindow(hwnd3,FALSE);
			return 1;
		}
	case WM_COMMAND:
		{
			flag++;
			if(HIWORD(wParam)==BN_CLICKED)
			{
				if(LOWORD(wParam)==IDC_BUTTON11)
				{
					sum=0;
					flag=_INIT;
					fuhao=_UNSIGN;
					ls=0;
					HWND hwndd = GetDlgItem(hwndDlg,IDC_EDIT1);
					buf[0]=0;
					SetWindowTextA(hwndd,buf);
					HWND hwnd =GetDlgItem(hwndDlg,IDC_BUTTON4);
					EnableWindow(hwnd,FALSE);
					HWND hwnd1 =GetDlgItem(hwndDlg,IDC_BUTTON8);
					EnableWindow(hwnd1,FALSE);
					HWND hwnd2 =GetDlgItem(hwndDlg,IDC_BUTTON12);
					EnableWindow(hwnd2,FALSE);
					HWND hwnd3 =GetDlgItem(hwndDlg,IDC_BUTTON9);
					EnableWindow(hwnd3,FALSE);


					HWND hwnd4 =GetDlgItem(hwndDlg,IDC_BUTTON1);
					EnableWindow(hwnd4,TRUE);
					HWND hwnd5 =GetDlgItem(hwndDlg,IDC_BUTTON2);
					EnableWindow(hwnd5,TRUE);
					HWND hwnd6 =GetDlgItem(hwndDlg,IDC_BUTTON3);
					EnableWindow(hwnd6,TRUE);
					HWND hwnd7 =GetDlgItem(hwndDlg,IDC_BUTTON5);
					EnableWindow(hwnd7,TRUE);
					HWND hwnd8 =GetDlgItem(hwndDlg,IDC_BUTTON6);
					EnableWindow(hwnd8,TRUE);
					HWND hwnd9 =GetDlgItem(hwndDlg,IDC_BUTTON7);
					EnableWindow(hwnd9,TRUE);
					HWND hwnd10 =GetDlgItem(hwndDlg,IDC_BUTTON10);
					EnableWindow(hwnd10,TRUE);
					HWND hwnd11 =GetDlgItem(hwndDlg,IDC_BUTTON13);
					EnableWindow(hwnd11,TRUE);
					HWND hwnd12 =GetDlgItem(hwndDlg,IDC_BUTTON14);
					EnableWindow(hwnd12,TRUE);
					HWND hwnd13 =GetDlgItem(hwndDlg,IDC_BUTTON15);
					EnableWindow(hwnd13,TRUE);
					return 1;
				}
				if(flag%2==0)
				{
					HWND hwnd =GetDlgItem(hwndDlg,IDC_BUTTON4);
					EnableWindow(hwnd,FALSE);
					HWND hwnd1 =GetDlgItem(hwndDlg,IDC_BUTTON8);
					EnableWindow(hwnd1,FALSE);
					HWND hwnd2 =GetDlgItem(hwndDlg,IDC_BUTTON12);
					EnableWindow(hwnd2,FALSE);
					HWND hwnd3 =GetDlgItem(hwndDlg,IDC_BUTTON9);
					EnableWindow(hwnd3,FALSE);


					HWND hwnd4 =GetDlgItem(hwndDlg,IDC_BUTTON1);
					EnableWindow(hwnd4,TRUE);
					HWND hwnd5 =GetDlgItem(hwndDlg,IDC_BUTTON2);
					EnableWindow(hwnd5,TRUE);
					HWND hwnd6 =GetDlgItem(hwndDlg,IDC_BUTTON3);
					EnableWindow(hwnd6,TRUE);
					HWND hwnd7 =GetDlgItem(hwndDlg,IDC_BUTTON5);
					EnableWindow(hwnd7,TRUE);
					HWND hwnd8 =GetDlgItem(hwndDlg,IDC_BUTTON6);
					EnableWindow(hwnd8,TRUE);
					HWND hwnd9 =GetDlgItem(hwndDlg,IDC_BUTTON7);
					EnableWindow(hwnd9,TRUE);
					HWND hwnd10 =GetDlgItem(hwndDlg,IDC_BUTTON10);
					EnableWindow(hwnd10,TRUE);
					HWND hwnd11 =GetDlgItem(hwndDlg,IDC_BUTTON13);
					EnableWindow(hwnd11,TRUE);
					HWND hwnd12 =GetDlgItem(hwndDlg,IDC_BUTTON14);
					EnableWindow(hwnd12,TRUE);
					HWND hwnd13 =GetDlgItem(hwndDlg,IDC_BUTTON15);
					EnableWindow(hwnd13,TRUE);

				}else
				{
					HWND hwnd =GetDlgItem(hwndDlg,IDC_BUTTON4);
					EnableWindow(hwnd,TRUE);
					HWND hwnd1 =GetDlgItem(hwndDlg,IDC_BUTTON8);
					EnableWindow(hwnd1,TRUE);
					HWND hwnd2 =GetDlgItem(hwndDlg,IDC_BUTTON12);
					EnableWindow(hwnd2,TRUE);
					HWND hwnd3 =GetDlgItem(hwndDlg,IDC_BUTTON9);
					EnableWindow(hwnd3,TRUE);

					HWND hwnd4 =GetDlgItem(hwndDlg,IDC_BUTTON1);
					EnableWindow(hwnd4,FALSE);
					HWND hwnd5 =GetDlgItem(hwndDlg,IDC_BUTTON2);
					EnableWindow(hwnd5,FALSE);
					HWND hwnd6 =GetDlgItem(hwndDlg,IDC_BUTTON3);
					EnableWindow(hwnd6,FALSE);
					HWND hwnd7 =GetDlgItem(hwndDlg,IDC_BUTTON5);
					EnableWindow(hwnd7,FALSE);
					HWND hwnd8 =GetDlgItem(hwndDlg,IDC_BUTTON6);
					EnableWindow(hwnd8,FALSE);
					HWND hwnd9 =GetDlgItem(hwndDlg,IDC_BUTTON7);
					EnableWindow(hwnd9,FALSE);
					HWND hwnd10 =GetDlgItem(hwndDlg,IDC_BUTTON10);
					EnableWindow(hwnd10,FALSE);
					HWND hwnd11 =GetDlgItem(hwndDlg,IDC_BUTTON13);
					EnableWindow(hwnd11,FALSE);
					HWND hwnd12 =GetDlgItem(hwndDlg,IDC_BUTTON14);
					EnableWindow(hwnd12,FALSE);
					HWND hwnd13 =GetDlgItem(hwndDlg,IDC_BUTTON15);
					EnableWindow(hwnd13,FALSE);
				}
				if(LOWORD(wParam)==IDOK||LOWORD(wParam)==IDCANCEL)
				{
					EndDialog(hwndDlg,100);
					return 1;
				}
				if(fuhao==_UNSIGN)
				{
					switch(LOWORD(wParam))
					{
					case IDC_BUTTON2:
						{
							sum=7;
							HWND hwnd = GetDlgItem(hwndDlg,IDC_EDIT1);
							sprintf_s(buf,256,"%d",sum);
							SetWindowTextA(hwnd,buf);
							return 1;
						}
					case IDC_BUTTON1:
						{
							sum=8;
							HWND hwnd = GetDlgItem(hwndDlg,IDC_EDIT1);
							sprintf_s(buf,256,"%d",sum);
							SetWindowTextA(hwnd,buf);
							return 1;
						}
					case IDC_BUTTON3:
						{
							sum=9;
							HWND hwnd = GetDlgItem(hwndDlg,IDC_EDIT1);
							sprintf_s(buf,256,"%d",sum);
							SetWindowTextA(hwnd,buf);
							return 1;
						}
					case IDC_BUTTON5:
						{
							sum=4;
							HWND hwnd = GetDlgItem(hwndDlg,IDC_EDIT1);
							sprintf_s(buf,256,"%d",sum);
							SetWindowTextA(hwnd,buf);
							return 1;
						}
					case IDC_BUTTON6:
						{
							sum=5;
							HWND hwnd = GetDlgItem(hwndDlg,IDC_EDIT1);
							sprintf_s(buf,256,"%d",sum);
							SetWindowTextA(hwnd,buf);
							return 1;
						}
					case IDC_BUTTON7:
						{
							sum=6;
							HWND hwnd = GetDlgItem(hwndDlg,IDC_EDIT1);
							sprintf_s(buf,256,"%d",sum);
							SetWindowTextA(hwnd,buf);
							return 1;
						}
					case IDC_BUTTON13:
						{
							sum=1;
							HWND hwnd = GetDlgItem(hwndDlg,IDC_EDIT1);
							sprintf_s(buf,256,"%d",sum);
							SetWindowTextA(hwnd,buf);
							return 1;
						}
					case IDC_BUTTON15:
						{
							sum=2;
							HWND hwnd = GetDlgItem(hwndDlg,IDC_EDIT1);
							sprintf_s(buf,256,"%d",sum);
							SetWindowTextA(hwnd,buf);
							return 1;
						}
					case IDC_BUTTON14:
						{
							sum=3;
							HWND hwnd = GetDlgItem(hwndDlg,IDC_EDIT1);
							sprintf_s(buf,256,"%d",sum);
							SetWindowTextA(hwnd,buf);
							return 1;
						}
					case IDC_BUTTON10:
						{
							sum=0;
							HWND hwnd = GetDlgItem(hwndDlg,IDC_EDIT1);
							sprintf_s(buf,256,"%d",sum);
							SetWindowTextA(hwnd,buf);
							return 1;
						}
					case IDC_BUTTON4:
						{
							fuhao = _ADD;
							return 1;
						}
					case IDC_BUTTON8:
						{
							fuhao = _SUB;
							return 1;
						}
					case IDC_BUTTON12:
						{
							fuhao = _MUL;
							return 1;
						}
					case IDC_BUTTON9:
						{
							fuhao = _DIV;
							return 1;
						}
					}
				
				}else
				{
					switch(LOWORD(wParam))
					{
						case IDC_BUTTON2:
							{
								ls=7;
								break;
							}
						case IDC_BUTTON1:
							{
								ls=8;
								break;
							}
						case IDC_BUTTON3:
							{
								ls=9;
								break;
							}
						case IDC_BUTTON5:
							{
								ls=4;
								break;
							}
						case IDC_BUTTON6:
							{
								ls=5;
								break;
							}
						case IDC_BUTTON7:
							{
								ls=6;
								break;
							}
						case IDC_BUTTON13:
							{
								ls=1;
								break;
							}
						case IDC_BUTTON15:
							{
								ls=2;
								break;
							}
						case IDC_BUTTON14:
							{
								ls=3;
								break;
							}
						case IDC_BUTTON10:
							{
								ls=0;
								break;
							}
						case IDC_BUTTON4:
						{
							fuhao = _ADD;
							return 1;
						}
						case IDC_BUTTON8:
						{
							fuhao = _SUB;
							return 1;
						}
						case IDC_BUTTON12:
						{
							fuhao = _MUL;
							return 1;
						}
						case IDC_BUTTON9:
						{
							fuhao = _DIV;
							return 1;
						}
					}
					switch(fuhao)
					{
					case _ADD:
						{
							sum+=ls;
							HWND hwnd = GetDlgItem(hwndDlg,IDC_EDIT1);
							sprintf_s(buf,256,"%d",sum);
							SetWindowTextA(hwnd,buf);
							ls=0;
							return 1;
						}
					case _SUB:
						{
							sum-=ls;
							HWND hwnd = GetDlgItem(hwndDlg,IDC_EDIT1);
							sprintf_s(buf,256,"%d",sum);
							SetWindowTextA(hwnd,buf);
							ls=0;
							return 1;
						}
					case _MUL:
						{
							sum*=ls;
							HWND hwnd = GetDlgItem(hwndDlg,IDC_EDIT1);
							sprintf_s(buf,256,"%d",sum);
							SetWindowTextA(hwnd,buf);
							ls=0;
							return 1;
						}
					case _DIV:
						{
							sum/=ls;
							HWND hwnd = GetDlgItem(hwndDlg,IDC_EDIT1);
							sprintf_s(buf,256,"%d",sum);
							SetWindowTextA(hwnd,buf);
							ls=0;
							return 1;
						}
					}
				}
				
			return 1;
			}
		}
	}
	return 0;
}

//__w64 long __stdcall WindowProc(HWND hwnd,unsigned int uMsg,__w64 unsigned int wParam,__w64 
//
//long lParam)
//{
//	switch(uMsg)
//	{
//	case WM_DESTROY:
//		{
//			PostQuitMessage(0);
//			return 0;
//		}
//	
//	
//	case WM_PAINT:
//		{
//			PAINTSTRUCT ps;
//			HDC hdc =BeginPaint(hwnd,&ps);
//			
//			
//			EndPaint(hwnd,&ps);
//			return 0;
//		}
//	case WM_COMMAND:
//		{
//			
//			return 0;
//		}
//	}
//	return DefWindowProc(hwnd,uMsg,wParam,lParam);
//}

int __stdcall WinMain(HINSTANCE hInstance,//Ó¦ÓÃ³ÌÐòÊµÀý¾ä±ú
					  HINSTANCE hPrevInstance,
					  LPSTR lpCmdLine,
					  int nCmdShow)
{
	/*WNDCLASS wc;
	wc.style = CS_HREDRAW|CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon =LoadIcon(0,IDI_APPLICATION);
	wc.hCursor =LoadCursor(0,IDC_ARROW);
	wc.hbrBackground=(HBRUSH)COLOR_WINDOW;
	wc.lpszMenuName = 0;
	wc.lpszClassName =L"°Ë°à";
	RegisterClass(&wc);
	HWND hWnd = CreateWindow(wc.lpszClassName,
							L"¼ÆËãÆ÷",
							WS_OVERLAPPEDWINDOW,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							816,
							458,
							HWND_DESKTOP,
							0,
							wc.hInstance,
							0);
	*/
	
	/*ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);*/
	
	
	INT_PTR r =DialogBox(hInstance,
						 MAKEINTRESOURCE(IDD_DIALOG1),
						 HWND_DESKTOP,
						 f);
	

	/*MSG msg;
	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}*/
	return 1;
}