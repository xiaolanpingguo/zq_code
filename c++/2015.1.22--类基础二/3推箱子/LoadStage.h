#ifndef _LOAD_STAGE_H_
#define _LOAD_STAGE_H_

#include "LinkList.h"
#include "BoxType.h"

//加载关卡
//无法打开关卡索引文件-3
//无关卡-2
//关卡打开失败-1
//不是本游戏地图文件0
//成功1
int LoadStage(const char* , LinkList);

#endif