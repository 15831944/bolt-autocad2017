#pragma once
#include "ExperienceDialog.h"
#include "TheoreticalDialog.h"
#include "LooseRangeDialog.h"
#include "ParametersDialog.h"
#include "MFCUtil.h"

// CMethodChooseDialog 对话框

class CMethodChooseDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CMethodChooseDialog)

public:
	CMethodChooseDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMethodChooseDialog();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	void UpdateUI();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_METHOD_CHOOSE_DIALOG };
#endif
private:
	CButton mRadioTheoretical;
	CButton mRadioExperience;
	CButton mRadioLooseRange;
	CButton mRadioExpert;
	CStatic mMethodChooseTitle;

	void SetMethodFlag(int flag);
	int GetMethodFlag();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	afx_msg void OnBnClickedButtonTunnelDialog();
	afx_msg void OnMoving(UINT fwSide, LPRECT pRect);
};
