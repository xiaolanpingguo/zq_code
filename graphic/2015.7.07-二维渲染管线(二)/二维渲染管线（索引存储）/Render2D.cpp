#include "Render2D.h"

CMatrix3 g_Matrix[3];
int left, top, right, bottom;

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
	t[1].Rotate(at->x < eye->x ? +angle : -angle);

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

void SetView(int d_left,
			 int d_top,
			 int d_width,
			 int d_height)
{
	left = d_left;
	top = d_top;
	right = d_left + d_width - 1;
	bottom = d_top + d_height - 1;
}

void SetMatrix(int type, const CMatrix3* m)
{
	if (type >= _WORLD_MATRIX && type <= _VIEW_MATRIX)
		g_Matrix[type] = *m;
}

bool LoadMODAL2D(MODAL2D* modal2d, const char* file)
{
	//得到文件内容
	FILE* pf = 0;
	fopen_s(&pf, file, "rb");
	if (!pf)
		return false;
	fseek(pf, 0, SEEK_END);
	int fs1 = ftell(pf);
	rewind(pf);
	char* fd1 = new char[fs1 + 1];
	fread(fd1, 1, fs1, pf);
	fclose(pf);
	fd1[fs1] = 0;

	//过滤非打印字符并得到顶点个数、三角形个数
	char* fd2 = new char[fs1 + 1];
	int fs2 = 0;
	int vn = 0;
	int tn = 0;
	for (int i = 0; i < fs1 + 1; ++i)
	{
		if (fd1[i] > ' ')
		{
			if (fd1[i] == '(')
				vn += 1;
			if (fd1[i] == '[')
				tn += 1;
			fd2[fs2++] = fd1[i];
		}
	}
	fd2[fs2] = 0;
	delete [] fd1;

	//提取顶点数据
	modal2d->v_coordinate.clear();
	modal2d->t_coordinate.clear();
	char* p = fd2;
	for (int i = 0; i < vn; ++i)
	{
		CVector2 v, t;

		//得到顶点x坐标
		char* b = p + 1;
		char* e = strchr(b, ',');
		*e = 0;
		v.x = (float)atof(b);

		//得到顶点y坐标
		b = e + 1;
		e = strchr(b, ',');
		*e = 0;
		v.y = (float)atof(b);

		//得到顶点u坐标
		b = e + 1;
		e = strchr(b, ',');
		*e = 0;
		t.x = (float)atof(b);

		//得到顶点v坐标
		b = e + 1;
		e = strchr(b, ')');
		*e = 0;
		t.y = (float)atof(b);

		modal2d->v_coordinate.push_back(v);
		modal2d->t_coordinate.push_back(t);

		p = e + 1;
	}

	//提取三角形索引
	modal2d->t_index.clear();
	for (int i = 0; i < tn; ++i)
	{
		_MODAL_2D::_TRIANGLE triangle;

		char* b = p + 1;
		char* e = strchr(b, ',');
		*e = 0;
		triangle.i[0] = atoi(b);

		b = e + 1;
		e = strchr(b, ',');
		*e = 0;
		triangle.i[1] = atoi(b);

		b = e + 1;
		e = strchr(b, ']');
		*e = 0;
		triangle.i[2] = atoi(b);

		p = e + 1;

		modal2d->t_index.push_back(triangle);
	}

	delete [] fd2;
	return true;
}

static void DrawTriangleTexture_FlatBottom(HDC destdc,
										   int x0, int y0,
										   int x1, int y1,
										   int x2, int y2,
										   HDC bmpdc,
										   int u0, int v0,
										   int u1, int v1,
										   int u2, int v2)
{
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
			SetPixel(destdc, x, y, c);
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

static void DrawTriangleTexture_FlatTop(HDC destdc,
										int x0, int y0,
										int x1, int y1,
										int x2, int y2,
										HDC bmpdc,
										int u0, int v0,
										int u1, int v1,
										int u2, int v2)
{
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
			SetPixel(destdc, x, y, c);
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

static void DrawTriangleTexture(HDC destdc,
								int x0, int y0,
								int x1, int y1,
								int x2, int y2,
								HDC bmpdc,
								int u0, int v0,
								int u1, int v1,
								int u2, int v2)
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
				destdc,
				p[0].x, p[0].y,
				r.x, r.y,
				p[1].x, p[1].y,
				bmpdc,
				q[0].x, q[0].y,
				new_u, new_v,
				q[1].x, q[1].y);

			DrawTriangleTexture_FlatTop(
				destdc,
				p[2].x, p[2].y,
				r.x, r.y,
				p[1].x, p[1].y,
				bmpdc,
				q[2].x, q[2].y,
				new_u, new_v,
				q[1].x, q[1].y);
		}
		else
		{
			// p[0]
			//p[1] r
			// p[2]

			DrawTriangleTexture_FlatBottom(
				destdc,
				p[0].x, p[0].y,
				p[1].x, p[1].y,
				r.x, r.y,
				bmpdc,
				q[0].x, q[0].y,
				q[1].x, q[1].y,
				new_u, new_v);

			DrawTriangleTexture_FlatTop(
				destdc,
				p[2].x, p[2].y,
				p[1].x, p[1].y,
				r.x, r.y,
				bmpdc,
				q[2].x, q[2].y,
				q[1].x, q[1].y,
				new_u, new_v);
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
				destdc,
				cx0, cy0,
				cx1, cy1,
				cx2, cy2,
				bmpdc,
				cu0, cv0,
				cu1, cv1,
				cu2, cv2);
		}
		//平顶三角形
		else
		{
			DrawTriangleTexture_FlatTop(
				destdc,
				cx0, cy0,
				cx1, cy1,
				cx2, cy2,
				bmpdc,
				cu0, cv0,
				cu1, cv1,
				cu2, cv2);
		}
	}
}

void DrawMODAL2D(HDC destdc, MODAL2D* modal2d, HDC texture)
{
	//得到顶点数量
	int vn = (int)modal2d->v_coordinate.size();

	//准备各个坐标系下的顶点
	std::vector<CVector2> w, c, v, uv;
	w.resize(vn);
	c.resize(vn);
	v.resize(vn);
	uv.resize(modal2d->t_coordinate.size());

	//世界变换
	for (int i = 0; i < vn; ++i)
		_Vec_X_Mat(&modal2d->v_coordinate[i], &g_Matrix[_WORLD_MATRIX], &w[i]);

	//摄像机变换
	for (int i = 0; i < vn; ++i)
		_Vec_X_Mat(&w[i], &g_Matrix[_CAMERA_MATRIX], &c[i]);

	//视口变换
	for (int i = 0; i < vn; ++i)
		_Vec_X_Mat(&c[i], &g_Matrix[_VIEW_MATRIX], &v[i]);

	//处理uv坐标
	HBITMAP hbmp = (HBITMAP)GetCurrentObject(texture, OBJ_BITMAP);
	BITMAP bmp;
	GetObject(hbmp, sizeof(bmp), &bmp);
	for (int i = 0; i < (int)uv.size(); ++i)
	{
		uv[i].x = modal2d->t_coordinate[i].x * bmp.bmWidth;
		uv[i].y = modal2d->t_coordinate[i].y * bmp.bmHeight;
	}

	//绘制三角形
	for (int i = 0; i < (int)modal2d->t_index.size(); ++i)
	{
		v[modal2d->t_index[i].i[0]].x, 

		DrawTriangleTexture(
			destdc,
			v[modal2d->t_index[i].i[0]].x, v[modal2d->t_index[i].i[0]].y,
			v[modal2d->t_index[i].i[1]].x, v[modal2d->t_index[i].i[1]].y,
			v[modal2d->t_index[i].i[2]].x, v[modal2d->t_index[i].i[2]].y,
			texture,
			uv[modal2d->t_index[i].i[0]].x, uv[modal2d->t_index[i].i[0]].y,
			uv[modal2d->t_index[i].i[1]].x, uv[modal2d->t_index[i].i[1]].y,
			uv[modal2d->t_index[i].i[2]].x, uv[modal2d->t_index[i].i[2]].y);
	}
}