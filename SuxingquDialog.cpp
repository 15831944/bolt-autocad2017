// SuxingquDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCad.h"
#include "SuxingquDialog.h"
#include "afxdialogex.h"
#include "ProjectBuilder.h"
#include "DataChecker.h"
#include "DialogManager.h"


// CSuxingquDialog 对话框

IMPLEMENT_DYNAMIC(CSuxingquDialog, CDialogEx)

CSuxingquDialog::CSuxingquDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SUXINGQU_METHOD_DIALOG, pParent)
	, mInnerFriction(0)
	, mAvgGravity(0)
	, mBoltAttach(0)
	, mMaiDepth(0)
	, mMeiyanZhongdu(0)
	, mNianPower(0)
	, mShuLength(0)
	, mBoltDesignNumber(0)
	, mBoltDiameter(0)
	, mCableDiameter(0)
	, mCableFreeLength(0)
	, mCableAttach(0)
	, mCableBreakPower(0)
{
	// 容重是围岩平均重度
	mAvgGravity = 26;
	mMeiyanZhongdu = 26;
	mMaiDepth = 400;
	mNianPower =3;
	mInnerFriction = 25;
	mShuLength = 350;

	mBoltDiameter = 25;
	mBoltDesignNumber = 50;
	mBoltAttach = 7;
	mCableDiameter = 40;
	mCableBreakPower = 250;
	mCableAttach = 16;
	mCableFreeLength = 3000;
}

CSuxingquDialog::~CSuxingquDialog()
{
}

void CSuxingquDialog::UpdateUI()
{
	CArcProjectBuilder::GetInstance()->BuildMethod();

	CSuxingquMethod * suxingqu = CArcProjectBuilder::GetInstance()->GetSuxingquMethod();
	UpdateData(TRUE);

	mInnerFriction = suxingqu->GetInnerFriction();
	mAvgGravity = suxingqu->GetAvgGravity();
	mMaiDepth = suxingqu->GetMaiDepth();
	mMeiyanZhongdu = suxingqu->GetMeiyanZhongdu();
	mNianPower = suxingqu->GetNianPower();
	mShuLength = suxingqu->GetShuLength();
	mBoltAttach = suxingqu->GetBoltAttach();
	mBoltDesignNumber = suxingqu->GetBoltDesignNumber();
	mBoltDiameter = suxingqu->GetBoltDiameter();
	mCableDiameter = suxingqu->GetCableDiameter();
	mCableFreeLength = suxingqu->GetCableFreeLength();
	mCableAttach = suxingqu->GetCableAttach();
	mCableBreakPower = suxingqu->GetCableBreakPower();

	mConcreteThickness = CArcProjectBuilder::GetInstance()->GetArcTunnel()->GetConcreteThickness();
	mQiThickness = CArcProjectBuilder::GetInstance()->GetArcTunnel()->GetQiThickness();

	UpdateData(FALSE);
}

void CSuxingquDialog::SetThicknessEdit()
{
	if (CArcProjectBuilder::GetInstance()->GetArcTunnel()->GetZhihuWay() > 1)
	{
		CEdtConThickcness.EnableWindow(TRUE);
		CEdtQiThickcness.EnableWindow(TRUE);
	}
	else {
		CEdtConThickcness.EnableWindow(FALSE);
		CEdtQiThickcness.EnableWindow(FALSE);
	}
}

void CSuxingquDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_INNER_FRICTION, mInnerFriction);
	DDX_Text(pDX, IDC_EDIT_LOOSE_AVG_GRIVITY, mAvgGravity);
	DDX_Text(pDX, IDC_EDIT_LOOSE_BOLT_ATTACH, mBoltAttach);
	DDX_Text(pDX, IDC_EDIT_MAI_DEPTH, mMaiDepth);
	DDX_Text(pDX, IDC_EDIT_MEIYAN_ZHONGDU, mMeiyanZhongdu);
	DDX_Text(pDX, IDC_EDIT_NIAN_POWER, mNianPower);
	DDX_Text(pDX, IDC_EDIT_SHU_LENGTH, mShuLength);
	DDX_Text(pDX, IDC_EDIT_LOOSE_BOLT_DESIGN_NUMBER, mBoltDesignNumber);
	DDX_Text(pDX, IDC_EDIT_LOOSE_BOLT_DIAMETER, mBoltDiameter);
	DDX_Text(pDX, IDC_EDIT_LOOSE_CABLE_DIAMETER, mCableDiameter);
	DDX_Text(pDX, IDC_EDIT_LOOSE_CABLE_FREELENGTH, mCableFreeLength);
	DDX_Text(pDX, IDC_EDIT_LOOSE_CABLE_ATTACH, mCableAttach);
	DDX_Text(pDX, IDC_EDIT_LOOSE_CABLE_BREAK_POWER, mCableBreakPower);
	DDX_Text(pDX, IDC_EDIT_CONCRETE_THICKNESS, mConcreteThickness);
	DDX_Text(pDX, IDC_EDIT_QI_THICKNESS, mQiThickness);
	DDX_Control(pDX, IDC_EDIT_CONCRETE_THICKNESS, CEdtConThickcness);
	DDX_Control(pDX, IDC_EDIT_QI_THICKNESS, CEdtQiThickcness);
}

void CSuxingquDialog::CheckThickness()
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

void CSuxingquDialog::SetExpertValue()
{
	CSuxingquMethod * suxingqu = CArcProjectBuilder::GetInstance()->GetSuxingquMethod();

	CBolt * topBolt = CArcProjectBuilder::GetInstance()->GetArcTunnel()->GetTopBolt();
	CBolt  * leftBolt = CArcProjectBuilder::GetInstance()->GetArcTunnel()->GetLeftBolt();
	CCable *cable = CArcProjectBuilder::GetInstance()->GetArcTunnel()->GetCable();
	int tmp = 1000;

	topBolt->setLength(suxingqu->GetTopBoltLength() * tmp);
	topBolt->setDiameter(suxingqu->GetBoltDiameter());
	topBolt->setNumber(suxingqu->GetTopBoltNumber());
	topBolt->setPitch(suxingqu->GetTopSpaceAndPitch() * tmp);
	topBolt->setSpace(suxingqu->GetTopSpaceAndPitch() * tmp);
	topBolt->setALength(suxingqu->GetBoltALength() * tmp);

	leftBolt->setLength(suxingqu->GetBangBoltLength() * tmp);
	leftBolt->setNumber(suxingqu->GetBangBoltNumber());
	leftBolt->setSpace(suxingqu->GetBangSpaceAndPitch() *tmp);
	leftBolt->setPitch(suxingqu->GetBangSpaceAndPitch() *tmp);
	leftBolt->setDiameter(suxingqu->GetBoltDiameter());
	leftBolt->setALength(suxingqu->GetBoltALength() * tmp);

	cable->setDiameter(suxingqu->GetCableDiameter());
	cable->setLength(suxingqu->GetCableLength() * tmp);
	cable->setNumber(suxingqu->GetCableNumber());
	cable->setPitch(suxingqu->GetCablePitch() * tmp);
	cable->setSpace(suxingqu->GetCableSpace() *tmp);
	cable->setALength(suxingqu->GetCableALength() * tmp);
}


BEGIN_MESSAGE_MAP(CSuxingquDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSuxingquDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CSuxingquDialog::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_TUNNEL_DIALOG, &CSuxingquDialog::OnBnClickedButtonTunnelDialog)
END_MESSAGE_MAP()


// CSuxingquDialog 消息处理程序


void CSuxingquDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	std::vector<double> mVecValue = {  mInnerFriction,
	 mAvgGravity,
	 mMaiDepth,
	 mMeiyanZhongdu,
	 mNianPower,
	 mShuLength,
	 mBoltAttach,
	 mBoltDesignNumber,
	 mBoltDiameter,
	 mCableDiameter,
	 mCableFreeLength,
	 mCableAttach,
	 mCableBreakPower
	};

	if (DataChecker::HasZeroOrNegativeValue(mVecValue) == true) {
		MessageBox(_T("参数必须大于0"), _T("警告"), MB_ICONWARNING);
		pmLeagal = false;
	}
	else {
		CSuxingquFactory * factory = new CSuxingquFactory();
		CMethod * method = factory->createMethod();

		// 静态转型
		CSuxingquMethod* tmpMethod = static_cast<CSuxingquMethod *>(method);
		CArcProjectBuilder::GetInstance()->SetMethod(tmpMethod);

		CSuxingquMethod * suxingqu = CArcProjectBuilder::GetInstance()->GetSuxingquMethod();
		CArcTunnel * pArc = CArcProjectBuilder::GetInstance()->GetArcTunnel();

		if (CArcProjectBuilder::GetInstance()->GetTunnelProejct()->GetTunnelType() == 3) {
			suxingqu->SetA(pArc->GetTrapBottomWidth()/1000);
		}
		else
		{
			suxingqu->SetA(pArc->GetWidth()/1000);
		}
		suxingqu->SetH(pArc->GetHeight() / 1000);
		suxingqu->SetInnerFriction(mInnerFriction);
		suxingqu->SetAvgGravity(mAvgGravity);
		suxingqu->SetMaiDepth(mMaiDepth);
		suxingqu->SetMeiyanZhongdu(mMeiyanZhongdu);
		suxingqu->SetNianPower(mNianPower);
		suxingqu->SetShuLength(mShuLength);
		suxingqu->SetBoltAttach(mBoltAttach);
		suxingqu->SetBoltDesignNumber(mBoltDesignNumber);
		suxingqu->SetBoltDiameter(mBoltDiameter);
		suxingqu->SetCableDiameter(mCableDiameter);
		suxingqu->SetCableFreeLength(mCableFreeLength);
		suxingqu->SetCableAttach(mCableAttach);
		suxingqu->SetCableBreakPower(mCableBreakPower);

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


void CSuxingquDialog::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_HIDE);
	DialogManager::GetInstance().ShowMethodChooseDlg();
}


void CSuxingquDialog::OnBnClickedButtonTunnelDialog()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_HIDE);
	DialogManager::GetInstance().ShowMethodChooseDlg();
}


BOOL CSuxingquDialog::OnInitDialog()
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
