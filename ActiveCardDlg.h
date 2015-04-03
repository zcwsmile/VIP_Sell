#ifndef _ACTIVECARDDLG_H_
#define _ACTIVECARDDLG_H_

#pragma once
#include "afxdtctl.h"
#include "atltime.h"


// CActiveCardDlg �Ի���

class CActiveCardDlg : public CDialog
{
	DECLARE_DYNAMIC(CActiveCardDlg)

public:
	CActiveCardDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CActiveCardDlg();

// �Ի�������
	enum { IDD = IDD_ACTIVECARDDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	UINT64 m_longCardID;
	CString m_strName;
	UINT64 m_longPhone;
	BOOL m_bWoman;
	CTime m_CtimeBirthday;
	CDateTimeCtrl m_CtrBirthdayTime;
	float m_flSumMoney;
	CString m_strMarket;
	virtual BOOL OnInitDialog();

};


#endif