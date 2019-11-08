// ProtobufPanel.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ProtobufTool.h"
#include "ProtobufPanel.h"
#include "afxdialogex.h"
#include<google\protobuf\io\coded_stream.h>


// CProtobufPanel �Ի���

IMPLEMENT_DYNAMIC(CProtobufPanel, CDialogEx)

CProtobufPanel::CProtobufPanel(CWnd* pParent /*=NULL*/)
	: CDialogEx(CProtobufPanel::IDD, pParent)
	, mEdtResult(_T(""))
	, mValue(_T(""))
	, mProtoFile(_T(""))
{

}

CProtobufPanel::~CProtobufPanel()
{
}

void CProtobufPanel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, mEdtResult);
	DDX_Text(pDX, IDC_EDIT2, mValue);
	DDX_Control(pDX, IDC_EDIT3, mProtoEdit);
	DDX_Text(pDX, IDC_MFCEDITBROWSE1, mProtoFile);
	DDX_Control(pDX, IDC_MFCEDITBROWSE1, mProtoFileEdit);
	DDX_Control(pDX, IDC_COMBO1, mMessageList);
}


BEGIN_MESSAGE_MAP(CProtobufPanel, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CProtobufPanel::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CProtobufPanel::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CProtobufPanel::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CProtobufPanel::OnBnClickedButton4)
END_MESSAGE_MAP()


// CProtobufPanel ��Ϣ�������

BOOL CProtobufPanel::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//���ص�һ��HexControl
	pHexControl1.CreateHexView(AfxGetInstanceHandle(),m_hWnd);
	pHexControl1.SetPosition(10, 20, 600, 80);
	unsigned char buffer[] = { 0x08, 0x02, 0x12, 0x27,
		0x08, 0x01, 0x10, 0xcb, 0xb1, 0xb0, 0xbd, 0x03,
		0x18, 0x04, 0x22, 0x1b, 0x08, 0x17, 0x12, 0x17,
		0x0a, 0x13, 0x77, 0x78, 0x69, 0x64, 0x5f, 0x76,
		0x34, 0x78, 0x33, 0x74, 0x76, 0x36, 0x70, 0x68,
		0x63, 0x77, 0x69, 0x32, 0x31, 0x10, 0x07, 0x12,
		0x18, 0x08, 0x03, 0x10, 0xcb, 0xb1, 0xb0, 0xbd,
		0x03, 0x18, 0x05, 0x22, 0x0c, 0x08, 0x08, 0x12,
		0x08, 0x08, 0x04, 0x12, 0x04, 0x05, 0x00, 0x00,
		0x00, 0x18, 0x06 };
	pHexControl1.SetData(buffer, sizeof(buffer));

	unsigned char value[] = { 0x99, 0xE4, 0xB7, 0x37, };
	pHexControl2.CreateHexView(AfxGetInstanceHandle(), m_hWnd);
	pHexControl2.SetPosition(10, 470, 600, 35);
	pHexControl2.SetData(value, sizeof(value));

	((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(1);
	mProtoFile = "C:\\Users\\Administrator\\Desktop\\MicroMsg3D.proto";
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}



//Э�����ݽ���
void CProtobufPanel::OnBnClickedButton1()
{
	if (((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck())
	{
		//��̬����
		UpdateData(TRUE);
		unsigned int len2 = pHexControl1.GetDataLen();//Э�����ݳ���
		if (len2)
		{
			unsigned char *data = (unsigned char*)malloc(len2);
			pHexControl1.GetData(data, len2);

			CString strMessage = L"";
			mMessageList.GetLBText(mMessageList.GetCurSel(), strMessage);
			std::wstring wstr = strMessage.GetString();
			std::string str = WStringToString(wstr);
			std::string strResult = mParseProto.PrintDataFile(str.c_str(), data, len2);
			free(data);
			if (strResult == "")
			{
				mEdtResult = "��������...";
			}
			else
			{
				mEdtResult = "";
				wstr = StringToWString(strResult);
				mEdtResult.Append(wstr.c_str(), wstr.length());
				mEdtResult.Replace(L"\n", L"\r\n");
			}

			UpdateData(FALSE);
		}
	}
	else
	{
		unsigned int len = pHexControl1.GetDataLen();
		if (len)
		{
			unsigned char *data = (unsigned char*)malloc(len);
			pHexControl1.GetData(data, len);

			std::string ret=mParseProto.PrintDebugString(data, len);
			mEdtResult = "";
			std::wstring wstr = StringToWString(ret);
			mEdtResult.Append(wstr.c_str(), wstr.length());
			mEdtResult.Replace(L"\n", L"\r\n");
			UpdateData(FALSE);
		}
	}
	
}
//����
void CProtobufPanel::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (mValue.Trim().GetLength())
	{	
		LONGLONG value = 0;
		StrToInt64Ex(mValue, STIF_DEFAULT, &value);
		int nLen = google::protobuf::io::CodedOutputStream::VarintSize64(value);
		google::protobuf::uint8 *pLen = new google::protobuf::uint8[nLen];
		memset(pLen, 0, nLen);
		google::protobuf::io::CodedOutputStream::WriteVarint64ToArray(value, pLen);
		pHexControl2.SetData( pLen, nLen);
		delete[] pLen;
	}
}

//����
void CProtobufPanel::OnBnClickedButton3()
{
	//0:Varint(int32, int64, uint32, uint64, sint32, sint64, bool, enum)
	//1:64-bit(fixed64, sfixed64, double)
	//2:Length-delimited(string, bytes, embedded messages, packed repeated fields)
	//3:Start group(groups (deprecated))
	//4:End group(groups (deprecated))
	//5:32-bit(fixed32, sfixed32, float)
	//unsigned int len = HexEditControl::GetDataLength(pHexControl2);
	//if (len != 0)
	//{
	//	unsigned char *data = (unsigned char*)malloc(len+1);
	//	data[0] = 0x08;
	//	HexEditControl::GetData(pHexControl2, data+1, len);

	//	TestMsg::TestMsg m;
	//	m.ParseFromArray(data, len+1);
	//	free(data);
	//	int i=m.unknown_fields().field_count();
	//	if (m.unknown_fields().field_count() >= 1)
	//	{
	//		google::protobuf::UnknownField fild = m.unknown_fields().field(0);
	//		switch (fild.type())
	//		{
	//		case google::protobuf::UnknownField::TYPE_VARINT:
	//		{
	//			__int64 value = fild.varint();
	//			mValue.Format(L"%lu", value);
	//		}break;
	//		case google::protobuf::UnknownField::TYPE_FIXED32:
	//		{
	//			__int32 value = fild.fixed32();
	//			mValue.Format(L"%lu", value);
	//		}break;
	//		case google::protobuf::UnknownField::TYPE_FIXED64:
	//		{
	//			__int64 value = fild.fixed64();
	//			mValue.Format(L"%lu", value);
	//		}break;
	//		case google::protobuf::UnknownField::TYPE_LENGTH_DELIMITED:
	//		{

	//		}break;
	//		case google::protobuf::UnknownField::TYPE_GROUP:
	//		{

	//		}break;
	//		}
	//		
	//		UpdateData(FALSE);
	//	}
	//}

}

//����proto�ļ�
void CProtobufPanel::OnBnClickedButton4()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CFile mFile(mProtoFile, CFile::modeRead);
	DWORD filesize = 0;
	filesize = GetFileSize(mFile, 0);
	if (filesize)
	{
		char *buffer = (char*)malloc(filesize);
		mFile.Read(buffer, filesize);
		std::string strResult;
		strResult.append(buffer, filesize);
		free(buffer);
		std::wstring wstr = StringToWString(strResult);
		CString Result = L"";
		Result.Append(wstr.c_str(), wstr.length());
		Result.Replace(L"\n", L"\r\n");
		mProtoEdit.SetWindowTextW(Result);
	}
	mFile.Close();
	//����
	mMessageList.ResetContent();
	unsigned int len1 = mProtoFile.GetLength();//proto�ļ�·������
	if(len1)
	{
		std::wstring wstr = mProtoFile.GetString();
		std::string str = WStringToString(wstr);
		mParseProto.LoadProtoFromFile(str);
		std::vector<std::string> Messages = mParseProto.GetMessageList();
		for (int i = 0; i < Messages.size(); i++)
		{
			wstr = StringToWString(Messages[i]);
			mMessageList.AddString(wstr.c_str());
		}
		mMessageList.SetCurSel(0);
	}
}


std::wstring CProtobufPanel::StringToWString(const std::string &str)
{
	std::wstring wstr(str.length(), L' ');
	std::copy(str.begin(), str.end(), wstr.begin());
	return wstr;
}

//ֻ�������ֽ���string��
std::string CProtobufPanel::WStringToString(const std::wstring &wstr)
{
	std::string str(wstr.length(), ' ');
	std::copy(wstr.begin(), wstr.end(), str.begin());
	return str;
}