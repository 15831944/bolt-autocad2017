#pragma once

#include "TunnelChooseDialog.h"
#include "ProjectBuilder.h"
#include "afxwin.h"
#include <vector>
#include "afxdtctl.h"
// CProjectDialog 对话框

class CProjectDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CProjectDialog)

public:
	CProjectDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CProjectDialog();
	void UpdateUI();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROJECT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
private:	

	CTunnelProject* GetProjectInfoFromMFC();

	CEdit mEdtPaperTitle;
	CEdit mEdtDevelopApart;
	CDateTimeCtrl mDtDate;
	CDateTimeCtrl mDtCheckDate;
	CEdit mEdtChecker;

	CEdit mEdtDescription;
	CEdit mEdtDesignApart;
	CEdit mEdtDesigner;
	CEdit mEdtPaperNumber;
	CEdit mEdtScaleOne;
	CEdit mEdtScaleNumber;
	CComboBox mComboPaperSize;

	std::vector<CEdit * > mVectorProject{ &mEdtPaperTitle, &mEdtDevelopApart,
		&mEdtChecker  ,&mEdtDescription ,&mEdtDesignApart ,&mEdtDesigner ,
		&mEdtPaperNumber ,&mEdtScaleNumber };

private:
	CString mStrPaperDescription;
	CString mStrPaperTitle;
	int mIntScaleNumber;
	CString mStrPaperNumber;
	CString mStrPaperSize;
	CString mStrDesigner;

	CString mStrDate;
	CString mStrChecker;
	CString mStrCheckDate;
	CString mStrDesignApart;
	virtual void OnCancel();
public:
	afx_msg void OnMove(int x, int y);
	afx_msg void OnMoving(UINT fwSide, LPRECT pRect);
	afx_msg void OnBnClickedCancel();
};
