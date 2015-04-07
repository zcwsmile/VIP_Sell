#pragma once


// CCostDlg 对话框

class CCostDlg : public CDialog
{
	DECLARE_DYNAMIC(CCostDlg)

public:
	CCostDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCostDlg();

// 对话框数据
	enum { IDD = IDD_COSTDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strProduct;
	float m_fPrice;
	float m_fSale;
	int m_iNum;
	float m_fSum;
	float m_fCost;
	CString m_strMarks;
	afx_msg void OnBnClickedOk();

	afx_msg void OnBnClickedButton2();
};
