#ifndef _RECHARGEDLG_H_
#define _RECHARGEDLG_H_
#pragma once


// CRechargeDlg 对话框

class CRechargeDlg : public CDialog
{
	DECLARE_DYNAMIC(CRechargeDlg)

public:
	CRechargeDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRechargeDlg();

// 对话框数据
	enum { IDD = IDD_RECHARGEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};

#endif
