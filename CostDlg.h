#pragma once


// CCostDlg �Ի���

class CCostDlg : public CDialog
{
	DECLARE_DYNAMIC(CCostDlg)

public:
	CCostDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCostDlg();

// �Ի�������
	enum { IDD = IDD_COSTDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
