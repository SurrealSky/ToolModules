// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE 类
#include <afxodlgs.h>       // MFC OLE 对话框类
#include <afxdisp.h>        // MFC 自动化类
#endif // _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>                      // MFC ODBC 数据库类
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>                     // MFC DAO 数据库类
#endif // _AFX_NO_DAO_SUPPORT

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT


#include "../CommonLib/include/CipherManager/PluginLibrary.h"

#include"../CommonLib/include/HexControl.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\CommonLib\\lib\\Debug\\HexView.lib")
#else
#pragma comment(lib, "..\\CommonLib\\lib\\Release\\HexView.lib")
#endif

#include <afxcontrolbars.h>

#include"resource.h"


#include <google/protobuf/descriptor.h>
#include <google/protobuf/dynamic_message.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/tokenizer.h>
#include <google/protobuf/compiler/parser.h>
#include<google/protobuf/compiler/importer.h>
#include<fstream>
#include<string>
//using namespace google::protobuf;

#ifdef _DEBUG
#pragma comment(lib,"..\\proto_3_9_0_vs2015_LIB\\Debug\\libprotobufd.lib")
#pragma comment(lib,"..\\proto_3_9_0_vs2015_LIB\\Debug\\libprotobuf-lited.lib")
#pragma comment(lib,"..\\proto_3_9_0_vs2015_LIB\\Debug\\libprotocd.lib")
#else
#pragma comment(lib,"..\\proto_3_9_0_vs2015_LIB\\Release\\libprotobuf.lib")
#pragma comment(lib,"..\\proto_3_9_0_vs2015_LIB\\Release\\libprotobuf-lite.lib")
#pragma comment(lib,"..\\proto_3_9_0_vs2015_LIB\\Release\\libprotoc.lib")
#endif