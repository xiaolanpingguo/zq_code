#include "FindPathW.h"

bool FindPathW(const char* map,
			   int width,
			   int height,
			   int start,
			   int end,
			   std::vector<int>* path)
{
	//参数判断
	if (!map ||
		width < 1 ||
		height < 1 ||
		start < 0 ||
		start >= width * height ||
		end < 0 ||
		end >= width * height ||
		!path)
		return false;

	//清空路径
	path->clear();

	//如果起始点就是终止点
	if (start == end)
	{
		path->push_back(start);
		return true;
	}

	//辅助表
	//下面的h1、h2设置为静态使得其
	//构造函数只在最初被执行一次，
	//其后没有必要执行，仅仅将其清
	//空即可
	static std::vector<int> h1, h2;
	h1.clear();
	h2.clear();

	//起始点入表
	h1.push_back(start);
	h2.push_back(-1);

	//得到发散的起始、终止下标
	int i1 = 0, i2 = 0;

	//设置方向偏移量
	static const int offsetx[] = {0,0,-1,1};
	static const int offsety[] = {-1,1,0,0};

	//找路循环
	while (1)
	{
		//记录发散前的辅助表长
		unsigned int i3 = (unsigned int)h1.size();

		//发散找路
		for (int i = i1; i <= i2; ++i)
		{
			//得到当前发散点的坐标
			int cx = h1[i] % width;
			int cy = h1[i] / width;

			for (int j = 0; j < 4; ++j)
			{
				//得到当前发散点的4个方向的坐标
				int dx = cx + offsetx[j];
				int dy = cy + offsety[j];

				//不能越界
				if (dx >= 0 && dx < width && dy >= 0 && dy < height)
				{
					//得到当前方向的点的下标
					int di = dx + dy * width;

					//找到终止点了
					if (di == end)
					{
						//装入终止点
						h1.push_back(di);
						h2.push_back(i);

						//得到路径
						int cur = (int)h1.size() - 1;
						while (cur != -1)
						{
							path->push_back(h1[cur]);
							cur = h2[cur];
						}

						//注意路径是反着放的
						//end、...、start

						return true;
					}
					//不是终止点
					else
					{
						//不能是障碍
						if (map[di] > 0)
						{
							//没有走过
							bool go = false;
							for (unsigned int k = 0; k < h1.size(); ++k)
							{
								if (di == h1[k])
								{
									go = true;
									break;
								}
							}
							if (!go)
							{
								//将当前点及其父节点信息放入辅助表中
								h1.push_back(di);
								h2.push_back(i);
							}
						}
					}
				}
			}
		}

		//本轮有发散出来新的下标
		if (h1.size() > i3)
		{
			i1 = i3;
			i2 = (int)h1.size() - 1;
		}
		//本轮没有发散出来新的下
		//标就意味着整个地图能走
		//的地方都走完了还没有遇
		//到终止点
		else
			break;
	}

	return false;
}