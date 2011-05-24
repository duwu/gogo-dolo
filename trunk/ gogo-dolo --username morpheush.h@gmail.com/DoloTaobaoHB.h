#pragma once
#include "dolo.h"
class CDoloTaobaoHB :
	public CDolo
{
public:
	CDoloTaobaoHB(void);
	~CDoloTaobaoHB(void);
	bool SearchLayer1(CString &str_url);
	bool SearchLayer3(CString &str_url);
};

