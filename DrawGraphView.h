
// DrawGraphView.h: CDrawGraphView 类的接口
//

#pragma once


class CDrawGraphView : public CView
{
protected: // 仅从序列化创建
	CDrawGraphView() noexcept;
	DECLARE_DYNCREATE(CDrawGraphView)

// 特性
public:
	CDrawGraphDoc* GetDocument() const;
	CPoint m_point1;
	CPoint m_point2;
	void DDALine(HDC hdc, int x0, int y0, int x1, int y1, int color);
	void MidpointLine(HDC hdc, int x0, int y0, int x1, int y1, int color);
	void IntegerBresenhamLine(HDC hdc, int x0, int y0, int x1, int y1, int color);
	void CircleMiddle(HDC hdc, int x0, int y0, int x1, int y1, int color);
	void CircleBresenham(HDC hdc, int x0, int y0, int x1, int y1, int color);
	void OvalMiddle(HDC hdc, int x0, int y0, int x1, int y1, int color);
	int Sign(int x);
	void CirclePoints(HDC hdc, int x, int y, int color);//圆的8对称性画点
	int CircleInit(int x0, int y0, int x1, int y1);
	int Choose = 0;
	int Type=0;
// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CDrawGraphView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnDDA();
	afx_msg void OnMiddledraw();
	afx_msg void OnBresenhamLine();
	afx_msg void OnCircleMiddle();
	afx_msg void OnCircleBresenham();
	afx_msg void OnOvalMiddle();
};

#ifndef _DEBUG  // DrawGraphView.cpp 中的调试版本
inline CDrawGraphDoc* CDrawGraphView::GetDocument() const
   { return reinterpret_cast<CDrawGraphDoc*>(m_pDocument); }
#endif

