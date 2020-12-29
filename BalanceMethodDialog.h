#pragma once


// CBalanceMethodDialog 对话框

class CBalanceMethodDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CBalanceMethodDialog)

public:
	CBalanceMethodDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBalanceMethodDialog();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonPredialog();
	afx_msg void OnBnClickedCancel();


// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BALANCE_METHOD_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()


};
