#include "Render2D.h"

CMatrix3 g_Matrix[3];

void GetCameraMatrix(CMatrix3* m,
					 const CVector2* eye,
					 const CVector2* at)
{
	CMatrix3 t[2];

	//得到平移矩阵
	t[0].Translate(-eye->x, -eye->y);

	//得到旋转矩阵
	CVector2 v(at->x - eye->x, at->y - eye->y);
	float angle = acos(v.Normalize() * CVector2(0.0f, -1.0f));
	t[1].Rotate(angle);

	_Mat_X_Mat(&t[0], &t[1], m);
}

void GetViewMatrix(CMatrix3* m,
				   int s_width,
				   int s_height,
				   int d_left,
				   int d_top,
				   int d_width,
				   int d_height)
{
	CMatrix3 t[2];

	//得到缩放矩阵
	t[0].Scaling((float)d_width / s_width, (float)d_height / s_height);

	//得到平移矩阵
	t[1].Translate(d_left + d_width / 2.0f, d_top + d_height / 2.0f);

	_Mat_X_Mat(&t[0], &t[1], m);
}

void SetMatrix(int type, const CMatrix3* m)
{
	if (type >= _WORLD_MATRIX && type <= _VIEW_MATRIX)
		g_Matrix[type] = *m;
}