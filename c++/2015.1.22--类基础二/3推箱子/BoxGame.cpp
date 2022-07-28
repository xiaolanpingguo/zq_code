#include "BoxGame.h"
#include "BoxType.h"
#include <iostream>
#include <conio.h>

#define _GAME_INIT 0
#define _GAME_RUN  1

//判断游戏是否通关
void BoxGame(LinkList linklist,int StartStage)
{
	bool over = true;
	for(int i = StartStage; i <= LengthLinkList(linklist); ++i)
	{
		if(PushBox(GetLinkList(linklist,i),i))
		{
			over = false;
			break;
		}
	}
	if(over)
	{
		//通关
	}
}

//游戏主逻辑
bool PushBox(const _BOX_STAGE* pBS,int StageNum)
{
	//创建当前关卡
	_BOX_STAGE bs = {0,pBS->w,pBS->h,0,0};
	int size = pBS->w*pBS->h;
	bs.m = (char*)malloc(size);
	bool ReturnMainMenu = false;
	int state = _GAME_INIT;
	while(1)
	{
		if(state == _GAME_INIT)
		{
			bs.x = pBS->x;
			bs.y = pBS->y;
			for(int i = 0; i < size; ++i)
				bs.m[i] = pBS->m[i];
			state = _GAME_RUN;
		}
		else
		{
			//存档
			int SaveData = StageNum;
			SaveData ^= 0x11223344;
			FILE* pFile;
			fopen_s(&pFile,"Save","wb");
			fwrite(&SaveData,sizeof(int),1,pFile);
			//fwrite(bs.m ,sizeof(char),bs.w * bs.h,pFile)
			//fwrite(&bs.w,sizeof(int),1,pFile)
			//fwrite(&bs.h,sizeof(int),1,pFile)
			
			fclose(pFile);
		}
	}
	free(bs.m);
	return ReturnMainMenu;
}

//加载存档
int LoadGame(int LastStage)
{
	FILE* pFile;
	fopen_s(&pFile,"Save","rb");
	/////////
}