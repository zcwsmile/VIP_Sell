// VIP_Sell.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
#ifndef _VIP_SELL_H_
#define _VIP_SELL_H_

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "TextLogger.h"
#include "ucext_api.h"
#include "sqlite3.h"

// CVIP_SellApp:
// �йش����ʵ�֣������ VIP_Sell.cpp
//

class CVIP_SellApp : public CWinApp
{
public:
	CVIP_SellApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CVIP_SellApp theApp;

#endif