#pragma once


// COutputBar

class COutputBar : public CDockablePane
{
	DECLARE_DYNAMIC(COutputBar)

public:
	COutputBar();
	void AdjusrHorzScroll(CListBox& wndListBox);
	void OutputString(CString& str);
	virtual ~COutputBar();
	CFont m_Font;
	CListBox m_wndOutput;
protected:
	DECLARE_MESSAGE_MAP()
	
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


