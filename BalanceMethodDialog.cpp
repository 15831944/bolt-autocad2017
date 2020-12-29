// BalanceMethodDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCad.h"
#include "BalanceMethodDialog.h"
#include "afxdialogex.h"
#include "DialogManager.h"


// CBalanceMethodDialog 对话框

IMPLEMENT_DYNAMIC(CBalanceMethodDialog, CDialogEx)

CBalanceMethodDialog::CBalanceMethodDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_BALANCE_METHOD_DIALOG, pParent)
{

}

CBalanceMethodDialog::~CBalanceMethodDialog()
{
}

void CBalanceMethodDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBalanceMethodDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CBalanceMethodDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_PREDIALOG, &CBalanceMethodDialog::OnBnClickedButtonPredialog)
	ON_BN_CLICKED(IDCANCEL, &CBalanceMethodDialog::OnBnClickedCancel)
END_MESSAGE_MAP()


// CBalanceMethodDialog 消息处理程序


BOOL CBalanceMethodDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect dlg;
	GetWindowRect(dlg);
	ScreenToClient(dlg);
	SetWindowPos(0, (GetSystemMetrics(SM_CXSCREEN) / 2) - (dlg.Width() / 2),
		(GetSystemMetrics(SM_CYSCREEN) / 2) - (dlg.Height() / 2), dlg.Width(), dlg.Height(),
		SW_SHOW);

	HICON hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_FOLDER));
	SetIcon(hIcon, FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CBalanceMethodDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_HIDE);
	DialogManager::GetInstance().ShowResultDlg();
}


void CBalanceMethodDialog::OnBnClickedButtonPredialog()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_HIDE);
	DialogManager::GetInstance().ShowMethodChooseDlg();
}


void CBalanceMethodDialog::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_HIDE);
}
