#pragma once
#include "dolo.h"
class CDolo800meinv :
	public CDolo
{
public:
	CDolo800meinv(void);
	~CDolo800meinv(void);

	bool SearchLayer1(CString &str_url);
	bool SearchLayer3(CString &str_url);
};

