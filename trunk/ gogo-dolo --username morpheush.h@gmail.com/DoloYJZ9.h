#pragma once
#include "dolo.h"
class CDoloYJZ9 :
	public CDolo
{
public:
	CDoloYJZ9(void);
	~CDoloYJZ9(void);
	bool SearchLayer1(CString &str_url);
	bool SearchLayer3(CString &str_url);
};

