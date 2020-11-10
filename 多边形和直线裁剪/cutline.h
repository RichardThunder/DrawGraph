#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#define LEFT 1
#define RIGHT 2
#define BOTTOM 4
#define TOP 8
class CutLine
{
public:
	void IntegerBresenhamLine(int x0, int y0, int x1, int y1, unsigned int color); //IntegerBresenhamLine
	int Sign(int x);
	void point();
	void LineClip(double x1, double y1, double x2, double y2);
	int encode(float x, float y);
	double xl, xr, yt, yb; //设置裁剪框的大小和位置
};

void CutLine::IntegerBresenhamLine(int x0, int y0, int x1, int y1, unsigned int color)
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
int CutLine::Sign(int x) //判断符号
{
	if (x > 0)
		return 1;
	else if (x == 0)
		return 0;
	else
		return -1;
}

void CutLine::point()
{
	int x1, y1, x2, y2;
	MOUSEMSG m; // 定义结构体保存鼠标消息
	while (true)
	{
	flag:
		m = GetMouseMsg(); // 获取一次鼠标消息
		switch (m.uMsg)	   //判断鼠标信息类型
		{
		case WM_LBUTTONDOWN:
			x1 = m.x;
			y1 = m.y; //鼠标第一次按下时，获取鼠标当前坐标
			circle(x1, y1, 1);
			while (true)
			{
				m = GetMouseMsg(); // 再次获取一条鼠标消息
				switch (m.uMsg)
				{
				case WM_LBUTTONDOWN:
					x2 = m.x;
					y2 = m.y; //鼠标第二次按下时,得到坐标
					circle(x2, y2, 1);
					CutLine::IntegerBresenhamLine(x1, y1, x2, y2, RED);
					CutLine::LineClip(x1, y1, x2, y2);
					goto flag; //跳回到flag处进行重置
				}
			}
		}
	}
}
void CutLine::LineClip(double x1, double y1, double x2, double y2)
{
	int code1, code2, code;
	int x, y;
	code1 = encode(x1, y1);
	code2 = encode(x2, y2);
	while (code1 != 0 || code2 != 0)
	{

		if ((code1 & code2) != 0)
			return;
		if (code1 != 0)
			code = code1;
		else
			code = code2;
		if ((LEFT & code) != 0)
		{
			x = xl;
			y = y1 + (y2 - y1) * (xl - x1) / (x2 - x1);
		}
		else if ((RIGHT & code) != 0)
		{
			x = xr;
			y = y1 + (y2 - y1) * (xr - x1) / (x2 - x1);
		}
		else if ((BOTTOM & code) != 0)
		{
			y = yb;
			x = x1 + (x2 - x1) * (yb - y1) / (y2 - y1);
		}
		else if ((TOP & code) != 0)
		{
			y = yt;
			x = x1 + (x2 - x1) * (yt - y1) / (y2 - y1);
		}
		if (code == code1)
		{
			x1 = x;
			y1 = y;
			code1 = encode(x, y);
		}
		else
		{
			x2 = x;
			y2 = y;
			code2 = encode(x, y);
		}
	}
	CutLine::IntegerBresenhamLine(x1, y1, x2, y2, GREEN);
}

int CutLine::encode(float x, float y)
{
	int c = 0;
	if (x < xl)
		c |= LEFT;
	if (x > xr)
		c |= RIGHT;
	if (y < yb)
		c |= BOTTOM;
	if (y > yt)
		c |= TOP;
	return c;
}