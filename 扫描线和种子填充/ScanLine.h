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

struct XET
{ //记录边
	float xmin, ymax, ymin;
	float dx;
} pNET[1024];

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
//多边形扫描填色
void drawColor(float a, float b, int y) //扫描画线
{
	int x;
	for (x = a + 0.5; x <= b + 0.5; x++)
		putpixel(x, y, RED);
	Sleep(5);
}
