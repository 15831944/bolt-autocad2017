// LooseRangeDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCad.h"
#include "MethodChooseDialog.h"
#include "LooseRangeDialog.h"
#include "ParametersDialog.h"
#include "afxdialogex.h"
#include "ProjectBuilder.h"
#include "DialogManager.h"

// CLooseRangeDialog 对话框

IMPLEMENT_DYNAMIC(CLooseRangeDialog, CDialogEx)

CLooseRangeDialog::CLooseRangeDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LOOSE_RANGE_DIALOG, pParent)
	, mLooseRange(0)
{

}

CLooseRangeDialog::~CLooseRangeDialog()
{
}

void CLooseRangeDialog::UpdateUI()
{
	CArcProjectBuilder::GetInstance()->BuildMethod();

	CLooseRangeMethod * loose = CArcProjectBuilder::GetInstance()->GetLooseMethod();
	UpdateData(TRUE);
	mRadioLooseRange.SetCheck(loose->GetMeasureWay() == 1 ? TRUE : FALSE);
	mLooseRange = loose->GetLooseRange();
	UpdateData(FALSE);
}

void CLooseRangeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_LOOSE_RANGE, mLooseRange);
	DDX_Control(pDX, IDC_EDIT_LOOSE_RANGE, mEdtLooseRange);
	DDX_Control(pDX, IDC_EDIT_LOOSE_STONE_STRONG_NUMBER, mEdtStoneStrongNumber);
	DDX_Control(pDX, IDC_EDIT_LOOSE_AVG_GRIVITY, mEdtAvgGrivity);
	DDX_Control(pDX, IDC_EDIT_LOOSE_COMPRESSIVE, mEdtCompressive);
	DDX_Control(pDX, IDC_EDIT_LOOSE_DEPTH, mEdtDepth);
	DDX_Control(pDX, IDC_EDIT_LOOSE_FRICTION, mEdtFriction);
	DDX_Control(pDX, IDC_EDIT_LOOSE_ATTACH, mEdtAttach);
	DDX_Control(pDX, IDC_EDIT_LOOSE_SHU_LENGTH, mEdtShuLength);
	DDX_Control(pDX, IDC_EDIT_LOOSE_BOLT_SPACE, mEdtBoltSpace);
	DDX_Control(pDX, IDC_EDIT_LOOSE_BOLT_PITCH, mEdtBoltPitch);
	DDX_Control(pDX, IDC_EDIT_LOOSE_BOLT_DIAMETER, mEdtBoltDiameter);
	DDX_Control(pDX, IDC_EDIT_LOOSE_BOLT_DESIGN_NUMBER, mEdtBoltDesignNumber);
	DDX_Control(pDX, IDC_EDIT_LOOSE_BOLT_ATTACH, mEdtBoltAttach);
	DDX_Control(pDX, IDC_EDIT_LOOSE_CABLE_FREELENGTH, mCalbeFreeLength);
	DDX_Control(pDX, IDC_EDIT_LOOSE_CABLE_SPACE, mCableSpace);
	DDX_Control(pDX, IDC_EDIT_LOOSE_CABLE_PITCH, mEdtCablePitch);
	DDX_Control(pDX, IDC_EDIT_LOOSE_CABLE_DIAMETER, mEdtCableDiameter);
	DDX_Control(pDX, IDC_EDIT_LOOSE_CABLE_BREAK_POWER, mCableBreakPower);
	DDX_Control(pDX, IDC_EDIT_LOOSE_CABLE_ATTACH, mEdtCableAttach);
	DDX_Control(pDX, IDC_RADIO_LOOSE_MEASURE, mRadioLooseRange);
}


BEGIN_MESSAGE_MAP(CLooseRangeDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CLooseRangeDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_TUNNEL_DIALOG, &CLooseRangeDialog::OnBnClickedButtonTunnelDialog)
	ON_BN_CLICKED(IDC_RADIO_MAOLUO_MEASURE, &CLooseRangeDialog::OnBnClickedRadioMaoluoMeasure)
	ON_BN_CLICKED(IDC_RADIO_LOOSE_MEASURE, &CLooseRangeDialog::OnBnClickedRadioLooseMeasure)
	ON_WM_MOVING()
END_MESSAGE_MAP()


// CLooseRangeDialog 消息处理程序
void CLooseRangeDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码


	UpdateData(TRUE);

	CLooseRangeMethod * loose = CArcProjectBuilder::GetInstance()->GetLooseMethod();
	CArcTunnel * pArc = CArcProjectBuilder::GetInstance()->GetArcTunnel();

	int tmp = 1000;

	loose->SetA(pArc->GetWidth() / tmp);
	loose->SetH(pArc->GetHeight() / tmp);
	loose->SetMeasureWay(1);
	loose->SetLooseRange(mLooseRange / tmp);

	pArc->GetTopBolt()->setLength(loose->GetTopBoltLength() * tmp);

	CArcProjectBuilder::GetInstance()->SetCalMethodSaveToInstance(TRUE);

	ShowWindow(SW_HIDE);
	DialogManager::GetInstance().setHasCalculated(true);
	DialogManager::GetInstance().ShowResultDlg();
	

}

void CLooseRangeDialog::OnBnClickedButtonTunnelDialog()
{
	// TODO: 在此添加控件通知处理程序代码

	ShowWindow(SW_HIDE);
	DialogManager::GetInstance().ShowMethodChooseDlg();

}


BOOL CLooseRangeDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	// 窗口居中显示
	CRect dlg;
	GetWindowRect(dlg);
	ScreenToClient(dlg);
	SetWindowPos(0, (GetSystemMetrics(SM_CXSCREEN) / 2) - (dlg.Width() / 2),
		(GetSystemMetrics(SM_CYSCREEN) / 2) - (dlg.Height() / 2), dlg.Width(), dlg.Height(),
		SW_SHOW);
	HICON hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_FOLDER));
	SetIcon(hIcon, FALSE);

	mRadioLooseRange.SetCheck(TRUE);
	OnBnClickedRadioLooseMeasure();


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CLooseRangeDialog::OnBnClickedRadioMaoluoMeasure()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(_T("请选择理论计算法\n"));
}


void CLooseRangeDialog::OnBnClickedRadioLooseMeasure()
{
	// TODO: 在此添加控件通知处理程序代码
	if (mRadioLooseRange.GetCheck() == TRUE) {
		mEdtLooseRange.EnableWindow(TRUE);
	}
	else {
		mEdtLooseRange.EnableWindow(FALSE);
	}
}


void CLooseRangeDialog::OnMoving(UINT fwSide, LPRECT lpRect)
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
