// RechargeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VIP_Sell.h"
#include "RechargeDlg.h"
#include "afxdialogex.h"

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

	CDialog::OnOK();
}
