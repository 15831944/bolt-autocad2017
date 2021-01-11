// StoneClassDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCad.h"
#include "StoneClassDialog.h"
#include "afxdialogex.h"


// CStoneClassDialog 对话框

IMPLEMENT_DYNAMIC(CStoneClassDialog, CDialogEx)

CStoneClassDialog::CStoneClassDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_STONE_CLASSES_DIALOG, pParent)
{

}

CStoneClassDialog::~CStoneClassDialog()
{
}

void CStoneClassDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_STONE_CLASS, pic_display);
}


BEGIN_MESSAGE_MAP(CStoneClassDialog, CDialogEx)
END_MESSAGE_MAP()


