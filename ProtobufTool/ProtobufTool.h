// ProtobufTool.h : ProtobufTool DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CProtobufToolApp
// �йش���ʵ�ֵ���Ϣ������� ProtobufTool.cpp
//

class CProtobufToolApp : public CWinApp
{
public:
	CProtobufToolApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnProtobuf();
};
