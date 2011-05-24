#include "StdAfx.h"
#include "DoloTaobaoMM.h"


CDoloTaobaoMM::CDoloTaobaoMM(void)
{
	CreateDirectory(_T("taobaoMM"),NULL);
}


CDoloTaobaoMM::~CDoloTaobaoMM(void)
{
}
bool CDoloTaobaoMM::SearchLayer1(CString &str_url)
{
	CString cs_content;//保存网页内容
	CString cs_dir;
	CString cs_webContent;
	DownloadUrlPage(str_url,cs_webContent);
	
	//相册<span>(121)</span>
	CString cs_album_Root;
	int m_temp = cs_webContent.Find(_T("爱秀</a></li>"));
	if( m_temp >-1)
	{

		cs_album_Root=cs_webContent.Right(cs_webContent.GetLength()-cs_webContent.Find(_T("http:"),m_temp));
		cs_album_Root=cs_album_Root.Left(cs_album_Root.Find(_T("htm"),0)+3);
	}
	//获得用户名
	CString cs_album_name;
	m_temp = cs_webContent.Find(_T("<title>淘女郎 - "));
	if( m_temp >-1)
	{

		cs_album_name=cs_webContent.Right(cs_webContent.GetLength()-m_temp-16);
		cs_album_name=cs_album_name.Left(cs_album_name.Find(_T(" </title>"),0));
		checkDirname(cs_album_name);
		CreateDirectory(_T("taobaoMM\\")+cs_album_name,NULL);
	}
	//资料
	CString cs_album_file;
	m_temp = cs_webContent.Find(_T("<i class=\"new\"></i>"));
	if( m_temp >-1)
	{

		cs_album_file=cs_webContent.Right(cs_webContent.GetLength()-cs_webContent.Find(_T("http:"),m_temp));
		cs_album_file=cs_album_file.Left(cs_album_file.Find(_T("htm"),0)+3);
	}

	URLDownloadToFile(NULL, cs_album_file, _T("taobaoMM\\")+cs_album_name+_T("\\browseUserProfile.html"),0,NULL); 
	DownloadUrlPage(cs_album_Root,cs_webContent);
	
	vector<string> album_link;	
	regex reg("<a target=\"_blank\" href=\"[a-zA-z]+://mm.taobao.com[^\\s]*htm");  	//图片模式
	smatch m1; 
	string s = cs_webContent.GetBuffer();	
	string::const_iterator it = s.begin(); 
	string::const_iterator end=s.end();
	while(regex_search(it,end,m1,reg))
	{
/*		int size = m1[0].length();*/
		string msg(m1[0].first,m1[0].second);
		int i = msg.find(_T("http:"));
		msg.erase(0,i+26);
		msg.insert(0,_T("http://mm.taobao.com/pic"));
		msg.insert(msg.size(),_T("?page=1"));		
		album_link.push_back(msg);
		it = m1[0].second; 
		myidle();
	}
	for(unsigned int i=0; i<album_link.size();i++)
	{
		CString strMfc=album_link[i].c_str();
		SearchLayer3(strMfc);
	}
	CString str;
	str=_T("分析完毕");
	insertstring(str);
	return true;	
}
bool CDoloTaobaoMM::SearchLayer3(CString &str_url)
{
	CDolo::SearchLayer3(str_url);
	if(str_url.Find(_T("photo"))>-1)
	{
		str_url.Delete(0,26);
		if(str_url.Find(_T("#")))
		{
			str_url.Delete(str_url.Find(_T("#")),str_url.GetLength());
		}
		str_url.Insert(0,_T("http://mm.taobao.com/pic"));
		str_url.Insert(str_url.GetLength(),_T("?page=1"));	
	}
	CString tmp_str;
	CString cs_webContent;
	CString cs_content;

	CString cs_album_name;	//主目录名字
	int photo_num=0;		//像册数量
	CString cs_sub_album;  //子相册名字
	{//获得像册名字

		tmp_str = str_url;
		int i=tmp_str.Find(_T("pic"));
		if( i >-1)
		{
			tmp_str.Delete(i ,3);
			tmp_str.Insert(i,_T("photo"));
			try
			{
				htmlFile = (CInternetFile*) httpSession.OpenURL(tmp_str,1,INTERNET_FLAG_TRANSFER_ASCII);//m_url是输入控件Edit1的变量

				while (htmlFile->ReadString(cs_content))
				{
					cs_webContent+=cs_content;
					myidle();
				}
			}
			catch (CMemoryException* e)
			{
				delete e;
			}
			catch (CFileException* e)
			{
				delete e;
			}
			catch (CException* e)
			{			
				delete e;
			}
			//获得用户名
			int m_temp = cs_webContent.Find(_T("<title>淘女郎 - "));
			if( m_temp >-1)
			{

				cs_album_name=cs_webContent.Right(cs_webContent.GetLength()-m_temp-16);
				cs_album_name=cs_album_name.Left(cs_album_name.Find(_T(" </title>"),0));
				checkDirname(cs_album_name);
				CreateDirectory(_T("taobaoMM\\")+cs_album_name,NULL);
			}
			
			CString cst;
			cst = cs_webContent;
			int i=cs_webContent.Find(_T("lass=\"J_TotalPage\">"),0);
			cst.Delete(0,i+19);
			i=cst.Find(_T("<"),0);
			cst.Delete(i,cst.GetLength());
			photo_num=atoi(cst);
			//像册名

			cs_sub_album= cs_webContent;
			i=cs_sub_album.Find(_T("<a name=\"J_photoAnchor\"></a>"));
			cs_sub_album.Delete(0,i+28);
			i=cs_sub_album.Find(_T("<span class="));
			cs_sub_album.Delete(i-1, cs_webContent.GetLength());
		}
		
	}
	checkDirname(cs_sub_album);
	checkDirname(cs_album_name);
	CreateDirectory(_T("taobaoMM\\")+cs_album_name+_T("\\")+cs_sub_album,NULL);
	vector<string> astr;
	for(int m=1;m<photo_num/10+2;m++)
	{
		cs_webContent.Empty();
		try
		{
			htmlFile = (CInternetFile*) httpSession.OpenURL(str_url,1,INTERNET_FLAG_TRANSFER_ASCII);//m_url是输入控件Edit1的变量

			while (htmlFile->ReadString(cs_content))
			{
				cs_webContent+=cs_content;
				myidle();
			}
		}
		catch (CMemoryException* e)
		{
			delete e;
		}
		catch (CFileException* e)
		{
			delete e;
		}
		catch (CException* e)
		{			
			delete e;
		}
		regex reg("[a-zA-z]+://[^\\s]*.jpg");  	//图片模式
		smatch m1; 

		string s = cs_webContent.GetBuffer();	
		string::const_iterator it = s.begin(); 
		string::const_iterator end=s.end();
		while(regex_search(it,end,m1,reg))
		{
/*			int size = m1[0].length();*/
			string msg(m1[0].first,m1[0].second);	
			
			s_dolo.cs_url=msg.c_str();
			s_dolo.cs_LocalFullPath=_T("taobaoMM\\")+cs_album_name+_T("\\")+cs_sub_album;
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
	
// 	CString cs_album_name;	//主目录名字
// 	int photo_num;		//像册数量
// 	CString cs_sub_album;  //子相册名字
	checkDirname(cs_album_name);

// 	st_lp.urlGroup=astr;
// 	st_lp.strFileURLInServer.IsEmpty();
// 	st_lp.strFileLocalFullPath=_T("taobaoMM\\")+cs_album_name+_T("\\")+cs_sub_album;
// 	st_lp.strReferHead=_T("Referer: http://mm.taobao.com");//_T("Referer: http://mm.taobao.com");
// 	st_lp.hWnd=(HWND)this;
// 	m_pMyThread=AfxBeginThread(Download1,(LPVOID)&st_lp);//&st_lp[n]);

	return true;
}