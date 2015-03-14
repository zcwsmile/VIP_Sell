// VIP_Sell.h : PROJECT_NAME 应用程序的主头文件
#ifndef _VIP_SELL_H_
#define _VIP_SELL_H_

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include "TextLogger.h"
#include "ucext_api.h"
#include "sqlite3.h"

// CVIP_SellApp:
// 有关此类的实现，请参阅 VIP_Sell.cpp
//

class CVIP_SellApp : public CWinApp
{
public:
	CVIP_SellApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CVIP_SellApp theApp;

#endif