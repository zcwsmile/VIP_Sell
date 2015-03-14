// VIP_SellDlg.cpp : ʵ���ļ�

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

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CVIP_SellDlg �Ի���

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


// CVIP_SellDlg ��Ϣ�������

BOOL CVIP_SellDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CVIP_SellDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CVIP_SellDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CVIP_SellDlg::OnBnClickedBtnActivate()
{
	// TODO: ���¿�
	CActiveCardDlg ActiveCardDlg;      // ģ̬�Ի�����ʾʵ��
	if(ActiveCardDlg.DoModal() != IDOK) 
		return;
}


void CVIP_SellDlg::OnBnClickedButRecharge()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CRechargeDlg RechargeDlg;      // ģ̬�Ի�����ʾʵ��
	if(RechargeDlg.DoModal() != IDOK)
		return;
}

int LLoadSQLInfo(void* para, int n_column, char** column_value, char** column_name)
{

	//int i;
	//printf( ����¼���� %d ���ֶ�/n��, n_column );
	//for( i = 0 ; i < n_column; i ++ )
	//{
	//	printf( ���ֶ���:%s  �ֶ�ֵ:%s/n��,  column_name[i], column_value[i] );
	//}
	//printf( ��------------------/n�� );   


	return n_column;
}

void CVIP_SellDlg::OnBnClickedBtnQuery()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		MessageBox("���š��������ֻ���������һ����лл��", "Warning", MB_ICONWARNING|MB_OK);
	}


}