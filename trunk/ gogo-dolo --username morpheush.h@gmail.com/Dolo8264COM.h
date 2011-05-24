#pragma once
#include "dolo.h"
class CDolo8264COM :
	public CDolo
{
public:
	CDolo8264COM(void);
	~CDolo8264COM(void);
	bool SearchLayer1(CString &str_url);
	bool SearchLayer3(CString &str_url);
};

