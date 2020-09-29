
// DrawGraphView.cpp: CDrawGraphView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "DrawGraph.h"
#endif

#include "DrawGraphDoc.h"
#include "DrawGraphView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "ClassView.h"
#define RED RGB(255,0,0)
#define GREEN RGB(0,255,0)
#define BLUE RGB(0,0,255)
#define DRAWLINE 1
#define DRAWCIRCLE 2

// CDrawGraphView

IMPLEMENT_DYNCREATE(CDrawGraphView, CView)

BEGIN_MESSAGE_MAP(CDrawGraphView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CDrawGraphView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_MBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_DDA, &CDrawGraphView::OnDDA)
	ON_COMMAND(ID_MiddleDraw, &CDrawGraphView::OnMiddledraw)
	ON_COMMAND(ID_bresenham, &CDrawGraphView::OnBresenhamLine)
	ON_COMMAND(ID_CircleMiddle, &CDrawGraphView::OnCircleMiddle)
	ON_COMMAND(ID_CircleBresenham, &CDrawGraphView::OnCircleBresenham)
	ON_COMMAND(ID_OvalMiddle, &CDrawGraphView::OnOvalMiddle)
END_MESSAGE_MAP()

// CDrawGraphView 构造/析构

CDrawGraphView::CDrawGraphView() noexcept
{
	// TODO: 在此处添加构造代码

}

CDrawGraphView::~CDrawGraphView()
{}

BOOL CDrawGraphView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CDrawGraphView 绘图

void CDrawGraphView::OnDraw(CDC* /*pDC*/)
{
	CDrawGraphDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CDrawGraphView 打印


void CDrawGraphView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CDrawGraphView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CDrawGraphView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CDrawGraphView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CDrawGraphView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CDrawGraphView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CDrawGraphView 诊断

#ifdef _DEBUG
void CDrawGraphView::AssertValid() const
{
	CView::AssertValid();
}

void CDrawGraphView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDrawGraphDoc* CDrawGraphView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrawGraphDoc)));
	return (CDrawGraphDoc*)m_pDocument;
}
#endif //_DEBUG


// CDrawGraphView 消息处理程序



void CDrawGraphView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CView::OnLButtonDown(nFlags, point);
	m_point1 = point;
}


void CDrawGraphView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CView::OnLButtonUp(nFlags, point);
	CView::OnLButtonUp(nFlags, point);
	HWND hWnd = AfxGetMainWnd()->m_hWnd;
	HDC hdc = ::GetDC(m_hWnd);
	m_point2 = point;

	//选择绘制算法

	switch (Choose)
	{
	case 0:
		DDALine(hdc, m_point1.x, m_point1.y, m_point2.x, m_point2.y, RED);
		break;
	case 1:
		MidpointLine(hdc, m_point1.x, m_point1.y, m_point2.x, m_point2.y, GREEN);
		break;
	case 2:
		IntegerBresenhamLine(hdc, m_point1.x, m_point1.y, m_point2.x, m_point2.y, BLUE);
		break;
	case 3:
		CircleMiddle(hdc, m_point1.x, m_point1.y, m_point2.x, m_point2.y, RED);
		break;
	default:
		break;
	}
	DeleteDC(hdc);
}




void CDrawGraphView::DDALine(HDC hdc, int x0, int y0, int x1, int y1, int color)
{
	float dx, dy, k;
	dx = x1 - x0, dy = y1 - y0;
	if (abs(dx) > abs(dy))
	{
		int x;
		float y;
		k = dy / dx;
		if (x0 <= x1)
		{
			y = y0;
			for (x = x0; x <= x1; x++)
			{
				SetPixel(hdc, x, int(y + 0.5), color);
				y = y + k;
			}
		}
		else
		{
			y = y1;
			for (x = x1; x <= x0; x++)
			{
				SetPixel(hdc, x, int(y + 0.5), color);
				y = y + k;
			}
		}
	}
	else
	{
		int y;
		float x;
		k = dx / dy;
		if (y0 <= y1)
		{
			x = x0;
			for (y = y0; y <= y1; y++)
			{
				SetPixel(hdc, int(x + 0.5), y, color);
				x = x + k;
			}
		}
		else
		{
			x = x1;
			for (y = y1; y <= y0; y++)
			{
				SetPixel(hdc, int(x + 0.5), y, color);
				x = x + k;
			}
		}
	}
}
void CDrawGraphView::MidpointLine(HDC hdc, int x0, int y0, int x1, int y1, int color)
{
	int a, b, d1, d2, d, x, y;

	float  dx, dy, k;
	dx = x1 - x0;
	dy = y1 - y0;
	k = dy / dx;//判断方向
	if (abs(dx) > abs(dy))//用x
	{
		if (x0 < x1)
		{
			if (k >= 0)
			{
				a = y0 - y1, b = x1 - x0, d = 2 * a + b;
				d1 = 2 * a, d2 = 2 * (a + b);
				x = x0, y = y0;
				SetPixel(hdc, x, y, color);
				while (x < x1)
				{
					if (d < 0)
					{
						x++, y++, d += d2;
					}
					else
					{
						x++, d += d1;
					}
					SetPixel(hdc, x, y, color);
				}
			}
			else
			{
				a = y1 - y0, b = x1 - x0, d = 2 * a + b;
				d1 = 2 * a, d2 = 2 * (a + b);
				x = x0, y = y0;
				SetPixel(hdc, x, y, color);
				while (x < x1)
				{
					if (d < 0)
					{
						x++, y--, d += d2;
					}
					else
					{
						x++, d += d1;
					}
					SetPixel(hdc, x, y, color);
				}
			}
		}
		else
		{
			if (k >= 0)
			{
				a = y1 - y0, b = x0 - x1, d = 2 * a + b;
				d1 = 2 * a, d2 = 2 * (a + b);
				x = x1, y = y1;
				SetPixel(hdc, x, y, color);
				while (x < x0)
				{
					if (d < 0)
					{
						x++, y++, d += d2;
					}
					else
					{
						x++, d += d1;
					}
					SetPixel(hdc, x, y, color);
				}
			}
			else
			{
				a = y0 - y1, b = x0 - x1, d = 2 * a + b;
				d1 = 2 * a, d2 = 2 * (a + b);
				x = x1, y = y1;
				SetPixel(hdc, x, y, color);
				while (x < x0)
				{
					if (d < 0)
					{
						x++, y--, d += d2;
					}
					else
					{
						x++, d += d1;
					}
					SetPixel(hdc, x, y, color);
				}

			}
		}
	}
	else//dx<dy用y
	{
		if (y0 < y1)
		{
			if (k >= 0)
			{
				a = x0 - x1, b = y1 - y0, d = 2 * a + b;
				d1 = 2 * a, d2 = 2 * (a + b);
				y = y0, x = x0;
				SetPixel(hdc, x, y, color);
				while (y < y1)
				{
					if (d < 0)
					{
						y++, x++, d += d2;
					}
					else
					{
						y++, d += d1;
					}
					SetPixel(hdc, x, y, color);
				}
			}
			else
			{
				a = x1 - x0, b = y1 - y0, d = 2 * a + b;
				d1 = 2 * a, d2 = 2 * (a + b);
				y = y0, x = x0;
				SetPixel(hdc, x, y, color);
				while (y < y1)
				{
					if (d < 0)
					{
						y++, x--, d += d2;
					}
					else
					{
						y++, d += d1;
					}
					SetPixel(hdc, x, y, color);
				}
			}
		}
		else
		{
			if (k >= 0)
			{
				a = x1 - x0, b = y0 - y1, d = 2 * a + b;
				d1 = 2 * a, d2 = 2 * (a + b);
				y = y1, x = x1;
				SetPixel(hdc, x, y, color);
				while (y < y0)
				{
					if (d < 0)
					{
						y++, x++, d += d2;
					}
					else
					{
						y++, d += d1;
					}
					SetPixel(hdc, x, y, color);
				}
			}
			else
			{
				a = x0 - x1, b = y0 - y1, d = 2 * a + b;
				d1 = 2 * a, d2 = 2 * (a + b);
				y = y1, x = x1;
				SetPixel(hdc, x, y, color);
				while (y < y0)
				{
					if (d < 0)
					{
						y++, x--, d += d2;
					}
					else
					{
						y++, d += d1;
					}
					SetPixel(hdc, x, y, color);
				}

			}
		}
	}
}
void CDrawGraphView::IntegerBresenhamLine(HDC hdc, int x0, int y0, int x1, int y1, int color)
{
	int x, y, dx, dy, e, sx, sy, Interchange;
	x = x0;
	y = y0;
	dx = abs(x1 - x0), dy = abs(y1 - y0);
	sx = Sign(x1 - x0);
	sy = Sign(y1 - y0);
	if (dy > dx)//将dx,dy统一后方便分类
	{
		int t;
		t = dx;
		dx = dy;
		dy = t;
		Interchange = 1;
	}
	else Interchange = 0;
	e = 2 * dy - dx;
	for (int i = 0; i <= dx; i++)
	{
		SetPixel(hdc, x, y, color);
		while (e > 0)
		{
			if (Interchange == 1)
				x += sx;//更换之后使用x+1，此时现在的x相当于原来的y
			else y = y + sy;//不更换使用y+1
			e = e - 2 * dx;//
		}
		if (Interchange == 1)
			y = y + sy;
		else
			x = x + sx;
		e = e + 2 * dy;
	}
}
void CDrawGraphView::CircleMiddle(HDC hdc, int x0, int y0, int x1, int y1, int color)
{
	int x, y;
	float d;
	y = CircleInit(x0, y0, x1, y1);
	x = 0; d = 1.25 - y;
	CirclePoints(hdc, x, y, color); //显示圆弧上的八个对称点
	while (x <= y)
	{
		if (d < 0)   d += 2 * x + 3;
		else
		{
			d += 2 * (x - y) + 5;  y--;
		}
		x++;
		CirclePoints(hdc, x, y, color);
	}

}
void CDrawGraphView::CircleBresenham(HDC hdc, int x0, int y0, int x1, int y1, int color)
{

}
void CDrawGraphView::OvalMiddle(HDC hdc, int x0, int y0, int x1, int y1, int color)
{

}
int CDrawGraphView::Sign(int x)//判断符号
{
	if (x > 0) return 1;
	else if (x == 0) return 0;
	else  return -1;
}

void CDrawGraphView::CirclePoints(HDC hdc, int x, int y, int color)//圆的8对称点画法实现
{
	SetPixel(hdc, x + m_point1.x, y + m_point1.y, color);
	SetPixel(hdc, y + m_point1.x, x + m_point1.y, color);
	SetPixel(hdc, -x + m_point1.x, y + m_point1.y, color);
	SetPixel(hdc, y + m_point1.x, -x + m_point1.y, color);
	SetPixel(hdc, x + m_point1.x, -y + m_point1.y, color);
	SetPixel(hdc, -y + m_point1.x, x + m_point1.y, color);
	SetPixel(hdc, -x + m_point1.x, -y + m_point1.y, color);
	SetPixel(hdc, -y + m_point1.x, -x + m_point1.y, color);
}
int CDrawGraphView::CircleInit(int x0, int y0, int x1, int y1)
{
	int r = 0;
	r = sqrt((x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1));
	return r;
}
void CDrawGraphView::OnDDA()
{
	// TODO: 在此添加命令处理程序代码
	Choose = 0;
}
void CDrawGraphView::OnMiddledraw()
{
	// TODO: 在此添加命令处理程序代码
	Choose = 1;
}
void CDrawGraphView::OnBresenhamLine()
{
	// TODO: 在此添加命令处理程序代码
	Choose = 2;
}
void CDrawGraphView::OnCircleMiddle()
{
	// TODO: 在此添加命令处理程序代码
	Choose = 3;
}
void CDrawGraphView::OnCircleBresenham()
{
	// TODO: 在此添加命令处理程序代码
	Choose = 4;

}
void CDrawGraphView::OnOvalMiddle()
{
	// TODO: 在此添加命令处理程序代码
	Choose = 5;
}
