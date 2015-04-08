// VIP_SellDlg.h : 头文件
#ifndef _VIP_SELLDLG_H_
#define _VIP_SELLDLG_H_
#include "afxcmn.h"

#pragma once


// CVIP_SellDlg 对话框
class CVIP_SellDlg : public CDialogEx
{
// 构造
public:
	CVIP_SellDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_VIP_SELL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
	CString m_strCardID;
	CString m_strName;
	CString m_strPhone;
	float m_fBalance;
	afx_msg void OnBnClickedButUpdate();
	afx_msg void OnBnClickedBtnCost();
	void UpdateCheckList();
	void InitClear();
	CListCtrl m_ctrListCheck;
	int m_iNumindex;
};

#endif