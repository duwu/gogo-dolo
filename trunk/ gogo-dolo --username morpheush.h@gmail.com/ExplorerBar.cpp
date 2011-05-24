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
#include "ExplorerBar.h"
#include "PICDoloDoc.h"
#include "PICDoloView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int idTree = 1;
/*extern struct ST_URL;*/
extern vector<struct ST_URL> myUrl;
/////////////////////////////////////////////////////////////////////////////
// CExplorerBar

CExplorerBar::CExplorerBar()
{
}

CExplorerBar::~CExplorerBar()
{
}

BEGIN_MESSAGE_MAP(CExplorerBar, CMFCTasksPane)
	//{{AFX_MSG_MAP(CExplorerBar)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_NOTIFY(TVN_SELCHANGED, idTree, OnSelectTree)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExplorerBar message handlers

int CExplorerBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMFCTasksPane::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetWindowText (_T("Explorer Bar"));
	EnableOffsetCustomControls (FALSE);

	// ----------------------
	// Create favorites list:
	// ----------------------
	CRect rectDummy (0, 0, 0, 0);
	const DWORD dwTreeStyle =	WS_CHILD | WS_VISIBLE | TVS_SINGLEEXPAND | TVS_TRACKSELECT;

	if(!m_wndFavorites.Create (dwTreeStyle, rectDummy,
		this, idTree))
	{
		TRACE0("Failed to create the Favorites window\n");
		return FALSE;      // fail to create
	}

	theApp.m_Favorites.FillTree (m_wndFavorites);

	// -----------
	// Add groups:
	// -----------
	//CMFCTasksPane 是相关操作
//	int nGroup1 = AddGroup (_T("Favorites"), FALSE, TRUE);
// 	AddWindow (nGroup1, m_wndFavorites.GetSafeHwnd (), 100);
// 
// 	nGroup3 = AddGroup (_T("开始下载"),FALSE,TRUE);	
// 	AddTask (nGroup3, _T("本软件是美女图片下载辅助工具"), -1,0);
// 	AddTask (nGroup3, _T("没有做成插件主要是考虑兼容性麻烦"), -1,0);
// 	AddTask (nGroup3, _T("第一版的问题是不适合非专业人士"), -1,0);
// 	AddTask (nGroup3, _T("联系邮箱"), -1,0);
// 	AddTask (nGroup3, _T("morpheush.h@gmail.com"), -1,0);
// 	AddTask (nGroup3, _T("9"), -1,0);
// 	AddTask (nGroup3, _T("8"), -1,0);
// 	AddTask (nGroup3, _T("7"), -1,0);
// 	AddTask (nGroup3, _T("6"), -1,0);
// 	AddTask (nGroup3, _T("5"), -1,0);
// 	AddTask (nGroup3, _T("4"), -1,0);
// 	AddTask (nGroup3, _T("3"), -1,0);
// 	AddTask (nGroup3, _T("2"), -1,0);
// 	AddTask (nGroup3, _T("1"), -1,0);
// 	AddTask (nGroup3, _T("0"), -1,0);
	//RemoveTask(nGroup3,1,1);	

	int nGroup2 = AddGroup (_T("稂莠links"));
	//initurl();
 	for(UINT i=0;i<myUrl.size();i++)
 	{
 		AddTask (nGroup2, myUrl[i].name, -1, myUrl[i].id);
 	}
// 	AddTask (nGroup2, _T("Moko"), -1, ID_LINK_MSDN);
// 	AddTask (nGroup2, _T("淘宝画报"), -1, ID_LINK_MICROSOFT);
// 	AddTask (nGroup2, _T("淘宝女郎"), -1, ID_LINK_VISUALCPP);
// 	AddTask (nGroup2, _T("8564户外美女"), -1, ID_LINK_8564_COM);
// 	AddTask (nGroup2, _T("妖姬宅"), -1, ID_BEGINID);

	return 0;
}
//************************************************************************************
void CExplorerBar::OnSelectTree(NMHDR* /*pNMHDR*/, LRESULT* pResult) 
{
	HTREEITEM hTreeItem = m_wndFavorites.GetSelectedItem ();
	if (hTreeItem != NULL)
	{
		CFavorit* pFavorit = (CFavorit*) m_wndFavorites.GetItemData (hTreeItem);
		ASSERT_VALID (pFavorit);

		if (!pFavorit->GetURL ().IsEmpty ())
		{
			CPICDoloView* pView = 
				(CPICDoloView*)((CFrameWnd*) AfxGetMainWnd ())->GetActiveView ();
			ASSERT_VALID (pView);
	
			pView->Navigate2 (pFavorit->GetURL ());
		}
	}
	
	*pResult = 0;
}


// 添加显示
void CExplorerBar::AddTaskString(CString str)
{
	int i_count = GetTaskCount(nGroup3);
	if(i_count>15)
		RemoveTask(nGroup3,0,1);	
	AddTask (nGroup3, str, -1);
}
