#pragma once
#include "afxwin.h"


// CStoneClassDialog 对话框

class CStoneClassDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CStoneClassDialog)

public:
	CStoneClassDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CStoneClassDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STONE_CLASSES_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	CStatic pic_display;
};
