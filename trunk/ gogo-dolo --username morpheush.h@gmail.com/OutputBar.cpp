// OutputBar.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PICDolo.h"
#include "OutputBar.h"



// COutputBar

IMPLEMENT_DYNAMIC(COutputBar, CDockablePane)

COutputBar::COutputBar()
{

}

COutputBar::~COutputBar()
{
}


BEGIN_MESSAGE_MAP(COutputBar, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// COutputBar ��Ϣ�������





int COutputBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	m_Font.CreateStockObject(DEFAULT_GUI_FONT);

	CRect rectClient(0, 0, lpCreateStruct->cx, lpCreateStruct->cy);

	// Create output pane:
	const DWORD dwStyle = LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL |LBS_NOSEL;

	if (!m_wndOutput.Create(dwStyle, rectClient, this, 1))
	{
		TRACE0("Failed to create output window\n");
		return -1;      // fail to create
	}

	m_wndOutput.SetFont(&m_Font);
	m_wndOutput.AddString(_T("�˴�����ʾ���������Ϣ"));
	m_wndOutput.AddString(_T("ллʹ��"));
	m_wndOutput.AddString(_T("�汾V3-0-4"));
	m_wndOutput.AddString(_T("����������ϵ��"));
	m_wndOutput.AddString(_T("morpheush.h@gmail.com "));
	m_wndOutput.AddString(_T(""));
	return 0;
}

void COutputBar::OutputString(CString& str)
{
	//m_wndOutput.AddString(str);	
	if(m_wndOutput.GetCount()>50000)			//������ʾ 5���
		m_wndOutput.ResetContent();
	if(m_wndOutput.GetCurSel() <0)
		m_wndOutput.InsertString(0,str);
	else{
		m_wndOutput.ResetContent();
		m_wndOutput.InsertString(0,str);
	}
	
}
void COutputBar::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	CRect rc;
	GetClientRect(rc);

	m_wndOutput.SetWindowPos(NULL, rc.left + 1, rc.top + 1, rc.Width() - 2, rc.Height() - 2, SWP_NOACTIVATE | SWP_NOZORDER );

	AdjusrHorzScroll(m_wndOutput);
	// TODO: �ڴ˴������Ϣ����������
}
void COutputBar::AdjusrHorzScroll(CListBox& wndListBox)
{
	CClientDC dc(this);
	CFont* pOldFont = dc.SelectObject(&m_Font);

	int cxExtentMax = 0;

	for (int i = 0; i < wndListBox.GetCount(); i ++)
	{
		CString strItem;
		wndListBox.GetText(i, strItem);

		cxExtentMax = max(cxExtentMax, dc.GetTextExtent(strItem).cx);
	}

	wndListBox.SetHorizontalExtent(cxExtentMax);
	dc.SelectObject(pOldFont);
}