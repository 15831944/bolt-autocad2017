
// MFCadDlg.h : ͷ�ļ�
//

#pragma once

#include "ProjectDialog.h"

#include "ConfigFileUtil.h"
#include "afxwin.h"

// CMFCadDlg �Ի���
class CMFCadDlg : public CDialogEx
{
// ����
public:
	CMFCadDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME 
	enum { IDD = IDD_MFCAD_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	CBrush mBrush;

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
