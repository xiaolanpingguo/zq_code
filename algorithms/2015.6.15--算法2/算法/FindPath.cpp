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

#define _JDZ(a) ((a)<0?(-(a)):(a))
#define _H_VALUE(i) ((_JDZ((i%w)-(e%w))+_JDZ((i/w)-(e/w)))*5)

bool FindPathA(const char* map, //地图首地址
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

	//设置开表、闭表
	struct NODE
	{
		//当前下标、父下标、G值、H值
		int i, p, g, h;
	};
	std::vector<NODE> open, close;

	//起始点入开表
	NODE begin = {b, -1, 0, _H_VALUE(b)};
	open.push_back(begin);

	//8个方向的偏移量
	//701
	//6 2
	//543
	const int offsetx[] = {0,1,1,1,0,-1,-1,-1};
	const int offsety[] = {-1,-1,0,1,1,1,0,-1};
	const int add_g[] = {5,7,5,7,5,7,5,7};

	//找路循环
	while (!open.empty())
	{
		//得到开表中F值最小点
		int min_index = 0;
		for (int i = 1; i < (int)open.size(); ++i)
		{
			if (open[min_index].g + open[min_index].h > open[i].g + open[i].h)
				min_index = i;
		}
		NODE min = open[min_index];

		//将其从开表中删除并放入闭表
		open.erase(open.begin() + min_index);
		close.push_back(min);

		//循环F值最小点的8个方向
		int min_x = min.i % w;
		int min_y = min.i / w;
		for (int j = 0; j < 8; ++j)
		{
			//得到当前方向点坐标
			int dx = min_x + offsetx[j];
			int dy = min_y + offsety[j];
			int di = dx + dy * w;

			//不越界且不是障碍
			if (dx >= 0 && dx < w && dy >= 0 && dy < h && map[di] > 0)
			{
				//找到了路
				if (di == e)
				{
					//将终止点放入闭表，注意此时
					//的G、H都无关紧要了，随便填
					NODE cur = {di, min.i};
					close.push_back(cur);

					//得到当前应该放入path中的点的下标
					int index = (int)close.size() - 1;

					//返回路径
					while (index != -1)
					{
						path->push_back(close[index].i);
						int parent = close[index].p;
						if (parent == -1)
							break;
						while (close[index].i != parent)
							--index;
					}

					return true;
				}
				else
				{
					//判断是否在闭表中
					bool in_close = false;
					for (int k = 0; k < (int)close.size(); ++k)
					{
						if (close[k].i == di)
						{
							in_close = true;
							break;
						}
					}

					//不在闭表中
					if (!in_close)
					{
						//判断是否在开表中
						bool in_open = false;
						int k = 0;
						for (; k < (int)open.size(); ++k)
						{
							if (open[k].i == di)
							{
								in_open = true;
								break;
							}
						}

						//当前点的G值
						int cur_g = min.g + add_g[j];

						//在开表中
						if (in_open)
						{
							if (cur_g < open[k].g)
							{
								//更新父节点
								open[k].p = min.i;

								//更新G值
								open[k].g = cur_g;
							}
						}
						//不在开表中
						else
						{
							//当前点入开表
							NODE cur = {di, min.i, cur_g, _H_VALUE(di)};
							open.push_back(cur);
						}
					}
				}
			}
		}
	}

	return false;
}