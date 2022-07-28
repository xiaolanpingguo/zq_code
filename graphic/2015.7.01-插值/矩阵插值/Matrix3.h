#ifndef _MATRIX_3_H_
#define _MATRIX_3_H_

#include "Vector2.h"

class CMatrix3
{
public:
	float
		_11, _21, _31,
		_12, _22, _32,
		_13, _23, _33;

	CMatrix3()
	{
		Identity();
	}

	void Identity()
	{
		_11 = 1.0f; _21 = 0.0f; _31 = 0.0f;
		_12 = 0.0f; _22 = 1.0f; _32 = 0.0f;
		_13 = 0.0f; _23 = 0.0f; _33 = 1.0f;
	}

	void Scaling(float x, float y)
	{
		_11 = x;    _21 = 0.0f; _31 = 0.0f;
		_12 = 0.0f; _22 = y;    _32 = 0.0f;
		_13 = 0.0f; _23 = 0.0f; _33 = 1.0f;
	}

	void Translate(float x, float y)
	{
		_11 = 1.0f; _21 = 0.0f; _31 = 0.0f;
		_12 = 0.0f; _22 = 1.0f; _32 = 0.0f;
		_13 = x;    _23 = y;    _33 = 1.0f;
	}

	void Rotate(float a)
	{
		_11 = cos(a); _21 = sin(a); _31 = 0.0f;
		_12 = -_21;   _22 = _11;    _32 = 0.0f;
		_13 = 0.0f;   _23 = 0.0f;   _33 = 1.0f;
	}
};

inline CVector2* _VxM(const CVector2* v,
					  const CMatrix3* m,
					  CVector2* output)
{
	float f1[] = {v->x, v->y, 1.0f};
	float f2[]
	=
	{
		f1[0] * m->_11 + f1[1] * m->_12 + f1[2] * m->_13,
		f1[0] * m->_21 + f1[1] * m->_22 + f1[2] * m->_23,
		f1[0] * m->_31 + f1[1] * m->_32 + f1[2] * m->_33
	};
	output->x = f2[0] / f2[2];
	output->y = f2[1] / f2[2];
	return output;
}

inline CMatrix3* _MxM(const CMatrix3* m1,
					  const CMatrix3* m2,
					  CMatrix3* output)
{
	output->_11 = m1->_11 * m2->_11 + m1->_21 * m2->_12 + m1->_31 * m2->_13;
	output->_21 = m1->_11 * m2->_21 + m1->_21 * m2->_22 + m1->_31 * m2->_23;
	output->_31 = m1->_11 * m2->_31 + m1->_21 * m2->_32 + m1->_31 * m2->_33;

	output->_12 = m1->_12 * m2->_11 + m1->_22 * m2->_12 + m1->_32 * m2->_13;
	output->_22 = m1->_12 * m2->_21 + m1->_22 * m2->_22 + m1->_32 * m2->_23;
	output->_32 = m1->_12 * m2->_31 + m1->_22 * m2->_32 + m1->_32 * m2->_33;

	output->_13 = m1->_13 * m2->_11 + m1->_23 * m2->_12 + m1->_33 * m2->_13;
	output->_23 = m1->_13 * m2->_21 + m1->_23 * m2->_22 + m1->_33 * m2->_23;
	output->_33 = m1->_13 * m2->_31 + m1->_23 * m2->_32 + m1->_33 * m2->_33;
	
	return output;
}

#endif