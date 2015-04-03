// ActiveCardDlg.cpp : 实现文件

#include "stdafx.h"
#include "VIP_Sell.h"
#include "ActiveCardDlg.h"

extern sqlite3* g_pDB;
// CActiveCardDlg 对话框

IMPLEMENT_DYNAMIC(CActiveCardDlg, CDialog)

CActiveCardDlg::CActiveCardDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CActiveCardDlg::IDD, pParent)
	, m_strName(_T(""))
	, m_CtimeBirthday(0)
	, m_flSumMoney(0)
	, m_strMarket(_T(""))
	, m_bWoman(FALSE)
	, m_longCardID(0)
	, m_longPhone(0)
{

}

CActiveCardDlg::~CActiveCardDlg()
{
}

void CActiveCardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_CtrBirthdayTime);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_CtimeBirthday);
	DDX_Text(pDX, IDC_EDIT_CASH, m_flSumMoney);
	DDX_Text(pDX, IDC_EDIT5, m_strMarket);
	DDX_Radio(pDX, IDC_RADIO_WOMAN, m_bWoman);
	DDX_Text(pDX, IDC_EDIT_CARDID, m_longCardID);
	DDX_Text(pDX, IDC_EDIT_PHONE, m_longPhone);
}


BEGIN_MESSAGE_MAP(CActiveCardDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CActiveCardDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CActiveCardDlg 消息处理程序;

void CActiveCardDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码;
	UpdateData(true);
	if (!m_longCardID || m_strName.IsEmpty() || !m_longPhone)
	{
		MessageBox("请把信息填写完整~！");
		return;
	}
	CString Msg;
	Msg.Format("%s-%llu-激活,余额%.3f元。\n请确认？",m_strName,m_longPhone,m_flSumMoney);

	if (IDNO == MessageBox(Msg, "Warning",MB_ICONWARNING|MB_YESNO))
	{
		return;
	}
	UINT64 utimestamp = time(NULL);
	CString strJointime = ConvertSecondTimeToString(utimestamp);
	CString strBirthDay;
	strBirthDay.Format("%d-%d",m_CtimeBirthday.GetMonth(), m_CtimeBirthday.GetDay());
	char* cError=NULL;
	CString strSQL;
	strSQL.Format("insert into T_customers values(%llu, '%s', %d, %llu, '%s', '%s', 0, %f, '%s')", \
		m_longCardID, m_strName, (int)m_bWoman, m_longPhone, strJointime, strBirthDay, m_flSumMoney, m_strMarket);
	int nRet = sqlite3_exec(g_pDB, strSQL, 0, 0, &cError);
	TEXTLOG("Insert T_customers -%s,Err=(%s)", strSQL, cError);
	if(SQLITE_OK != nRet)
	{
		MessageBox("开卡失败~insert failed！", "Error",MB_ICONWARNING|MB_OK);
		return;
	}
	strSQL.Format("create table if not exists T_%llu(timestamp INTEGER PRIMARY KEY default 0, time text, \
				  product text, price integer, num integer, sumprice integer, balance integer, remarks text)", m_longCardID);
	//sumprice 此次消费总额     balance 账号余额。
	nRet = sqlite3_exec(g_pDB, strSQL, 0, 0, &cError);
	TEXTLOG("create T_CardID -%s,Err=(%s)", strSQL, cError);
	if(SQLITE_OK != nRet)
	{
		MessageBox("create T_CardID failed！", "Error",MB_ICONWARNING|MB_OK);
		return;
	}
	strSQL.Format("insert into T_%llu(timestamp,time,product,balance,remarks) values(%llu,'%s','Recharge',%f,'start充值办卡')", \
		m_longCardID, utimestamp, strJointime, m_flSumMoney);
	nRet = sqlite3_exec(g_pDB, strSQL, 0, 0, &cError);
	if(SQLITE_OK != nRet)
	{
		MessageBox("Insert useIDTable first failed！", "Error", MB_ICONWARNING|MB_OK);
		return;
	}
	MessageBox("卡片成功激活~！", "success",MB_ICONINFORMATION|MB_OK);
	
	CDialog::OnOK();   //GetDlgItem(IDC_EDIT_SQL)->SetWindowText(strSQL);
}


BOOL CActiveCardDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_CtrBirthdayTime.SetFormat("MM-dd");
	m_CtimeBirthday = time(NULL);
	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
