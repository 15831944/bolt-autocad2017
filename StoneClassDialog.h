#pragma once
#include "afxwin.h"


// CStoneClassDialog �Ի���

class CStoneClassDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CStoneClassDialog)

public:
	CStoneClassDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CStoneClassDialog();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STONE_CLASSES_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	CStatic pic_display;
};
