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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPICDoloDoc

IMPLEMENT_DYNCREATE(CPICDoloDoc, CDocument)

BEGIN_MESSAGE_MAP(CPICDoloDoc, CDocument)
	//{{AFX_MSG_MAP(CPICDoloDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPICDoloDoc construction/destruction

CPICDoloDoc::CPICDoloDoc()
{
	m_iHistoryOffset = 0;
	m_arHistory.SetSize (0, 1);
	hasDownPic.InitHashTable(408491);
	mhashmap_url.InitHashTable(408491);	
	GetAllMyFile();
}

CPICDoloDoc::~CPICDoloDoc()
{
	for (int i = 0; i < m_arHistory.GetSize (); i ++)
	{
		ASSERT (m_arHistory [i] != NULL);
		delete m_arHistory [i];
	}
}

BOOL CPICDoloDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPICDoloDoc serialization

void CPICDoloDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPICDoloDoc diagnostics

#ifdef _DEBUG
void CPICDoloDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPICDoloDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPICDoloDoc commands

CHistoryObj* CPICDoloDoc::AddURLToHistory (const CString& strTitle, const CString& strURL)
{
	ASSERT (m_arHistory.GetSize () <= HISTORY_LEN);

	for (int i = 0; i < m_arHistory.GetSize (); i ++)
	{
		CHistoryObj* pObj = m_arHistory [i];
		ASSERT (pObj != NULL);

		if (pObj && pObj->GetTitle () == strTitle && pObj->GetURL () == strURL)
		{
			return pObj;
		}
	}

	if (m_arHistory.GetSize () == HISTORY_LEN)
	{
		delete m_arHistory [0];
		m_arHistory.RemoveAt (0);
	}

	CHistoryObj* pObj = new CHistoryObj (strTitle, strURL, 
		FIRST_HISTORY_COMMAND + (UINT)m_arHistory.GetSize ());
	m_arHistory.InsertAt (0, pObj);

	m_iHistoryOffset = 0;
	return pObj;
}
//****************************************************************************************
void CPICDoloDoc::GetBackList (_T_HistotyList& lst) const
{
	lst.RemoveAll ();
	for (int i = m_iHistoryOffset + 1; i < m_arHistory.GetSize () ; i ++)
	{
		lst.AddTail (m_arHistory [i]);
	}
}
//****************************************************************************************
void CPICDoloDoc::GetFrwdList (_T_HistotyList& lst) const
{
	lst.RemoveAll ();
	for (int i = m_iHistoryOffset - 1; i >= 0; i --)
	{
		ASSERT (i < m_arHistory.GetSize ());
		lst.AddTail (m_arHistory [i]);
	}
}
//****************************************************************************************
CHistoryObj* CPICDoloDoc::Go (UINT uiCmd)
{
	for (int i = 0; i < m_arHistory.GetSize (); i ++)
	{
		CHistoryObj* pObj = m_arHistory [i];
		ASSERT (pObj != NULL);

		if (pObj && pObj->GetCommand () == uiCmd)
		{
			m_arHistory.RemoveAt (i);
			m_arHistory.Add (pObj);

			m_iHistoryOffset = 0;
			return pObj;
		}
	}

	return NULL;
}


void CPICDoloDoc::SaveALLMyFile(void)
{
	CFile file;		 
	int i;
	i=mhashmap_url.GetCount();
	if(i>0)
	{
		if(file.Open(_T("doloUrl.dbf"),CFile::modeCreate|CFile::modeWrite))//|CFile::typeBinary))
		{
			CArchive ar(&file,CArchive::store);
			mhashmap_url.Serialize(ar);
			//i=mhashmap_url.GetCount();
			//mhashmap_url.RemoveAll();			
		}	
		file.Close();
	}
	i=hasDownPic.GetCount();
	if(i>0)
	{
		if(file.Open(_T("doloPic.dbf"),CFile::modeCreate|CFile::modeWrite))
		{
			CArchive ar(&file,CArchive::store);
			hasDownPic.Serialize(ar);
			//i=hasDownfilename.GetCount();
			//hasDownPic.RemoveAll();					
		}	
		file.Close();
	}
}


void CPICDoloDoc::GetAllMyFile(void)
{
	CFile file;		 
	int i;
	if(file.Open(_T("doloUrl.dbf"),CFile::modeRead))
	{
		CArchive ar(&file,CArchive::load);
		mhashmap_url.Serialize(ar);
		i=mhashmap_url.GetCount();
		file.Close();
	}		

	if(file.Open(_T("doloPic.dbf"),CFile::modeRead))
	{
		CArchive ar(&file,CArchive::load);
		hasDownPic.Serialize(ar);
		i=hasDownPic.GetCount();	
		file.Close();
	}		
}

