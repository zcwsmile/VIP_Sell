// VIP_SellDlg.cpp : 实现文件

#include "stdafx.h"
#include "VIP_Sell.h"
#include "VIP_SellDlg.h"
#include "afxdialogex.h"
#include "ActiveCardDlg.h"
#include "RechargeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern sqlite3* g_pDB;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CVIP_SellDlg 对话框

CVIP_SellDlg::CVIP_SellDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CVIP_SellDlg::IDD, pParent)
	, m_llongCardID(0)
	, m_strName(_T(""))
	, m_longPhone(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVIP_SellDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ID, m_llongCardID);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_PHONE, m_longPhone);
}

BEGIN_MESSAGE_MAP(CVIP_SellDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_ACTIVATE, &CVIP_SellDlg::OnBnClickedBtnActivate)
	ON_BN_CLICKED(IDC_BUT_RECHARGE, &CVIP_SellDlg::OnBnClickedButRecharge)
	ON_BN_CLICKED(IDC_BTN_QUERY, &CVIP_SellDlg::OnBnClickedBtnQuery)
END_MESSAGE_MAP()


// CVIP_SellDlg 消息处理程序

BOOL CVIP_SellDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CVIP_SellDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CVIP_SellDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CVIP_SellDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CVIP_SellDlg::OnBnClickedBtnActivate()
{
	// TODO: 开新卡
	CActiveCardDlg ActiveCardDlg;      // 模态对话框显示实例
	if(ActiveCardDlg.DoModal() != IDOK) 
		return;
}


void CVIP_SellDlg::OnBnClickedButRecharge()
{
	// TODO: 在此添加控件通知处理程序代码
	CRechargeDlg RechargeDlg;      // 模态对话框显示实例
	if(RechargeDlg.DoModal() != IDOK)
		return;
}

int LLoadSQLInfo(void* para, int n_column, char** column_value, char** column_name)
{

	//int i;
	//printf( “记录包含 %d 个字段/n”, n_column );
	//for( i = 0 ; i < n_column; i ++ )
	//{
	//	printf( “字段名:%s  字段值:%s/n”,  column_name[i], column_value[i] );
	//}
	//printf( “------------------/n“ );   


	return n_column;
}

void CVIP_SellDlg::OnBnClickedBtnQuery()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_llongCardID)
	{
		CString strSQL;
		char* cError;
		strSQL.Format("select * from T_customers where id = %I64d", m_llongCardID);
		int nRet = sqlite3_exec(g_pDB, strSQL, LLoadSQLInfo, 0, &cError);
		TEXTLOG("Insert T_customers -%s,Err=(%s)", strSQL, cError);
		if(SQLITE_OK != nRet);
		
	}
	else if (!m_strName.IsEmpty())
	{
		
	}
	else if (m_longPhone)
	{
		
	}
	else
	{
		MessageBox("卡号、姓名、手机请至少填一个，谢谢。", "Warning", MB_ICONWARNING|MB_OK);
	}


}