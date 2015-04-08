
// VIP_Sell.cpp : 定义应用程序的类行为。
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
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
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

// 唯一的一个 CVIP_SellApp 对象
CVIP_SellApp theApp;
// CVIP_SellApp 初始化
BOOL CVIP_SellApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	INIT_TEXTLOG(GetAppPath()+"/Logs");
	CTextLogger::Instance().ModifyFlags(CTextLogger::FLAGS_THREAD, 0);
	initDB();

	CVIP_SellDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

