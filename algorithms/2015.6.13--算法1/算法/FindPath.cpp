#include "FindPath.h"

bool FindPathW(const char* map, //地图首地址
			   int w, //地图宽
			   int h, //地图高
			   int b, //起始点下标
			   int e, //终止点下标
			   std::vector<int>* path) //得到的路
{
	//参数判断
	if (!map ||
		w < 1 ||
		h < 1 ||
		b < 0 || b >= w * h ||
		e < 0 || e >= w * h ||
		!path)
		return false;

	//清空路
	path->clear();

	//若起始点就是终止点
	if (b == e)
	{
		//装入起始点
		path->push_back(b);
		return true;
	}

	//辅助数组
	std::vector<int> help1, help2;

	//起始点入数组
	help1.push_back(b);
	help2.push_back(-1);

	//初始化要发散的格子在数组1中的下标
	int i1 = 0, i2 = 0;

	//4个方向的偏移量
	int offsetx[] = {0,0,-1,1};
	int offsety[] = {-1,1,0,0};

	//寻路循环
	while (1)
	{
		//记录发散前的辅助数组长度
		int len = (int)help1.size();

		//发散
		for (int i = i1; i <= i2; ++i)
		{
			//得到当前点下标和坐标
			int ci = help1[i];
			int cx = ci % w;
			int cy = ci / w;
			
			//根据当前点坐标发散4个方向的坐标和下标
			for (int j = 0; j < 4; ++j)
			{
				int dx = cx + offsetx[j];
				int dy = cy + offsety[j];
				int di = dx + dy * w;

				//不能越界
				if (dx >= 0 && dx < w && dy >= 0 && dy < h)
				{
					//找到了路
					if (di == e)
					{
						//还原路径到path

						//将终止点放入表中
						help1.push_back(e);
						help2.push_back(i);

						//得到当前应该放入path的路径在
						//help1数组中的下标
						int index = (int)help1.size() - 1;

						//还原路径
						while (index != -1)
						{
							path->push_back(help1[index]);
							index = help2[index];
						}

						return true;
					}

					//不能是障碍
					if (map[di] > 0)
					{
						//没有走过
						bool go = false;
						for (int k = 0; k < (int)help1.size(); ++k)
						{
							if (di == help1[k])
							{
								go = true;
								break;
							}
						}
						if (!go)
						{
							//放入辅助表中
							help1.push_back(di);
							help2.push_back(i);
						}
					}
				}
			}
		}

		//本次没有发散
		if (len == (int)help1.size())
			break;
		//本次发散了
		else
		{
			//更新发散的范围下标
			i1 = len;
			i2 = (int)help1.size() - 1;
		}
	}

	return false;
}

bool _FindPathD(const char* map,
				int w,
				int h,
				int e,
				std::vector<int>* help,
				std::vector<int>* path)
{
	//判断是否是终止点，如果是终止
	//点就返回真表示找到路了
	if (e == path->back())
		return true;

	//4个方向的偏移量
	int offsetx[] = {0,0,-1,1};
	int offsety[] = {-1,1,0,0};

	//得到当前点的坐标
	int ci = path->back();
	int cx = ci % w;
	int cy = ci / w;

	//发散4个方向进行寻路
	for (int i = 0; i < 4; ++i)
	{
		int dx = cx + offsetx[i];
		int dy = cy + offsety[i];
		int di = dx + dy * w;

		//没有越界
		if (dx >= 0 && dx < w && dy >= 0 && dy < h)
		{
			//不是障碍
			if (map[di] > 0)
			{
				//没有走过
				bool go = false;
				for (int j = 0; j < (int)path->size(); ++j)
				{
					if (path->at(j) == di)
					{
						go = true;
						break;
					}
				}
				if (!go)
				{
					for (int j = 0; j < (int)help->size(); ++j)
					{
						if (help->at(j) == di)
						{
							go = true;
							break;
						}
					}
					if (!go)
					{
						//当前位置放入路径中
						path->push_back(di);

						//递归判断
						bool r = _FindPathD(map, w, h, e, help, path);

						//找到了路
						if (r)
							return true;
						//找不到路
						else
						{
							//将该位置放入辅助数组
							help->push_back(di);

							//将该位置从路径中去掉
							path->pop_back();
						}
					}
				}
			}
		}
	}

	return false;
}

bool FindPathD(const char* map, //地图首地址
			   int w, //地图宽
			   int h, //地图高
			   int b, //起始点下标
			   int e, //终止点下标
			   std::vector<int>* path) //得到的路
{
	//参数判断
	if (!map ||
		w < 1 ||
		h < 1 ||
		b < 0 || b >= w * h ||
		e < 0 || e >= w * h ||
		!path)
		return false;

	//清空路
	path->clear();

	//若起始点就是终止点
	if (b == e)
	{
		//装入起始点
		path->push_back(b);
		return true;
	}

	//将起始点装入路径
	path->push_back(b);

	//设置辅助数组
	std::vector<int> help;

	//递归进行寻路
	return _FindPathD(map, w, h, e, &help, path);
}