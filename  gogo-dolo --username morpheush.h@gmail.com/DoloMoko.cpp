#include "StdAfx.h"
#include "DoloMoko.h"


CDoloMoko::CDoloMoko(void)
{
	CreateDirectory(_T("Moko"),NULL);
}


CDoloMoko::~CDoloMoko(void)
{
}

bool CDoloMoko::GetManfile(CString& file_url)
{
	return false;
}
/*
��õ�һ�������
*/

/*
1.�з���content road gC1 dBd ��ҳ�����²��������� http://www.moko.cc/post/wangtingyu/indexpost.html  ��������g1mC u ���йؼ���ѡ�����������
 ����coverBg wC ����������ַ.
2.�������http://www.moko.cc/post/laomai/indexpost.html  coverBg wC �ؼ���,����������ַ


*/
#pragma comment(lib, "urlmon.lib")
bool CDoloMoko::SearchLayer1(CString &str_url)
{

//http://www.moko.cc/post/liuwenna/indexpost.html
	int i=0;
	i = str_url.Find(_T("/"),24);
	str_url =  str_url.Left(i);
	CString	cstcs_AlbumRoot;
	cstcs_AlbumRoot=str_url;
	CString man_url;
	man_url=str_url;
	str_url+=_T("/indexpost.html");
	man_url.Delete(19,5);
	man_url+=_T("/browseUserProfile.html");
	CString cs_content;//������ҳ����
	CString cs_dir;
	CString cs_webContent;
	vector<string> album_link;
	vector<string> subalbum_link;
	try
	{
		htmlFile = (CInternetFile*) httpSession.OpenURL(str_url,1,INTERNET_FLAG_TRANSFER_ASCII);//m_url������ؼ�Edit1�ı���

		while (htmlFile->ReadString(cs_content))
		{
			cs_webContent+=cs_content;
			myidle();
		}
//		htmlFile->Close();
//		httpSession.Close();
		//delete htmlFile;
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
	wstring wstr1;
	wstr1=UTF8ToUnicode( cs_webContent.GetBuffer() );
	// 	CString str1( wstr1.c_str() ); 
	// 	cs_webContent.Empty();
	cs_webContent=_T(wstr1.c_str());

	i=0;
	int i1 = cs_webContent.Find(_T("<title>"),0);
	int i2 = cs_webContent.Find(_T("'s"));
	CString cs_Maindir;
	for(i=i1+7;i<i2;i++)
		cs_Maindir+=cs_webContent.GetAt(i);//�����Ŀ¼����
	checkDirname(cs_Maindir);
	CreateDirectory(_T("moko\\")+cs_Maindir,NULL);
	URLDownloadToFile(NULL, man_url, _T("moko\\")+cs_Maindir+_T("\\browseUserProfile.html"),0,NULL); 


	i=cs_webContent.Find(_T("չ ʾ"),0);
	CString tempCstr;
	tempCstr=cs_webContent.Right(cs_webContent.GetLength()-i-6);
	i=tempCstr.Find(_T(")"),0);
	tempCstr=tempCstr.Left(i);
	int Album_num=atoi(tempCstr);			//���������
//*************************************************************************************************
	if (cs_webContent.Find(_T("content road gC1 dBd"),0)>-1)
	{
		//�з���  http://www.moko.cc/post/wangtingyu/3301/1/postclass.html
		//http://www.moko.cc/post/liribao/indexpost.html
		//��� g1mC u��÷���ҳ��   
		//         /post/[a-z]+/[0-9]+/1/postclass.html" class="g1mC u"
		regex reg("/post/[a-z]+/[0-9]+/1/postclass.html\" class=\"g1mC u\""); 	//ͼƬģʽ
		// 	regex regdir("description\" content=\".*<t");
		smatch m1; 
		string s = cs_webContent.GetBuffer();	
		//cstcs_AlbumRoot 
		string::const_iterator it = s.begin(); 
		string::const_iterator end = s.end(); 
		subalbum_link.empty();
		while(regex_search(it,end,m1,reg))
		{ 
			//m[1].matched ? ++new_counter : ++delete_counter; 
/*			int size = m1[0].length();*/
			string msg(m1[0].first,m1[0].second);
			int i=msg.find(_T("class="));
			msg.erase(i-2,msg.size());
			msg.insert(0,_T("http://www.moko.cc"));
			subalbum_link.push_back(msg);
			it = m1[0].second; 
			myidle();
		} //������Ͽ��Ի����Ŀ¼��ҳ��		
		unsigned int m=subalbum_link.size();
		for(unsigned int sub_i=0;sub_i<subalbum_link.size() ;sub_i++)
		{
			//���ÿ����Ŀ¼�Ľ���ҳ������
			cs_webContent.Empty();
			try
			{
				htmlFile = (CInternetFile*) httpSession.OpenURL(subalbum_link[sub_i].c_str(),1,INTERNET_FLAG_TRANSFER_ASCII);//m_url������ؼ�Edit1�ı���

				while (htmlFile->ReadString(cs_content))
				{
					cs_webContent+=cs_content;
					myidle();
				}
				//		htmlFile->Close();
				//		httpSession.Close();
				//delete htmlFile;
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
			wstring wstr1;
			wstr1=UTF8ToUnicode( cs_webContent.GetBuffer() );
			cs_webContent=_T(wstr1.c_str());

			//�鿴��û�ж�ҳ���� Ҫ���оͰѵ�ַѹ�뵽subabum_link��   this.blur()			
			if(sub_i<m)
			{
				int ii=cs_webContent.Find(_T("this.blur()"),0);
				CString strMfc;			
				strMfc=subalbum_link[sub_i].c_str();
				char ch=_T('1');
				while(ii>-1)
				{
					ch=ch+1;
					strMfc.SetAt(strMfc.Find(_T("/postclass.html"))-1, ch);
					string strStl=strMfc.GetBuffer(0);
					subalbum_link.push_back(strStl);
					ii=cs_webContent.Find(_T("this.blur()"),ii+1);
					myidle();
				}
			}
			//����������� ���� album_link��  
			///post/[a-z]+/[0-9]+/[0-9]+/[0-9]+.html" class="coverBg wC"
			regex reg("/post/[a-z]+/[0-9]+/[0-9]+/[0-9]+.html\" class=\"coverBg wC\""); 	//ͼƬģʽ
			smatch m1; 
			string s = cs_webContent.GetBuffer();	
			//cstcs_AlbumRoot 
			string::const_iterator it = s.begin(); 
			string::const_iterator end = s.end(); 

			album_link.empty();
			while(regex_search(it,end,m1,reg))
			{ 
				//m[1].matched ? ++new_counter : ++delete_counter; 
/*				int size = m1[0].length();*/
				string msg(m1[0].first,m1[0].second);
				int i = msg.find(_T("class="));
				msg.erase(i-2,msg.size());
				msg.insert(0,_T("http://www.moko.cc"));
				album_link.push_back(msg);
				it = m1[0].second; 
				myidle();
			} 
		}		
	} 
//*************************************************************************************************
	else if(cs_webContent.Find(_T("twShow bd"),0)>-1)
	{
		//��ͼƬԤ��ģʽ http://www.moko.cc/post/vivia/indexpost.html
	}
//*************************************************************************************************
	else{
		for(int m=1;m<Album_num/20+2;m++)
		{
			//  <a class="coverBg wC" href="/post*.[^\s]*.html
			regex reg("<a class=\"coverBg wC\" href=\"/post*.[^\\s]*.html"); 	//ͼƬģʽ
			// 	regex regdir("description\" content=\".*<t");
			smatch m1; 
			string s = cs_webContent.GetBuffer();	
			//cstcs_AlbumRoot 
			string::const_iterator it = s.begin(); 
			string::const_iterator end = s.end(); 


			while(regex_search(it,end,m1,reg))
			{ 
				//m[1].matched ? ++new_counter : ++delete_counter; 
/*				int size = m1[0].length();*/
				string msg(m1[0].first,m1[0].second);
				msg.erase(0,28);
				msg.insert(0,_T("http://www.moko.cc"));
				album_link.push_back(msg);
				it = m1[0].second; 
				myidle();
			} 

			CString temp_str_url;
			CString cs_a;
			cs_a.Format("%d",m+1);
			temp_str_url=cstcs_AlbumRoot+_T("/indexpage/")+cs_a+_T(".html");
			try
			{				
				cs_content.Empty();
				cs_webContent.Empty();
				htmlFile = (CInternetFile*) httpSession.OpenURL(temp_str_url,1,INTERNET_FLAG_TRANSFER_ASCII);//m_url������ؼ�Edit1�ı���


				while (htmlFile->ReadString(cs_content))
				{
					cs_webContent+=cs_content;
					myidle();
				}

				//delete htmlFile;
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
			wstring wstr1;
			wstr1=UTF8ToUnicode( cs_webContent.GetBuffer() );
			cs_webContent=_T(wstr1.c_str());


			// 	int new_counter = 0; 
			// 	int delete_counter = 0; 

			// 	listadd(0,_T("������ҳ���"));
			// 	//for(unsigned int  i=0;i<astr.size();i++)
			//CString cstr=astr[i].c_str();
// 			st_lp.urlGroup=astr;
// 			st_lp.strFileURLInServer.IsEmpty();
// 			st_lp.strFileLocalFullPath=cs_Maindir+_T("\\")+cs_Subdir;
// 			st_lp.strReferHead=_T("");//_T("Referer: http://moko.com");
// 			st_lp.hWnd=(HWND)this;
// 			m_pMyThread=AfxBeginThread(Download1,(LPVOID)&st_lp);//&st_lp[n]);
			// 	if (new_counter != delete_counter) 
			// 		int aa=0;
			// 	else 
			// 		int bb=1;

		}

	
	}

// 	htmlFile->Close();
// 	httpSession.Close();


	//man_url+=_T("/browseUserProfile.html");

	GetManfile(man_url);
	CString strMfc;
	for(unsigned int t=0;t<album_link.size();t++)
	{
		strMfc=album_link[t].c_str();
		SearchLayer3(strMfc);
	}
	return false;
}

/*
һ����ö����������
*/
bool CDoloMoko::SearchLayer2(CString &str_url)
{
	return false;
}

/*
�����Ƭ����.
*/
bool CDoloMoko::SearchLayer3(CString &str_url)
{

	//����http://moko.cc/post/laomai/1/378314.html
	/*
	*.���URL
	*.���ҳ������,����ҳ��,���ҳ������
	*.���ҳ��ͼƬ����
	*.����ͼƬ
	*/
	//httpSession;  
	CDolo::SearchLayer3(str_url);
	htmlFile = (CInternetFile*) httpSession.OpenURL(str_url,1,INTERNET_FLAG_TRANSFER_ASCII);//m_url������ؼ�Edit1�ı���
	CString cs_content;//������ҳ����
	CString cs_dir;
	CString cs_webContent;

	while (htmlFile->ReadString(cs_content))
	{
		cs_webContent+=cs_content;
		myidle();
	}
// 	htmlFile->Close();
// 	httpSession.Close();
	delete htmlFile;
	wstring wstr1;
	wstr1=UTF8ToUnicode( cs_webContent.GetBuffer() );
// 	CString str1( wstr1.c_str() ); 
// 	cs_webContent.Empty();
	cs_webContent=_T(wstr1.c_str());

	//����ͼƬ��Ŀ¼
	int i=0;
	int i1 = cs_webContent.Find(_T("<title>"),0);
	int i2 = cs_webContent.Find(_T("'s"));
	CString cs_Maindir;
	for(i=i1+7;i<i2;i++)
		cs_Maindir+=cs_webContent.GetAt(i);
	checkDirname(cs_Maindir);

	CreateDirectory(_T("moko\\")+cs_Maindir,NULL);
	//����ͼƬ��Ŀ¼
	i  = cs_webContent.Find(_T("sTitle"),0);
	i1 = cs_webContent.Find(_T("title="),i);
	i2 = cs_webContent.Find(_T("alt="),i1);
	CString cs_Subdir;
	for(i=i1+7;i<i2-2;i++)
		cs_Subdir+=cs_webContent.GetAt(i);
	checkDirname(cs_Subdir);
	CreateDirectory(_T("moko\\")+cs_Maindir+_T("\\")+cs_Subdir,NULL);

	
	/*
	src2="[a-zA-z]+://[^\s]*jpg|" src="[a-zA-z]+://[^\s]+img1_cover_+[0-9]+.jpg
	*/
	regex reg("src2=\"[a-zA-z]+://[^\\s]*jpg| src=\"[a-zA-z]+://[^\\s]+img1_cover_+[0-9]+.jpg"); 	//ͼƬģʽ
 	smatch m; 
 	string s = cs_webContent.GetBuffer();	
 
 	string::const_iterator it = s.begin(); 
 	string::const_iterator end = s.end(); 
 	vector<string> astr;
	//int photo_i=0;

 	while(regex_search(it,end,m,reg))
 	{ 
 		//m[1].matched ? ++new_counter : ++delete_counter; 
/* 		int size = m[0].length();*/
 		string msg(m[0].first,m[0].second);
		msg.erase(0,6);
 		//astr.push_back(msg);
		
		s_dolo.cs_url=msg.c_str();
		s_dolo.cs_LocalFullPath=_T("moko\\")+cs_Maindir+_T("\\")+cs_Subdir;
		s_dolo.cs_ReferHead=_T("");
		v_doloST.push_back(s_dolo);

 		it = m[0].second; 
		myidle();
 	} 
	return true;
// 	st_lp.urlGroup=astr;
// 	st_lp.strFileURLInServer.IsEmpty();
// 	st_lp.strFileLocalFullPath=_T("moko\\")+cs_Maindir+_T("\\")+cs_Subdir;
// 	st_lp.strReferHead=_T("");//_T("Referer: http://moko.com");
// 	//st_lp.hWnd=(HWND)this;
// 	st_lp.hWnd=(HWND)this;
// 	m_pMyThread=AfxBeginThread(Download1,(LPVOID)&st_lp);//&st_lp[n]);
	return false;
}
