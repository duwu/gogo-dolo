// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"
#include "PICDolo.h"

#include "PICDoloDoc.h"
#include "PICDoloView.h"

#include "MainFrm.h"
#include "ChineseCode.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

bool b_endownload ;
/////////////////////////////////////////////////////////////////////////////
// CPICDoloView

IMPLEMENT_DYNCREATE(CPICDoloView, CHtmlView)

BEGIN_MESSAGE_MAP(CPICDoloView, CHtmlView)
	//{{AFX_MSG_MAP(CPICDoloView)
	ON_COMMAND(ID_GO_BACK, OnGoBack)
	ON_COMMAND(ID_GO_FORWARD, OnGoForward)
	ON_COMMAND(ID_GO_SEARCH_THE_WEB, OnGoSearchTheWeb)
	ON_COMMAND(ID_GO_START_PAGE, OnGoStartPage)
	ON_COMMAND(ID_VIEW_STOP, OnViewStop)
	ON_COMMAND(ID_VIEW_REFRESH, OnViewRefresh)
	ON_COMMAND(ID_VIEW_FONTS_LARGEST, OnViewFontsLargest)
	ON_COMMAND(ID_VIEW_FONTS_LARGE, OnViewFontsLarge)
	ON_COMMAND(ID_VIEW_FONTS_MEDIUM, OnViewFontsMedium)
	ON_COMMAND(ID_VIEW_FONTS_SMALL, OnViewFontsSmall)
	ON_COMMAND(ID_VIEW_FONTS_SMALLEST, OnViewFontsSmallest)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_UPDATE_COMMAND_UI(ID_GO_FORWARD, OnUpdateGoForward)
	ON_UPDATE_COMMAND_UI(ID_GO_BACK, OnUpdateGoBack)
	ON_WM_DESTROY()
	ON_MESSAGE(WM_NEWURL, OnNewURL)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CHtmlView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CHtmlView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CHtmlView::OnFilePrintPreview)
	ON_COMMAND(ID_DIRDOWNLOAD, &CPICDoloView::OnDirdownload)
	ON_COMMAND(ID_AUTODOWNLOAD, &CPICDoloView::OnAutodownload)
	ON_COMMAND(ID_CREATEFILE, &CPICDoloView::OnCreatefile)
	ON_COMMAND(ID_UPDATA_ALLPIC, &CPICDoloView::OnUpdataAllpic)
	//ON_COMMAND_RANGE(ID_BEGINID,ID_ENDID,&CPICDoloView::ONSelectWebsite)
	ON_WM_TIMER()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPICDoloView construction/destruction

CPICDoloView::CPICDoloView()
{
	// TODO: add construction code here
	m_DownNum=0;
	if(m_DownNum==0)
	{
		//MessageBox(_T("图片批处理下载 无限制版本 morpheush.h@gmail.com "));

// 		CMainFrame *pMain=(CMainFrame *)GetParentFrame();	
// 		pMain->updataTaskString(_T("图片批处理下载 无限制版本"));
	}
	else
		MessageBox(_T("图片批处理下载 300张限制版 morpheush.h@gmail.com "));
	b_endownload=true;
}

CPICDoloView::~CPICDoloView()
{
	b_endownload = true;
}

BOOL CPICDoloView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CHtmlView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPICDoloView drawing

void CPICDoloView::OnDraw(CDC* /*pDC*/)
{
	//	CPICDoloDoc* pDoc = GetDocument();
	//	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CPICDoloView printing

BOOL CPICDoloView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPICDoloView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPICDoloView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPICDoloView diagnostics

#ifdef _DEBUG
void CPICDoloView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CPICDoloView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

CPICDoloDoc* CPICDoloView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPICDoloDoc)));
	return (CPICDoloDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPICDoloView message handlers
// these are all simple one-liners to do simple controlling of the browser
void CPICDoloView::OnGoBack()
{
	CPICDoloDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CHistoryObj* pHistoryObj = pDoc->GoBack ();
	if (pHistoryObj != NULL)
	{
		Navigate2 (pHistoryObj->GetURL (), 0, NULL);
	}
}

void CPICDoloView::OnGoForward()
{
	//	GoForward();
	CPICDoloDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CHistoryObj* pHistoryObj = pDoc->GoForward ();
	if (pHistoryObj != NULL)
	{
		Navigate2 (pHistoryObj->GetURL (), 0, NULL);
	}
}

void CPICDoloView::OnGoSearchTheWeb()
{
	GoSearch();
}

void CPICDoloView::OnGoStartPage()
{
	GoHome();
}

void CPICDoloView::OnViewStop()
{
	Stop();
}

void CPICDoloView::OnViewRefresh()
{
	Refresh();
}

// these functions control the font size.  There is no explicit command in the
// CHtmlView class to do this, but we can do it by using the ExecWB() function.
void CPICDoloView::OnViewFontsLargest()
{
	COleVariant vaZoomFactor(4l);

	ExecWB(OLECMDID_ZOOM, OLECMDEXECOPT_DONTPROMPTUSER,
		&vaZoomFactor, NULL);
}

void CPICDoloView::OnViewFontsLarge()
{
	COleVariant vaZoomFactor(3l);

	ExecWB(OLECMDID_ZOOM, OLECMDEXECOPT_DONTPROMPTUSER,
		&vaZoomFactor, NULL);
}

void CPICDoloView::OnViewFontsMedium()
{
	COleVariant vaZoomFactor(2l);

	ExecWB(OLECMDID_ZOOM, OLECMDEXECOPT_DONTPROMPTUSER,
		&vaZoomFactor, NULL);
}

void CPICDoloView::OnViewFontsSmall()
{
	COleVariant vaZoomFactor(1l);

	ExecWB(OLECMDID_ZOOM, OLECMDEXECOPT_DONTPROMPTUSER,
		&vaZoomFactor, NULL);
}

void CPICDoloView::OnViewFontsSmallest()
{
	COleVariant vaZoomFactor(0l);

	ExecWB(OLECMDID_ZOOM, OLECMDEXECOPT_DONTPROMPTUSER,
		&vaZoomFactor, NULL);
}

// This demonstrates how we can use the Navigate2() function to load local files
// including local HTML pages, GIFs, AIFF files, etc.
void CPICDoloView::OnFileOpen()
{
	BOOL bValidString;
	CString str;
	bValidString = str.LoadString(IDS_FILETYPES);

	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, str);

	if(fileDlg.DoModal() == IDOK)
		Navigate2(fileDlg.GetPathName(), 0, NULL);
}

void CPICDoloView::OnUpdateGoForward(CCmdUI* pCmdUI) 
{
	CPICDoloDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pCmdUI->Enable (pDoc->IsFrwdAvailable ());
}

void CPICDoloView::OnUpdateGoBack(CCmdUI* pCmdUI) 
{
	CPICDoloDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pCmdUI->Enable (pDoc->IsBackAvailable ());
}

void CPICDoloView::OnDocumentComplete(LPCTSTR lpszURL) 
{
	// make sure the main frame has the new URL.  This call also stops the animation
//	((CMainFrame*)GetParentFrame())->SetAddress(lpszURL);

	CPICDoloDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->AddURLToHistory (GetLocationName (), lpszURL);
	((CMainFrame*)GetParentFrame())->SetProgress (0, -1);
	((CMainFrame*)GetParentFrame())->SetAddress(lpszURL);

	CHtmlView::OnDocumentComplete(lpszURL);
}

void CPICDoloView::OnTitleChange(LPCTSTR lpszText) 
{
	// this will change the main frame's title bar
	if (m_pDocument != NULL)
		m_pDocument->SetTitle(lpszText);
}

void CPICDoloView::OnBeforeNavigate2(LPCTSTR lpszURL, DWORD /*nFlags*/, LPCTSTR /*lpszTargetFrameName*/, CByteArray& /*baPostedData*/, LPCTSTR /*lpszHeaders*/, BOOL* /*pbCancel*/) 
{
	// start the animation so that is plays while the new page is being loaded
	((CMainFrame*)GetParentFrame())->SetAddress(lpszURL);
	((CMainFrame*)GetParentFrame())->StartAnimation();
}

void CPICDoloView::OnInitialUpdate() 
{
	GoHome();
	SetTimer(108,1000,NULL);

}

void CPICDoloView::OnProgressChange(long nProgress, long nProgressMax) 
{
	((CMainFrame*)GetParentFrame())->SetProgress(nProgress, nProgressMax);

	CHtmlView::OnProgressChange(nProgress, nProgressMax);
}

void CPICDoloView::OnDestroy() 
{
	CHtmlView::OnDestroy();
	CView::OnDestroy();		// Fixes CHtmlView bug
}


LRESULT CPICDoloView::OnNewURL(WPARAM wParam, LPARAM lParam)
{
	LPDISPATCH* ppDispatch=(LPDISPATCH*)wParam;
	SendMessage(WM_COMMAND, ID_FILE_NEW, 0);
	CMainFrame* pChildFrame = (CMainFrame*)AfxGetMainWnd();
	*ppDispatch=((CPICDoloView*)pChildFrame->GetActiveView())->GetApplication();
	return 0;

}

void CPICDoloView::OnNewWindow2(LPDISPATCH* ppDisp, BOOL* Cancel)
{
	// TODO: 在此添加专用代码和/或调用基类
	// Get a pointer to the application object
	CWinApp* pApp = AfxGetApp();
	// Get the correct document template
	CDocTemplate* pDocTemplate;
	POSITION pos = pApp->GetFirstDocTemplatePosition();
	pDocTemplate = pApp->GetNextDocTemplate(pos);
	ASSERT(pDocTemplate);
	// Create the new frame
	CFrameWnd* pNewFrame = (CFrameWnd*)pDocTemplate->CreateNewFrame(GetDocument(),(CFrameWnd*)AfxGetMainWnd());
	ASSERT(pNewFrame);
	// Activate the frame and set its active view
	pDocTemplate->InitialUpdateFrame(pNewFrame, NULL);
	CHtmlView* pWBVw = (CHtmlView*)pNewFrame->GetActiveView();
	ASSERT(pWBVw);
	pWBVw->SetRegisterAsBrowser(TRUE);
	*ppDisp = pWBVw->GetApplication();
	*Cancel=TRUE;
	CHtmlView::OnNewWindow2(ppDisp, Cancel);
	return;
	//CHtmlView::OnNewWindow2(ppDisp, Cancel);
//	::SendMessage(AfxGetMainWnd()->m_hWnd,WM_NEWURL,(WPARAM)ppDisp,NULL);
//	*Cancel=TRUE;
//	CHtmlView::OnNewWindow2(ppDisp, Cancel);
/*
	// Get a pointer to the application object 
	CWinApp* pApp=AfxGetApp();
	CDocTemplate* pDocTemplate;
	POSITION pos = pApp->GetFirstDocTemplatePosition();
	pDocTemplate=pApp->GetNextDocTemplate(pos);
	ASSERT(pDocTemplate);

	//CFrameWnd* pNewFrame =(CFrameWnd*) pDocTemplate->CreateNewFrame(GetDocument(),(CFrameWnd*)AfxGetMainWnd());		
	CFrameWnd* pNewFrame=(CFrameWnd*)::AfxGetMainWnd()->GetActiveWindow()->frame;
	ASSERT(pNewFrame);
	pDocTemplate->InitialUpdateFrame(pNewFrame,NULL);
	CPICDoloView* pWBVw=(CPICDoloView*)pNewFrame->GetActiveView();
	ASSERT(pWBVw);

	//pWBVw->m_webBrowser.SetRegisterAsBrowser(TRUE);
	//*ppDisp = pWBVw->m_webBrowser.GetApplication();
	*ppDisp = pWBVw->GetApplication();
	*/
}


/*
本函数是目录下载
1.获得有效连接.
2.获得页面的所有图片连接,保存到下载图片链表中,把下载目录连接保存到下载目录链表中.
3.调用下载线程下载所有图片
*/
CString str_refer;			//定义防盗链连接头
#include "DoloMoko.h"		//moko
#include "DoloTaobaoHB.h"	//淘宝画报
#include "DoloTaobaoMM.h"	//淘女郎
#include "Dolo8264COM.h"	//户外
#include "DoloYJZ9.h"		//妖姬宅
#include "Dolo7ymm.h"		//7夜妹妹
#include "Dolo800meinv.h"	//800美女
#include "DoloPocoCN.h"		//poco.cn的摄影图片
void CPICDoloView::OnDirdownload()
{
	b_endownload = true;
	// TODO: 在此添加命令处理程序代码	
	/*theApp.m_wndAddress.GetWindowText()		;*/	
	CString str;
	CMainFrame *pMain=(CMainFrame *)GetParentFrame();	
	//CMainFrame *pMain= theApp.m_pMainWnd->GetParentFrame();
	pMain->m_wndAddress.GetWindowText(str);
	pMain->updataTaskString(str);				//显示下载串内容
	//分析url
	if(-1 < str.Find(_T("moko.cc")))
	{
		str_refer=_T("Referer: http://moko.cc");
		auto_ptr<CDoloMoko> m_dolo(new CDoloMoko) ;
		m_dolo->SearchLayer3(str);		//获得像册照片		hasDownfilename	链表
	}else if(-1 < str.Find(_T("poco.cn")))
	{
		auto_ptr<CDoloPocoCN> m_dolo(new CDoloPocoCN) ;
		m_dolo->SearchLayer3(str);		//获得像册照片		hasDownfilename	链表
	}else if (-1 < str.Find(_T("huabao.taobao.com")))
	{
		str_refer=_T("Referer: http://huabao.taobao.com");
		auto_ptr<CDoloTaobaoHB> m_dolo(new CDoloTaobaoHB) ;
		m_dolo->SearchLayer3(str);		//获得像册照片		hasDownfilename	链表

	}else if (-1 < str.Find(_T("mm.taobao.com")))
	{
		str_refer=_T("Referer: http://mm.taobao.com");
		auto_ptr<CDoloTaobaoMM> m_dolo(new CDoloTaobaoMM) ;
		m_dolo->SearchLayer3(str);		//获得像册照片		hasDownfilename	链表
	}else if(-1 < str.Find(_T("u.8264.com/home-space-uid-")))
	{
		//str_refer=_T("Referer: http://mm.taobao.com");
		auto_ptr<CDolo8264COM> m_dolo(new CDolo8264COM) ;
		m_dolo->SearchLayer3(str);		//获得像册照片		hasDownfilename	链表
	}else if(-1 < str.Find(_T("www.yjz9.com")))
	{		
		auto_ptr<CDoloYJZ9> m_dolo(new CDoloYJZ9) ;
		m_dolo->SearchLayer3(str);		//获得像册照片		hasDownfilename	链表
	}else if(-1 < str.Find(_T("http://www.7ymm.com")))
	{		
		auto_ptr<CDolo7ymm> m_dolo(new CDolo7ymm) ;
		m_dolo->SearchLayer3(str);		//获得像册照片		hasDownfilename	链表
	}else if(-1 < str.Find(_T("http://www.800meinv.com")))
	{		
		auto_ptr<CDolo800meinv> m_dolo(new CDolo800meinv) ;
		m_dolo->SearchLayer3(str);		//获得像册照片		hasDownfilename	链表
	}
		pMain->updataTaskString(_T("不能下载本连接"));

}


void CPICDoloView::OnAutodownload()
{
	b_endownload = true;
	// TODO: 在此添加命令处理程序代码	
	/*theApp.m_wndAddress.GetWindowText()		;*/	
	CString str;
	CMainFrame *pMain=(CMainFrame *)GetParentFrame();	
	//CMainFrame *pMain= theApp.m_pMainWnd->GetParentFrame();
	pMain->m_wndAddress.GetWindowText(str);
	pMain->updataTaskString(str);				//显示下载串内容
	//分析url
	//int i= str.Find(_T("moko.cc"));
	if(-1 < str.Find(_T("moko.cc")))
	{
		str_refer=_T("Referer: http://moko.cc");
		//CDoloMoko * m_dolo=new CDoloMoko;
		auto_ptr<CDoloMoko> m_dolo(new CDoloMoko) ;
		m_dolo->SearchLayer1(str);		//获得主题第一层链表	mhashmap_url 链表
		
// 		CString str;
// 		CMainFrame *pMain=(CMainFrame *)GetParentFrame();	
// 		pMain->m_wndAddress.GetEditCtrl()->GetWindowText(str);
//		PageDownload(str,NULL);
	}else if(-1 < str.Find(_T("poco.cn")))
	{		
		auto_ptr<CDoloPocoCN> m_dolo(new CDoloPocoCN) ;
		m_dolo->SearchLayer1(str);		//获得像册照片		hasDownfilename	链表
	}else if (-1 < str.Find(_T("huabao.taobao.com")))
	{
		if(str.Find(_T("#"),0)>-1)
			str.Delete(str.Find(_T("#")),str.GetLength());
		str_refer=_T("Referer: http://huabao.taobao.com");
		auto_ptr<CDoloTaobaoHB> m_dolo(new CDoloTaobaoHB) ;
		m_dolo->SearchLayer1(str);		//获得主题第一层链表	mhashmap_url 链表

	}else if (-1 < str.Find(_T("mm.taobao.com")))
	{
		str_refer=_T("Referer: http://mm.taobao.com");
		auto_ptr<CDoloTaobaoMM> m_dolo(new CDoloTaobaoMM) ;
		m_dolo->SearchLayer1(str);		//获得主题第一层链表	mhashmap_url 链表

	}else if(-1 < str.Find(_T("u.8264.com/home-space-uid-")))
	{
		//str_refer=_T("Referer: http://mm.taobao.com");
		auto_ptr<CDolo8264COM> m_dolo(new CDolo8264COM) ;
		m_dolo->SearchLayer1(str);		//获得像册照片		hasDownfilename	链表
	}else if(-1 < str.Find(_T("www.yjz9.com")))
	{
		auto_ptr<CDoloYJZ9> m_dolo(new CDoloYJZ9) ;
		m_dolo->SearchLayer1(str);		//获得像册照片		hasDownfilename	链表
	}else if(-1 < str.Find(_T("http://www.7ymm.com")))
	{		
		auto_ptr<CDolo7ymm> m_dolo(new CDolo7ymm) ;
		m_dolo->SearchLayer1(str);		//获得像册照片		hasDownfilename	链表
	}else if(-1 < str.Find(_T("http://www.800meinv.com")))
	{		
		auto_ptr<CDolo800meinv> m_dolo(new CDolo800meinv) ;
		m_dolo->SearchLayer1(str);		//获得像册照片		hasDownfilename	链表
	}else 
		pMain->updataTaskString(_T("不能下载本连接"));

}

void CPICDoloView::OnDownloadBegin()
{
	// TODO: 在此添加专用代码和/或调用基类
	CHtmlView::OnDownloadBegin();
}


//检查下载文件是不是存在
bool CPICDoloView::checkDownFile(CString & filename)
{
	if(!b_noUseDB)
	{
//		int leng = GetDocument()->hasDownPic.GetSize();
		if(GetDocument()->hasDownPic[filename]==TRUE)
			return false;

	}
	return true;
}

//在下载时候弄一个间隔
bool my_exit=false;
bool CPICDoloView::myidle(void)
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

wstring UTF8ToUnicode( const string  str )
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
// Unicode编码转为UTF8  
bool UnicodeToUTF8(vector<char>& pu8, const wchar_t* pun, unsigned int uLen)  
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


void CPICDoloView::MokoPageDownload(CString urlAddr,CString DstDir)
{
	/*
	1.获得页面内容,分析页面,获得页面数组
	2.获得页面图片数组
	3.下载图片
	*/
	//下载网页	
	CString cs_download[100];
	int m_downNum=0;
	//UpdateData(Con2Val);  //从控件到成员变量
	CInternetSession httpSession;
	CInternetFile* htmlFile = (CInternetFile*) httpSession.OpenURL(urlAddr,1,INTERNET_FLAG_TRANSFER_ASCII);//m_url是输入控件Edit1的变量
	CString cs_content;
	photoNum=0;
	CChineseCode chna;
	CString cs_dir;

	while (htmlFile->ReadString(cs_content))
	{		
		wstring wstr1;
		wstr1=UTF8ToUnicode( cs_content.GetBuffer() );
		CString str1( wstr1.c_str() ); 
		myidle();
		if(str1.Find(_T("<a class=\"gC\""),0)>0)
		{
			//cs_download[m_downNum]=cs_content.Right(cs_content.GetLength()-cs_content.Find(_T("<img class=\"borderOn\" src="),0)); 
			//			cs_download[m_downNum]=str1;
			//获得目录
			cs_dir=str1;
			int aaa;
			aaa=cs_dir.Find(_T("hidefocus=\"ture\" >"),0);
			cs_dir.Delete(0,aaa+18);	
			aaa=cs_dir.Find(_T("</a>"));
			cs_dir.Delete(aaa,cs_dir.GetLength());
			mokoCreateDirectory(cs_dir,NULL);
			Globe_Dir=cs_dir;
			DstDir=Globe_Dir;
		}
		//先找到照片数量		
		if(str1.Find(_T("sImg gC"),0)>-1)
		{
			int aaa=str1.Find(_T("title=\"图片\" alt=\"图片\" hidefocus=\"true\" >("),0);
			str1.Delete(0,aaa+43);
			int aaa1=str1.Find(_T(')'),0);
			str1.Delete(aaa1,str1.GetLength());
			str1.Format(_T("%d"),photoNum);//获得照片数量
			continue;			
		}
		//判断图片连接,获得第一个像册小图片	
		if(str1.Find(_T("img class=\"cover bd\""),0)>0)
		{
			//cs_download[m_downNum]=cs_content.Right(cs_content.GetLength()-cs_content.Find(_T("<img class=\"borderOn\" src="),0)); 
			cs_download[m_downNum]=str1;
			//获得目录
			cs_dir=str1;
			int aaa;
			aaa=cs_dir.Find(_T("alt=\""));
			cs_dir.Delete(0,aaa+5);
			aaa=cs_dir.Find(_T("\""));
			cs_dir.Delete(aaa,cs_dir.GetLength());

			m_downNum++;
		}
		if(cs_content.Find(_T("<div class=\"pic dBd\">"),0)>0)
		{
			htmlFile->ReadString(cs_content);	//读取第二行
			//cs_download[m_downNum]=cs_content.Right(cs_content.GetLength()-cs_content.Find(_T("<img class=\"borderOn\" src="),0)); 
			cs_download[m_downNum]=cs_content;
			m_downNum++;
		}
		//参考链接 http://www.moko.cc/post/songanni/21233.html 
		if(cs_content.Find(_T("id=\"seePhoto"),0)>=0)//如果照片存在左边的选择
		{

			do{
				wstring wstr1;
				wstr1=UTF8ToUnicode( cs_content.GetBuffer() );
				CString str1( wstr1.c_str() ); 
				myidle();
				//先找到照片数量
				if(str1.Find(_T("<input type=\"hidden\" value=\"http"),0)>0)
				{
					//cs_download[m_downNum]=cs_content.Right(cs_content.GetLength()-cs_content.Find(_T("<img class=\"borderOn\" src="),0)); 
					cs_download[m_downNum]=cs_content;
					m_downNum++;
				}			
				if((photoNum+1)==m_downNum)
					break;
			}while (htmlFile->ReadString(cs_content));
			break;
		}
		if(cs_content.Find(_T("class=\"pList dBd\""),0)>=0)		//如是列表
		{
			htmlFile->ReadString(cs_content);
			wstring wstr1;
			wstr1=UTF8ToUnicode( cs_content.GetBuffer() );
			CString str1( wstr1.c_str() ); 
			int sta=0;
			while(str1.Find(_T("hidden\" value=\"http"),0)>0)
			{
				sta=str1.Find(_T("hidden\" value=\"http"));
				str1=str1.Right(str1.GetLength()-sta-3);
				cs_download[m_downNum]=str1;
				cs_download[m_downNum].Left(sta);
				sta=str1.Find(_T("jpg"));
				str1=str1.Right(str1.GetLength()-sta-3);
				m_downNum++;
			}
			//while(photoNum!=)
			break;
		}
	}
	htmlFile->Close();
	httpSession.Close();
	delete htmlFile;

	int m0=0;
	int m1=0;
	//处理jpg的链接
	//UpdateData(Con2Val);
	//b_CKDir=0  建立目录  =1 不建立目录
	if(cs_dir.IsEmpty())
		cs_dir=_T("无名");
	if(cs_dir.GetAt(0)==_T(' '))
		cs_dir.SetAt(0,_T('_'));
	if(cs_dir.GetAt(cs_dir.GetLength())==_T(' '))
		cs_dir.SetAt(cs_dir.GetLength(),_T('_'));
	//m_ListBox.SetCurSel(m_ListBox.GetCount()-1);
	CString aaa;
	aaa.Format(_T("%d"),pagecount);
	//hce listadd(0,_T("下载像册")+aaa+_T(": ")+cs_dir);	
	CMainFrame *pMain=(CMainFrame *)GetParentFrame();	
	pMain->updataTaskString(_T("下载像册")+aaa+_T(": ")+cs_dir);
	pagecount++;
	//	Invalidate(FALSE);


	if(DstDir.IsEmpty())
	{
		checkDirname(DstDir);
		checkDirname(cs_dir);
		mokoCreateDirectory( cs_dir,NULL);
	}
	else
	{
		checkDirname(DstDir);
		checkDirname(cs_dir);
		CreateDirectory(DstDir,NULL);
		CreateDirectory(DstDir+_T("/")+cs_dir,NULL);
	}
	for(int i=0;i<m_downNum;i++)
	{	
		m0=cs_download[i].Find(_T("\"http"),NULL);
		cs_download[i].Delete(0,m0+1);
		m1=cs_download[i].Find(_T(".jpg\""));
		cs_download[i].Delete(m1+4,cs_download[i].GetLength());	
		myidle();
		//UpdateData(Val2Con);
		if(DstDir.IsEmpty())
		{
			//			mokoCreateDirectory( cs_dir,NULL);			
			// 			m_ListBox.AddString(_T("图片:")+i);
			// 			UpdateData(Val2Con);
			imgDownload(cs_download[i],_T("./")+cs_dir);			
		}
		else
		{
			//			mokoCreateDirectory(DstDir+_T("/")+cs_dir,NULL);
			// 			m_ListBox.AddString(_T("图片:")+i);
			// 			UpdateData(Val2Con);
			if(b_CKDir==0)		//建立目录
				imgDownload(cs_download[i],DstDir+_T("/")+cs_dir);
			else
				imgDownload(cs_download[i],DstDir);
		}

	}
}
void CPICDoloView::imgDownload(CString urlimgAddr,CString DstDIR)
{
//	Download(urlimgAddr,DstDIR);
}
void CPICDoloView::mokoCreateDirectory(CString mokoDir,LPSECURITY_ATTRIBUTES lpSecurityAttributes)//判断目录字符
{
	checkDirname(mokoDir);
	CreateDirectory(mokoDir,NULL);
}
void CPICDoloView::checkDirname(CString &mokoDir)
{
	myidle();
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



void CPICDoloView::OnCreatefile()
{
	// TODO: 在此添加命令处理程序代码
    //MessageBox(_T("this zhu 猪22"));
 	CMainFrame   *pMain=(CMainFrame   *)AfxGetApp()-> m_pMainWnd; 
 	CPICDoloDoc *pDoc = (CPICDoloDoc *)GetDocument();


	if(::MessageBox(this-> m_hWnd, _T("现在会对本目录进行文件汇总\r\n生成的数据文件会减少重复下载\r\n本操作时间会较长，静请等候 "),
		_T("生成图片数据文件"),   MB_OKCANCEL)   ==  IDOK) 
	{ 
		//ListFolder(_T(".\\"));

		ListFolder1();
	}
 	int i=pDoc->hasDownPic.GetCount();
 	CString str;	
 	str.Format(_T("你现在有图片: %d 个"), i);
 	pMain->outputString(str);
 	pDoc->SaveALLMyFile();
	str = _T("生成完毕");
	pMain->outputString(str);	
	str = _T("############################");
	pMain->outputString(str);	
}


// 搜索文件 把文件存入到数据中，进行图像数据备份
void CPICDoloView::ListFolder(CString sPath)
{
	CFileFind   ff; 
	BOOL   bFound; 
	bFound = ff.FindFile(sPath   +   _T("*.*"));//找第一个文件 
	while(bFound)//如果找到,继续 
	{ 
		bFound  = ff.FindNextFile(); 
		CString   sFilePath   =   ff.GetFilePath(); 

		if(ff.IsDirectory())//如果是目录,注意任何一个目录都包括.和..目录 
		{ 
			if(!ff.IsDots())//去除.和..目录 
				ListFolder(sFilePath);//递归下一层目录 
		}
		else
		{ 		 
 			if(sFilePath.Right(4).MakeUpper()==_T(".JPG") ||sFilePath.Right(5).MakeUpper()== _T(".JPEG"))
 			{
				CMainFrame   *pMain=(CMainFrame   *)AfxGetApp()-> m_pMainWnd; 
				CPICDoloDoc *pDoc = (CPICDoloDoc *)GetDocument();
 				pDoc->hasDownPic[sFilePath]=TRUE;				
				pMain->outputString(sFilePath);	
 			}
				//AfxMessageBox(sFilePath);//枚举到的文件名字 
		} 
	}
	ff.Close(); 
}
int m_listNum=0;
CString cs_listNum;
void CPICDoloView::ListFolder1()
{
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(_T("*.*"),&fd);
	if(hFind != INVALID_HANDLE_VALUE)
	{
		do 
		{
			if(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				CString name = fd.cFileName;
				if(name != _T(".")&& name !=_T(".."))
				{
					::SetCurrentDirectory(fd.cFileName);
					myidle();
					ListFolder1();
					::SetCurrentDirectory(_T(".."));
				}
			}
			else if(!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{				
				CString str = fd.cFileName;
				if((str.Right(4)==_T(".JPG"))||(str.Right(4)==_T(".jpg"))  ||(str.Right(5)== _T(".JPEG")))
				{
					TRACE(_T("%s\n"),fd.cFileName);
					CMainFrame   *pMain=(CMainFrame   *)AfxGetApp()-> m_pMainWnd; 
					CPICDoloDoc *pDoc = (CPICDoloDoc *)GetDocument();					
					GetCurrentDirectory(MAX_PATH,path);
					CString str1;
					str1.Format(_T("%s\\"),path);
					pDoc->hasDownPic[path+str]=TRUE;				
					pMain->outputString(str);
					m_listNum++;
					cs_listNum.Format(_T("%d"),m_listNum);
					GetStatusBar ().SetPaneText(3,cs_listNum,1);
					myidle();
					
				}
				else
				{
					TRACE(_T("%s\n"),fd.cFileName);
				}
			}
		}while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	return;
}

void CPICDoloView::OnUpdataAllpic()
{
	// TODO: 在此添加命令处理程序代码
	//MessageBox(_T("gengxin"));
	SetTimer(108,1000,NULL);
	AddDownload (_T("http://www.codeproject.com/KB/IP/asynchttp/preview.jpg")) ;

	// download with custom user-agent and header
// 	HTTP_SEND_HEADER   h ;
// 	h.m_url = _T("http://www.codeproject.com") ;
// 	h.m_user_agent = _T("My App") ;
// 	h.m_header = _T("Referer: http://www.codeproject.com/\r\n") ;
// 	h.m_header += _T("Accept: */*\r\n") ;
// 	AddDownload (h) ;


	return; 
	m_listNum++;
	cs_listNum.Format(_T("%d"),m_listNum);
	//GetStatusBar ().SetPaneTextColor(3,COLORREF(16711680),1);
	GetStatusBar ().SetPaneText(3,cs_listNum,1);
	((CMainFrame*)GetParentFrame())->SetProgress (0, -1);
}


void CPICDoloView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if((108 == nIDEvent)&&b_endownload== true)
	{
		//下载代码
		if(v_doloST.size()!=0)
		{
			if(v_doloST[0].cs_ReferHead.IsEmpty())
			{
				b_endownload=false;
				AddDownload(v_doloST[0].cs_url);
			}
			else{
				b_endownload=false;
				HTTP_SEND_HEADER   h ;
				h.m_url = v_doloST[0].cs_url ;
				/*h.m_user_agent = _T("My App") ;*/
				h.m_header = v_doloST[0].cs_ReferHead;
				h.m_header += _T("Accept: */*\r\n") ;
				AddDownload (h) ;
			}
		}
	}
	__super::OnTimer(nIDEvent);
}





// void CPICDoloView::ONSelectWebsite(UINT nID)
// {
// 	int n;
// 	n=nID;
// }
