#pragma once
#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <queue>
#include <windows.h>

struct Point
{ //记录点
	float x, y;
} point[100];

struct Seed
{
	float x, y;
} seed;

//打点
void pt();
//连线
void DDALine(int x0, int y0, int x1, int y1, int color)
{
	int t;
	float dx, dy, k;
	dx = x1 - x0;
	dy = y1 - y0;
	k = dy / dx;

	if (-1 <= k && k <= 1)
	{ //判断斜率
		if (x1 < x0)
		{ //确定起始点终点
			t = x0, x0 = x1, x1 = t;
			t = y0, y0 = y1, y1 = t;
		}
		int x;
		float y;
		y = y0;
		for (x = x0; x <= x1; x++)
		{
			putpixel(x, int(y + 0.5), color);
			y = y + k;
		}
	}
	else
	{
		if (y1 < y0)
		{ //确定起始点终点
			t = x0, x0 = x1, x1 = t;
			t = y0, y0 = y1, y1 = t;
		}
		int y;
		float x;
		x = x0;
		for (y = y0; y <= y1; y++)
		{
			putpixel(int(x + 0.5), y, color);
			x = x + 1 / k;
		}
	}
}
void Boundfill(int x, int y, int boundarycolor, int newcolor)
{
	int color = getpixel(x, y);
	if (color != newcolor && color != boundarycolor)
	{
		putpixel(x, y, newcolor);
		Boundfill(x, y + 1, boundarycolor, newcolor);
		Boundfill(x, y - 1, boundarycolor, newcolor);
		Boundfill(x - 1, y, boundarycolor, newcolor);
		Boundfill(x + 1, y, boundarycolor, newcolor);
	}
}
//重绘边
void edge(int num, int x, int y)
{
	//再次连线，保证边界为黄色
	for (int n = 1; n < num - 1; n++)
	{
		DDALine(point[n - 1].x, point[n - 1].y, point[n].x, point[n].y, YELLOW);
	}
	DDALine(point[0].x, point[0].y, point[num - 2].x, point[num - 2].y, YELLOW);
	//调用种子填充
	Boundfill(x, y, YELLOW, BLUE);
	//重置点
	pt();
}
