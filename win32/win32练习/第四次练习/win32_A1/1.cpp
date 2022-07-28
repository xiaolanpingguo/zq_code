#include <windows.h>
#include<time.h>
#include<vector>

#define _BUTTON1 0
#define _BUTTON2 1

HWND g_hWnd[3];
RECT rButton1;
RECT rButton2;
RECT r1;

std::vector<RECT> g_vRect;
std::vector<int> g_vInt;



__w64 long __stdcall WindowProc(HWND hwnd,unsigned int uMsg,__w64 unsigned int wParam,__w64 long lParam)
{
	switch(uMsg)
	{
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	case WM_KEYDOWN:
		{
			srand((unsigned int)time(0));
			if(wParam=='j'||wParam=='J')
			{
				SendMessage(g_hWnd[1],BM_CLICK,0,0);
			}
			if(wParam=='y'||wParam=='Y')
			{
				SendMessage(g_hWnd[2],BM_CLICK,0,0);
			}
			return 0;
		}
	
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc =BeginPaint(hwnd,&ps);
			std::vector<int>::iterator intit =g_vInt.begin();
			for(std::vector<RECT>::iterator iter = g_vRect.begin();iter!=g_vRect.end();/*flag++,*/intit++,iter++)
			{
				if(*intit==1)
				{
					Rectangle(hdc,iter->left,iter->top,iter->right,iter->bottom);
				}else
				{
					Ellipse(hdc,iter->left,iter->top,iter->right,iter->bottom);
				}
			}
			
			EndPaint(hwnd,&ps);
			return 0;
		}
	case WM_TIMER:
		{
			
			return 0;
		}
	case WM_COMMAND:
		{
			if(BN_CLICKED == HIWORD(wParam))
			{
				if(LOWORD(wParam) == _BUTTON1)
				{
					int flag;
					RECT r;
					GetClientRect(g_hWnd[0],&r);
					r1;
					r1.left = rand()%(r.right+1);
					r1.top = rand()%(r.bottom+1);
					r1.right = rand()%(r.right-r1.left)+r1.left+1;
					r1.bottom =rand()%(r.bottom-r1.top)+r1.top+1;
					g_vRect.push_back(r1);
					flag = 1;
					g_vInt.push_back(flag);
					
					InvalidateRect(hwnd,0,TRUE);	
				}
				if(LOWORD(wParam) == _BUTTON2)
				{
					int flag;
					RECT r;
					GetClientRect(g_hWnd[0],&r);
					r1;
					r1.left = rand()%(r.right+1);
					r1.top = rand()%(r.bottom+1);
					r1.right = rand()%(r.right-r1.left)+r1.left+1;
					r1.bottom =rand()%(r.bottom-r1.top)+r1.top+1;
					g_vRect.push_back(r1);
					flag = 2;
					g_vInt.push_back(flag);
					InvalidateRect(hwnd,0,TRUE);	
				}

			}
			return 0;
		}
	case WM_LBUTTONDOWN:
		{
			srand((unsigned int)time(0));
			POINT p = {LOWORD(lParam),HIWORD(lParam)};
			if(PtInRect(&rButton1,p))
				SendMessage(g_hWnd[1],BM_CLICK,0,0);
			if(PtInRect(&rButton2,p))
				SendMessage(g_hWnd[2],BM_CLICK,0,0);
			return 0;
		}
	}
	return DefWindowProc(hwnd,uMsg,wParam,lParam);
}

int __stdcall WinMain(HINSTANCE hInstance,//Ó¦ÓÃ³ÌÐòÊµÀý¾ä±ú
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
	wc.hIcon =LoadIcon(0,IDI_APPLICATION);
	wc.hCursor =LoadCursor(0,IDC_ARROW);
	wc.hbrBackground=(HBRUSH)COLOR_WINDOW;
	wc.lpszMenuName =0;
	wc.lpszClassName =L"°Ë°à";
	RegisterClass(&wc);
	g_hWnd[0] = CreateWindow(wc.lpszClassName,
							L"»æÖÆÏß¶Î",
							WS_OVERLAPPEDWINDOW,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							HWND_DESKTOP,
							0,
							wc.hInstance,
							0);

	g_hWnd[1] = CreateWindow(L"button",
							L"¾ØÐÎ(J¼ü)",
							WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,
							0,
							0,
							60,
							25,
							g_hWnd[0],
							(HMENU)_BUTTON1,
							wc.hInstance,
							0);
	rButton1.left = 0 ;
	rButton1.top = 0;
	rButton1.right = rButton1.left + 60;
	rButton1.bottom = rButton1.top + 25;
	g_hWnd[2] = CreateWindow(L"button",
							L"ÍÖÔ²(Y¼ü)",
							WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,
							0,
							50,
							60,
							25,
							g_hWnd[0],
							(HMENU)_BUTTON2,
							wc.hInstance,
							0);
	rButton2.left = 0 ;
	rButton2.top = 50;
	rButton2.right = rButton2.left + 60;
	rButton2.bottom = rButton2.top + 25;
	
	ShowWindow(g_hWnd[0],nCmdShow);
	UpdateWindow(g_hWnd[0]);
	
	

	MSG msg;
	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 1;
}