
// VIP_Sell.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "VIP_Sell.h"
#include "VIP_SellDlg.h"
#include <map>

sqlite3* g_pDB = NULL;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVIP_SellApp

BEGIN_MESSAGE_MAP(CVIP_SellApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


CVIP_SellApp::CVIP_SellApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


int initDB()
{
	CreatePath(GetAppPath()+"\\data");
	CString strFileDB = "NewLife.db";
	CString strDBPath;
	strDBPath.Format("%s\\data\\%s",GetAppPath(),strFileDB);
	int liRet = sqlite3_open_v2(strDBPath, &g_pDB, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
	if(SQLITE_OK != liRet)
	{
		TEXTLOG("sqlite3 open DB failed~");
		return 1;
	}

	char* szError=0;
	char szSQL[] = "create table if not exists T_customers(id text PRIMARY KEY, name text, sex integer, phone text, jointime text, birthday text, sumspent real, balance real, remarks text)";
	liRet = sqlite3_exec(g_pDB, szSQL, 0, 0, &szError);
	if(SQLITE_OK != liRet)
	{
		TEXTLOG("create table T_customers failed~");
		return 1;
	}
	//sqlite3_stmt* lpdExcute = NULL;
	//sqlite3_prepare(pDb, cIsExit, -1, &lpdExcute, NULL);
	//int nRet = sqlite3_step(pVM);
	//sqlite3_close(pDb);
	return 0;
}

// Ψһ��һ�� CVIP_SellApp ����
CVIP_SellApp theApp;
// CVIP_SellApp ��ʼ��
BOOL CVIP_SellApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	INIT_TEXTLOG(GetAppPath()+"/Logs");
	CTextLogger::Instance().ModifyFlags(CTextLogger::FLAGS_THREAD, 0);
	initDB();

	CVIP_SellDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

