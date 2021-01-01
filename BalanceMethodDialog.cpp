// BalanceMethodDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCad.h"
#include "BalanceMethodDialog.h"
#include "afxdialogex.h"
#include "DataChecker.h"
#include "DialogManager.h"


// CBalanceMethodDialog 对话框

IMPLEMENT_DYNAMIC(CBalanceMethodDialog, CDialogEx)

CBalanceMethodDialog::CBalanceMethodDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_BALANCE_METHOD_DIALOG, pParent)
	, mGroundAvgGravity(0)
	, mMaiDepth(0)
	, mCoalHardNumber(0)
	, mCoalThickness(0)
	, mCaiEffectNumber(0)
	, mInnerFriction(0)
	, mCableSafeNumber(0)
	, mBoltNumber(0)
	, mBoltOutLength(0)
	, mBoltPower(0)
	, mBoltSafeNumber(0)
	, mBoltSpace(0)
	, mBoltYieldNumber(0)
	, mCableAlength(0)
	, mCableOutLength(0)
	, mCoalFriction(0)
	, mMinBreakPower(0)
	, mCableStoneHeight(0)
	, mStoneToughNumber(0)
	, mStableNumber(0)
	, mTopAvgGravity(0)
	, mConcreteThickness(0)
	, mQiThickness(0)
{

	mGroundAvgGravity = 24.9;
	mMaiDepth = 581;
	mCaiEffectNumber = 1.1;
	mCoalHardNumber = 1.3;
	mCoalThickness = 5.9;
	mInnerFriction = 52;
	mCoalFriction = 6;
	mStableNumber = 0.5;
	mStoneToughNumber = 5;
	mBoltOutLength = 0.5;
	mBoltPower = 50;
	mBoltNumber = 7;
	mBoltSafeNumber = 2;
	mTopAvgGravity = 24.9;
	mBoltSpace = 800;
	mBoltYieldNumber = 240;

	mCableOutLength = 0.3;
	mCableStoneHeight = 5;
	mCableAlength = 1.4;
	mCableSafeNumber = 0.2;
	mMinBreakPower = 260;


}

CBalanceMethodDialog::~CBalanceMethodDialog()
{
}

void CBalanceMethodDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_GROUND_AVG_g, mGroundAvgGravity);
	DDX_Text(pDX, IDC_EDIT_MAI_DEPTH, mMaiDepth);
	DDX_Text(pDX, IDC_EDIT_MEI_TOUGH_NUMBER, mCoalHardNumber);
	DDX_Text(pDX, IDC_EDIT_MEI_THICKNESS, mCoalThickness);
	DDX_Text(pDX, IDC_EDIT_CAI_NUMBER, mCaiEffectNumber);
	DDX_Text(pDX, IDC_EDIT_INNER_FRICTION, mInnerFriction);
	DDX_Text(pDX, IDC_EDIT_CABLE_SAFE_NUMBER, mCableSafeNumber);
	DDX_Text(pDX, IDC_EDIT_BOLT_NUMBER, mBoltNumber);
	DDX_Text(pDX, IDC_EDIT_BOLT_OUT_LENGTH, mBoltOutLength);
	DDX_Text(pDX, IDC_EDIT_BOLT_POWER, mBoltPower);
	DDX_Text(pDX, IDC_EDIT_BOLT_SAFE_NUMBER, mBoltSafeNumber);
	DDX_Text(pDX, IDC_EDIT_BOLT_SPACE, mBoltSpace);
	DDX_Text(pDX, IDC_EDIT_BOLT_YIELD_NUMBER, mBoltYieldNumber);
	DDX_Text(pDX, IDC_EDIT_CABLE_ALENGTH, mCableAlength);
	DDX_Text(pDX, IDC_EDIT_CABLE_OUT_LENGTH, mCableOutLength);
	DDX_Text(pDX, IDC_EDIT_MEI_QING_FRCTION, mCoalFriction);
	DDX_Text(pDX, IDC_EDIT_MIN_BREAK, mMinBreakPower);
	DDX_Text(pDX, IDC_EDIT_STONE_HEIGHT, mCableStoneHeight);
	DDX_Text(pDX, IDC_EDIT_STONE_TOUGH_NUMBER, mStoneToughNumber);
	DDX_Text(pDX, IDC_EDIT_STABLE_NUMBER, mStableNumber);
	DDX_Text(pDX, IDC_EDIT_TOP_AVG_G, mTopAvgGravity);
	DDX_Text(pDX, IDC_EDIT_THE_CONCRETE_THICKNESS, mConcreteThickness);
	DDX_Text(pDX, IDC_EDIT_THE_QI_THICKNESS, mQiThickness);
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

	std::vector<double> mVecValue = { mGroundAvgGravity, mMaiDepth,
		mCoalHardNumber, mCoalThickness, mCaiEffectNumber, mInnerFriction,
		mCableSafeNumber,mBoltOutLength, mBoltPower, mBoltSafeNumber,
		mBoltSpace,mBoltYieldNumber,
		mCableAlength,mCableOutLength,mCoalFriction,mMinBreakPower,
		mCableStoneHeight,mStoneToughNumber,mStableNumber,
		mTopAvgGravity
	};

	if (DataChecker::HasZeroOrNegativeValue(mVecValue) == true) {
		MessageBox(_T("参数必须大于0"));
		pmLeagal = false;
	}
	else {
		CBalanceMethodFactory * factory = new CBalanceMethodFactory();
		CMethod * method = factory->createMethod();

		// 静态转型
		CBalanceMethod* BalanceMethod = static_cast<CBalanceMethod *>(method);
		CArcProjectBuilder::GetInstance()->SetMethod(BalanceMethod);


	}
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
