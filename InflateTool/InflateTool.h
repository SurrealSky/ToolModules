// InflateTool.h : InflateTool DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CInflateToolApp
// �йش���ʵ�ֵ���Ϣ������� InflateTool.cpp
//

class CInflateToolApp : public CWinApp
{
public:
	CInflateToolApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnInflate();
};
