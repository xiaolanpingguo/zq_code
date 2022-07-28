#ifndef _FIND_PATH_H_
#define _FIND_PATH_H_

#include <vector>

//约定
//1）地图为char类型的数组
//2）凡是<=0的数组元素都认为是障碍，>0的数组元素都认为是通路
//3）如果要希望寻路函数可以适应所有的地图，那么可以采取模板函数
	//template <typename T>
	//bool FindPathW(const T* map, //地图首地址
	//			   int w, //地图宽
	//			   int h, //地图高
	//			   int b, //起始点下标
	//			   int e, //终止点下标
	//			   bool (* is_block)(const T* grid), //用来判断指定位置是否是障碍的函数指针
	//			   std::vector<int>* path); //得到的路
//4）寻路函数返回真表示找到了路，路径放在path中，如果返回假就没
//   有找到路

//广度优先寻路
//1）类似地毯式搜索，能够走的地方全部走，找到路之后就返回
//2）能够找到的是最短路径，但是效率损耗较大
bool FindPathW(const char* map, //地图首地址
			   int w, //地图宽
			   int h, //地图高
			   int b, //起始点下标
			   int e, //终止点下标
			   std::vector<int>* path); //得到的路

//深度优先寻路
//1）一条路走到底，走不下去了就倒回来（回溯）
//2）如果有路一定可以找到，但是找到的路不一定是最短
//   路径，路径是和我们的寻路方向的顺序有关系，效率
//   一般来说优于广度优先
bool FindPathD(const char* map, //地图首地址
			   int w, //地图宽
			   int h, //地图高
			   int b, //起始点下标
			   int e, //终止点下标
			   std::vector<int>* path); //得到的路

//A星寻路
//1）优化了的广度优先寻路
//2）找到的是最短路径
//3）可以用最大堆进行优化
bool FindPathA(const char* map, //地图首地址
			   int w, //地图宽
			   int h, //地图高
			   int b, //起始点下标
			   int e, //终止点下标
			   std::vector<int>* path); //得到的路

#endif