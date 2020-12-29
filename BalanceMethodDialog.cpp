// BalanceMethodDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCad.h"
#include "BalanceMethodDialog.h"
#include "afxdialogex.h"
#include "DialogManager.h"


// CBalanceMethodDialog �Ի���

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


// CBalanceMethodDialog ��Ϣ�������


BOOL CBalanceMethodDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect dlg;
	GetWindowRect(dlg);
	ScreenToClient(dlg);
	SetWindowPos(0, (GetSystemMetrics(SM_CXSCREEN) / 2) - (dlg.Width() / 2),
		(GetSystemMetrics(SM_CYSCREEN) / 2) - (dlg.Height() / 2), dlg.Width(), dlg.Height(),
		SW_SHOW);

	HICON hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_FOLDER));
	SetIcon(hIcon, FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CBalanceMethodDialog::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ShowWindow(SW_HIDE);
	DialogManager::GetInstance().ShowResultDlg();
}


void CBalanceMethodDialog::OnBnClickedButtonPredialog()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ShowWindow(SW_HIDE);
	DialogManager::GetInstance().ShowMethodChooseDlg();
}


void CBalanceMethodDialog::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ShowWindow(SW_HIDE);
}
