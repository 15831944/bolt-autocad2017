// MethodChooseDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCad.h"
#include "MethodChooseDialog.h"
#include "TunnelChooseDialog.h"
#include "afxdialogex.h"
#include "ProjectBuilder.h"

#include "DialogManager.h"

// CMethodChooseDialog 对话框

IMPLEMENT_DYNAMIC(CMethodChooseDialog, CDialogEx)

CMethodChooseDialog::CMethodChooseDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_METHOD_CHOOSE_DIALOG, pParent)
{
}

CMethodChooseDialog::~CMethodChooseDialog()
{
}

void CMethodChooseDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO_THEORETICAL_CALCULATION, mRadioTheoretical);
	DDX_Control(pDX, IDC_RADIO_PROGRAM_EXPERIENCE, mRadioExperience);
	DDX_Control(pDX, IDC_RADIO_LOOSE_RANGE_DESIGN, mRadioLooseRange);
	DDX_Control(pDX, IDC_RADIO_EXPERT_DECISION, mRadioExpert);
	DDX_Control(pDX, IDC_STATIC_CHOOSE_METHOD, mMethodChooseTitle);
	DDX_Control(pDX, IDC_RADIO_BALANCE_METHOD, mRadioBalanceMethod);
	DDX_Control(pDX, IDC_RADIO_ZUHELIANG_METHOD, mRadioZuheliang);
}


BEGIN_MESSAGE_MAP(CMethodChooseDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CMethodChooseDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_TUNNEL_DIALOG, &CMethodChooseDialog::OnBnClickedButtonTunnelDialog)
	ON_WM_MOVING()
END_MESSAGE_MAP()


// CMethodChooseDialog 消息处理程序
BOOL CMethodChooseDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	// 设置窗口居中显示
	CRect dlg;
	GetWindowRect(dlg);
	ScreenToClient(dlg);
	SetWindowPos(0, (GetSystemMetrics(SM_CXSCREEN) / 2) - (dlg.Width() / 2),
		(GetSystemMetrics(SM_CYSCREEN) / 2) - (dlg.Height() / 2), dlg.Width(), dlg.Height(),
		SW_SHOW);
	HICON hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_FOLDER));
	SetIcon(hIcon, FALSE);

	// 设置标题字体
	mMethodChooseTitle.SetFont(MFCUtil::GetTitleFont());

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CMethodChooseDialog::UpdateUI()
{
	SetMethodFlag(CArcProjectBuilder::GetInstance()->GetArcTunnel()->GetCalMethod());
}

void CMethodChooseDialog::SetMethodFlag(int flag) {
	switch (flag)
	{
	case 1:
		mRadioTheoretical.SetCheck(TRUE);
		mRadioExperience.SetCheck(FALSE);
		mRadioLooseRange.SetCheck(FALSE);
		mRadioExpert.SetCheck(FALSE);
		mRadioBalanceMethod.SetCheck(FALSE);
		mRadioZuheliang.SetCheck(FALSE);
		CArcProjectBuilder::GetInstance()->GetArcTunnel()->SetCalMethod(1);
		break;
	case 2:
		mRadioTheoretical.SetCheck(FALSE);
		mRadioExperience.SetCheck(TRUE);
		mRadioLooseRange.SetCheck(FALSE);
		mRadioExpert.SetCheck(FALSE);
		mRadioBalanceMethod.SetCheck(FALSE);
		mRadioZuheliang.SetCheck(FALSE);
		CArcProjectBuilder::GetInstance()->GetArcTunnel()->SetCalMethod(2);
		break;
	case 3:
		mRadioTheoretical.SetCheck(FALSE);
		mRadioExperience.SetCheck(FALSE);
		mRadioLooseRange.SetCheck(TRUE);
		mRadioExpert.SetCheck(FALSE);
		mRadioBalanceMethod.SetCheck(FALSE);
		mRadioZuheliang.SetCheck(FALSE);
		CArcProjectBuilder::GetInstance()->GetArcTunnel()->SetCalMethod(3);
		break;
	case 4:
		mRadioTheoretical.SetCheck(FALSE);
		mRadioExperience.SetCheck(FALSE);
		mRadioLooseRange.SetCheck(FALSE);
		mRadioExpert.SetCheck(TRUE);
		mRadioBalanceMethod.SetCheck(FALSE);
		mRadioZuheliang.SetCheck(FALSE);
		CArcProjectBuilder::GetInstance()->GetArcTunnel()->SetCalMethod(4);
		break;
	case 5:
		mRadioTheoretical.SetCheck(FALSE);
		mRadioExperience.SetCheck(FALSE);
		mRadioLooseRange.SetCheck(FALSE);
		mRadioExpert.SetCheck(FALSE);
		mRadioBalanceMethod.SetCheck(TRUE);
		mRadioZuheliang.SetCheck(FALSE);
		CArcProjectBuilder::GetInstance()->GetArcTunnel()->SetCalMethod(5);
		break;
	case 6:
		mRadioTheoretical.SetCheck(FALSE);
		mRadioExperience.SetCheck(FALSE);
		mRadioLooseRange.SetCheck(FALSE);
		mRadioExpert.SetCheck(FALSE);
		mRadioBalanceMethod.SetCheck(FALSE);
		mRadioZuheliang.SetCheck(TRUE);
		CArcProjectBuilder::GetInstance()->GetArcTunnel()->SetCalMethod(6);
		break;
	default:
		break;
	}
}

int CMethodChooseDialog::GetMethodFlag() {
	if (mRadioTheoretical.GetCheck() == TRUE) return 1;
	if (mRadioExperience.GetCheck() == TRUE) return 2;
	if (mRadioLooseRange.GetCheck() == TRUE) return 3;
	if (mRadioExpert.GetCheck() == TRUE) return 4;
	if (mRadioBalanceMethod.GetCheck() == TRUE) return 5;
	if (mRadioZuheliang.GetCheck() == TRUE) return 6;
	return 0;
}

void CMethodChooseDialog::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

}                                                       



void CMethodChooseDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	int flag = GetMethodFlag();
	std::cout << "method flag: " << flag << std::endl;
	if (flag == 0)
	{
		MessageBox(_T("至少选择一种计算方法"), _T("警告"), MB_ICONWARNING | MB_OK);
	}
	else {
		CArcProjectBuilder::GetInstance()->GetArcTunnel()->SetCalMethod(flag);
		CArcProjectBuilder::GetInstance()->SetMethodSaveToInstance(TRUE);

		int pTheoreticalState = mRadioTheoretical.GetCheck();
		int pExperienceState = mRadioExperience.GetCheck();
		int pLooseState = mRadioLooseRange.GetCheck();
		int pExpertState = mRadioExpert.GetCheck();
		int pBalanceMethod = mRadioBalanceMethod.GetCheck();
		int pZuheliang = mRadioZuheliang.GetCheck();

		if (pTheoreticalState != 0)
		{
			//理论法被选中
			DialogManager::GetInstance().ShowTheoryDlg();
		}
		if (pExperienceState != 0)
		{
			DialogManager::GetInstance().ShowExpDlg();
		}
		if (pLooseState != 0) {
			DialogManager::GetInstance().ShowLooseDlg();
		}
		if (pExpertState != 0) {
			DialogManager::GetInstance().ShowResultDlg();
		}
		if (pBalanceMethod != 0) {
			DialogManager::GetInstance().ShowBalanceDlg();
		}
		if (pZuheliang != 0) {
			DialogManager::GetInstance().ShowZuheliangDlg();
		}
		ShowWindow(SW_HIDE);
	}

}



void CMethodChooseDialog::OnBnClickedButtonTunnelDialog()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_HIDE);
	DialogManager::GetInstance().ShowTunnelChooseDlg();
}


void CMethodChooseDialog::OnMoving(UINT fwSide, LPRECT lpRect)
{
	CRect rectParent;
	GetParent()->GetClientRect(&rectParent);
	GetParent()->ClientToScreen(&rectParent);
	CRect rectChild; GetWindowRect(&rectChild);
	lpRect->left = min(lpRect->left, rectParent.right - rectChild.Width());
	lpRect->left = max(lpRect->left, rectParent.left);
	lpRect->top = min(lpRect->top, rectParent.bottom - rectChild.Height());
	lpRect->top = max(lpRect->top, rectParent.top);
	lpRect->right = min(lpRect->right, rectParent.right);
	lpRect->right = max(lpRect->right, rectParent.left + rectChild.Width());
	lpRect->bottom = min(lpRect->bottom, rectParent.bottom);
	lpRect->bottom = max(lpRect->bottom, rectParent.top + rectChild.Height());

	CDialogEx::OnMoving(fwSide, lpRect);

	// TODO: 在此处添加消息处理程序代码
}
