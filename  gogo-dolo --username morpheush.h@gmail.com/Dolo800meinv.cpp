#include "StdAfx.h"
#include "Dolo800meinv.h"


CDolo800meinv::CDolo800meinv(void)
{
	CreateDirectory(_T("八百美女"),NULL);
}


CDolo800meinv::~CDolo800meinv(void)
{
}


bool CDolo800meinv::SearchLayer1(CString &str_url)
{
	SearchLayer3(str_url);
	return true;
}

bool CDolo800meinv::SearchLayer3(CString &str_url)
{
	//下载http://moko.cc/post/laomai/1/378314.html
	int i_addr;
	i_addr = str_url.Find(_T("_"));
	if(i_addr>-1)
	{
		str_url.Delete(i_addr,str_url.GetLength()-i_addr);
		str_url.Insert(i_addr,_T(".html"));	
	}

	CString tmp_str;
	CString cs_webContent;
	CString cs_album_name;	//主目录名字
	int photo_num=0;		//像册数量
	//获得照片数-------------------------------------------------photo_num
	tmp_str = str_url;
	DownloadUrlPage(tmp_str,cs_webContent);
	int m_temp=cs_webContent.Find(_T("a>共"),0);
	if(m_temp>-1)
	{
		//photo_num
		CString str;
		str = cs_webContent.Right(cs_webContent.GetLength()-m_temp-4);
		m_temp=str.Find(_T("页"),0);
		str = str.Left(m_temp);
		photo_num=atoi(str);
	}
	//获得用户名-------------------------------------------------cs_album_name
	m_temp = cs_webContent.Find(_T("<title>"),0);
	if( m_temp >-1)
	{

		cs_album_name=cs_webContent.Right(cs_webContent.GetLength()-m_temp-7);
		cs_album_name=cs_album_name.Left(cs_album_name.Find(_T("_"),0));
		checkDirname(cs_album_name);
		CreateDirectory(_T("八百美女\\")+cs_album_name,NULL);
	}
	//开始下载
	for(int m=1;m<photo_num+1;m++)
	{
		cs_webContent.Empty();
		DownloadUrlPage(str_url,cs_webContent);

		checkDirname(cs_album_name);
		regex reg("(http://800meinv.com/[^\\s]*.jpg)|(http://www.800meinv.com/uploads/[^\\s]*.jpg)");  	//图片模式
		smatch m1; 
		string s = cs_webContent.GetBuffer();	
		string::const_iterator it = s.begin(); 
		string::const_iterator end=s.end();
		while(regex_search(it,end,m1,reg))
		{
			string msg(m1[0].first,m1[0].second);	
			s_dolo.cs_url=msg.c_str();
			s_dolo.cs_LocalFullPath=_T("八百美女\\")+cs_album_name;
			s_dolo.cs_ReferHead=_T("Referer: http://www.800meinv.com");
			v_doloST.push_back(s_dolo); 
			it = m1[0].second; 
		}
		if(m<2)
		{
			str_url.Delete(str_url.GetLength()-5,5);	
		}else if(m/10<1)
		{
			str_url.Delete(str_url.GetLength()-7,7);			
		}else if(m/100<1)
		{
			str_url.Delete(str_url.GetLength()-8,8);
		}else if(m/1000<1)
		{
			str_url.Delete(str_url.GetLength()-9,9);
		}else if(m/10000<1)
		{
			str_url.Delete(str_url.GetLength()-10,10);
		}
		CString ch;
		ch.Format(_T("_%d.html"),m+1);
		str_url+=ch;
	}
	return true;
}