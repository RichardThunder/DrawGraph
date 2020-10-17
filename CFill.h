#pragma once

#include "CAET.h"
#include "CBucket.h"

class CFill
{
public:
	CFill();
	virtual ~CFill();
	void SetPoint(CPoint* p, int);//��ʼ������Ͷ�����Ŀ
	void CreateBucket();//����Ͱ
	void CreateEdge();//�߱�
	void AddET(CAET*);//�ϲ�ET��
	void ETOrder();//ET������
	void Gouraud(CDC*);//�������
	void ClearMemory();//�����ڴ�
	void DeleteAETChain(CAET* pAET);//ɾ���߱�
protected:
	int     PNum;//�������
	CPoint* P;//�������궯̬����
	CAET* pHeadE, * pCurrentE, * pEdge; //��Ч�߱���ָ��
	CBucket* pHeadB, * pCurrentB;        //Ͱ����ָ��
};