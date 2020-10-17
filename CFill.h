#pragma once

#include "CAET.h"
#include "CBucket.h"

class CFill
{
public:
	CFill();
	virtual ~CFill();
	void SetPoint(CPoint* p, int);//初始化顶点和顶点数目
	void CreateBucket();//创建桶
	void CreateEdge();//边表
	void AddET(CAET*);//合并ET表
	void ETOrder();//ET表排序
	void Gouraud(CDC*);//填充多边形
	void ClearMemory();//清理内存
	void DeleteAETChain(CAET* pAET);//删除边表
protected:
	int     PNum;//顶点个数
	CPoint* P;//顶点坐标动态数组
	CAET* pHeadE, * pCurrentE, * pEdge; //有效边表结点指针
	CBucket* pHeadB, * pCurrentB;        //桶表结点指针
};