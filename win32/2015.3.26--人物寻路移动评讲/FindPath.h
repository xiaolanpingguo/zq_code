#ifndef _FIND_PATH_H_
#define _FIND_PATH_H_

//地图为char数组,<=0为障碍,>0为通路

class CFindPath
{
	template <typename T>
	class CCSqList
	{
		int m_S;
		int m_L;
		T* m_P;
	public:
		CCSqList();
		~CCSqList();
		CCSqList(const CCSqList& that);
		CCSqList& operator = (const CCSqList& that);
		void Push(T d);
		bool Erase(int p);
		void Clear();
		T* Get(int p);
		int Length();
		T* Locate(T d, int b = 1);
	};

	//深度相关
	static CCSqList<int> m_BeGone;
	static bool _FindPathD(const char* map, int w, int h, int b, int e, int* pPath, int* pPathLen, CCSqList<int>* pBeGone);

	//广度相关
	static CCSqList<int> m_F;
	static CCSqList<int> m_Z;
	static void Inverse(int* p, int c);

	//A星相关
	struct _ASN
	{
		int f, z, g, h;
		bool operator == (const _ASN& that)
		{
			return z == that.z;
		}
	};
	static CCSqList<_ASN> m_Open;
	static CCSqList<_ASN> m_Close;
	static int _ABS(int i);
	static int _GetH(int i1, int i2, int w);
	static int _GetMinFIndex(CCSqList<_ASN>* m_pOpen);
	static void _GetChild(const char* map, int w, int h, const _ASN* f, int e, _ASN* child, int* childlen);

public:

	//返回true值则找到路,路径放入到pPath中,pPath长度应为地图大小
	//返回false则未找到路
	
	//4方向(顺序为上下左右)
	static bool FindPathD(const char* map, int w, int h, int b, int e, int* pPath, int* pPathLen);

	//4方向
	static bool FindPathW(const char* map, int w, int h, int b, int e, int* pPath, int* pPathLen);

	//8方向
	static bool FindPathA(const char* map, int w, int h, int b, int e, int* pPath, int* pPathLen);
};

#endif