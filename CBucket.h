#pragma once

#include "CAET.h"
#include "CBucket.h"

class CBucket
{
public:
	CBucket();
	virtual ~CBucket();
public:
	int     ScanLine;     //扫描线
	CAET* pET;         //桶上的边表指针
	CBucket* pNext;
};