#include <windows.h>
#include"resource.h"
#include<iostream>

#define _CLIENT_W 640    //客户区的宽
#define _CLIENT_H 480	 //客户区的高

#define _TL 0		//通路
#define _ZA 1		//障碍
#define _HERO 2     //英雄
#define _XZ 3		//箱子
#define _AIM 4      //目标
#define _H_AIM 5	//英雄目标
#define _X_AIM 6    //箱子目标

#define MAP_W 10             //地图的宽
#define MAP_H 10			 //地图的高
#define MAP_S MAP_W*MAP_H    //地图总大小

#define EW 25
#define EH 25

#define _TL_C        RGB(255,255,255)			//通路的颜色
#define _ZA_C 		 RGB(192,192,192)			//障碍的颜色
#define _HERO_C 	 RGB(255,0,0)				//英雄的颜色
#define _XZ_C 		 RGB(0,255,0)				//箱子的颜色
#define _AIM_C 		 RGB(0,0,255)				//目标的颜色
#define _H_AIM_C 	 RGB(138,43,226)			//英雄目标的颜色
#define _X_AIM_C 	 RGB(0,245,255)				//箱子目标的颜色


//当前选择的工具类型
int Current_Mouse;
//自定义地图
char map[MAP_S];
//自定义字符串
const char* c[] ={"通路","障碍","英雄","箱子","目标","英雄目标","箱子目标"};

__w64 long __stdcall WindowProc(HWND hwnd,
								unsigned int uMsg,
								__w64 unsigned int wParam,
								__w64 long lParam)
{
	switch(uMsg)
	{
	case WM_CREATE:
		{
			for(int i=0;i<MAP_S;i++)
			{
				map[i]=_TL;
			}
			Current_Mouse = _TL;
			return 0;
		}
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	case WM_COMMAND:
		{
			if(HIWORD(wParam)==0)
			{
				switch(LOWORD(wParam))
				{
				case ID_40001:
					{
						for(int i=0;i<MAP_S;i++)
						{
							map[i]=_TL;
							InvalidateRect(hwnd,0,TRUE);
						}
						break;
					}
				case ID_40002:
					{
						char buf[MAX_PATH]	= {};
						OPENFILENAME ofn = {};
						ofn.lStructSize = sizeof(ofn);
						ofn.hwndOwner = hwnd;
						ofn.lpstrFile = buf;
						ofn.nMaxFile = MAX_PATH;
						if(IDOK == GetOpenFileName(&ofn))
						{
							FILE* pf = 0;
							fopen_s(&pf,buf,"rb");
							int a;
							fread(&a,1,4,pf);
							if(a!=110)
							{
								MessageBoxA(hwnd,"文件类型非法","提示",MB_OK);
							}else
							{
								for(int i=0;i<MAP_S;i++)
								{
									fread(&map[i],1,1,pf);
								}
								MessageBoxA(hwnd,"打开成功","提示",MB_OK);
								InvalidateRect(hwnd,0,1);
							}
							fclose(pf);
						}
						break;
					}
				case ID_40003:
					{
						int num_yx = 0;
						int num_xiangzi = 0;
						int num_mubiao =0;
						//遍历地图，获取英雄、箱子、与目标的数量
						for(int i=0;i<MAP_S;i++)
						{
							if(map[i]==_HERO||map[i]==_H_AIM)
							{
								num_yx++;
							}
							if(map[i]==_XZ||map[i]==_X_AIM)
							{
								num_xiangzi++;
							}
							if(map[i]==_AIM||map[i]==_H_AIM||map[i]==_X_AIM)
							{
								num_mubiao++;
							}
						}
						//判断关卡是否符合逻辑
						if(num_yx==1&&(num_xiangzi==num_mubiao)&&num_xiangzi!=0)
						{
							char buf[MAX_PATH]	= {};
							OPENFILENAME ofn = {};
							ofn.lStructSize = sizeof(ofn);
							ofn.hwndOwner = hwnd;
							ofn.lpstrFile = buf;
							ofn.nMaxFile = MAX_PATH;
							if(IDOK == GetSaveFileName(&ofn))
							{
								int a =110;
								FILE* pf = 0;
								fopen_s(&pf,buf,"wb");
								fwrite(&a,1,4,pf);
								fwrite(map,1,MAP_S,pf);
								fclose(pf);
								MessageBoxA(hwnd,"保存成功","提示",MB_OK);
							}
						}else
						{
							MessageBoxA(hwnd,"关卡非法,并不能保存","提示",MB_OK);
						}
						break;
					}
				case ID_40004:
					{
						DestroyWindow(hwnd);
						break;
					}
				}
			}
			return 0;
		}
	case WM_LBUTTONDOWN:
		{
			if( LOWORD(lParam)>=100 
				&& LOWORD(lParam)<=100+MAP_W*EW 
				&& HIWORD(lParam)>=100
				&& HIWORD(lParam)<=350+MAP_H*EH )
			{
				int x =  (LOWORD(lParam)-100)/EW;
				int y =  (HIWORD(lParam)-100)/EH;
				map[x+y*MAP_W] = Current_Mouse;
				InvalidateRect(hwnd,0,TRUE);
			}
			if( LOWORD(lParam)>=400 
				&& LOWORD(lParam)<=480 
				&& HIWORD(lParam)>=100
				&& HIWORD(lParam)<=100+7*EH )
			{
				Current_Mouse = (HIWORD(lParam)-100)/EH;
				InvalidateRect(hwnd,0,TRUE);
			}
			return 0;
		}
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd,&ps);
			HBRUSH oldb = (HBRUSH)GetCurrentObject(hdc,OBJ_BRUSH);
			HBRUSH newb ;
			for(int i=0;i<MAP_S;i++)
			{
				switch(map[i])
				{
				case _TL:
					{
						newb = CreateSolidBrush(_TL_C);
						break;
					}
				case _ZA:
					{
						newb = CreateSolidBrush(_ZA_C);
						break;
					}
				case _HERO:
					{
						newb = CreateSolidBrush(_HERO_C);
						break;
					}
				case _XZ:
					{
						newb = CreateSolidBrush(_XZ_C);
						break;
					}
				case _AIM:
					{
						newb = CreateSolidBrush(_AIM_C);
						break;
					}
				case _H_AIM:
					{
						newb = CreateSolidBrush(_H_AIM_C);
						break;
					}
				case _X_AIM:
					{
						newb = CreateSolidBrush(_X_AIM_C);
						break;
					}
				}
				SelectObject(hdc,newb);
				Rectangle(hdc,100+(i%MAP_W)*EW,100+(i/MAP_W)*EH,100+(i%MAP_W)*EW+EW,100+(i/MAP_W)*EH+EH);
				DeleteObject(newb);
			}
			for(int i=0;i<7;i++)
			{
				switch(i)
				{
				case _TL:
					{
						newb = CreateSolidBrush(_TL_C);
						break;
					}
				case _ZA:
					{
						newb = CreateSolidBrush(_ZA_C);
						break;
					}
				case _HERO:
					{
						newb = CreateSolidBrush(_HERO_C);
						break;
					}
				case _XZ:
					{
						newb = CreateSolidBrush(_XZ_C);
						break;
					}
				case _AIM:
					{
						newb = CreateSolidBrush(_AIM_C);
						break;
					}
				case _H_AIM:
					{
						newb = CreateSolidBrush(_H_AIM_C);
						break;
					}
				case _X_AIM:
					{
						newb = CreateSolidBrush(_X_AIM_C);
						break;
					}
				}
				SelectObject(hdc,newb);
				//绘制选择条
				Rectangle(hdc,400,100+i*EH,480,100+i*EH+EH);
				SetBkMode(hdc,TRANSPARENT);

				char buf[256]={0};

				if(Current_Mouse==i)
				{
					strcat_s(buf,256,c[i]);
					strcat_s(buf,256," √");
					TextOutA(hdc,400,100+i*EH,buf,(int)strlen(buf));
				}else
					TextOutA(hdc,400,100+i*EH,c[i],(int)strlen(c[i]));

				DeleteObject(newb);
			}

			SelectObject(hdc,oldb);
			EndPaint(hwnd,&ps);
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
	WNDCLASS wc;
	wc.style = CS_HREDRAW|CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = 0;
	wc.hCursor = 0;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.lpszClassName = "八班";
	RegisterClass(&wc);
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);
	RECT r = 
	{
		(sw - _CLIENT_W)/2,
		(sh - _CLIENT_H)/2,
		(sw - _CLIENT_W)/2 + _CLIENT_W,
		(sh - _CLIENT_H)/2 + _CLIENT_H
	};
	AdjustWindowRect(&r,//设定的客户区的位置，宽高
	WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX ,//窗口风格
	FALSE);//是否有菜单

	//03)用窗口类别结构体来创建窗口
	HWND hWnd = CreateWindow(wc.lpszClassName,//窗口类别结构体的名称，操作系统会根据
		                    //这个名称来的找到注册的窗口，然后使用这个窗口类别的结构体
							 //帮助完成创建窗口的任务
							"推箱子关卡编辑器",//窗口标题栏文字
							 //WS_THICKFRAME 通过鼠标拖动改变窗口大小
							 //WS_MAXIMIZEBOX 窗口右上角的最大化和还原按钮
							 WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,//窗口风格
							 r.left,//窗口的左上角x坐标
							 r.top,//窗口的左上角y坐标
							 r.right - r.left,//窗口的宽（像素）
							 r.bottom - r.top,//窗口的高（像素）
							 HWND_DESKTOP,//父窗口窗口句柄,HWND_DESKTOP表示桌面
							 0,//窗口菜单句柄，不使用菜单填0
							 wc.hInstance,//应用程序实例句柄
							 0);//任意地址，该地址可以通过WM_CREATE消息得到，不使用设置为0


	//04)显示窗口
	ShowWindow(hWnd,nCmdShow);

	//05)更新窗口
	UpdateWindow(hWnd);

	

	MSG msg;
	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 1;
}

