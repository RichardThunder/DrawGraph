#pragma once

#include "CAET.h"
#include "CBucket.h"

class CBucket
{
public:
	CBucket();
	virtual ~CBucket();
public:
	int     ScanLine;     //ɨ����
	CAET* pET;         //Ͱ�ϵı߱�ָ��
	CBucket* pNext;
};