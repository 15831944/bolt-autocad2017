
// MFCadDlg.h : 头文件
//

#pragma once

#include "ProjectDialog.h"

#include "ConfigFileUtil.h"
#include "afxwin.h"

// CMFCadDlg 对话框
class CMFCadDlg : public CDialogEx
{
// 构造
public:
	CMFCadDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME 
	enum { IDD = IDD_MFCAD_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	CBrush mBrush;

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();

	void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNewProject();
	afx_msg void OnAboutApplication();
	virtual void OnOK();
	afx_msg void OnBnClickedButtonSaveFile();
	afx_msg void OnOpenProject();
	afx_msg void OnSaveProject();
	afx_msg void OnBnClickedButtonFindAcadPath();
	afx_msg void OnProjectInformation();
	virtual void OnCancel();
	afx_msg void OnMenuExit();
private:
	void ConcreteOpenProject();

public:
	afx_msg void OnMove(int x, int y);
	afx_msg void OnSaveto();
	afx_msg void OnDestroy();
};
