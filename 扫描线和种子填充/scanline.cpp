#if 0
#include "ScanLine.h"
using namespace std;
//优先队列保存某条扫描线上的x值
priority_queue<float, vector<float>, greater<float> >s;
int MaxY = 0;
int MinY = 2000;
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

//扫描填充算法
void polyfill(int num)
{
	//连线
	for (int n = 1; n < num; n++)
	{
		DDALine(point[n - 1].x, point[n - 1].y, point[n].x, point[n].y, YELLOW);
	}
	DDALine(point[0].x, point[0].y, point[num - 1].x, point[num - 1].y, YELLOW);

	int i, j, k, t = 0;
	// 获取最大y,最小y
	for (k = 0; k < num; k++)
	{
		if (point[k].y > MaxY)
		{
			MaxY = point[k].y;
		}

		if (point[k].y < MinY)
		{
			MinY = point[k].y;
		}
	}
	//获取边信息
	for (i = MinY; i <= MaxY; i++)
	{
		for (j = 0; j < num; j++)
		{
			if (point[j].y == i)
			{
				//按逆时针，某顶点的前一个顶点
				if (point[(j - 1 + num) % num].y > point[j].y)
				{
					struct XET p;
					p.xmin = point[j].x;
					p.ymax = point[(j - 1 + num) % num].y;
					p.ymin = point[j].y;
					p.dx = (point[(j - 1 + num) % num].x - point[j].x) / (point[(j - 1 + num) % num].y - point[j].y);
					//判断是否为局部最值
					if (point[(j + 1 + num) % num].y <= point[j].y)
						p.ymin++;
					pNET[t++] = p;
				}
				//按逆时针，某顶点的后一个顶点
				if (point[(j + 1 + num) % num].y > point[j].y)
				{
					struct XET p;
					p.xmin = point[j].x;
					p.ymax = point[(j + 1 + num) % num].y;
					p.ymin = point[j].y;
					p.dx = (point[(j + 1 + num) % num].x - point[j].x) / (point[(j + 1 + num) % num].y - point[j].y);
					//判断是否为局部最值
					if (point[(j - 1 + num) % num].y <= point[j].y)
						p.ymin++;
					pNET[t++] = p;
				}
			}
		}
	}
	//扫描线
	for (i = MinY; i <= MaxY; i++)
	{
		for (j = 0; j < t; j++)
		{
			//当前扫描线在某条边之间
			if (pNET[j].ymin <= i && pNET[j].ymax >= i)
			{
				s.push(pNET[j].xmin);
				//更新xmin坐标
				pNET[j].xmin += pNET[j].dx;
			}
		}
		//填色
		while (!s.empty())
		{	//每两个一对,a,b均为扫描线上的x坐标
			float a = s.top(); s.pop();
			float b = s.top(); s.pop();
			drawColor(a, b, i);
		}
	}

}

void pt()//鼠标响应
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
			polyfill(N); //扫描线算法

			break;
		}

	}
}
#endif
