// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#pragma once
#include "MainFrm.h"
#include "PICDoloDoc.h"
#include "http_download.h"
#include <iostream>
#include <fstream>
using namespace std;
#include "Dolo.h"
/*extern struct ST_LP;*/
extern vector<struct ST_Dolo> v_doloST;
extern CString cs_CurrDir;

extern bool b_endownload ;

class CPICDoloView : public CHtmlView,
					public FCHttpDownloadManager
{
protected: // create from serialization only
	CPICDoloView();
	DECLARE_DYNCREATE(CPICDoloView)

// Attributes
public:
	CPICDoloDoc* GetDocument();
	TCHAR	path[MAX_PATH];
// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPICDoloView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnDocumentComplete(LPCTSTR lpszURL);
	virtual void OnTitleChange(LPCTSTR lpszText);
	virtual void OnBeforeNavigate2(LPCTSTR lpszURL, DWORD nFlags, LPCTSTR lpszTargetFrameName, CByteArray& baPostedData, LPCTSTR lpszHeaders, BOOL* pbCancel);
	virtual void OnInitialUpdate();
	virtual void OnProgressChange(long nProgress, long nProgressMax);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPICDoloView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPICDoloView)
	afx_msg void OnGoBack();
	afx_msg void OnGoForward();
	afx_msg void OnGoSearchTheWeb();
	afx_msg void OnGoStartPage();
	afx_msg void OnViewStop();
	afx_msg void OnViewRefresh();
	afx_msg void OnViewFontsLargest();
	afx_msg void OnViewFontsLarge();
	afx_msg void OnViewFontsMedium();
	afx_msg void OnViewFontsSmall();
	afx_msg void OnViewFontsSmallest();
	afx_msg void OnFileOpen();
	afx_msg void OnUpdateGoForward(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGoBack(CCmdUI* pCmdUI);
	afx_msg void OnDestroy();
	//自定义消息
	afx_msg LRESULT OnNewURL(WPARAM wParam, LPARAM lParam);	
//	afx_msg void ONSelectWebsite(UINT nID);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDirdownload();
	afx_msg void OnAutodownload();
	afx_msg void OnCreatefile();

	virtual void OnDownloadBegin();
	virtual void OnNewWindow2(LPDISPATCH* ppDisp, BOOL* Cancel);
	// 用来下载图片函数
	int m_DownNum; //
	bool b_noUseDB;
	bool m_bAutoUpdata;
	int photoNum;			//照片下载数量
// 	bool Download(const  CString &  strFileURLInServer,  // 待下载文件的URL 
// 		const  CString  &  strFileLocalFullPath) ;// 存放到本地的路径 
	bool checkDownFile(CString & filename);
	bool myidle(void);

	CString Globe_Dir;		//全局目录
	BOOL b_CKDir;			//决定是不是建立目录
	int pagecount;
	void MokoPageDownload(CString urlAddr,CString DstDir);
	void mokoCreateDirectory(CString mokoDir,LPSECURITY_ATTRIBUTES lpSecurityAttributes);//判断目录字符
	void checkDirname(CString& mokoDir);
	void imgDownload(CString urlimgAddr,CString DstDIR);
	// 搜索文件
	void ListFolder(CString sPath);
	void ListFolder1();
	afx_msg void OnUpdataAllpic();

	CMFCStatusBar& GetStatusBar () const
	{
		return ((CMainFrame*) AfxGetMainWnd ())->GetStatusBar ();
	}


	
	virtual void OnAfterDownloadFinish (FCHttpDownload* pTask)
	{
		// get all downloaded data
		BYTE   * p ;
		int    n ;
		pTask->PopReceived(p, n) ;
		if (p)
		{
			// process ...
			CString strFileURLInServer;
			strFileURLInServer = v_doloST[0].cs_url;
			int i = strFileURLInServer.ReverseFind(_T('/'));
			CString str;
			str = strFileURLInServer.Right(strFileURLInServer.GetLength()-i-1);
			str=cs_CurrDir+v_doloST[0].cs_LocalFullPath+_T("\\")+str;
			fstream ofs; 
			ofs.open(str,ios::in|ios::out|ios::binary|ios::trunc);
			ofs.write((char *)p,n);
			delete[] p ;
			ofs.close();
			CMainFrame *pFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd;
			
			CString cs_i;
			cs_i.Format(_T("余%dP"),v_doloST.size()-1);
			cs_i+=v_doloST[0].cs_url;
			pFrame->m_mOutputBar.OutputString(cs_i);
			
			v_doloST.erase(v_doloST.begin());
			if(v_doloST.size()==0)
			{
				CString str;
				str = _T("下载完毕");
				pFrame->m_mOutputBar.OutputString(str);
				//MessageBox(_T("下载完毕"));
			}
			b_endownload= true;

		}
	}
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};





#ifndef _DEBUG  // debug version in PICDoloView.cpp
inline CPICDoloDoc* CPICDoloView::GetDocument()
   { return (CPICDoloDoc*)m_pDocument; }
#endif

