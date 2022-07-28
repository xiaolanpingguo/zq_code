#ifndef _MY_XFORM_H_
#define _MY_XFORM_H_

#include <windows.h>

class CMY_XFORM : public XFORM
{
public:
	CMY_XFORM()
	{
		Identity();
	}

	//单位化
	void Identity()
	{
		eM11 = eM22 = 1.0f;
		eM12 = eM21 = eDx = eDy = 0.0f;
	}

	//缩放
	void Scaling(float x, float y)
	{
		eM11 = x;    eM12 = 0.0f;
		eM21 = 0.0f; eM22 = y;
		eDx = 0.0f;  eDy = 0.0f;
	}

	//旋转
	void Rotate(float a)
	{
		eM11 = cos(a); eM12 = sin(a);
		eM21 = -eM12;  eM22 = eM11;
		eDx = 0.0f;    eDy = 0.0f;
	}

	//平移
	void Translate(float x, float y)
	{
		eM11 = 1.0f;	eM12 = 0.0f;
		eM21 = 0.0f;	eM22 = 1.0f;
		eDx = x;		eDy = y;
	}

	CMY_XFORM* _XF_X_XF(const CMY_XFORM* that, CMY_XFORM* output)
	{
		output->eM11 = eM11 * that->eM11 + eM12 * that->eM21;
		output->eM12 = eM11 * that->eM12 + eM12 * that->eM22;

		output->eM21 = eM21 * that->eM11 + eM22 * that->eM21;
		output->eM22 = eM21 * that->eM12 + eM22 * that->eM22;

		output->eDx = eDx * that->eM11 + eDy * that->eM21 + that->eDx;
		output->eDy = eDx * that->eM12 + eDy * that->eM22 + that->eDy;

		return output;
	}	

	CMY_XFORM operator * (const CMY_XFORM& that)
	{
		CMY_XFORM mx;
		return *_XF_X_XF(&that, &mx);
	}
};

#endif