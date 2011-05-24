#include "StdAfx.h"
#include "DoloTaobaoHB.h"


CDoloTaobaoHB::CDoloTaobaoHB(void)
{
}


CDoloTaobaoHB::~CDoloTaobaoHB(void)
{
}

bool CDoloTaobaoHB::SearchLayer3(CString &str_url)
{
	CDolo::SearchLayer3(str_url);
	CString cs_content;//保存网页内容
	CString cs_dir;
	CString cs_webContent;
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
// 	wstring wstr1;
// 	wstr1=UTF8ToUnicode( cs_webContent.GetBuffer() );
	// 	CString str1( wstr1.c_str() ); 
	// 	cs_webContent.Empty();
//	cs_webContent=_T(wstr1.c_str());


	regex reg("[a-zA-z]+://[^\\s]*JPEG\\b"); 
	regex regdir("<title>[\\w ]*- 画报\\b");
	regex regdir1("[\\S\\w ]*- 画报\\b");
	smatch m1; 
	string s = cs_webContent.GetBuffer();	

/*	int new_counter = 0; */
	int delete_counter = 0; 
	string::const_iterator it = s.begin(); 
	string::const_iterator end = s.end(); 
	vector<string> astr;
	//while (regex_search(it,(string::const_iterator)s.end(),m,reg))  
	CString str;
	if(cs_webContent.Find(_T("<title>"))>-1)
	{
		str=cs_webContent.Right(cs_webContent.GetLength()-7-cs_webContent.Find(_T("<title>")));
		str=str.Left(str.Find(_T("- 画报")));
		checkDirname(str);		
		CreateDirectory(_T("taobaoHB"),NULL);	
		CreateDirectory(_T("taobaoHB\\")+str,NULL);	
//hce		st_lp.strFileLocalFullPath=_T("taobaoHB\\")+str;
	}


	while(regex_search(it,end,m1,reg))
	{ 
		//m[1].matched ? ++new_counter : ++delete_counter; 
		int size = m1[0].length();
		string msg(m1[0].first,m1[0].second);
		
		s_dolo.cs_url=msg.c_str();
		s_dolo.cs_LocalFullPath=_T("taobaoHB\\")+str;
		s_dolo.cs_ReferHead=_T("");
		v_doloST.push_back(s_dolo);

		it = m1[0].second; 
		myidle();
	} 
	//listadd(0,_T("分析网页完毕"));
// 	st_lp.urlGroup=astr;
// 	st_lp.strFileURLInServer.IsEmpty();
// 	//st_lp.strFileLocalFullPath=_T(".\\");
// 	st_lp.hWnd=(HWND)this;
// 	m_pMyThread=AfxBeginThread(Download1,(LPVOID)&st_lp);//&st_lp[n]);
// 	if (new_counter != delete_counter) 
// 		int aa=0;
// 	else 
// 		int bb=1;
	return true;
}

bool CDoloTaobaoHB::SearchLayer1(CString &str_url)
{
	SearchLayer3(str_url);
	return true;
}