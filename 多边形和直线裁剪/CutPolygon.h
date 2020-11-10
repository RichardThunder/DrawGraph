#pragma once
#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <windows.h>

class CutPolygon
{
public:
	int Sign(int x);
	void point();
	void IntegerBresenhamLine(int x0, int y0, int x1, int y1, unsigned int color);
	void Intersect(POINT S, POINT P, POINT Point0, POINT Point1, POINT &I);
	bool Inside(POINT text, POINT Point0, POINT Point1);
	void Output(POINT newPoint, int &length, POINT outps[]);
	void SutherlandHodgmanPolygonClip(int inlength, POINT inPoints[], int &outlength, POINT outPoints[], POINT Point0, POINT Point1);
	void aline(int num);
	//int max = 30;
	double xl;
	double xr;
	double yb;
	double yt;
	POINT PT[30];
};

void CutPolygon::IntegerBresenhamLine(int x0, int y0, int x1, int y1, unsigned int color)
{
	int x, y, dx, dy, e, sx, sy, Interchange;
	x = x0;
	y = y0;
	dx = abs(x1 - x0), dy = abs(y1 - y0);
	sx = Sign(x1 - x0);
	sy = Sign(y1 - y0);
	if (dy > dx) //将dx,dy统一后方便分类
	{
		int t;
		t = dx;
		dx = dy;
		dy = t;
		Interchange = 1;
	}
	else
		Interchange = 0;
	e = 2 * dy - dx;
	for (int i = 0; i <= dx; i++)
	{
		putpixel(x, y, color);
		while (e > 0)
		{
			if (Interchange == 1)
				x += sx; //更换之后使用x+1，此时现在的x相当于原来的y
			else
				y = y + sy; //不更换使用y+1
			e = e - 2 * dx; //
		}
		if (Interchange == 1)
			y = y + sy;
		else
			x = x + sx;
		e = e + 2 * dy;
	}
}
int CutPolygon::Sign(int x) //判断符号
{
	if (x > 0)
		return 1;
	else if (x == 0)
		return 0;
	else
		return -1;
}

void CutPolygon::Intersect(POINT S, POINT P, POINT Point0, POINT Point1, POINT &I)
{
	if (Point0.y == Point1.y) //水平裁剪边
	{
		I.y = Point0.y;
		I.x = S.x + (Point0.y - S.y) * (P.x - S.x) / (P.y - S.y);
	}
	else //竖直裁剪边
	{
		I.x = Point0.x;
		I.y = S.y + (Point0.x - S.x) * (P.y - S.y) / (P.x - S.x);
	}
}
bool CutPolygon::Inside(POINT text, POINT Point0, POINT Point1)
{
	if (Point1.x > Point0.x)
	{ //裁剪边为窗口的下边
		if (text.y >= Point0.y)
			return true;
	}

	else if (Point1.x < Point0.x)
	{ //裁剪边为窗口的上边
		if (text.y <= Point0.y)
			return true;
	}

	else if (Point1.y > Point0.y)
	{ //裁剪边为窗口的右边
		if (text.x <= Point0.x)
			return true;
	}

	else if (Point1.y < Point0.y)
	{ //裁剪边为窗口的左边
		if (text.x >= Point0.x)
			return true;
	}

	return false;
}
void CutPolygon::Output(POINT newPoint, int &length, POINT outps[])
{
	outps[length].x = newPoint.x;
	outps[length].y = newPoint.y;
	length++;
}

void CutPolygon::SutherlandHodgmanPolygonClip(int inlength, POINT inPoints[], int &outlength, POINT outPoints[], POINT Point0, POINT Point1)
{
	POINT S, P, I;
	int j;
	outlength = 0;
	S = inPoints[inlength - 1];
	for (j = 0; j < inlength; j++)
	{
		P = inPoints[j];
		if (Inside(P, Point0, Point1))
		{
			if (Inside(S, Point0, Point1))
			{
				Output(P, outlength, outPoints);
			}
			else
			{
				Intersect(S, P, Point0, Point1, I);
				Output(I, outlength, outPoints);
				Output(P, outlength, outPoints);
			}
		}
		else if (Inside(S, Point0, Point1))
		{
			Intersect(S, P, Point0, Point1, I);
			Output(I, outlength, outPoints);
		}
		S = P;
	}
}

void CutPolygon::aline(int num)
{
	//连线
	for (int n = 1; n < num; n++)
	{
		IntegerBresenhamLine(PT[n - 1].x, PT[n - 1].y, PT[n].x, PT[n].y, YELLOW);
	}
	IntegerBresenhamLine(PT[0].x, PT[0].y, PT[num - 1].x, PT[num - 1].y, YELLOW);

	POINT Edge[] = {{xr, yb}, {xr, yt}, {xl, yt}, {xl, yb}}; //定义裁剪窗口

	POINT OutPts1[30], OutPts2[30], OutPts3[30], OutPts4[30];
	int length1, length2, length3, length4;

	int inlength = num;

	SutherlandHodgmanPolygonClip(inlength, PT, length1, OutPts1, Edge[0], Edge[1]);		//右边窗口裁剪边
	SutherlandHodgmanPolygonClip(length1, OutPts1, length2, OutPts2, Edge[1], Edge[2]); //下边窗口裁剪边
	SutherlandHodgmanPolygonClip(length2, OutPts2, length3, OutPts3, Edge[2], Edge[3]); //左边窗口裁剪边
	SutherlandHodgmanPolygonClip(length3, OutPts3, length4, OutPts4, Edge[3], Edge[0]); //上边窗口裁剪边

	Sleep(200);
	//连线 覆盖黄色线
	for (int n = 1; n < num; n++)
	{
		IntegerBresenhamLine(PT[n - 1].x, PT[n - 1].y, PT[n].x, PT[n].y, BLACK);
	}
	IntegerBresenhamLine(PT[0].x, PT[0].y, PT[num - 1].x, PT[num - 1].y, BLACK);
	//覆盖点
	for (int n = 0; n < num; n++)
	{
		setcolor(BLACK);
		circle(PT[n].x, PT[n].y, 1);
	}
	//画出裁剪多边形
	setcolor(RED);
	polygon(OutPts4, length4);

	point();
}

void CutPolygon::point()
{

	int N = 0; //记录打点个数

	MOUSEMSG m; // 定义结构体保存鼠标消息

	while (true)
	{
		m = GetMouseMsg(); // 获取一次鼠标消息
		switch (m.uMsg)	   //判断鼠标信息类型
		{
		case WM_LBUTTONDOWN:
			setcolor(YELLOW);
			PT[N].x = m.x;
			PT[N].y = m.y;				 //获取鼠标当前坐标
			circle(PT[N].x, PT[N].y, 1); //绘制点
			N++;
			break;
		case WM_RBUTTONDOWN: //点击进行填充
			aline(N);
		}
	}
}
