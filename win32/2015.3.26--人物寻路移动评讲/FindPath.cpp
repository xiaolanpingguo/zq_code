#include "FindPath.h"

#define _SC_OFFSET 5
#define _XX_OFFSET 7 

template <typename T>
CFindPath::CCSqList<T>::CCSqList()
:
m_S(32),
m_L(0),
m_P(new T[m_S])
{}

template <typename T>
CFindPath::CCSqList<T>::~CCSqList()
{
	delete [] m_P;
}

template <typename T>
CFindPath::CCSqList<T>::CCSqList(const CCSqList& that)
:
m_S(that.m_S),
m_L(that.m_L),
m_P(new T[m_S])
{
	for (int i = 0; i < m_L; ++i)
		m_P[i] = that.m_P[i];
}

template <typename T>
CFindPath::CCSqList<T>& CFindPath::CCSqList<T>::operator = (const CCSqList& that)
{
	if (this != &that)
	{
		if (m_S < that.m_S)
		{
			m_S = that.m_S;
			delete [] m_P;
			m_P = new T[m_S];
		}

		m_L = that.m_L;
		for (int i = 0; i < m_L; ++i)
			m_P[i] = that.m_P[i];
	}
	return *this;
}

template <typename T>
void CFindPath::CCSqList<T>::Push(T d)
{
	if (m_L == m_S)
	{
		T* p = new T[m_S *= 2];
		for (int i = 0; i < m_L; ++i)
			p[i] = m_P[i];
		delete [] m_P;
		m_P = p;
	}

	m_P[m_L++] = d;
}

template <typename T>
bool CFindPath::CCSqList<T>::Erase(int p)
{
	if (p < 1 || p > m_L)
		return false;

	int m = m_L - p;
	for (int i = 0; i < m; ++i)
		m_P[p - 1 + i] = m_P[p + i];
	m_L -= 1;

	return true;
}

template <typename T>
void CFindPath::CCSqList<T>::Clear()
{
	m_L = 0;
}

template <typename T>
T* CFindPath::CCSqList<T>::Get(int p)
{
	if (p < 1 || p > m_L)
		return false;

	return m_P + p - 1;
}

template <typename T>
int CFindPath::CCSqList<T>::Length()
{
	return m_L;
}

template <typename T>
T* CFindPath::CCSqList<T>::Locate(T d, int b)
{
	if (b < 1 || b > m_L)
		return 0;

	for (int i = b - 1; i < m_L; ++i)
	{
		if (m_P[i] == d)
			return m_P + i;
	}

	return 0;
}

CFindPath::CCSqList<int> CFindPath::m_BeGone;

bool CFindPath::_FindPathD(const char* map, int w, int h, int b, int e, int* pPath, int* pPathLen, CCSqList<int>* pBeGone)
{
	static const int xoffset[] = {0, 0, -1, 1};
	static const int yoffset[] = {-1, 1, 0, 0};

	int i = pPath[*pPathLen - 1], x = i % w, y = i / w;

	for (int j = 0; j < 4; ++j)
	{
		int cx = x + xoffset[j];
		int cy = y + yoffset[j];
		int ci = cx + cy * w;

		if (cx >= 0 && cx < w && cy >= 0 && cy < h)
		{
			if (ci == e)
			{
				pPath[*pPathLen] = ci;
				*pPathLen += 1;
				return true;
			}

			if (map[ci] > 0)
			{
				bool b = true;
				for (int k = 0; k < *pPathLen; ++k)
				{
					if (ci == pPath[k])
					{
						b = false;
						break;
					}
				}
				if (b)
				{
					if (0 == pBeGone->Locate(ci, 1))
					{
						pPath[*pPathLen] = ci;
						*pPathLen += 1;

						bool f = _FindPathD(map, w, h, b, e, pPath, pPathLen, pBeGone);
						if (f)
							return true;
						else
						{
							pBeGone->Push(ci);
							*pPathLen -= 1;
						}
					}
				}
			}
		}
	}

	return false;
}

bool CFindPath::FindPathD(const char* map, int w, int h, int b, int e, int* pPath, int* pPathLen)
{
	if (!map || w < 1 || h < 1 || b < 0 || b >= w * h || e < 0 || e >= w * h || !pPath || !pPathLen)
		return false;

	pPath[(*pPathLen) = 0] = b;
	*pPathLen += 1;

	if (b == e)
		return true;

	m_BeGone.Clear();

	return _FindPathD(map, w, h, b, e, pPath, pPathLen, &m_BeGone);
}

CFindPath::CCSqList<int> CFindPath::m_F;
CFindPath::CCSqList<int> CFindPath::m_Z;

void CFindPath::Inverse(int* p, int c)
{
	int h = c >> 1;
	c -= 1;
	for (int i = 0; i < h; ++i)
	{
		int t = p[i];
		p[i] = p[c - i];
		p[c - i] = t;
	}
}

bool CFindPath::FindPathW(const char* map, int w, int h, int b, int e, int* pPath, int* pPathLen)
{
	if (!map || w < 1 || h < 1 || b < 0 || b >= w * h || e < 0 || e >= w * h || !pPath || !pPathLen)
		return false;

	if (b == e)
	{
		pPath[(*pPathLen) = 0] = b;
		*pPathLen += 1;
		return true;
	}

	m_F.Clear();
	m_Z.Clear();

	m_F.Push(-1);
	m_Z.Push(b);

	static const int xoffset[] = {0, 0, -1, 1};
	static const int yoffset[] = {-1, 1, 0, 0};

	int qishi = 1;
	int zhongzhi = 1;

	while (1)
	{
		int zlength = m_Z.Length();

		for (int j = qishi; j <= zhongzhi; ++j)
		{
			int i = *m_Z.Get(j);
			int x = i % w;
			int y = i / w;

			for (int k = 0; k < 4; ++k)
			{
				int cx = x + xoffset[k];
				int cy = y + yoffset[k];
				int ci = cx + cy * w;
				
				if (cx >= 0 && cx < w && cy >= 0 && cy < h)
				{
					if (ci == e)
					{
						m_Z.Push(ci);
						m_F.Push(j);

						*pPathLen = 0;
						pPath[(*pPathLen)++] = ci;

						int r = m_Z.Length();

						while (1)
						{
							int findex = *m_F.Get(r);
							if (findex == -1)
							{
								Inverse(pPath, *pPathLen);
								return true;
							}
							else
							{
								r = findex;
								pPath[(*pPathLen)++] = *m_Z.Get(findex);
							}
						}
					}

					if (map[ci] == 0)
					{
						if (0 == m_Z.Locate(ci))
						{
							m_Z.Push(ci);
							m_F.Push(j);
						}
					}
				}
			}
		}

		if (zlength == m_Z.Length())
			break;
		else
		{
			qishi = zlength + 1;
			zhongzhi = m_Z.Length();
		}
	}

	return false;
}

CFindPath::CCSqList<CFindPath::_ASN> CFindPath::m_Open;
CFindPath::CCSqList<CFindPath::_ASN> CFindPath::m_Close;

int CFindPath::_ABS(int i)
{
	return i < 0 ? -i : i;
}

int CFindPath::_GetH(int i1, int i2, int w)
{
	return (_ABS(i1 % w - i2 % w) + _ABS(i1 / w - i2 / w)) * _SC_OFFSET;
}

int CFindPath::_GetMinFIndex(CCSqList<_ASN>* m_pOpen)
{
	if (0 == m_pOpen->Length())
		return 0;

	int MinFIndex = 1;
	for (int i = 2; i <= m_pOpen->Length(); ++i)
	{
		_ASN* p = m_pOpen->Get(MinFIndex);
		_ASN* q = m_pOpen->Get(i);
		if (p->g + p->h > q->g + q->h)
			MinFIndex = i;
	}
	return MinFIndex;
}

void CFindPath::_GetChild(const char* map, int w, int h, const _ASN* f, int e, _ASN* child, int* childlen)
{
	int fx = f->z % w, fy = f->z / w;
	int zx[] = {fx - 1, fx, fx + 1, fx + 1, fx + 1, fx, fx - 1, fx - 1};
	int zy[] = {fy - 1, fy - 1, fy - 1, fy, fy + 1, fy + 1, fy + 1, fy};
	static const int gadd[] = {_XX_OFFSET, _SC_OFFSET, _XX_OFFSET, _SC_OFFSET, _XX_OFFSET, _SC_OFFSET, _XX_OFFSET, _SC_OFFSET};
	*childlen = 0;
	for (int i = 0; i < 8; ++i)
	{
		int ci = zx[i] + zy[i] * w;
		if (zx[i] >= 0 && zx[i] < w && zy[i] >= 0 && zy[i] < h && map[ci] > 0)
		{
			child[*childlen].f = f->z;
			child[*childlen].z = ci;
			child[*childlen].g = f->g + gadd[i];
			child[*childlen].h = _GetH(ci, e, w);
			(*childlen)++;
		}
	}
}

bool CFindPath::FindPathA(const char* map, int w, int h, int b, int e, int* pPath, int* pPathLen)
{
	if (!map || w < 1 || h < 1 || b < 0 || b >= w * h || e < 0 || e >= w * h || !pPath || !pPathLen)
		return false;

	if (b == e)
	{
		pPath[(*pPathLen) = 0] = b;
		*pPathLen += 1;
		return true;
	}

	m_Open.Clear();
	m_Close.Clear();

	_ASN first = {-1, b, 0, _GetH(b, e, w)};
	m_Open.Push(first);

	while (m_Open.Length())
	{
		int MinFIndex = _GetMinFIndex(&m_Open);
		_ASN p = *m_Open.Get(MinFIndex);

		m_Close.Push(p);
		m_Open.Erase(MinFIndex);

		_ASN child[8];
		int childlen;
		_GetChild(map, w, h, &p, e, child, &childlen);

		for (int i = 0; i < childlen; ++i)
		{
			if (child[i].z == e)
			{
				pPath[(*pPathLen) = 0] = e;
				*pPathLen += 1;

				_ASN* pCur = &child[i];

				for (int j = m_Close.Length(); j > 0; --j)
				{
					_ASN* q = m_Close.Get(j);

					if (q->z == pCur->f)
					{
						pPath[*pPathLen] = q->z;
						pCur = q;
						*pPathLen += 1;
					}
				}

				Inverse(pPath, *pPathLen);

				return true;
			}
			else
			{
				if (!m_Close.Locate(child[i]))
				{
					_ASN* q = m_Open.Locate(child[i]);

					if (0 == q)
						m_Open.Push(child[i]);
					else
					{
						if (q->g > child[i].g)
						{
							q->f = child[i].f;
							q->g = child[i].g;
						}
					}
				}
			}
		}
	}

	return false;
}