#pragma once
#include "afxwin.h"


// CSkipDialog 对话框

class CSkipDialog : public CDialog
{
	DECLARE_DYNAMIC(CSkipDialog)

public:
	CSkipDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSkipDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SKIP_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
