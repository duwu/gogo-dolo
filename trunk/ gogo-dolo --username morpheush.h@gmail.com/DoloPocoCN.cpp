#include "StdAfx.h"
#include "DoloPocoCN.h"


CDoloPocoCN::CDoloPocoCN(void)
{
	CreateDirectory(_T("Poco"),NULL);
}


CDoloPocoCN::~CDoloPocoCN(void)
{
}


bool CDoloPocoCN::SearchLayer1(CString &str_url)
{
	return true;
}
//暂时找到两个下载链接
bool CDoloPocoCN::SearchLayer3(CString &str_url)
{
	CString tmp_str;
	CString cs_webContent;
	CString cs_album_name;	//主目录名字
	int photo_num=0;		//像册数量
	tmp_str = str_url;
	DownloadUrlPage(tmp_str,cs_webContent);

	if(str_url.Find(_T("album_show_photo_list"),0)>-1)
	{
		if(cs_webContent.Find(_T("张 )"),0)>-1)
		{
			CString str;
			str = cs_webContent.Right(cs_webContent.GetLength()-cs_webContent.Find(_T("张 )"),0)-4);
			int m_temp=str.Find(_T("页"),0);
			str = str.Left(m_temp);
			photo_num=atoi(str);
		}
	}
	//获得用户名-------------------------------------------------cs_album_name
	int m_temp = cs_webContent.Find(_T("poco_share_title"),0);
	if( m_temp >-1)
	{
		cs_album_name=cs_webContent.Right(cs_webContent.GetLength()-m_temp-20);
		cs_album_name=cs_album_name.Left(cs_album_name.Find(_T("'"),0));
		checkDirname(cs_album_name);
		CreateDirectory(_T("Poco\\")+cs_album_name,NULL);
	}
	else if(cs_webContent.Find(_T("<title>"),0))
	{
		cs_album_name=cs_webContent.Right(cs_webContent.GetLength()-cs_webContent.Find(_T("<title>"),0)-7);
		cs_album_name=cs_album_name.Left(cs_album_name.Find(_T("_"),0));
		checkDirname(cs_album_name);
		CreateDirectory(_T("Poco\\")+cs_album_name,NULL);
	}
	else
		return false;
	//开始下载
	{
// 		cs_webContent.Empty();
// 		DownloadUrlPage(str_url,cs_webContent);
//		checkDirname(cs_album_name);
		//regex reg("((?<=src=')[^\\s]*.jpg)|((?<=].src = ')[^\\s]*.jpg)");  	//图片模式
		regex reg("orgimg = 'http://[^\\s]*jpg|src=\"http://[^\\s]*_165.jpg");  	//图片模式

		smatch m1; 
		string s = cs_webContent.GetBuffer();	
		string::const_iterator it = s.begin(); 
		string::const_iterator end=s.end();
		while(regex_search(it,end,m1,reg))
		{
			string msg(m1[0].first,m1[0].second);
			string s="orgimg";
			string::size_type i=msg.find(s);
			if(i!=string::npos)
				msg.erase(0,10);
			else{ 
				s="_165";
				if(msg.find(s)!=string::npos)
				{
					msg.erase(0,5);
					msg.erase(msg.size()-8,4);
				}
			}
			s_dolo.cs_url=msg.c_str();
			s_dolo.cs_LocalFullPath=_T("Poco\\")+cs_album_name;
			s_dolo.cs_ReferHead=_T("");	//_T("Referer: http://www.800meinv.com");
			v_doloST.push_back(s_dolo); 
			it = m1[0].second; 
		}
	}
	return true;
}