#pragma once
#include<afxeditbrowsectrl.h>
#include<afx.h>
#include<afxdlgs.h>


// CMyEditBrowseCtrl

class CMyEditBrowseCtrl : public CMFCEditBrowseCtrl
{
	DECLARE_DYNAMIC(CMyEditBrowseCtrl)

public:
	CMyEditBrowseCtrl();
	virtual ~CMyEditBrowseCtrl();
protected:
	DECLARE_MESSAGE_MAP()

public:  
    CString m_strFileType;//�Զ��忪�ļ�����
private:  
    virtual void OnBrowse();//��дCMFCEditBrowseCtrl�Ĵ򿪺���


public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
};


