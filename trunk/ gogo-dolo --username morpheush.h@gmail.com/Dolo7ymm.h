#pragma once
#include "dolo.h"
class CDolo7ymm :
	public CDolo
{
public:
	CDolo7ymm(void);
	~CDolo7ymm(void);

	bool SearchLayer1(CString &str_url);
	bool SearchLayer3(CString &str_url);
};

