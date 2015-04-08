// VIP_SellDlg.cpp : ʵ���ļ�

#include "stdafx.h"
#include "VIP_Sell.h"
#include "VIP_SellDlg.h"
#include "afxdialogex.h"
#include "ActiveCardDlg.h"
#include "RechargeDlg.h"
#include "CostDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern sqlite3* g_pDB;
int g_count;

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
	, m_strCardID(_T(""))
	, m_strName(_T(""))
	, m_strPhone(_T(""))
	, m_fBalance(0)
	, m_iNumindex(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVIP_SellDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ID, m_strCardID);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_PHONE, m_strPhone);
	DDX_Text(pDX, IDC_EDIT_BALANCE, m_fBalance);
	DDX_Control(pDX, IDC_LIST_CHECK, m_ctrListCheck);
}

BEGIN_MESSAGE_MAP(CVIP_SellDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_ACTIVATE, &CVIP_SellDlg::OnBnClickedBtnActivate)
	ON_BN_CLICKED(IDC_BUT_RECHARGE, &CVIP_SellDlg::OnBnClickedButRecharge)
	ON_BN_CLICKED(IDC_BTN_QUERY, &CVIP_SellDlg::OnBnClickedBtnQuery)
	ON_BN_CLICKED(IDC_BTN_COST, &CVIP_SellDlg::OnBnClickedBtnCost)
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

	
	LONG lStyle;
	lStyle = GetWindowLong(m_ctrListCheck.m_hWnd, GWL_STYLE);	//��ȡ��ǰ����style
	lStyle &= ~LVS_TYPEMASK;									//�����ʾ��ʽλ
	lStyle |= LVS_REPORT;										//����style
	SetWindowLong(m_ctrListCheck.m_hWnd, GWL_STYLE, lStyle);	//����style

	DWORD dwStyle = m_ctrListCheck.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;	//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
	dwStyle |= LVS_EX_GRIDLINES;		//�����ߣ�ֻ������report����listctrl��
	dwStyle |= LVS_EX_CHECKBOXES;		//itemǰ����checkbox�ؼ�
	m_ctrListCheck.SetExtendedStyle(dwStyle);	//������չ���

	m_ctrListCheck.InsertColumn( 0, "ʱ��", LVCFMT_LEFT, 150 );
	m_ctrListCheck.InsertColumn( 1, "��Ʒ", LVCFMT_CENTER, 150 );
	m_ctrListCheck.InsertColumn( 2, "��ע", LVCFMT_CENTER, 120 );
	m_ctrListCheck.InsertColumn( 3, "����(Ԫ)", LVCFMT_CENTER, 110 );
	m_ctrListCheck.InsertColumn( 4, "���(Ԫ)", LVCFMT_CENTER, 120 );


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

int LoadUseInfo(void* para, int n_column, char** column_value, char** column_name)
{
	g_count++;
	for(int i = 0 ; i < n_column; i ++ )
	{
		if (strcmp(column_name[i],"id")==0)
		{
			((CVIP_SellDlg *)para)->m_strCardID = column_value[i];
		}
		else if (strcmp(column_name[i],"name")==0)
		{
			((CVIP_SellDlg *)para)->m_strName = column_value[i];
		}
		else if (strcmp(column_name[i],"phone")==0)
		{
			((CVIP_SellDlg *)para)->m_strPhone = column_value[i];
		}
		else if(strcmp(column_name[i],"balance")==0)
		{
			((CVIP_SellDlg *)para)->m_fBalance = atof(column_value[i]);
		}
	}

	return 0;
}

int LoadCostList(void* para, int n_column, char** column_value, char** column_name)
{
	CVIP_SellDlg * pCDlg = (CVIP_SellDlg *)para;

	pCDlg->m_ctrListCheck.InsertItem(pCDlg->m_iNumindex,"");
	for(int i = 0 ; i < n_column; i ++ )
	{
		if (strcmp(column_name[i],"time")==0)
		{
			pCDlg->m_ctrListCheck.SetItemText(pCDlg->m_iNumindex, 0, column_value[i]);
		}
		else if (strcmp(column_name[i],"product")==0)
		{
			pCDlg->m_ctrListCheck.SetItemText(pCDlg->m_iNumindex, 1, column_value[i]);
		}
		else if (strcmp(column_name[i],"remarks")==0)
		{
			pCDlg->m_ctrListCheck.SetItemText(pCDlg->m_iNumindex, 2, column_value[i]);
		}
		else if(strcmp(column_name[i],"sumprice")==0)
		{
			pCDlg->m_ctrListCheck.SetItemText(pCDlg->m_iNumindex, 3, column_value[i]);
		}
		else if(strcmp(column_name[i],"balance")==0)
		{
			pCDlg->m_ctrListCheck.SetItemText(pCDlg->m_iNumindex, 4, column_value[i]);
		}

	}
	pCDlg->m_iNumindex++;

	return 0;
}

void CVIP_SellDlg::UpdateCheckList()
{
	CString strSQL;
	char* cError = NULL;
	m_iNumindex = 0;
	m_ctrListCheck.DeleteAllItems();
	strSQL.Format("select * from T_%s order by timestamp", m_strCardID);
	sqlite3_exec(g_pDB, strSQL, LoadCostList, this, &cError);
	TEXTLOG("%s:%s:Error=%s", __FUNCTION__, strSQL, cError);

}

void CVIP_SellDlg::InitClear()
{
	m_strCardID = m_strName = m_strPhone = "";
	m_fBalance = 0;
	m_ctrListCheck.DeleteAllItems();
	UpdateData(FALSE);
}

void CVIP_SellDlg::OnBnClickedBtnActivate()
{
	// TODO: ���¿�
	CActiveCardDlg ActiveCardDlg;      // ģ̬�Ի�����ʾʵ��
	if(ActiveCardDlg.DoModal() == IDOK)
	{
		m_strName = ActiveCardDlg.m_strName;
		m_strCardID = ActiveCardDlg.m_strCardID;
		m_strPhone = ActiveCardDlg.m_strPhone;
		m_fBalance = ActiveCardDlg.m_flSumMoney;
	}
	UpdateData(FALSE);
	UpdateCheckList();
	return;
}


void CVIP_SellDlg::OnBnClickedButRecharge()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������;
	
	if (m_strCardID.IsEmpty() || m_strPhone.IsEmpty() || m_strName.IsEmpty())
	{
		MessageBox("���Ȳ�ѯ���˻�","Worn", MB_ICONWARNING|MB_OK);
		return;
	}
	CRechargeDlg RechargeDlg;
	if(RechargeDlg.DoModal() == IDOK)
	{
		if (RechargeDlg.m_fRechange < 0.01)
		{
			MessageBox("��ֵ����Ϊ 0 ","Error", MB_ICONWARNING|MB_OK);
			return;
		}
		CString strSQL;
		char* cError = NULL;
		UINT64 utimestamp = time(NULL);
		CString strtime = ConvertSecondTimeToString(utimestamp);
		strSQL.Format("insert into T_%s(timestamp,time,product,sumprice,balance,remarks) values(%llu,'%s','Recharge',%.3f,%.3f,'Recharge��ֵ')", \
			m_strCardID, utimestamp, strtime, -RechargeDlg.m_fRechange, m_fBalance+RechargeDlg.m_fRechange);
		int nRet = sqlite3_exec(g_pDB, strSQL, 0, 0, &cError);
		if(SQLITE_OK != nRet)
		{
			MessageBox("��ֵʧ��","Error", MB_ICONWARNING|MB_OK);
			TEXTLOG("%s:%s:Error=%s",__FUNCTION__,strSQL,cError);
			return;
		}
		else
		{
			MessageBox("��ֵ�ɹ���", "success",MB_ICONINFORMATION|MB_OK);
		}
		TEXTLOG("%s:%s:Error=%s",__FUNCTION__,strSQL,cError);
		m_fBalance += RechargeDlg.m_fRechange;
		UpdateData(FALSE);

		//�����û���;
		strSQL.Format("update T_customers set balance = %.3f where id = '%s'", m_fBalance, m_strCardID);
		nRet = sqlite3_exec(g_pDB, strSQL, 0, 0, &cError);
		if(SQLITE_OK != nRet)
		{
			MessageBox("�û�������ʧ�ܣ�","Error", MB_ICONWARNING|MB_OK);
		}
		TEXTLOG("%s:%s:Error=%s",__FUNCTION__,strSQL,cError);

	}

	UpdateCheckList();

}

void CVIP_SellDlg::OnBnClickedBtnQuery()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CString strSQL;
	char* cError;
	if (!m_strCardID.IsEmpty())
	{
		//strSQL.Format("select * from T_customers where id is '%s' or name is '%s' or phone is '%s'",m_strCardID, m_strName, m_strPhone);
		strSQL.Format("select * from T_customers where id is '%s'", m_strCardID);
		g_count = 0;
		sqlite3_exec(g_pDB, strSQL, LoadUseInfo, this, &cError);
		TEXTLOG("%s:%s:Error=%s",__FUNCTION__,strSQL,cError);
		if (0==g_count)
		{
			MessageBox("û�д˿��ŵ���Ϣ~��", "Warning", MB_ICONWARNING|MB_OK);
			InitClear();
			return;
		}
		
	}
	else if (!m_strName.IsEmpty())
	{
		g_count = 0;
		strSQL.Format("select * from T_customers where name is '%s'", m_strName);
		sqlite3_exec(g_pDB, strSQL, LoadUseInfo, this, &cError);
		TEXTLOG("%s:%s:Error=%s",__FUNCTION__,strSQL,cError);
		if (0==g_count)
		{
			MessageBox("û�д���������Ϣ~��", "Warning", MB_ICONWARNING|MB_OK);
			InitClear();
			return;
		}
	}
	else if (!m_strPhone.IsEmpty())
	{
		g_count = 0;
		strSQL.Format("select * from T_customers where phone is '%s'", m_strPhone);
		sqlite3_exec(g_pDB, strSQL, LoadUseInfo, this, &cError);
		TEXTLOG("%s:%s:Error=%s",__FUNCTION__,strSQL,cError);
		if (0==g_count)
		{
			MessageBox("û�д˵绰�ŵ���Ϣ~��", "Warning", MB_ICONWARNING|MB_OK);
			InitClear();
			return;
		}
	}
	else
	{
		MessageBox("���š��������ֻ���������һ����лл��", "Warning", MB_ICONWARNING|MB_OK);
		return;
	}
	UpdateData(FALSE);

	UpdateCheckList();

}

void CVIP_SellDlg::OnBnClickedBtnCost()
{
	if (m_strCardID.IsEmpty() || m_strPhone.IsEmpty() || m_strName.IsEmpty())
	{
		MessageBox("���Ȳ�ѯ���˻�","Worn", MB_ICONWARNING|MB_OK);
		return;
	}
	CCostDlg CostDlg;
	if(CostDlg.DoModal() == IDOK)
	{
		float Balanc = m_fBalance - CostDlg.m_fCost;
		if (Balanc < 0.001)
		{
			MessageBox("�˻�����","Worn", MB_ICONWARNING|MB_OK);
			return;
		}

		CString strSQL;
		char* cError;
		UINT64 utimestamp = time(NULL);
		CString strtime = ConvertSecondTimeToString(utimestamp);
		CString Msg;
		Msg.Format("�û�%s-%s\n������� %.3fԪ�� �˻����Ϊ %.3fԪ��\n��ȷ�ϣ�",m_strName, m_strPhone, CostDlg.m_fCost, Balanc);

		if (IDNO == MessageBox(Msg, "Warning",MB_ICONWARNING|MB_YESNO))
		{
			return;
		}
		m_fBalance = Balanc;
		strSQL.Format("insert into T_%s(timestamp,time,product,price,num,sumprice,balance,remarks)values(%llu,'%s','%s',%.3f,%d,%.3f,%.3f,'%s')",\
			m_strCardID, utimestamp, strtime, CostDlg.m_strProduct, CostDlg.m_fPrice, CostDlg.m_iNum, CostDlg.m_fCost, m_fBalance, CostDlg.m_strMarks);
		sqlite3_exec(g_pDB, strSQL, 0, 0, &cError);
		TEXTLOG("%s:%s:Error=%s",__FUNCTION__,strSQL,cError);

		//�����û���;
		strSQL.Format("update T_customers set balance = %.3f, sumspent = sumspent +%.3f  where id = '%s'",m_fBalance,CostDlg.m_fCost, m_strCardID);
		int nRet = sqlite3_exec(g_pDB, strSQL, 0, 0, &cError);
		TEXTLOG("%s:%s:Error=%s",__FUNCTION__,strSQL,cError);
		if(SQLITE_OK != nRet)
		{
			MessageBox("�û�������ʧ�ܣ�","Error", MB_ICONWARNING|MB_OK);
			return;
		}
		//MessageBox("������ѳɹ���","Error", MB_ICONWARNING|MB_OK);
		UpdateData(FALSE);
	}
	UpdateCheckList();
	
}
