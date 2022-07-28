#include <iostream>
#include <windows.h>
#include <conio.h>

////当前场景标示
//int cur_scene = 0;
//
////设置当前场景标示
//void set_cur_scene(int index)
//{
//	cur_scene = index;
//}

void set_cur_scene(int index);

//具体的场景代码
void scene1()
{
	std::cout<<"场景1"<<std::endl;
	if (GetAsyncKeyState(VK_SPACE) & 1)
		set_cur_scene(1);
}
void scene2()
{
	std::cout<<"场景2"<<std::endl;
	if (GetAsyncKeyState(VK_SPACE) & 1)
		set_cur_scene(2);
}
void scene3()
{
	std::cout<<"场景3"<<std::endl;
	if (GetAsyncKeyState(VK_SPACE) & 1)
		set_cur_scene(0);
}

//void main()
//{
//	//设置初始场景为1号场景
//	set_cur_scene(1);
//	while (1)
//	{
//		system("cls");
//		switch (cur_scene)
//		{
//		case 1: scene1(); break;
//		case 2: scene2(); break;
//		case 3: scene3(); break;
//		//如果还要添加新的场景，就必须在这个地方添加类似上面的语句
//		//case 4:	...
//		//case 5:	...
//		}
//		Sleep(33);
//	}
//
//	system("pause");
//}

//装载场景函数的函数指针数组
void (* all_scene[8])() = {};

//函数指针数组的长度
int scene_length = 0;

//当前场景函数下标
int cur_scene = -1;

//本情况下我们用了数组来装载场景，也就是说对
//场景函数做了统一的管理，所以应该添加相应的
//管理函数
bool add_scene(void (* scene)())
{
	if (scene_length == 8)
		return false;
	else
	{
		all_scene[scene_length++] = scene;
		return true;
	}
}

//设置当前场景下标
void set_cur_scene(int index)
{
	cur_scene = index;
}

void main()
{
	add_scene(scene1);
	add_scene(scene2);
	add_scene(scene3);

	//设置初始场景为0号场景
	set_cur_scene(0);

	while (1)
	{
		//无论有多少场景，本循环代码无需修改
		system("cls");
		if (cur_scene != -1)
			(*all_scene[cur_scene])();
		Sleep(33);
	}

	system("pause");
}