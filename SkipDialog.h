#pragma once
#include "afxwin.h"


// CSkipDialog �Ի���

class CSkipDialog : public CDialog
{
	DECLARE_DYNAMIC(CSkipDialog)

public:
	CSkipDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSkipDialog();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SKIP_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
