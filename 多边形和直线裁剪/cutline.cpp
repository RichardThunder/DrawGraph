#if 0
#include "cutline.h"
using namespace std;
void main()
{
	CutLine c;
	//设置裁剪框的大小和位置 
	c.xl = 300;
	c.xr = 600;
	c.yt = 600;
	c.yb = 200;
	initgraph(900, 800);    //初始化图形界面
	rectangle(c.xl, c.yt, c.xr, c.yb);
	MOUSEMSG p;			    //定义一个鼠标的结构体 
	setcolor(WHITE);
	//鼠标按下则开始运行函数
	while (true)
	{
		p = GetMouseMsg();
		if (p.uMsg == WM_LBUTTONDOWN) 
		c.point();
	}
}
#endif
