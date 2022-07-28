#ifndef _XY_H_
#define _XY_H_

struct _XY
{
	int type;
};

struct CS_DL : public _XY
{
	CS_DL(){type = 0;}
	char id[32];
	char pw[32];
};

struct SC_NO_ID : public _XY
{
	SC_NO_ID(){type = 1;}
};

struct SC_PW_ERROR : public _XY
{
	SC_PW_ERROR(){type = 2;}
};

struct SC_DL_OK : public _XY
{
	SC_DL_OK(){type = 3;}
	int num;
	//后面要添加所有其它玩家的信息
};

struct SC_NEW_CLIENT : public _XY
{
	SC_NEW_CLIENT(){type = 4;}
	char id[32];
};

struct CS_ZC : public _XY
{
	CS_ZC(){type = 5;}
	char id[32];
	char pw[32];
};

struct SC_ZC_FAIL : public _XY
{
	SC_ZC_FAIL(){type = 6;}
};

struct SC_ZC_OK : public _XY
{
	SC_ZC_OK(){type = 7;}
};

#endif