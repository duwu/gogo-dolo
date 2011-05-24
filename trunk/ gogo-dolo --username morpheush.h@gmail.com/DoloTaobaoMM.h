#pragma once
#include "dolo.h"
class CDoloTaobaoMM :
	public CDolo
{
public:
	CDoloTaobaoMM(void);
	~CDoloTaobaoMM(void);
	bool SearchLayer1(CString &str_url);
	bool SearchLayer3(CString &str_url);
};

