// ZuheliangDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCad.h"
#include "ZuheliangDialog.h"
#include "afxdialogex.h"
#include "ProjectBuilder.h"
#include "DataChecker.h"
#include "DialogManager.h"

// CZuheliangDialog 对话框

IMPLEMENT_DYNAMIC(CZuheliangDialog, CDialogEx)

CZuheliangDialog::CZuheliangDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ZUHELIANG_METHOD_DIALOG, pParent)
	, mGroundAvgGravity(0)
	, mMaiDepth(0)
	, mCoalHardNumber(0)
	, mCoalThickness(0)
	, mCaiEffectNumber(0)
	, mInnerFriction(0)
	, mBoltALength(0)
	, mBoltDiameter(0)
	, mBoltOutLength(0)
	, mBoltSafeNumber(0)
	, mCeyaliNumber(0)
	, mCoalFriction(0)
	, mKangjian(0)
	, mKangla(0)
	, mKuadu(0)
	, mStableNumber(0)
	, mStoneHardNumber(0)
	, mConcreteThickness(0)
	, mQiThickness(0)
	, mTopGravity(0)
	, mTopSafeNumber(0)
	, mTopThickness(0)
	, mZhejianNumber(0)
{
	mGroundAvgGravity = 24.9;
	mMaiDepth = 581;
	mCaiEffectNumber = 1.1;
	mCoalHardNumber = 1.3;
	mCoalThickness = 5.9;
	mInnerFriction = 52;
	mTopGravity = 24.9;
	mCeyaliNumber = 1.1;
	mZhejianNumber = 0.75;
	mCoalFriction = 6;
	mStableNumber = 0.5;
	mStoneHardNumber = 5;
	mBoltDiameter = 22;
	mBoltOutLength = 0.1;
	mBoltALength = 0.5;
	mKuadu = 5.2;
	mKangla = 1.09;
	mKangjian = 266;
	mTopSafeNumber = 3;
	mTopThickness = 5;
	mBoltSafeNumber = 5;
	mInnerFriction = 52;
}

CZuheliangDialog::~CZuheliangDialog()
{
}

void CZuheliangDialog::UpdateUI()
{
	CArcProjectBuilder::GetInstance()->BuildMethod();

	CZuheliangMethod * zuheliang = CArcProjectBuilder::GetInstance()->GetZuheliangMethod();
	UpdateData(TRUE);

	mGroundAvgGravity = zuheliang->GetGroundAvgGravity();
	mMaiDepth = zuheliang->GetMaiDepth();
	mCoalHardNumber = zuheliang->GetCoalHardNumber();
	mCoalThickness = zuheliang->GetCoalThickness();
	mCaiEffectNumber = zuheliang->GetCaiEffectNumber();
	mInnerFriction = zuheliang->GetInnerFriction();
	mBoltALength = zuheliang->GetBoltALength();
	mBoltDiameter = zuheliang->GetBoltDiameter();
	mBoltOutLength = zuheliang->GetBoltOutLength();
	mBoltSafeNumber = zuheliang->GetBoltSafeNumber();
	mCeyaliNumber = zuheliang->GetCeyaliNumber();
	mCoalFriction = zuheliang->GetCoalFriction();
	mKangjian = zuheliang->GetKangjian();
	mKangla = zuheliang->GetKangla();
	mKuadu = zuheliang->GetKuadu();
	mStableNumber = zuheliang->GetStableNumber();
	mStoneHardNumber = zuheliang->GetStoneHardNumber();
	mTopGravity = zuheliang->GetTopGravity();
	mTopSafeNumber = zuheliang->GetTopSafeNumber();
	mTopThickness = zuheliang->GetTopThickness();
	mZhejianNumber = zuheliang->GetZhejianNumber();

	mConcreteThickness = CArcProjectBuilder::GetInstance()->GetArcTunnel()->GetConcreteThickness();
	mQiThickness = CArcProjectBuilder::GetInstance()->GetArcTunnel()->GetQiThickness();

	UpdateData(FALSE);
}

void CZuheliangDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_GROUND_AVG_g, mGroundAvgGravity);
	DDX_Text(pDX, IDC_EDIT_MAI_DEPTH, mMaiDepth);
	DDX_Text(pDX, IDC_EDIT_MEI_TOUGH_NUMBER, mCoalHardNumber);
	DDX_Text(pDX, IDC_EDIT_COAL_THICKNESS, mCoalThickness);
	DDX_Text(pDX, IDC_EDIT_CAI_NUMBER, mCaiEffectNumber);
	DDX_Text(pDX, IDC_EDIT_INNER_FRICTION2, mInnerFriction);
	DDX_Text(pDX, IDC_EDIT_BOLT_ALENGTH, mBoltALength);
	DDX_Text(pDX, IDC_EDIT_BOLT_DIAMETER, mBoltDiameter);
	DDX_Text(pDX, IDC_EDIT_BOLT_OUT_LENGTH, mBoltOutLength);
	DDX_Text(pDX, IDC_EDIT_BOLT_SAFE_NUMBER, mBoltSafeNumber);
	DDX_Text(pDX, IDC_EDIT_CEYALI_NUMBER, mCeyaliNumber);
	DDX_Text(pDX, IDC_EDIT_COAL_QING_FRCTION, mCoalFriction);
	DDX_Text(pDX, IDC_EDIT_KANGJIAN, mKangjian);
	DDX_Text(pDX, IDC_EDIT_KANGLA, mKangla);
	DDX_Text(pDX, IDC_EDIT_KUADU, mKuadu);
	DDX_Text(pDX, IDC_EDIT_STABLE_NUMBER, mStableNumber);
	DDX_Text(pDX, IDC_EDIT_STONE_TOUGH_NUMBER, mStoneHardNumber);
	DDX_Text(pDX, IDC_EDIT_THE_CONCRETE_THICKNESS, mConcreteThickness);
	DDX_Text(pDX, IDC_EDIT_THE_QI_THICKNESS, mQiThickness);
	DDX_Text(pDX, IDC_EDIT_TOP_AVG_G, mTopGravity);
	DDX_Text(pDX, IDC_EDIT_TOP_SAFE_NUMBER, mTopSafeNumber);
	DDX_Text(pDX, IDC_EDIT_TOP_THICKNESS, mTopThickness);
	DDX_Text(pDX, IDC_EDIT_ZHEJIAN_NUMBER, mZhejianNumber);
}


BEGIN_MESSAGE_MAP(CZuheliangDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CZuheliangDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CZuheliangDialog::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_PREDIALOG, &CZuheliangDialog::OnBnClickedButtonPredialog)
END_MESSAGE_MAP()


// CZuheliangDialog 消息处理程序


void CZuheliangDialog::CheckThickness()
{
	CArcTunnel * pArc = CArcProjectBuilder::GetInstance()->GetArcTunnel();
	switch (pArc->GetZhihuWay())
	{
	case 1:
		pArc->SetConcreteThickness(0);
		pArc->SetQiThickness(0);
		break;
	case 2:
		pArc->SetConcreteThickness(mConcreteThickness);
		pArc->SetQiThickness(mQiThickness);
		break;
	case 3:
		pArc->SetConcreteThickness(mConcreteThickness);
		pArc->SetQiThickness(0);
		break;
	case 4:
		pArc->SetConcreteThickness(mConcreteThickness);
		pArc->SetQiThickness(mQiThickness);
		break;
	default:
		break;
	}
}

void CZuheliangDialog::SetExpertValue()
{
	CZuheliangMethod * zuheliang = CArcProjectBuilder::GetInstance()->GetZuheliangMethod();

	CBolt * topBolt = CArcProjectBuilder::GetInstance()->GetArcTunnel()->GetTopBolt();
	int tmp = 1000; // 进制单位转换
	topBolt->setLength(zuheliang->GetTopBoltLength());
	topBolt->setNumber(zuheliang->GetBoltNumber());
	topBolt->setDiameter(zuheliang->GetBoltDiameter());
	topBolt->setPitch(zuheliang->GetBoltSpaceAndPitch() * tmp);
	topBolt->setSpace(zuheliang->GetBoltSpaceAndPitch() * tmp);
}

BOOL CZuheliangDialog::OnInitDialog()
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


void CZuheliangDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	std::vector<double> mVecValue = { mGroundAvgGravity, mMaiDepth,
	  mCoalHardNumber,
	  mCoalThickness,
	  mCaiEffectNumber,
	  mInnerFriction,
	  mBoltALength,
	  mBoltDiameter,
	  mBoltOutLength,
	  mBoltSafeNumber,
	  mCeyaliNumber,
	  mCoalFriction,
	  mKangjian,
	  mKangla,
	  mKuadu,
	  mStableNumber,
	  mStoneHardNumber,
	  mTopGravity,
	  mTopSafeNumber, mTopThickness, mZhejianNumber,
	};

	if (DataChecker::HasZeroOrNegativeValue(mVecValue) == true) {
		MessageBox(_T("参数必须大于0"), _T("警告"), MB_ICONWARNING);
		pmLeagal = false;
	}
	else {
		CZuheliangFactory * factory = new CZuheliangFactory();
		CMethod * method = factory->createMethod();

		// 静态转型
		CZuheliangMethod* tmpMethod = static_cast<CZuheliangMethod *>(method);
		CArcProjectBuilder::GetInstance()->SetMethod(tmpMethod);

		CZuheliangMethod * zuheliang = CArcProjectBuilder::GetInstance()->GetZuheliangMethod();
		CArcTunnel * pArc = CArcProjectBuilder::GetInstance()->GetArcTunnel();

		zuheliang->SetA(pArc->GetWidth());
		zuheliang->SetGroundAvgGravity(mGroundAvgGravity);
		zuheliang->SetMaiDepth(mMaiDepth);
		zuheliang->SetCoalHardNumber( mCoalHardNumber);
		zuheliang->SetCoalThickness( mCoalThickness);
		zuheliang->SetCaiEffectNumber( mCaiEffectNumber);
		zuheliang->SetInnerFriction( mInnerFriction);
		zuheliang->SetBoltALength( mBoltALength);
		zuheliang->SetBoltDiameter( mBoltDiameter);
		zuheliang->SetBoltOutLength( mBoltOutLength);
		zuheliang->SetBoltSafeNumber(mBoltSafeNumber);
		zuheliang->SetCeyaliNumber(mCeyaliNumber);
		zuheliang->SetCoalFriction(mCoalFriction);
		zuheliang->SetKangjian(mKangjian);
		zuheliang->SetKangla(mKangla);
		zuheliang->SetKuadu(mKuadu);
		zuheliang->SetStableNumber(mStableNumber);
		zuheliang->SetStoneHardNumber(mStoneHardNumber);
		zuheliang->SetTopGravity(mTopGravity);
		zuheliang->SetTopSafeNumber(mTopSafeNumber);
		zuheliang->SetTopThickness(mTopThickness);
		zuheliang->SetZhejianNumber(mZhejianNumber);

		CArcProjectBuilder::GetInstance()->GetMethod()->SetConcreteThickness(mConcreteThickness);
		CArcProjectBuilder::GetInstance()->GetMethod()->SetQiThickness(mQiThickness);
		CArcProjectBuilder::GetInstance()->SetCalMethodSaveToInstance(TRUE);

		SetExpertValue();
		CheckThickness();
		pmLeagal = true;
	}

	if (pmLeagal) {
		DialogManager::GetInstance().setHasCalculated(true);
		CArcProjectBuilder::GetInstance()->GetArcTunnel()->SetHasLeftBolt(true);
		CArcProjectBuilder::GetInstance()->GetArcTunnel()->SetHasCable(true);

		DialogManager::GetInstance().ShowResultDlg();
		ShowWindow(SW_HIDE);
	}
}


void CZuheliangDialog::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_HIDE);
}


void CZuheliangDialog::OnBnClickedButtonPredialog()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_HIDE);
	DialogManager::GetInstance().ShowMethodChooseDlg();
}
