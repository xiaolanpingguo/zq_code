#ifndef _RENDER_2D_H_
#define _RENDER_2D_H_

#include "Matrix3.h"
#include <vector>
#include <windows.h>

#define _WORLD_MATRIX 0 //世界变换矩阵
#define _CAMERA_MATRIX 1 //摄像机变换矩阵
#define _VIEW_MATRIX 2 //视口变换矩阵

//得到摄像机变换矩阵
void GetCameraMatrix(CMatrix3* m,
					 const CVector2* eye, //摄像机的位置
					 const CVector2* at); //摄像机看过去的一个点

//得到视口变换矩阵
void GetViewMatrix(CMatrix3* m,
				   int s_width, //源宽
				   int s_height, //源高
				   int d_left, //目标视口矩形左上角x
				   int d_top, //目标视口矩形左上角y
				   int d_width, //目标视口矩形宽
				   int d_height); //目标视口矩形高

void SetView(int d_left,
			 int d_top,
			 int d_width,
			 int d_height);

//设置指定变换矩阵
void SetMatrix(int type, const CMatrix3* m);

typedef struct _MODAL_2D
{
	std::vector<CVector2> v_coordinate; //顶点坐标
	std::vector<CVector2> t_coordinate; //纹理坐标
}MODAL2D;
bool LoadMODAL2D(MODAL2D* modal2d, const char* file);
//(x1,y1,u1,v1)
//(x2,y2,u2,v2)
//(x3,y3,u3,v3)
//...
//(xn,yn,un,vn)
//1）顶点个数必须是3的整数倍
//2）uv坐标用比例来标记（0.0f~0.999f）

void DrawMODAL2D(HDC destdc, MODAL2D* modal2d, HDC texture);

#endif