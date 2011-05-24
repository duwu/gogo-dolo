#pragma once
#include "dolo.h"
class CDoloPocoCN :
	public CDolo
{
public:
	CDoloPocoCN(void);
	~CDoloPocoCN(void);

	bool SearchLayer1(CString &str_url);
	bool SearchLayer3(CString &str_url);
};

