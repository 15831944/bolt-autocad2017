#pragma once


// CThicknessDialog 对话框

class CThicknessDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CThicknessDialog)

public:
	CThicknessDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CThicknessDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_THICKNESS_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	double mConThickness;
	double mQiThickness;
	bool isPmLeagal = false;

	void SaveParams();
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonPredialog();
	virtual BOOL OnInitDialog();

};
