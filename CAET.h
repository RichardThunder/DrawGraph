#pragma once

class CAET
{
public:
	CAET();
	virtual ~CAET();
public:
	double  x;//��ǰɨ��������Ч�߽����x����
	int     yMax;//�ߵ����yֵ
	double  k;//б�ʵĵ���(x������)
	CAET* pNext;
};