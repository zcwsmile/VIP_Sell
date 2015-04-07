// CostDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "VIP_Sell.h"
#include "CostDlg.h"
#include "afxdialogex.h"


// CCostDlg 对话框

IMPLEMENT_DYNAMIC(CCostDlg, CDialog)

CCostDlg::CCostDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCostDlg::IDD, pParent)
	, m_strProduct(_T(""))
	, m_fPrice(0)
	, m_fSale(10)
	, m_iNum(1)
	, m_fSum(0)
	, m_fCost(0)
	, m_strMarks(_T(""))
{
}

CCostDlg::~CCostDlg()
{
}

void CCostDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PRODUCT, m_strProduct);
	DDX_Text(pDX, IDC_EDIT_PRICE, m_fPrice);
	DDX_Text(pDX, IDC_EDIT_SALE, m_fSale);
	DDX_Text(pDX, IDC_EDIT_NUM, m_iNum);
	DDX_Text(pDX, IDC_EDIT_SUM, m_fSum);
	DDX_Text(pDX, IDC_EDIT_COST, m_fCost);
	DDX_Text(pDX, IDC_EDIT_MARKS, m_strMarks);
}


BEGIN_MESSAGE_MAP(CCostDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CCostDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON2, &CCostDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CCostDlg 消息处理程序


void CCostDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_fCost < 0.01)
	{
		MessageBox("实际消费额不能为空~！","Worn", MB_ICONWARNING|MB_OK);
		return;
	}
	TEXTLOG("%s,product=%s,price=%f,num=%d,sale=%f,sum=%f,cost=%f,mark=%s",__FUNCTION__,\
		m_strProduct,m_fPrice,m_iNum,m_fSale,m_fSum,m_fCost,m_strMarks);
	CDialog::OnOK();
}

void CCostDlg::OnBnClickedButton2()
{
	UpdateData(TRUE);
	m_fSum = m_fPrice * m_iNum * (m_fSale/10);
	m_fCost = m_fSum;
	UpdateData(FALSE);

}
