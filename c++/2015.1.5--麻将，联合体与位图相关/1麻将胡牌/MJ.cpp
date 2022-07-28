#include "MJ.h"


int HuPai(_MJ* p,int n)
{
	//张数判断
	if(n < 1 || n > 14 || n % 3 != 2)
		return -3;
	//将麻将数组转换为char数组
	char pai[27] = {};
	for(int i = 0; i < n;++i)
		pai[(p[i].ds - 1) + (p[i].hs - 1) * 9] += 1;

	//每种牌的数量检查
	for(int  i = 0; i < 27;++i)
	{
		if(pai[i] > 4)
			return -2;
	}
	//打缺
	int tong = 0,tiao = 0, wan = 0;
	for(int i = 0; i < 9;++i)
	{
		if(pai[i]>0)
			tong = 1;
	}
	for(int i = 9; i < 18;++i)
	{
		if(pai[i]>0)
			tiao = 1;
	}
	for(int i = 18; i < 27;++i)
	{
		if(pai[i]>0)
			wan = 1;
	}
	if(tong + tiao + wan == 3)
		return -1;
	//七对胡牌
	int dui = 0;
	for(int i = 0; i < 27;++i)
	{
		if(pai[i] == 2)
			dui += 1;
		else if(pai[i] == 4)
			dui += 2;
	}
	if(dui == 7)
		return 2;
	//其他
	bool jd = false;
	return _HuPai(pai,&jd);
}

int _HuPai(char* pai,bool* jd)
{
	//如果没有牌了就胡牌了
	int num = 0;
	for(int i = 0;i < 27;++i)
		num+=pai[i];
	if(num == 0)
		return 1;

	//找到最开始有牌的地方
	int begin = 0;
	for(;pai[begin] == 0;++begin)
		;
	//刻子判断
	if(pai[begin] >= 3)
	{
		//去除刻子
		pai[begin] -= 3;
		int r = _HuPai(pai,jd);
		if(1 == r)
			return 1;
		else
		{
			//该牌拿去组成刻子不成功的话就恢复
			pai[begin] += 3;
		}
	}
	//将对判断
	if(pai[begin] >= 2 && *jd == false)
	{
		//去除将对
		pai[begin] -= 2;
		*jd = true;
		int r = _HuPai(pai,jd);
		if(1 == r)
			return 1;
		else
		{
			//该牌拿去组成将对不成功的话就恢复
			pai[begin] += 2;
			*jd = false;
		}
	}
	if((begin % 9 ) < 7 
		&& pai[begin] >= 1
		&& pai[begin + 1] >= 1
		&& pai[begin + 2] >= 1)
	{
		//去除顺子
		pai[begin] -= 1;
		pai[begin + 1] -= 1;
		pai[begin + 2] -= 1;
		//在将剩下的牌继续判断
		int r = _HuPai(pai,jd);
		if(r == 1)
			return 1;
		else
		{
			pai[begin] += 1;
			pai[begin + 1] += 1;
			pai[begin + 2] += 1;
		}
	}
	return 0;
}