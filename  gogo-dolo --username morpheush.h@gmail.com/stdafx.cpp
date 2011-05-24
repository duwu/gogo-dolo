// stdafx.cpp : source file that includes just the standard includes
// Dolo.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

vector<struct ST_URL> myUrl;

void initurl()
{
	ST_URL t_Myurl;;
	myUrl.erase(myUrl.begin(),myUrl.end());

	t_Myurl.name=_T("Poco");
	t_Myurl.url=_T("http://www.poco.cn");
	t_Myurl.id=60003;
	myUrl.push_back(t_Myurl);

	t_Myurl.name=_T("Moko");
	t_Myurl.url=_T("http://www.moko.cc");
	t_Myurl.id=60005;
	myUrl.push_back(t_Myurl);

	t_Myurl.name=_T("淘宝画报");
	t_Myurl.url=_T("http://huabao.taobao.com");
	t_Myurl.id=60010;
	myUrl.push_back(t_Myurl);

	t_Myurl.name=_T("淘女郎");
	t_Myurl.url=_T("http://mm.taobao.com");
	t_Myurl.id=60015;
	myUrl.push_back(t_Myurl);

	t_Myurl.name=_T("妖姬宅");
	t_Myurl.url=_T("www.yjz9.com/");
	t_Myurl.id=60020;
	myUrl.push_back(t_Myurl);

	t_Myurl.name=_T("8564户外美女");
	t_Myurl.url=_T("http://www.8264.com/pp/");
	t_Myurl.id=60025;
	myUrl.push_back(t_Myurl);

	t_Myurl.name=_T("7夜美女图片");
	t_Myurl.url=_T("http://www.7ymm.com/");
	t_Myurl.id=60030;
	myUrl.push_back(t_Myurl);

	t_Myurl.name=_T("八百美女");
	t_Myurl.url=_T("http://www.800meinv.com/");
	t_Myurl.id=60035;
	myUrl.push_back(t_Myurl);

}
