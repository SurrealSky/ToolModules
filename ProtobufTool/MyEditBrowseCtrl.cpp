// MyEditBrowseCtrl.cpp : ʵ���ļ�
//

#include"stdafx.h"
#include "MyEditBrowseCtrl.h"


// CMyEditBrowseCtrl

IMPLEMENT_DYNAMIC(CMyEditBrowseCtrl, CMFCEditBrowseCtrl)

CMyEditBrowseCtrl::CMyEditBrowseCtrl()
{
	 m_strFileType = _T("Proto Files (*.proto)|*.proto||"); 
}

CMyEditBrowseCtrl::~CMyEditBrowseCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyEditBrowseCtrl, CMFCEditBrowseCtrl)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// CMyEditBrowseCtrl ��Ϣ�������
void CMyEditBrowseCtrl::OnBrowse()  
{  
    CString TempPathName;  
  
    CFileDialog dlg(TRUE,NULL,NULL,NULL,m_strFileType,NULL,0,TRUE);  
    (dlg.m_ofn).lpstrTitle=_T("���ļ�");  
  
    if(dlg.DoModal()==IDOK)  
    {  
        TempPathName=dlg.GetPathName();  
        SetWindowText(TempPathName);  
    }  
    else  
        return;  
}

void CMyEditBrowseCtrl::OnDropFiles(HDROP hDropInfo)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (hDropInfo)
	{
		int nDrag; //��ק�ļ�������
		nDrag = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);
		if (nDrag == 1)
		{
			// ����ק���ļ����ļ���
			TCHAR Path[MAX_PATH + 1] = { 0 };
			int len;
			// �õ�����ק���ļ���
			len = DragQueryFile(hDropInfo, 0, Path, MAX_PATH);
			// ���ļ�����ʾ����
			SetWindowText(Path);
		}
		else
		{
			MessageBox(_T("ֻ����קһ���ļ�����"));
		}
	}
	CMFCEditBrowseCtrl::OnDropFiles(hDropInfo);
}
