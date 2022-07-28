#ifndef _FIND_PATH_W_H_
#define _FIND_PATH_W_H_

#include <vector>

//地图是char类型
//障碍：小于等于0的地图块
//通路：大于0的地图块

//广度优先寻路的特点
//1）找到的是最短路径
//2）效率不高

bool FindPathW(const char* map, //地图
			   int width, //地图宽
			   int height, //地图高
			   int start, //起始点
			   int end, //终止点
			   std::vector<int>* path); //得到的路

#endif