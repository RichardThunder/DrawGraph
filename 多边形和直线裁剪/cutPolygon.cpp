#if 0
#include "CutPolygon.h"
using namespace std;
void main()
{
	initgraph(700, 700); //初始化图形界面
	CutPolygon C;
	//设置裁剪框的大小和位置
	C.xl = 100;
	C.xr = 550;
	C.yb = 150;
	C.yt = 550;
	rectangle(C.xl, C.yt, C.xr, C.yb);
	MOUSEMSG p; //定义一个鼠标的结构体
	//鼠标按下则开始运行函数
	while (true)
	{
		p = GetMouseMsg();
		if (p.uMsg == WM_LBUTTONDOWN)
			C.point(); //绘制
	}
}

#endif
