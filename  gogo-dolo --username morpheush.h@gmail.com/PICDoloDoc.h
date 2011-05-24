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

#define FIRST_HISTORY_COMMAND	0x1000
#define HISTORY_LEN	10

#include "HistoryObj.h"
#include <afxtempl.h>
typedef CList<CHistoryObj*, CHistoryObj*> _T_HistotyList;


//CMap<CString, CString&, CString, CString&> myMap;

class CPICDoloDoc : public CDocument
{
protected: // create from serialization only
	CPICDoloDoc();
	DECLARE_DYNCREATE(CPICDoloDoc)

// Attributes
public:
	CArray<CHistoryObj*, CHistoryObj*>	m_arHistory;
	int	m_iHistoryOffset;
// 	hash_set	mhashset_jpgName;		//保存图片文件名称
// 	//hash_map	mhashmap_url;			//保存url名称
	CMap<CString, LPCTSTR ,BOOL,BOOL&>	hasDownPic;		//保存图片文件名称
 	CMap<CString, LPCTSTR ,CString, LPCTSTR> mhashmap_url;		///保存url名称
	CMapStringToString myMap_url;
	
// Operations
public:
	void GetBackList (_T_HistotyList& lst) const;
	void GetFrwdList (_T_HistotyList& lst) const;

	BOOL IsBackAvailable () const
	{
		return m_iHistoryOffset < m_arHistory.GetSize () - 1;
	}

	BOOL IsFrwdAvailable ()
	{
		return m_iHistoryOffset > 0;
	}

	CHistoryObj* GoBack ()
	{
		if (m_iHistoryOffset >= m_arHistory.GetSize ())
		{
			ASSERT (FALSE);
			return NULL;
		}

		return m_arHistory [++ m_iHistoryOffset];
	}

	CHistoryObj* GoForward ()
	{
		if (m_iHistoryOffset < 1)
		{
			ASSERT (FALSE);
			return NULL;
		}

		return m_arHistory [--m_iHistoryOffset];
	}

	CHistoryObj* Go (UINT uiCmd);
	CHistoryObj* AddURLToHistory (const CString& strTitle, const CString& strURL);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPICDoloDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	void SaveALLMyFile(void);
	void GetAllMyFile(void);
public:
	virtual ~CPICDoloDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPICDoloDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
