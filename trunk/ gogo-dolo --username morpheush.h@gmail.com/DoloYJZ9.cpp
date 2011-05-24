#include "StdAfx.h"
#include "DoloYJZ9.h"


CDoloYJZ9::CDoloYJZ9(void)
{
	CreateDirectory(_T("妖姬宅"),NULL);
}


CDoloYJZ9::~CDoloYJZ9(void)
{
}


bool CDoloYJZ9::SearchLayer1(CString &str_url)
{
	SearchLayer3(str_url);
	return true;
}
bool CDoloYJZ9::SearchLayer3(CString &str_url)
{
	CDolo::SearchLayer3(str_url);

	if(str_url.Find(_T("photo_show.asp"))>-1)
	{
		int i=str_url.Find(_T("id="),0);
		if(i>-1)
		{
			int m=str_url.Find(_T("&"),i);
			if(m>-1)
			{
				str_url.Delete(str_url.Find(_T("&"),i),str_url.GetLength()-str_url.Find(_T("&")));
			}
			if(str_url.Find(_T("http://"),0))
			{
				str_url.Insert(0,_T("http://"));
			}
			str_url.Insert(str_url.GetLength(),_T("&Page=1"));	
		}
		
	}
	else
		return false;

	CString tmp_str;
	CString cs_webContent;
	CString cs_content;

	CString cs_album_name;	//主目录名字
	int photo_num=0;		//像册数量
	{//获得像册名字

		tmp_str = str_url;
		int i=tmp_str.Find(_T("photo_show.asp?id="));
		if( i >-1)
		{
			DownloadUrlPage(tmp_str,cs_webContent);
	
			//获得用户名
			int m_temp = cs_webContent.Find(_T("<title>妖姬宅官网"));
			if( m_temp >-1)
			{

				cs_album_name=cs_webContent.Right(cs_webContent.GetLength()-m_temp-46);
				cs_album_name=cs_album_name.Left(cs_album_name.Find(_T("</title>"),0));
				checkDirname(cs_album_name);
				CreateDirectory(_T("妖姬宅\\")+cs_album_name,NULL);
			}
			m_temp=cs_webContent.Find(_T("共有"),0);
			if(m_temp>-1)
			{
				//photo_num
				CString str;
				str = cs_webContent.Right(cs_webContent.GetLength()-m_temp-4);
				m_temp=str.Find(_T("条记录"));
				str = str.Left(m_temp);
				photo_num=atoi(str);
			}
		}		
	}

	for(int m=1;m<photo_num/8+2;m++)
	{
		cs_webContent.Empty();
		DownloadUrlPage(str_url,cs_webContent);
		
		regex reg("(/upload/[0-9]*/([0-9]|[a-z])*.jpg)|(/images/news/([0-9]|[a-z])*.jpg)");  	//图片模式
		smatch m1; 

		string s = cs_webContent.GetBuffer();	
		string::const_iterator it = s.begin(); 
		string::const_iterator end=s.end();
		while(regex_search(it,end,m1,reg))
		{
/*			int size = m1[0].length();*/
			string msg(m1[0].first,m1[0].second);	
			msg.insert(0,_T("http://www.yjz9.com"));
			s_dolo.cs_url=msg.c_str();
			s_dolo.cs_LocalFullPath=_T("妖姬宅\\")+cs_album_name;
			s_dolo.cs_ReferHead=_T("Referer: http://mm.taobao.com");
			v_doloST.push_back(s_dolo);

			it = m1[0].second; 
			myidle();
		}
		if(m/10<1)
		{
			str_url.Delete(str_url.GetLength()-1,1);			
		}else if(m/100<1)
		{
			str_url.Delete(str_url.GetLength()-2,2);
		}else if(m/1000<1)
		{
			str_url.Delete(str_url.GetLength()-3,3);
		}else if(m/10000<1)
		{
			str_url.Delete(str_url.GetLength()-4,4);
		}
		CString ch;
		ch.Format(_T("%d"),m+1);
		str_url+=ch;
	}

	checkDirname(cs_album_name);
	
	return true;
}