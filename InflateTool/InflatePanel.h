#pragma once


// InflatePanel �Ի���

class InflatePanel : public CDialogEx
{
	DECLARE_DYNAMIC(InflatePanel)

public:
	InflatePanel(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~InflatePanel();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	HexControl pHexControl1;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
