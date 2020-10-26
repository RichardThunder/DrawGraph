#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <queue>
#include <windows.h>

using namespace std;

struct Point
{    //��¼��
	float x, y;
}point[100];

struct Seed
{
	float x, y;
}seed;

struct XET
{       //��¼��
	float xmin, ymax, ymin;
	float dx;
}pNET[1024];

//���ȶ��б���ĳ��ɨ�����ϵ�xֵ
priority_queue<float, vector<float>, greater<float> >s;

int MaxY = 0;
int MinY = 2000;
//���
void pt();
//����
void DDALine(int x0, int y0, int x1, int y1, int color)
{
	int t;
	float dx, dy, k;
	dx = x1 - x0;
	dy = y1 - y0;
	k = dy / dx;

	if (-1 <= k && k <= 1)
	{  //�ж�б��
		if (x1 < x0)
		{  //ȷ����ʼ���յ�
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
		{  //ȷ����ʼ���յ�
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
//�ػ��
void edge(int num, int x, int y)
{
	//�ٴ����ߣ���֤�߽�Ϊ��ɫ
	for (int n = 1; n < num-1; n++)
	{
		DDALine(point[n - 1].x, point[n - 1].y, point[n].x, point[n].y, YELLOW);
	}
	DDALine(point[0].x, point[0].y, point[num - 2].x, point[num - 2].y, YELLOW);
	//�����������
	Boundfill(x, y, YELLOW, BLUE);
	//���õ�
	pt();
}

void main()
{
	initgraph(700, 550);    //��ʼ��ͼ�ν���
	MOUSEMSG p;			    //����һ�����Ľṹ�� 
	setcolor(YELLOW);
	//��갴����ʼ���к���
	while (true)
	{
		p = GetMouseMsg();
		if (p.uMsg == WM_LBUTTONDOWN) pt();
	}
}

void pt()
{
	int N = 0;         //��¼������

	MOUSEMSG m;        // ����ṹ�屣�������Ϣ 

	while (true)
	{
		m = GetMouseMsg();             // ��ȡһ�������Ϣ
		switch (m.uMsg)                //�ж������Ϣ����
		{
		case WM_LBUTTONDOWN:
			point[N].x = m.x; point[N].y = m.y;    //��ȡ��굱ǰ����
			circle(point[N].x, point[N].y, 1);     //���Ƶ�
			N++;
			break;
		case WM_RBUTTONDOWN:	  //����������
			setcolor(WHITE);
			circle(point[N - 1].x, point[N - 1].y, 1);
			edge(N, point[N - 1].x, point[N - 1].y);
		
			break;
		}
	}
}