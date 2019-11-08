#pragma once
#include "afxwin.h"
#include "MyEditBrowseCtrl.h"
#include<string>
#include"ParseProto.h"


// CProtobufPanel �Ի���

class CProtobufPanel : public CDialogEx
{
	DECLARE_DYNAMIC(CProtobufPanel)

public:
	CProtobufPanel(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CProtobufPanel();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	virtual BOOL OnInitDialog();
public:
	HexControl pHexControl1;
	HexControl pHexControl2;
	CString mEdtResult;
	CString mValue;
	CEdit mProtoEdit;
	CString mProtoFile;
	CMyEditBrowseCtrl mProtoFileEdit;
	CComboBox mMessageList;
public:
	std::wstring StringToWString(const std::string &str);
	std::string WStringToString(const std::wstring &wstr);
	ParseProto mParseProto;
};
