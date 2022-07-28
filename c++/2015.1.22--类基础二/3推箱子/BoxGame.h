#ifndef _BOX_GAME_H_
#define _BOX_GAME_H_

#include "LinkList.h"

void BoxGame(LinkList linklist,int StartStage);

bool PushBox(const _BOX_STAGE* pBS,int StageNum);

int LoadGame(int LastStage);



#endif