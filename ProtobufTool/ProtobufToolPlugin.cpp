#include "stdafx.h"
#include "ProtobufToolPlugin.h"


IMPLEMENT_PLUGIN(ProtobufToolPlugin)

void ProtobufToolPlugin::Init()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// merge menu
	CMenu append;
	append.LoadMenu(IDR_MENU1);
	MergeMenu(&append, TRUE);
}

void ProtobufToolPlugin::Query(CPluginInfo& plugininfo)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	plugininfo.m_strName = _T("Protobuf test");
	plugininfo.m_strBlurb = _T("ProtobufЭ�����");
	plugininfo.m_strHelp = _T("����");
	plugininfo.m_strAuthor = _T("wangzha");
	plugininfo.m_strCopyRight = _T("Copyright wangzha");
	plugininfo.m_strDate = _T("2017.11.28");
	plugininfo.m_strMenuLabel = "���";
}
