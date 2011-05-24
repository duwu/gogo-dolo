#pragma once
#include "dolo.h"
class CDoloMoko :
	public CDolo
{
public:
	CDoloMoko(void);
	~CDoloMoko(void);
	bool SearchLayer1(CString &str_url);
	bool SearchLayer2(CString &str_url);
	bool SearchLayer3(CString &str_url);
	bool GetManfile(CString& file_url);
};

