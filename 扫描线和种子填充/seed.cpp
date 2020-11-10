#if 0
#include "Seed.h"
using namespace std;
void main()
{
	initgraph(700, 550);    //初始化图形界面
	MOUSEMSG p;			    //定义一个鼠标的结构体 
	setcolor(YELLOW);
	//鼠标按下则开始运行函数
	while (true)
	{
		p = GetMouseMsg();
		if (p.uMsg == WM_LBUTTONDOWN) pt();//取最后一个点作为种子点,一定要在多边形内,否则会溢出
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
#endif