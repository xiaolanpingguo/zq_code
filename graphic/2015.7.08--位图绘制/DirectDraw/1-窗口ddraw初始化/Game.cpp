#include "Game.h"
#include "Main.h"

#include "ddraw.h"
#pragma comment(lib, "ddraw.lib")
#pragma comment(lib, "dxguid.lib")

LPDIRECTDRAW7 dd; //ddraw对象


void Init()
{
	//1)创建ddraw
	//注意IID_IDirectDraw7是一个全局变量，它的声明在ddraw
	//中,定义在dxguid中，填写它表示要求创建7.0版本的ddraw,
	//所谓ID就是一个128位的数组，DirectX中的各种组件都有一
	//个自己的ID作为唯一标示，我们可以通过这些ID来明确指出
	//创建哪种DirectX的组件对象
	if (DD_OK != DirectDrawCreateEx(0, (void**)&dd, IID_IDirectDraw7, 0))
		return;

	//2)设置本程序和操作系统的协调方式，因为DirectX组件都是
	//  可以直接和硬件的驱动程序打交道的，而在Windows操作系
	//  统下面，本身所有的硬件的驱动都是Windows来管理的，所
	//  以我们要用ddraw，就必须和Windows协商好双方如何协调
	//  工作，主要分窗口模式、全屏模式两种，如果是窗口模式的
	//  DirectDraw程序，则参数2填写DDSCL_NORMAL即可
	if (DD_OK != dd->SetCooperativeLevel(g_hWnd, DDSCL_NORMAL))
		return;

	//3)通过ddraw得到桌面大小
	DDSURFACEDESC2 ddsd = {};
	ddsd.dwSize = sizeof(ddsd);
	dd->GetDisplayMode(&ddsd);

	//4)设置显卡当前的工作模式，前两个参数是当前的屏幕宽
	//  、高，如果是窗口程序那么一般是不修改屏幕的宽高的
	//  ，然后是色彩格式，色彩格式可以是1、2、4、8、16、
	//  24、32这些数字，它们代表了像素的不同的颜色表示方
	//  法即一个像素用多少位来表示，当然数字越大颜色就越
	//  丰富，不同位深的概念如下
	//1:用1个位来表示颜色，只能表示黑白两种色彩
	//2:用2个位来表示颜色，可以表示白、浅灰、深灰、黑四种色彩
	//4:用4个位来表示颜色，可以表示十六种颜色，典型的这种色彩
	//的运用就是8位机（任天堂）
	//8:含有一个长度为256的色彩表，然后用1个字节做色彩表的索引
	//来完成的颜色表示，典型的这种色彩的运用就是16位机（超级任
	//天堂、世嘉），早期的PC游戏中8位色也运用地非常地多，比如星
	//际争霸1代
	//16:也称增强色，是用2个字节来表示像素颜色的，格式一般为
	//RRRRRGGG GGGBBBBB，这种称之为565表示法，因为人眼对绿色的
	//分辨能力是最强的，所以绿色要比红色、蓝色多一个位
	//24:也称真彩色，是用3个字节来表示像素颜色的，格式一般为
	//RRRRRRRR GGGGGGGG BBBBBBBB，目前最常用的颜色格式
	//32:在24位色的基础上增加了一个字节，这个字节主要是用来对齐
	//的，也就是用4字节表示一像素，以加快某些运算，有些时候也用
	//这多出的一个字节来存储Alpha透明度值
	//第4个参数是刷新率，如果是窗口程序则填写0即可，表示我们使用
	//当前显示器的刷新率，如果是全屏程序则填写我们希望的、显卡支
	//持的任何刷新率（液晶一般是60），最后一个参数是标志，我们暂
	//时填写0即可
	dd->SetDisplayMode(ddsd.dwWidth, ddsd.dwHeight, 8, 0, 0);
}

void Run()
{
	
}

void End()
{
	if (dd)
		dd->Release();
}