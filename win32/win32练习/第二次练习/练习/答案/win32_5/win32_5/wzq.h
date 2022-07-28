#ifndef _WZQ_
#define _WZQ_

class CWzq
{
	int m_ipc;
	/*CMap* m_cp;*/
public:
	CWzq();
	int GetPc();
	void SetPc(int pc);
	/*void SetCp(CMap * cp);
	CMap* GetCp();*/
	int run(char* map,int x,int y);
};

#endif