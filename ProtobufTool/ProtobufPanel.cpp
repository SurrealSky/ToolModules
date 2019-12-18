// ProtobufPanel.cpp : 实现文件
//

#include "stdafx.h"
#include "ProtobufTool.h"
#include "ProtobufPanel.h"
#include "afxdialogex.h"
#include<google\protobuf\io\coded_stream.h>
#include<CodedConvert.h>


// CProtobufPanel 对话框

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


// CProtobufPanel 消息处理程序

BOOL CProtobufPanel::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//加载第一个HexControl
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
	// 异常:  OCX 属性页应返回 FALSE
}



//协议数据解析
void CProtobufPanel::OnBnClickedButton1()
{
	if (((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck())
	{
		//动态解析
		UpdateData(TRUE);
		unsigned int len2 = pHexControl1.GetDataLen();//协议数据长度
		if (len2)
		{
			unsigned char *data = (unsigned char*)malloc(len2);
			pHexControl1.GetData(data, len2);

			CString strMessage = L"";
			mMessageList.GetLBText(mMessageList.GetCurSel(), strMessage);
			std::wstring wstr = strMessage.GetString();
			std::string str = WStringToString(wstr);
			std::map<std::string,std::string> mapresult;
			mParseProto.PrintDataFile(str.c_str(), data, len2, mapresult);
			free(data);
			std::string strResult = mapresult["DebugString"];
			if (strResult == "")
			{
				mEdtResult = "解析出错...";
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
//编码
void CProtobufPanel::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
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

//解码
void CProtobufPanel::OnBnClickedButton3()
{
	unsigned int len = pHexControl2.GetDataLen();
	if (len != 0)
	{
		unsigned char *data = (unsigned char*)malloc(len + 1);
		memset(data, 0, len + 1);
		pHexControl2.GetData(data, len);
		google::protobuf::io::CodedInputStream stream(data, len);
		google::protobuf::uint64 value;
		stream.ReadVarint64(&value);
		mValue.Format(L"%llu", value);
		UpdateData(FALSE);
	}
}

//加载proto文件
void CProtobufPanel::OnBnClickedButton4()
{
	// TODO:  在此添加控件通知处理程序代码
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
	//加载
	mMessageList.ResetContent();
	unsigned int len1 = mProtoFile.GetLength();//proto文件路径长度
	if(len1)
	{
		SurrealConvert::CodedConvert mCode;
		std::string str=mCode.UnicodeToAscii(mProtoFile.GetString());
		mParseProto.LoadProtoFromFile(str);
		std::vector<std::string> Messages = mParseProto.GetMessageList();
		for (int i = 0; i < Messages.size(); i++)
		{
			std::wstring wstr = StringToWString(Messages[i]);
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

//只拷贝低字节至string中
std::string CProtobufPanel::WStringToString(const std::wstring &wstr)
{
	std::string str(wstr.length(), ' ');
	std::copy(wstr.begin(), wstr.end(), str.begin());
	return str;
}