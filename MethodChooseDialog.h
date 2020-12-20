#pragma once
#include "ExperienceDialog.h"
#include "TheoreticalDialog.h"
#include "LooseRangeDialog.h"
#include "ParametersDialog.h"
#include "MFCUtil.h"

// CMethodChooseDialog �Ի���

class CMethodChooseDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CMethodChooseDialog)

public:
	CMethodChooseDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMethodChooseDialog();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	void UpdateUI();

// �Ի�������
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	afx_msg void OnBnClickedButtonTunnelDialog();
	afx_msg void OnMoving(UINT fwSide, LPRECT pRect);
};
