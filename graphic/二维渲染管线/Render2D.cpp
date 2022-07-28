#include "Render2D.h"

#include<string>

extern HDC g_BackDC;

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

bool LoadMODAL2D(MODAL2D* modal2d, const char* file)
//(x1,y1,u1,v1)
//(x2,y2,u2,v2)
//(x3,y3,u3,v3)
//...
//(xn,yn,un,vn)
//1）顶点个数必须是3的整数倍
//2）uv坐标用比例来标记（0.0f~0.999f）
{
	FILE* pf = 0;
	fopen_s(&pf,file,"rb");
	fseek(pf,0,SEEK_END);
	int len = ftell(pf);
	rewind(pf);
	char* p = new char[len];
	fread(p,1,len,pf);
	fclose(pf);
	
	int size = 0;
	for (int i = 0; i < len; ++i)
	{
		if (p[i] == '(')
			++size;
	}
	int index = 0; //下标
	for (int i = 0; i < size; ++i)
	{
		CVector2 v;
		CVector2 t;
		std::string ss[4];
		int index2 = 0;
		while(1)
		{
			if (p[index] == '(' || p[index] == ')' || p[index] == '\r' || p[index] == '\n' || p[index] == ',')
			{
				if (i == size - 1 && p[index] == ')')
					break;
				if (p[index] == '\n')
				{
					++index;
					break;
				}
				if (p[index] == ',')
				{
					++index2;
				}
				++index;
				continue;
			}
			ss[index2] += p[index++];
		}
		v.x = atof(ss[0].c_str());
		v.y = atof(ss[1].c_str());
		t.x = atof(ss[2].c_str());
		t.y = atof(ss[3].c_str());
		modal2d->v_coordinate.push_back(v);
		modal2d->t_coordinate.push_back(t);
	}
	return true;
}

void DrawTriangleTexture(int x0, int y0,
						 int x1, int y1,
						 int x2, int y2,
						 HDC bmpdc,
						 int u0, int v0,
						 int u1, int v1,
						 int u2, int v2,
						 int left, int top, int right, int bottom);

void DrawMODAL2D(MODAL2D* modal2d, HDC texture,int left, int top, int right, int bottom)
{
	CMatrix3 m1,m2;
	_Mat_X_Mat(_Mat_X_Mat(&g_Matrix[0],&g_Matrix[1],&m1),&g_Matrix[2],&m2);
	
	HBITMAP hbmp = (HBITMAP)GetCurrentObject(texture,OBJ_BITMAP);
	BITMAP bmp;
	GetObject(hbmp,sizeof(bmp),&bmp);

	float texture_w = (float)bmp.bmWidth;
	float texture_h = (float)bmp.bmHeight;

	int size = modal2d->v_coordinate.size() / 3;

	for (int i = 0; i < size; ++i)
	{
		CVector2 v[3],t[3];
		for (int j = 0; j < 3; ++j)
		{
			_Vec_X_Mat(&modal2d->v_coordinate[i * 3 + j],&m2,v + j);
			t[j].x = modal2d->t_coordinate[i * 3 + j].x;
			t[j].y = modal2d->t_coordinate[i * 3 + j].y;
		}
		DrawTriangleTexture(v[0].x,v[0].y,v[1].x,v[1].y,v[2].x,v[2].y,texture,
			t[0].x * texture_w,t[0].y * texture_h,
			t[1].x * texture_w,t[1].y * texture_h,
			t[2].x * texture_w,t[2].y * texture_h,
			left,top,right,bottom);
	}
}


void DrawTriangleTexture_FlatBottom(int x0, int y0,
									int x1, int y1,
									int x2, int y2,
									HDC bmpdc,
									int u0, int v0,
									int u1, int v1,
									int u2, int v2,
									int left, int top, int right, int bottom)
{
	//判断是否要进行绘制
	if ((x0 < left && x1 < left && x2 < left) ||
		(y0 < top && y1 < top && y2 < top) ||
		(x0 >= right && x1 >= right && x2 >= right) ||
		(y0 >= bottom && y1 >= bottom && y2 >= bottom))
		return;

	//		 (x0,y0)
	//(x1,y1)		(x2,y2)

	//得到所有梯度，即得到每一个变化的坐标随着目标三
	//角形上y值每递增一个单位这些变化的坐标的变化量
	float left_x_grads = (float)(x0 - x1) / (y0 - y1);
	float right_x_grads = (float)(x0 - x2) / (y0 - y2);
	float left_u_grads = (float)(u0 - u1) / (y0 - y1);
	float right_u_grads = (float)(u0 - u2) / (y0 - y2);
	float left_v_grads = (float)(v0 - v1) / (y0 - y1);
	float right_v_grads = (float)(v0 - v2) / (y0 - y2);

	//得到每个变化的坐标的初值
	float left_x = x0;
	float right_x = x0;
	float left_u = u0;
	float right_u = u0;
	float left_v = v0;
	float right_v = v0;

	//范围判断
	if (y0 < top)
	{
		//如果y0是小于top，那么更新所有的起始量
		int offset_y = top - y0;
		left_x += left_x_grads * offset_y;
		right_x += right_x_grads * offset_y;
		left_u += left_u_grads * offset_y;
		right_u += right_u_grads * offset_y;
		left_v += left_v_grads * offset_y;
		right_v += right_v_grads * offset_y;
		y0 = top;
	}
	if (y1 >= bottom)
		y1 = bottom - 1;

	//绘制循环
	for (int y = y0; y <= y1; ++y)
	{
		int x_left = (int)left_x;
		int x_right = (int)right_x;

		//得到当前u、v随着x每递增1个单位它们的变化量
		float u_grads = (left_u - right_u) / (left_x - right_x);
		float v_grads = (left_v - right_v) / (left_x - right_x);
		float cur_u = left_u;
		float cur_v = left_v;

		if (x_left < left)
		{
			int offset_x = left - x_left;
			cur_u += u_grads * offset_x;
			cur_v += v_grads * offset_x;
			x_left = left;
		}
		if (x_right >= right)
			x_right = right - 1;

		for (int x = x_left; x <= x_right; ++x)
		{
			COLORREF c = GetPixel(bmpdc, (int)cur_u, (int)cur_v);
			SetPixel(g_BackDC, x, y, c);
			cur_u += u_grads;
			cur_v += v_grads;
			//Sleep(1);
		}

		left_x += left_x_grads;
		right_x += right_x_grads;
		left_u += left_u_grads;
		right_u += right_u_grads;
		left_v += left_v_grads;
		right_v += right_v_grads;
	}
}

void DrawTriangleTexture_FlatTop(int x0, int y0,
								 int x1, int y1,
								 int x2, int y2,
								 HDC bmpdc,
								 int u0, int v0,
								 int u1, int v1,
								 int u2, int v2,
								 int left, int top, int right, int bottom)
{
	//判断是否要进行绘制
	if ((x0 < left && x1 < left && x2 < left) ||
		(y0 < top && y1 < top && y2 < top) ||
		(x0 >= right && x1 >= right && x2 >= right) ||
		(y0 >= bottom && y1 >= bottom && y2 >= bottom))
		return;

	//(x1,y1)		(x2,y2)
	//		 (x0,y0)

	//得到所有梯度，即得到每一个变化的坐标随着目标三
	//角形上y值每递减一个单位这些变化的坐标的变化量
	float left_x_grads = (float)(x0 - x1) / (y1 - y0);
	float right_x_grads = (float)(x0 - x2) / (y2 - y0);
	float left_u_grads = (float)(u0 - u1) / (y1 - y0);
	float right_u_grads = (float)(u0 - u2) / (y2 - y0);
	float left_v_grads = (float)(v0 - v1) / (y1 - y0);
	float right_v_grads = (float)(v0 - v2) / (y2 - y0);

	//得到每个变化的坐标的初值
	float left_x = x0;
	float right_x = x0;
	float left_u = u0;
	float right_u = u0;
	float left_v = v0;
	float right_v = v0;

	//范围判断
	if (y0 >= bottom)
	{
		int offset_y = y0 - bottom;
		left_x += left_x_grads * offset_y;
		right_x += right_x_grads * offset_y;
		left_u += left_u_grads * offset_y;
		right_u += right_u_grads * offset_y;
		left_v += left_v_grads * offset_y;
		right_v += right_v_grads * offset_y;
		y0 = bottom - 1;
	}
	if (y1 < top)
		y1 = top;

	//绘制循环
	for (int y = y0; y >= y1; --y)
	{
		int x_left = (int)left_x;
		int x_right = (int)right_x;

		//得到当前u、v随着x每递增1个单位它们的变化量
		float u_grads = (left_u - right_u) / (left_x - right_x);
		float v_grads = (left_v - right_v) / (left_x - right_x);
		float cur_u = left_u;
		float cur_v = left_v;

		if (x_left < left)
		{
			int offset_x = left - x_left;
			cur_u += u_grads * offset_x;
			cur_v += v_grads * offset_x;
			x_left = left;
		}
		if (x_right >= right)
			x_right = right - 1;

		for (int x = x_left; x <= x_right; ++x)
		{
			COLORREF c = GetPixel(bmpdc, (int)cur_u, (int)cur_v);
			SetPixel(g_BackDC, x, y, c);
			cur_u += u_grads;
			cur_v += v_grads;
			//Sleep(1);
		}

		left_x += left_x_grads;
		right_x += right_x_grads;
		left_u += left_u_grads;
		right_u += right_u_grads;
		left_v += left_v_grads;
		right_v += right_v_grads;
	}
}

void DrawTriangleTexture(int x0, int y0,
						 int x1, int y1,
						 int x2, int y2,
						 HDC bmpdc,
						 int u0, int v0,
						 int u1, int v1,
						 int u2, int v2,
						 int left, int top, int right, int bottom)
{
	//三点相同的判断
	if (x0 == x1 && x1 == x2 && y0 == y1 && y1 == y2)
		return;

	//三点共线的判断
	if ((y0 - y1) * (x1 - x2) == (y1 - y2) * (x0 - x1))
		return;

	//三点的y值都不相同
	if (y0 != y1 && y1 != y2 && y0 != y2)
	{
		//按照y值从小到大排列三点
		POINT p[3] = {{x0, y0}, {x1, y1}, {x2, y2}};
		POINT q[3] = {{u0, v0}, {u1, v1}, {u2, v2}};
		for (int i = 2; i > 0; --i)
		{
			for (int j = 0; j < i; ++j)
			{
				if (p[j].y > p[j + 1].y)
				{
					POINT r;

					r = p[j];
					p[j] = p[j + 1];
					p[j + 1] = r;

					r = q[j];
					q[j] = q[j + 1];
					q[j + 1] = r;
				}
			}
		}

		//求xy新点
		POINT r = {0, p[1].y};
		float k, b;
		if (p[0].x != p[2].x)
		{
			k = (float)(p[0].y - p[2].y) / (p[0].x - p[2].x);
			b = p[0].y - k * p[0].x;
			r.x = (int)(((float)r.y - b) / k);
		}
		else
			r.x = p[0].x;

		float len1 = sqrt((float)(r.x - p[0].x) * (r.x - p[0].x) + (r.y - p[0].y) * (r.y - p[0].y));
		float len2 = sqrt((float)(p[2].x - p[0].x) * (p[2].x - p[0].x) + (p[2].y - p[0].y) * (p[2].y - p[0].y));
		float bl = len1 / len2;

		//求uv新点
		float f0[2] = {q[0].x, q[0].y};
		float f2[2] = {q[2].x, q[2].y};
		float f3[2] = {f2[0] - f0[0], f2[1] - f0[1]};
		float new_u = q[0].x + f3[0] * bl;
		float new_v = q[0].y + f3[1] * bl;

		//绘制平顶、平底三角形
		if (r.x < p[1].x)
		{
			// p[0]
			//r	p[1]
			// p[2]

			DrawTriangleTexture_FlatBottom(
				p[0].x, p[0].y,
				r.x, r.y,
				p[1].x, p[1].y,
				bmpdc,
				q[0].x, q[0].y,
				new_u, new_v,
				q[1].x, q[1].y,
				left, top, right, bottom);

			DrawTriangleTexture_FlatTop(
				p[2].x, p[2].y,
				r.x, r.y,
				p[1].x, p[1].y,
				bmpdc,
				q[2].x, q[2].y,
				new_u, new_v,
				q[1].x, q[1].y,
				left, top, right, bottom);
		}
		else
		{
			// p[0]
			//p[1] r
			// p[2]

			DrawTriangleTexture_FlatBottom(
				p[0].x, p[0].y,
				p[1].x, p[1].y,
				r.x, r.y,
				bmpdc,
				q[0].x, q[0].y,
				q[1].x, q[1].y,
				new_u, new_v,
				left, top, right, bottom);

			DrawTriangleTexture_FlatTop(
				p[2].x, p[2].y,
				p[1].x, p[1].y,
				r.x, r.y,
				bmpdc,
				q[2].x, q[2].y,
				q[1].x, q[1].y,
				new_u, new_v,
				left, top, right, bottom);
		}
	}
	//三点中的2个点的y值相同
	else
	{
		//让cx0、cy0得到单独的那个点的坐标
		//让cx1、cy1、cx2、cy2得到y值相等的那两个点的坐标，且cx1在cx2左侧
		//经过处理我们一定得到下面的情况
		//			(cx0、cy0)
		//(cx1、cy1)		(cx2、cy2)
		//或
		//(cx1、cy1)		(cx2、cy2)
		//			(cx0、cy0)
		int cx0, cx1, cx2, cy0, cy1, cy2;
		int cu0, cu1, cu2, cv0, cv1, cv2;

		if (y1 == y2)
		{
			cx0 = x0; cy0 = y0;
			cu0 = u0; cv0 = v0;
			if (x1 < x2)
			{
				cx1 = x1; cy1 = y1;
				cu1 = u1; cv1 = v1;
				cx2 = x2; cy2 = y2;
				cu2 = u2; cv2 = v2;
			}
			else
			{
				cx1 = x2; cy1 = y2;
				cu1 = u2; cv1 = v2;
				cx2 = x1; cy2 = y1;
				cu2 = u1; cv2 = v1;
			}
		}
		else if (y0 == y1)
		{
			cx0 = x2; cy0 = y2;
			cu0 = u2; cv0 = v2;
			if (x0 < x1)
			{
				cx1 = x0; cy1 = y0;
				cu1 = u0; cv1 = v0;
				cx2 = x1; cy2 = y1;
				cu2 = u1; cv2 = v1;
			}
			else
			{
				cx1 = x1; cy1 = y1;
				cu1 = u1; cv1 = v1;
				cx2 = x0; cy2 = y0;
				cu2 = u0; cv2 = v0;
			}
		}
		else
		{
			cx0 = x1; cy0 = y1;
			cu0 = u1; cv0 = v1;
			if (x0 < x2)
			{
				cx1 = x0; cy1 = y0;
				cu1 = u0; cv1 = v0;
				cx2 = x2; cy2 = y2;
				cu2 = u2; cv2 = v2;
			}
			else
			{
				cx1 = x2; cy1 = y2;
				cu1 = u2; cv1 = v2;
				cx2 = x0; cy2 = y0;
				cu2 = u0; cv2 = v0;
			}
		}

		//平底三角形
		if (cy0 < cy1)
		{
			DrawTriangleTexture_FlatBottom(
				cx0, cy0,
				cx1, cy1,
				cx2, cy2,
				bmpdc,
				cu0, cv0,
				cu1, cv1,
				cu2, cv2,
				left, top, right, bottom);
		}
		//平顶三角形
		else
		{
			DrawTriangleTexture_FlatTop(
				cx0, cy0,
				cx1, cy1,
				cx2, cy2,
				bmpdc,
				cu0, cv0,
				cu1, cv1,
				cu2, cv2,
				left, top, right, bottom);
		}
	}
}