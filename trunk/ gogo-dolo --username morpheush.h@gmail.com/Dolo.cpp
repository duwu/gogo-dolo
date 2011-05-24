#include "StdAfx.h"
#include "Dolo.h"
extern bool b_closeP;
CString cs_CurrDir;
struct ST_LP{
	vector<string> urlGroup;	
	CString strFileURLInServer;
	CString strFileLocalFullPath;
	CString strReferHead;
	HWND hWnd;
};
vector<struct ST_Dolo> v_doloST;
CDolo::CDolo(void)
{
	my_exit=false;
	TCHAR	path[MAX_PATH];
	GetCurrentDirectory(MAX_PATH,path);
	cs_CurrDir.Format(_T("%s\\"),path);
}


CDolo::~CDolo(void)
{
// 	if(htmlFile != NULL)
// 	{
// 		htmlFile->Close();
// 		delete htmlFile;
// 	}
}

//��ÿ���������ö���һ����,��Ҫ����д.
/*
һ��������������������
*/
bool CDolo::SearchLayer1(CString &str_url)
{
	return false;
}

/*
һ����ö����������
*/
bool CDolo::SearchLayer2(CString &str_url)
{
	return false;
}

/*
�����Ƭ����.
*/
bool CDolo::SearchLayer3(CString &str_url)
{
	::SendMessage(AfxGetMainWnd()->m_hWnd,WM_WRURL,(WPARAM)str_url.GetBuffer(),NULL);
	return false;
}


// ���ؼ�����txt������ʵ�Ҹо���html����
bool CDolo::Resume2Txt(void)
{
	return false;
}

//��������ļ��ǲ��Ǵ���
#include "PICDoloDoc.h"
bool CDolo::checkDownFile(CString & filename)
{
	int leng = hasDownfilename.GetSize();
	if(leng>-1)
	{
		if(hasDownfilename[filename]==TRUE)
			return false;
	}
	return true;
}

void CDolo::checkDirname(CString &mokoDir)
{
	while(mokoDir.Find(_T('\\'),0)!=-1)
		mokoDir.SetAt(mokoDir.Find(_T('\\'),0),_T('_'));
	while(mokoDir.Find(_T('/'),0)!=-1)
		mokoDir.SetAt(mokoDir.Find(_T('/'),0),_T('_'));
	while(mokoDir.Find(_T(':'),0)!=-1)
		mokoDir.SetAt(mokoDir.Find(_T(':'),0),_T('_'));
	while(mokoDir.Find(_T('*'),0)!=-1)
		mokoDir.SetAt(mokoDir.Find(_T('*'),0),_T('_'));
	while(mokoDir.Find(_T('?'),0)!=-1)
		mokoDir.SetAt(mokoDir.Find(_T('?'),0),_T('_'));
	while(mokoDir.Find(_T('"'),0)!=-1)
		mokoDir.SetAt(mokoDir.Find(_T('"'),0),_T('_'));
	while(mokoDir.Find(_T('>'),0)!=-1)
		mokoDir.SetAt(mokoDir.Find(_T('>'),0),_T('_'));
	while(mokoDir.Find(_T('<'),0)!=-1)
		mokoDir.SetAt(mokoDir.Find(_T('<'),0),_T('_'));
	while(mokoDir.Find(_T('|'),0)!=-1)
		mokoDir.SetAt(mokoDir.Find(_T('|'),0),_T('_'));
	while(mokoDir.Find(_T(' '),0)!=-1)
		mokoDir.SetAt(mokoDir.Find(_T(' '),0),_T('_'));
	while(mokoDir.Find(_T('.'),0)!=-1)
		mokoDir.SetAt(mokoDir.Find(_T('.'),0),_T('_'));
}

BOOL CDolo::myidle()
{	
	MSG msg;
	if(my_exit)
	{
		//OnBnClickedOk();
		exit(0);
	}
	while (::PeekMessage(&msg,NULL,0,0,PM_NOREMOVE))
	{
		if (!AfxGetApp()->PumpMessage())
		{
			::PostQuitMessage(0);
			return FALSE;
		}
		return TRUE;
	}
	LONG midle=0;
	while(AfxGetApp()->OnIdle(midle++))
	{
		return TRUE;
	}
	return TRUE;
}

wstring CDolo::UTF8ToUnicode( const string  str )
{
	int  len = 0;
	len = str.length();
	int  unicodeLen = ::MultiByteToWideChar( CP_UTF8,
		0,
		str.c_str(),
		-1,
		NULL,
		0 ); 
	wchar_t *  pUnicode; 
	pUnicode = new  wchar_t[unicodeLen+1]; 
	memset(pUnicode,0,(unicodeLen+1)*sizeof(wchar_t)); 
	::MultiByteToWideChar( CP_UTF8,
		0,
		str.c_str(),
		-1,
		(LPWSTR)pUnicode,
		unicodeLen ); 
	wstring  rt; 
	rt = ( wchar_t* )pUnicode;
	delete  pUnicode;
	return  rt; 
}
// Unicode����תΪUTF8  
bool CDolo::UnicodeToUTF8(vector<char>& pu8, const wchar_t* pun, unsigned int uLen)  
{  
	// convert an widechar string to utf8  
	unsigned int utf8Len = WideCharToMultiByte(CP_UTF8, 0, pun, uLen, NULL, 0, NULL, NULL);  
	if (utf8Len<=0)  
	{  
		return false;  
	}  
	pu8.resize(utf8Len);  
	unsigned int nRtn = WideCharToMultiByte(CP_UTF8, 0, pun, uLen, &*pu8.begin(), utf8Len, NULL, NULL);  

	if (nRtn != utf8Len)  
	{  
		pu8.clear();  
		return false;  
	}  
	return true;  
}  







#include "PICDolo.h"
ST_LP st_lp;
char pszBuffer[1024*10];   // ��ȡ�ļ��Ļ��� 
bool DownloadPic( const  CString &  strFileURLInServer, 
	const  CString  &  strFileLocalFullPath,
	const  CString &referHead
	)
{
	CInternetSession session;
	CHttpConnection *  pHttpConnection  =  NULL;
	CHttpFile *  pHttpFile  =  NULL;
	CString strServer, strObject;
	INTERNET_PORT wPort;	


	DWORD dwType;
	const   int  nTimeOut  =   2000 ;
	session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, nTimeOut);  // ����֮��ĵȴ���ʱ 
	session.SetOption(INTERNET_OPTION_CONNECT_RETRIES,  10 );    // ���Դ��� 

	//char *  pszBuffer  =  NULL;  

	try 
	{
		//UpdateData(Val2Con);
		AfxParseURL(strFileURLInServer, dwType, strServer, strObject, wPort);
		pHttpConnection  =  session.GetHttpConnection(strServer, wPort);
		pHttpFile  =  pHttpConnection -> OpenRequest(CHttpConnection::HTTP_VERB_GET, strObject);
		if(!referHead.IsEmpty())
			pHttpFile->AddRequestHeaders(referHead);		
		if (pHttpFile -> SendRequest()  ==  FALSE)
			return   false ;
		DWORD dwStateCode;

		pHttpFile -> QueryInfoStatusCode(dwStateCode);
		if (dwStateCode  ==  HTTP_STATUS_OK)
		{
			//			int m1=strObject.Find(_T("/img"));
			int m1=strObject.ReverseFind('/');
			CString cs_download;
			cs_download = strObject;
			cs_download.Delete(0,m1);	

			CString str_autoup;
			str_autoup=strObject;
			str_autoup.Delete(0,m1+1);
			// 			int ll=hasDownfilename.GetSize();		
			// 			UpdateData(Con2Val);
			// 			if(b_noUseDB!=TRUE)
			// 			{
			// 				if(m_bAutoUpdata)
			// 				{
			// 					bool aaa=checkDownFile(str_autoup);
			// 					if(aaa==true)		//û���ҵ���ͬ���ļ�.�����������
			// 						hasDownfilename.InsertAt(0,str_autoup);
			// 					else				//����һ���ļ�,�˳�����
			// 					{
			// 						if (pHttpFile  !=  NULL)
			// 							pHttpFile -> Close();
			// 						if (pHttpConnection  !=  NULL)
			// 							pHttpConnection -> Close();
			// 						delete pHttpConnection;
			// 						delete pHttpFile;
			// 						session.Close();
			// 						return   true ;
			// 					}
			// 				}
			// 
			// 			}
			HANDLE hFile  =  CreateFile(strFileLocalFullPath+cs_download, GENERIC_WRITE,
				FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL,
				NULL);   // ���������ļ� 
			if (hFile  ==  INVALID_HANDLE_VALUE)
			{
				pHttpFile -> Close();
				pHttpConnection -> Close();
				session.Close();
				return   false ;
			} 

			char  szInfoBuffer[ 1000 ];   // ������Ϣ 
			DWORD dwFileSize  =   0 ;    // �ļ����� 
			DWORD dwInfoBufferSize  =   sizeof (szInfoBuffer);
			BOOL bResult  =  FALSE;
			bResult  =  pHttpFile -> QueryInfo(HTTP_QUERY_CONTENT_LENGTH,
				( void * )szInfoBuffer, & dwInfoBufferSize,NULL);

			dwFileSize  =  atoi(szInfoBuffer);
			const   int  BUFFER_LENGTH  =   1024   *   10 ;
			/*pszBuffer  =   new   char [BUFFER_LENGTH];   // ��ȡ�ļ��Ļ��� */
			DWORD dwWrite, dwTotalWrite;
			dwWrite  =  dwTotalWrite  =   0 ;
			UINT nRead  =  pHttpFile -> Read(pszBuffer, BUFFER_LENGTH);  // ��ȡ������������ 

			while (nRead  >   0 )
			{
				WriteFile(hFile, pszBuffer, nRead,  & dwWrite, NULL);   // д�������ļ� 
				dwTotalWrite  +=  dwWrite;
				nRead  =  pHttpFile -> Read(pszBuffer, BUFFER_LENGTH);
			} 

// 			delete[]pszBuffer;
// 			pszBuffer  =  NULL;
			::ZeroMemory(pszBuffer,10240);
			CloseHandle(hFile);
		} 
		else 
		{
// 			delete[]pszBuffer;
// 			pszBuffer  =  NULL;
			::ZeroMemory(pszBuffer,10240);
			if (pHttpFile  !=  NULL)
			{
				pHttpFile -> Close();
				delete pHttpFile;
				pHttpFile  =  NULL;
			} 
			if (pHttpConnection  !=  NULL)
			{
				pHttpConnection -> Close();
				delete pHttpConnection;
				pHttpConnection  =  NULL;
			} 
			session.Close();
			// 			hasDownfilename.RemoveAt(0,1);
			// 			WriteDownFile();
			return   false ;
		} 
	} 
	catch(CInternetException  *pEx)
	{
// 		delete[]pszBuffer;
// 		pszBuffer  =  NULL;
		::ZeroMemory(pszBuffer,10240);
		if (pHttpFile  !=  NULL)
		{
			pHttpFile -> Close();
			delete pHttpFile;
			pHttpFile  =  NULL;
		} 
		if (pHttpConnection  !=  NULL)
		{
			pHttpConnection -> Close();
			delete pHttpConnection;
			pHttpConnection  =  NULL;
		} 
		session.Close();
		// 		hasDownfilename.RemoveAt(0,1);
		// 		WriteDownFile();
		//MessageBox(_T("������,��������"));
		pEx->Delete();
		return   false ;
	} 

	if (pHttpFile  !=  NULL)
		pHttpFile -> Close();
	if (pHttpConnection  !=  NULL)
		pHttpConnection -> Close();
	delete pHttpConnection;
	delete pHttpFile;
	session.Close();
	return   true ;
} 

UINT Download1(LPVOID pParam)
{
	ST_LP * MyLP=(ST_LP*)pParam;
	vector<string> ve_urlGroup;
	CString  strFileURLInServer;  // �������ļ���URL 
	CString  strFileLocalFullPath; // ��ŵ����ص�·�� 
	CString  strReferHead;			//referͷ������
	ve_urlGroup = MyLP->urlGroup;
	strFileURLInServer=(CString)MyLP->strFileURLInServer;
	strFileLocalFullPath=(LPCTSTR)MyLP->strFileLocalFullPath;
	strReferHead=(CString)MyLP->strReferHead;
	//CPICDoloApp* WorkerThreadDlg=(CPICDoloApp*)MyLP->hWnd;
	//WorkerThreadDlg->listadd(0,_T("��ʼ������Ƭ��Ƭ  "));
	//	WorkerThreadDlg->listadd(0,_T("0"));
	// 	if(!strFileURLInServer.IsEmpty())
	// 	{
	// 		DownloadPic(strFileURLInServer, strFileURLInServer,strReferHead);
	// 		thread_num--;
	// 		return true;
	// 	}
	for(int i=0;i< (int)ve_urlGroup.size();i++)
	{
		// 		if(WorkerThreadDlg->m_DownNum>0)			//�������0��ֻ������300��
		// 		{	
		// 			if(WorkerThreadDlg->m_DownNum>(downNUM1*downNUM2+1))
		// 			{
		// 				WorkerThreadDlg->listadd(0,_T("���س���300��,��������´������������"));
		// 				thread_num--;
		// 				return true;
		// 			}
		// 			WorkerThreadDlg->m_DownNum++;
		// 		}
		//		WorkerThreadDlg->m_ListBox.DeleteString(0);
		// 		CString num;
		// 		num.Format(_T("%d"),i);
		// 		WorkerThreadDlg->listadd(0, num);
		strFileURLInServer.Format(_T("%s"),ve_urlGroup[i].c_str());
		
		BOOL b_dlo=DownloadPic(strFileURLInServer,strFileLocalFullPath,strReferHead);		
		if(b_dlo == TRUE)
		{		
			CString str;
			int i = strFileURLInServer.ReverseFind(_T('/'));
			str = strFileURLInServer.Right(strFileURLInServer.GetLength()-i-1);
			str=cs_CurrDir+strFileLocalFullPath+_T("\\")+str;
// 			if(b_closeP== true)
// 				return false;
// 			else
			::SendMessage(AfxGetMainWnd()->m_hWnd,WM_UPOUTPUTtoSELANG,(WPARAM)str.GetBuffer(),NULL);
		}
	}
	//WorkerThreadDlg->listadd(0,_T("������Ƭ��Ƭ�������  ")+strFileLocalFullPath);
	//thread_num--;
	return true;
}

// ����û����ĵ�����
bool CDolo::GetManfile(CString& file_url)
{
	
	return false;
}


// ����һ��Ҫ���ص�url,���ص������ص�ҳ������
bool CDolo::DownloadUrlPage(CString & UrlPage, CString & cs_webContent)
{
	CString cs_content;
	htmlFile = (CInternetFile*) httpSession.OpenURL(UrlPage,1,INTERNET_FLAG_TRANSFER_ASCII);//m_url������ؼ�Edit1�ı���

	while (htmlFile->ReadString(cs_content))
	{
		cs_webContent+=cs_content;
		myidle();
	}


// 	wstring wstr1;
// 	wstr1=UTF8ToUnicode( cs_webContent.GetBuffer() );
	// 	CString str1( wstr1.c_str() ); 
	// 	cs_webContent.Empty();
//	cs_webContent=_T(wstr1.c_str());
		
	return false;
}
