#ifndef _GAME_H_
#define _GAME_H_

void Init();
void Run();
void End();

#endif

void capture_screen(const char* fn);

//DirectX是微软推出的专门针对多媒体、视屏游戏等进行开发的
//编程工具（h、lib、dll），所谓Direct，它本身的英文含义是
//“直接”、“路径”等意思，此处的意思就是“直接”和硬件的
//驱动程序进行交互，以提高程序的运行效率，而DirectX中最重
//要的组件是和视频有关的组件DirectGraphics，这个组件又分为
//DirectDraw和Direct3D，其中DirectDraw是进行二维绘制的组件
//，而Direct3D是进行三维绘制的组件，下面图示使用GDI和Direct
//Graphics的区别：
//程序A使用GDI <---> Windows <---> 硬件驱动 <---> 适配器
//程序A使用DirectGraphics <---> 硬件驱动 <---> 适配器
//随着计算机硬件的发展，GDI和DirectDraw的效率区别慢慢没有最
//早先那么大了，早期的DirectDraw的效率普遍比GDI快上几倍，那
//个时候（98~05）二维游戏的开发99%都会采用DirectDraw来开发，
//但是现在来说，很多画面简单的二维游戏（比如愤怒的小鸟等）就
//是GDI来完成游戏的画面绘制而没有使用DirectDraw，只要安装了
//VS2005，那么可以通过工具Depends来查看一个exe或dll运行时候
//所需要的dll，Depends在C:\Program Files\Microsoft Visual Studio 8\Common7\Tools\Bin\Depends
//使用DirectDraw来进行画面的绘制非常类似直接读写显存，使用
//DirectDraw搭建的环境就非常适合进行三维图形学的学习
//DirectX总共有如下一些组件
//1）Direct Graphics
//  {
//		DirectDraw：二维绘制
//		Direct3D：三维绘制
//  }
//2）Direct Audio
//	{
//		DirectMusic：高阶音频，主要用于进行音乐、音效的播放
//		DirectSound：低阶音频，主要用于采集音频样本、三维音效实现
//	}
//3）Direct Input：对输入功能的支持，除了支持常规的鼠标、键盘，还支持其它的输入设备（手柄、摇杆、跳舞毯）
//4）Direct Play：网络连接的支持，最大只支持64个客户端的连接，所以真正的网络游戏一般都使用socket
//5）Direct Show：流媒体的处理