#pragma once
#include <iostream>
#include <map>
#include <array>
#include <regex>
#include <string>
using namespace std;
using namespace tr1;
using tr1::regex;
using tr1::smatch;
using tr1::match_results;
using namespace std;
#include "MainFrm.h"
#include "HistoryObj.h"
typedef CList<CHistoryObj*, CHistoryObj*> _T_HistotyList;



//extern struct ST_LP;

extern struct ST_LP st_lp;
extern UINT Download1(LPVOID pParam);
extern bool DownloadPic( const  CString &  strFileURLInServer, 
	const  CString  &  strFileLocalFullPath,
	const  CString &referHead
	);

struct ST_Dolo{
	CString cs_url;
	CString	cs_LocalFullPath;
	CString cs_ReferHead;
};
extern vector<struct ST_Dolo> v_doloST;
extern CString cs_CurrDir;
class CDolo
{
public:
	bool my_exit;
	CWinThread* m_pMyThread;

	CArray<CHistoryObj*, CHistoryObj*>	m_arHistory;
	int	m_iHistoryOffset;
	// 	hash_set	mhashset_jpgName;		//����ͼƬ�ļ�����
	// 	//hash_map	mhashmap_url;			//����url����
	CMap<CString, LPCTSTR ,BOOL,BOOL&>	hasDownfilename;		//����ͼƬ�ļ�����
	CMap<CString, LPCTSTR ,CString, LPCTSTR> mhashmap_url;		///����url����

	//http��Ҫ������
	CInternetSession httpSession;
	CInternetFile* htmlFile ;
	ST_Dolo s_dolo;
	
public:
	CDolo(void);
	virtual ~CDolo(void);
	wstring UTF8ToUnicode( const string  str );
	bool UnicodeToUTF8(vector<char>& pu8, const wchar_t* pun, unsigned int uLen)  ;

	virtual bool SearchLayer1(CString &str_url);
	virtual bool SearchLayer2(CString &str_url);
	virtual bool SearchLayer3(CString &str_url);

	BOOL myidle();		//����ʱ��Ƭ
	bool checkDownFile(CString & filename);			//�ж��ļ��ǲ����Ѿ�����
	void checkDirname(CString &mokoDir);

	// ���ؼ�����txt������ʵ�Ҹо���html����
	bool Resume2Txt(void);
	// ����û����ĵ�����
	bool GetManfile(CString& file_url);
	// ����һ��Ҫ���ص�url,���ص������ص�ҳ������
	bool DownloadUrlPage(CString & UrlPage, CString & cs_webContent);
	void insertstring(CString &str)
	{	
		::SendMessage(AfxGetMainWnd()->m_hWnd,WM_UPOUTPUTtoSELANG,(WPARAM)str.GetBuffer(),NULL);
	}
};




