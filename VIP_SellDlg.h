// VIP_SellDlg.h : ͷ�ļ�
#ifndef _VIP_SELLDLG_H_
#define _VIP_SELLDLG_H_

#pragma once


// CVIP_SellDlg �Ի���
class CVIP_SellDlg : public CDialogEx
{
// ����
public:
	CVIP_SellDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_VIP_SELL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	//int LoadSQLInfo(void * para, int n_column, char ** column_value, char ** column_name);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnActivate();
	afx_msg void OnBnClickedButRecharge();
	afx_msg void OnBnClickedBtnQuery();
	UINT64 m_llongCardID;
	CString m_strName;
	UINT64 m_longPhone;
};

#endif