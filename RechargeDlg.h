#ifndef _RECHARGEDLG_H_
#define _RECHARGEDLG_H_
#pragma once


// CRechargeDlg �Ի���

class CRechargeDlg : public CDialog
{
	DECLARE_DYNAMIC(CRechargeDlg)

public:
	CRechargeDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRechargeDlg();

// �Ի�������
	enum { IDD = IDD_RECHARGEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};

#endif
