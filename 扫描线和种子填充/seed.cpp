#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <queue>
#include <windows.h>

using namespace std;

struct Point
{    //记录点
	float x, y;
}point[100];

struct Seed
{
	float x, y;
}seed;

struct XET
{       //记录边
	float xmin, ymax, ymin;
	float dx;
}pNET[1024];

//优先队列保存某条扫描线上的x值
priority_queue<float, vector<float>, greater<float> >s;

int MaxY = 0;
int MinY = 2000;
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
	{  //判断斜率
		if (x1 < x0)
		{  //确定起始点终点
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
		{  //确定起始点终点
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
	for (int n = 1; n < num-1; n++)
	{
		DDALine(point[n - 1].x, point[n - 1].y, point[n].x, point[n].y, YELLOW);
	}
	DDALine(point[0].x, point[0].y, point[num - 2].x, point[num - 2].y, YELLOW);
	//调用种子填充
	Boundfill(x, y, YELLOW, BLUE);
	//重置点
	pt();
}

void main()
{
	initgraph(700, 550);    //初始化图形界面
	MOUSEMSG p;			    //定义一个鼠标的结构体 
	setcolor(YELLOW);
	//鼠标按下则开始运行函数
	while (true)
	{
		p = GetMouseMsg();
		if (p.uMsg == WM_LBUTTONDOWN) pt();
	}
}

void pt()
{
	int N = 0;         //记录打点个数

	MOUSEMSG m;        // 定义结构体保存鼠标消息 

	while (true)
	{
		m = GetMouseMsg();             // 获取一次鼠标消息
		switch (m.uMsg)                //判断鼠标信息类型
		{
		case WM_LBUTTONDOWN:
			point[N].x = m.x; point[N].y = m.y;    //获取鼠标当前坐标
			circle(point[N].x, point[N].y, 1);     //绘制点
			N++;
			break;
		case WM_RBUTTONDOWN:	  //点击进行填充
			setcolor(WHITE);
			circle(point[N - 1].x, point[N - 1].y, 1);
			edge(N, point[N - 1].x, point[N - 1].y);
		
			break;
		}
	}
}