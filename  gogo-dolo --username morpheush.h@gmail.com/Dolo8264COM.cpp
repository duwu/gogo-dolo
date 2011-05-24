#include "StdAfx.h"
#include "Dolo8264COM.h"


CDolo8264COM::CDolo8264COM(void)
{
	CreateDirectory(_T("8264com"),NULL);
}


CDolo8264COM::~CDolo8264COM(void)
{

}


bool CDolo8264COM::SearchLayer1(CString &str_url)
{

	CString cs_webContent;
	vector<string> astr;  //下载链接集合
	// http://u.8264.com/home-space-uid-104370-do-album-id-1496-page-1.html#comment
	// http://u.8264.com/home-space-uid-104370-do-album-view-me-from-space.html
	int t1 = str_url.Find(_T("album-id"));
	if(t1 >-1)
	{
		str_url.Delete(t1,str_url.GetLength() - t1);
		str_url+=_T("album-view-me-from-space.html");
	}

	DownloadUrlPage(str_url,cs_webContent);	
	regex reg("[a-zA-z]+://[^\\s]*.html\"  class=\"xi2\"");  	//图片模式
	smatch m1; 

	string s = cs_webContent.GetBuffer();	
	string::const_iterator it = s.begin(); 
	string::const_iterator end=s.end();
	while(regex_search(it,end,m1,reg))
	{
/*		int size = m1[0].length();*/
		string msg(m1[0].first,m1[0].second);	
		msg.erase(msg.size()-14,msg.size());
		astr.push_back(msg);
		it = m1[0].second; 
		msg.empty();
		myidle();
	}
	s.empty();
	for(unsigned int i=0; i<astr.size();i++)
	{
		CString strMfc=astr[i].c_str();
		SearchLayer3(strMfc);
	}
	astr.empty();
	return true;
}
//下载像册信息
// http://u.8264.com/home-space-uid-16752722-do-album-id-1766.html
// http://u.8264.com/home-space-uid-16752722-do-album-id-1766-page-4.html#comment
bool CDolo8264COM::SearchLayer3(CString &str_url)
{
	CString cs_webContent;
	CString cs_tmp;
	int photo_num=0;		//像册数量
	int i_tmp;
	vector<string> astr;  //下载链接集合
	int m_page= 1;			//设置页面数
	CString cs_album_name;	//用户目录
	CString cs_sub_album;	//像册目录

	if(str_url.Find(_T("#comment")) < 0)
	{
		str_url.Delete(str_url.GetLength()-5,5);
		str_url+=_T("-page-1.html#comment");
	}
	else
		str_url.SetAt(str_url.GetLength()-14,_T('1'));

	//获得页面
	bool en_P=false;
	bool en_G=false;
	do 
	{
		cs_webContent.Empty();
		DownloadUrlPage(str_url,cs_webContent);	

		i_tmp = cs_webContent.Find(_T("张图片"),0);
		if(i_tmp>-1)
		{
			cs_tmp = cs_webContent.Left(i_tmp);
			cs_tmp = cs_tmp.Right(4);
			cs_tmp.TrimLeft(_T(" ")); 
			cs_tmp.TrimRight( _T(" "));
			if((atoi(cs_tmp)==0)||(cs_tmp.IsEmpty()))
			{
				return false;
			}
			else
				photo_num = atoi(cs_tmp);
		}
		//获得像册的题目
		if(en_P == false)
		{
			int i=cs_webContent.Find(_T("keywords\" content=\""),0);
			if(i>-1)
			{
				cs_sub_album= cs_webContent.Right(cs_webContent.GetLength() -i -19);
				cs_sub_album = cs_sub_album.Left(cs_sub_album.Find(_T("\"")));
				en_P = true;
			}
		}
		//获得用户题目cs_album_name
		if(en_G == false)
		{
			int i=cs_webContent.Find(_T("<h2 class=\"xs2\">"),0);
			if(i>-1)
			{
				i=cs_webContent.Find(_T("html"),i);
				cs_album_name= cs_webContent.Right(cs_webContent.GetLength() -i -6);
				cs_album_name = cs_album_name.Left(cs_album_name.Find(_T("<"),0));
				en_G = true;
			}
		}
		checkDirname(cs_album_name);
		checkDirname(cs_sub_album);
		CreateDirectory(_T("8264com\\")+cs_album_name,NULL);
		CreateDirectory(_T("8264com\\")+cs_album_name+_T("\\")+cs_sub_album,NULL);

		regex reg("html\"><img src=\"[a-zA-z]+://[^\\s]*thumb.jpg");  	//图片模式
		smatch m1; 

		string s = cs_webContent.GetBuffer();	
		string::const_iterator it = s.begin(); 
		string::const_iterator end=s.end();

		while(regex_search(it,end,m1,reg))
		{
/*			int size = m1[0].length();*/
			string msg(m1[0].first,m1[0].second);	
			msg.erase(0,16);
			msg.erase(msg.size()-10,msg.size());
			//astr.push_back(msg);
			
			s_dolo.cs_url=msg.c_str();
			s_dolo.cs_LocalFullPath=_T("8264com\\")+cs_album_name+_T("\\")+cs_sub_album;
			s_dolo.cs_ReferHead=_T("");
			v_doloST.push_back(s_dolo);

			it = m1[0].second; 
			msg.empty();
			myidle();
		}
		s.empty();

		str_url.Delete(str_url.Find(_T("page")),str_url.GetLength()-str_url.Find(_T("page")) );
		str_url.Insert(str_url.GetLength(), _T("page-"));
		CString tc;
		m_page++;
		tc.Format(_T("%d"),m_page);
		str_url.Insert(str_url.GetLength(), tc);
		str_url.Insert(str_url.GetLength(), _T(".html#comment"));	
		tc.Empty();
	} while (photo_num/20 +2 >m_page);
	


	// 	CString cs_album_name;	//主目录名字
	// 	int photo_num;		//像册数量
	// 	CString cs_sub_album;  //子相册名字
//	checkDirname(cs_album_name);


// 	st_lp.urlGroup=astr;
// 	st_lp.strFileURLInServer.IsEmpty();
// 	st_lp.strFileLocalFullPath=_T("8264com\\")+cs_album_name+_T("\\")+cs_sub_album;
// 	st_lp.strReferHead=_T("");					//_T("Referer: http://mm.taobao.com");
// 	st_lp.hWnd=(HWND)this;
// 	m_pMyThread=AfxBeginThread(Download1,(LPVOID)&st_lp);//&st_lp[n]);
// 	astr.empty();
	return true;
}
