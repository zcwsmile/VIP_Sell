// RechargeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VIP_Sell.h"
#include "RechargeDlg.h"
#include "afxdialogex.h"

extern sqlite3* g_pDB;

// CRechargeDlg �Ի���

IMPLEMENT_DYNAMIC(CRechargeDlg, CDialog)

CRechargeDlg::CRechargeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRechargeDlg::IDD, pParent)
	, m_fRechange(0)
{

}

CRechargeDlg::~CRechargeDlg()
{
}

void CRechargeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_fRechange);
}


BEGIN_MESSAGE_MAP(CRechargeDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CRechargeDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CRechargeDlg ��Ϣ�������


void CRechargeDlg::OnBnClickedOk()
{
	UpdateData(true);
	if (m_fRechange < 0.01)
	{
		MessageBox("�������ֵ���~��");
		return;
	}
	UINT64 utimestamp = time(NULL);
	CString strtime = ConvertSecondTimeToString(utimestamp);
	CString strSQL;
	//strSQL.Format("insert into T_%llu(timestamp,time,product,balance,remarks) values(%llu,'%s','Recharge',%f,'��ֵ')", \
	//	m_longCardID, utimestamp, strtime, m_fRechange);
	//char* cError = NULL;
	//int nRet = sqlite3_exec(g_pDB, strSQL, 0, 0, &cError);
	//if(SQLITE_OK != nRet)
	//{
	//	MessageBox("Insert useIDTable failed::CRechargeDlg::OnBnClickedOk","Error", MB_ICONWARNING|MB_OK);
	//	return;
	//}
	MessageBox("��ֵ�ɹ���", "success",MB_ICONINFORMATION|MB_OK);

	CDialog::OnOK();
}
