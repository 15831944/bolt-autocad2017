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
	
	SetMeasureButton(loose->GetMeasureWay());
	mEdtAvgGrivity.SetWindowText(MFCUtil::dtostr(loose->GetAvgGravity()));
	 mEdtDepth.SetWindowText(MFCUtil::dtostr(loose->GetMaiDepth()));
	 mEdtFriction.SetWindowText(MFCUtil::dtostr(loose->GetInnerFriction()));
	 mMeiyanZhongdu.SetWindowText(MFCUtil::dtostr(loose->GetMeiyanZhongdu()));
	 mEdtNianPower.SetWindowText(MFCUtil::dtostr(loose->GetNianPower()));
	 mEdtShuLength.SetWindowText(MFCUtil::dtostr(loose->GetShuLength()));
	 mEdtBoltDiameter.SetWindowText(MFCUtil::dtostr(loose->GetBoltDiameter()));
	 mEdtBoltDesignNumber.SetWindowText(MFCUtil::dtostr(loose->GetBoltDesignNumber()));
	 mEdtBoltAttach.SetWindowText(MFCUtil::dtostr(loose->GetBoltAttach()));
	 mCalbeFreeLength.SetWindowText(MFCUtil::dtostr(loose->GetCableFreeLength()));
	 mEdtCableDiameter.SetWindowText(MFCUtil::dtostr(loose->GetCableDiameter()));
	 mCableBreakPower.SetWindowText(MFCUtil::dtostr(loose->GetCableBreakPower()));
	 mEdtCableAttach.SetWindowText(MFCUtil::dtostr(loose->GetCableAttach()));

	 mConThickness = CArcProjectBuilder::GetInstance()->GetArcTunnel()->GetConcreteThickness();
	 mQiThickness = CArcProjectBuilder::GetInstance()->GetArcTunnel()->GetQiThickness();

	 UpdateData(FALSE);
}

void CLooseRangeDialog::SetMeasureButton(int type) {
	switch (type)
	{
	case 1:
		mRadioLooseRange.SetCheck (TRUE);
		mRadioMaoluo.SetCheck(FALSE);
		mLooseRange = CArcProjectBuilder::GetInstance()->GetLooseMethod()->GetLooseRange();
		break;
	case 2:
		mRadioLooseRange.SetCheck(FALSE);
		mRadioMaoluo.SetCheck(TRUE);
		mPushiNumber = CArcProjectBuilder::GetInstance()->GetLooseMethod()->GetPushiNumber();
		break;
	default:
		mRadioLooseRange.SetCheck(FALSE);
		mRadioMaoluo.SetCheck(FALSE);
		mLooseRange = 0;
		mPushiNumber = 0;
		break;
	}
	OnBnClickedRadioLooseMeasure();
};

void CLooseRangeDialog::SetThicknessEdit()
{
	if (CArcProjectBuilder::GetInstance()->GetArcTunnel()->GetZhihuWay() > 1)
	{
		mEdtConThickness.EnableWindow(TRUE);
		mEdtConThickness.EnableWindow(TRUE);
	}
	else {
		mEdtConThickness.EnableWindow(FALSE);
		mEdtConThickness.EnableWindow(FALSE);
	}
}

void CLooseRangeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_LOOSE_RANGE, mLooseRange);
	DDX_Control(pDX, IDC_EDIT_LOOSE_RANGE, mEdtLooseRange);
	DDX_Text(pDX, IDC_EDIT_LOOSE_STONE_STRONG_NUMBER, mPushiNumber);
	DDX_Control(pDX, IDC_EDIT_LOOSE_STONE_STRONG_NUMBER, mEdtPushiNumber);
	DDX_Control(pDX, IDC_EDIT_LOOSE_AVG_GRIVITY, mEdtAvgGrivity);
	DDX_Control(pDX, IDC_EDIT_LOOSE_DEPTH, mEdtDepth);
	DDX_Control(pDX, IDC_EDIT_LOOSE_FRICTION, mEdtFriction);
	DDX_Control(pDX, IDC_EDIT_LOOSE_SHU_LENGTH, mEdtShuLength);
	DDX_Control(pDX, IDC_EDIT_LOOSE_BOLT_DIAMETER, mEdtBoltDiameter);
	DDX_Control(pDX, IDC_EDIT_LOOSE_BOLT_DESIGN_NUMBER, mEdtBoltDesignNumber);
	DDX_Control(pDX, IDC_EDIT_LOOSE_BOLT_ATTACH, mEdtBoltAttach);
	DDX_Control(pDX, IDC_EDIT_LOOSE_CABLE_FREELENGTH, mCalbeFreeLength);
	DDX_Control(pDX, IDC_EDIT_LOOSE_CABLE_DIAMETER, mEdtCableDiameter);
	DDX_Control(pDX, IDC_EDIT_LOOSE_CABLE_BREAK_POWER, mCableBreakPower);
	DDX_Control(pDX, IDC_EDIT_LOOSE_CABLE_ATTACH, mEdtCableAttach);
	DDX_Control(pDX, IDC_RADIO_LOOSE_MEASURE, mRadioLooseRange);
	DDX_Control(pDX, IDC_EDIT_CONCRETE_THICKNESS, mEdtConThickness);
	DDX_Control(pDX, IDC_EDIT_QI_THICKNESS, mEdtQiThickness);
	DDX_Text(pDX, IDC_EDIT_CONCRETE_THICKNESS, mConThickness);
	DDX_Text(pDX, IDC_EDIT_QI_THICKNESS, mQiThickness);
	DDX_Control(pDX, IDC_RADIO_MAOLUO_MEASURE, mRadioMaoluo);
	DDX_Control(pDX, IDC_EDIT_MEIYAN_ZHONGDU, mMeiyanZhongdu);
	DDX_Control(pDX, IDC_EDIT_ATTACH, mEdtNianPower);
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

	if (GetMeasureWay() == 0) {
		MessageBox(_T("请选择一种计算方法"), _T("警告"), MB_ICONWARNING);
	}
	else {
		std::vector<double> mVecValue = {
			MFCUtil::GetDoubleEdtValue(&mEdtAvgGrivity),
			MFCUtil::GetDoubleEdtValue(&mMeiyanZhongdu),
			MFCUtil::GetDoubleEdtValue(&mEdtDepth),
			MFCUtil::GetDoubleEdtValue(&mEdtFriction),
			MFCUtil::GetDoubleEdtValue(&mEdtNianPower),
			MFCUtil::GetDoubleEdtValue(&mEdtShuLength),
			MFCUtil::GetDoubleEdtValue(&mEdtBoltDiameter),
			MFCUtil::GetDoubleEdtValue(&mEdtBoltDesignNumber),
			MFCUtil::GetDoubleEdtValue(&mEdtBoltAttach),
			MFCUtil::GetDoubleEdtValue(&mCalbeFreeLength),
			MFCUtil::GetDoubleEdtValue(&mEdtCableDiameter),
			MFCUtil::GetDoubleEdtValue(&mCableBreakPower),
			MFCUtil::GetDoubleEdtValue(&mEdtCableAttach)
		};

		if (DataChecker::HasZeroOrNegativeValue(mVecValue) == true) {
			MessageBox(_T("参数必须大于0"), _T("警告"), MB_ICONWARNING);
			pmLeagal = false;
		}
		else {
			CLooseRangeMethodFactory * factory = new CLooseRangeMethodFactory();
			CMethod * method = factory->createMethod();

			// 静态转型
			CLooseRangeMethod* tmpMethod = static_cast<CLooseRangeMethod *>(method);
			CArcProjectBuilder::GetInstance()->SetMethod(tmpMethod);

			CLooseRangeMethod * loose = CArcProjectBuilder::GetInstance()->GetLooseMethod();
			CArcTunnel * pArc = CArcProjectBuilder::GetInstance()->GetArcTunnel();

			if (CArcProjectBuilder::GetInstance()->GetTunnelProejct()->GetTunnelType() == 3) {
				loose->SetA(pArc->GetTrapBottomWidth() / 1000);
			}
			else
			{
				loose->SetA(pArc->GetWidth() / 1000);
			}
			loose->SetH(pArc->GetHeight() / 1000);
			int measureway = GetMeasureWay();
			loose->SetMeasureWay(measureway);
			if (measureway == 1) {
				loose->SetLooseRange(mLooseRange);
				loose->SetPushiNumber(0);
			}
			else if(measureway == 2) {
				loose->SetLooseRange(0);
				loose->SetPushiNumber(mPushiNumber);
			}
			
			loose->SetInnerFriction(MFCUtil::GetDoubleEdtValue(&mEdtFriction));
			loose->SetAvgGravity(MFCUtil::GetDoubleEdtValue(&mEdtAvgGrivity));
			loose->SetMaiDepth(MFCUtil::GetDoubleEdtValue(&mEdtDepth));
			loose->SetMeiyanZhongdu(MFCUtil::GetDoubleEdtValue(&mMeiyanZhongdu));
			loose->SetNianPower(MFCUtil::GetDoubleEdtValue(&mEdtNianPower));
			loose->SetShuLength(MFCUtil::GetDoubleEdtValue(&mEdtShuLength));
			loose->SetBoltAttach(MFCUtil::GetDoubleEdtValue(&mEdtBoltAttach));
			loose->SetBoltDesignNumber(MFCUtil::GetDoubleEdtValue(&mEdtBoltDesignNumber));
			loose->SetBoltDiameter(MFCUtil::GetDoubleEdtValue(&mEdtBoltDiameter));
			loose->SetCableDiameter(MFCUtil::GetDoubleEdtValue(&mEdtCableDiameter));
			loose->SetCableFreeLength(MFCUtil::GetDoubleEdtValue(&mCalbeFreeLength));
			loose->SetCableAttach(MFCUtil::GetDoubleEdtValue(&mEdtCableAttach));
			loose->SetCableBreakPower(MFCUtil::GetDoubleEdtValue(&mCableBreakPower));

			CArcProjectBuilder::GetInstance()->GetMethod()->SetConcreteThickness(MFCUtil::GetDoubleEdtValue(&mEdtConThickness));
			CArcProjectBuilder::GetInstance()->GetMethod()->SetQiThickness(MFCUtil::GetDoubleEdtValue(&mEdtQiThickness));
			CArcProjectBuilder::GetInstance()->SetCalMethodSaveToInstance(TRUE);
			SetExpertValue();
			CheckThickness();
			
			pmLeagal = true;
		}

		if (mRadioLooseRange.GetCheck() && mLooseRange == 0) {
			MessageBox(_T("松动范围数值输入错误"), _T("警告"), MB_ICONWARNING);
			pmLeagal = false;
		}
		if (mRadioMaoluo.GetCheck() && mPushiNumber == 0) {
			MessageBox(_T("普氏系数数值输入错误"), _T("警告"), MB_ICONWARNING);
			pmLeagal = false;
		}

		if (pmLeagal) {

			DialogManager::GetInstance().setHasCalculated(true);
			CArcProjectBuilder::GetInstance()->GetArcTunnel()->SetHasLeftBolt(true);
			CArcProjectBuilder::GetInstance()->GetArcTunnel()->SetHasCable(true);

			DialogManager::GetInstance().ShowResultDlg();
			ShowWindow(SW_HIDE);
		}
	}
}

void CLooseRangeDialog::OnBnClickedButtonTunnelDialog()
{
	// TODO: 在此添加控件通知处理程序代码

	ShowWindow(SW_HIDE);
	DialogManager::GetInstance().ShowMethodChooseDlg();
}


void CLooseRangeDialog::InitEdtVector()
{
	mVectorEdt.push_back(&mEdtAvgGrivity);
	mVectorEdt.push_back(&mEdtNianPower);
	mVectorEdt.push_back(&mEdtDepth);
	mVectorEdt.push_back(&mEdtFriction);
	mVectorEdt.push_back(&mMeiyanZhongdu);
	mVectorEdt.push_back(&mEdtShuLength);
	mVectorEdt.push_back(&mEdtBoltDiameter);
	mVectorEdt.push_back(&mEdtBoltDesignNumber);
	mVectorEdt.push_back(&mEdtBoltAttach);
	mVectorEdt.push_back(&mCalbeFreeLength);
	mVectorEdt.push_back(&mEdtCableDiameter);
	mVectorEdt.push_back(&mCableBreakPower);
	mVectorEdt.push_back(&mEdtCableAttach);
}

void CLooseRangeDialog::CheckThickness()
{
	CArcTunnel * pArc = CArcProjectBuilder::GetInstance()->GetArcTunnel();
	switch (pArc->GetZhihuWay())
	{
	case 1:
		pArc->SetConcreteThickness(0);
		pArc->SetQiThickness(0);
		break;
	case 2:
		pArc->SetConcreteThickness(MFCUtil::GetDoubleEdtValue(&mEdtConThickness));
		pArc->SetQiThickness(MFCUtil::GetDoubleEdtValue(&mEdtQiThickness));
		break;
	case 3:
		pArc->SetConcreteThickness(MFCUtil::GetDoubleEdtValue(&mEdtConThickness));
		pArc->SetQiThickness(0);
		break;
	case 4:
		pArc->SetConcreteThickness(MFCUtil::GetDoubleEdtValue(&mEdtConThickness));
		pArc->SetQiThickness(MFCUtil::GetDoubleEdtValue(&mEdtQiThickness));
		break;
	default:
		break;
	}
}

void CLooseRangeDialog::SetExpertValue()
{
	CLooseRangeMethod * suxingqu = CArcProjectBuilder::GetInstance()->GetLooseMethod();

	CBolt * topBolt = CArcProjectBuilder::GetInstance()->GetArcTunnel()->GetTopBolt();
	CBolt  * leftBolt = CArcProjectBuilder::GetInstance()->GetArcTunnel()->GetLeftBolt();
	CCable *cable = CArcProjectBuilder::GetInstance()->GetArcTunnel()->GetCable();
	int tmp = 1000;

	topBolt->setLength(suxingqu->GetTopBoltLength() * tmp);
	topBolt->setDiameter(suxingqu->GetBoltDiameter());
	topBolt->setNumber(suxingqu->GetTopBoltNumber());
	topBolt->setPitch(suxingqu->GetTopBoltSpacePitch() * tmp);
	topBolt->setSpace(suxingqu->GetTopBoltSpacePitch() * tmp);
	topBolt->setALength(suxingqu->GetTopBoltAlength() * tmp);

	leftBolt->setLength(suxingqu->GetTopBoltLength() * tmp);
	leftBolt->setNumber(suxingqu->GetBangBoltNumber());
	leftBolt->setSpace(suxingqu->GetTopBoltSpacePitch() *tmp);
	leftBolt->setPitch(suxingqu->GetTopBoltSpacePitch() *tmp);
	leftBolt->setDiameter(suxingqu->GetBoltDiameter());
	leftBolt->setALength(suxingqu->GetTopBoltAlength() * tmp);

	cable->setDiameter(suxingqu->GetCableDiameter());
	cable->setLength(suxingqu->GetCableLength() * tmp);
	cable->setNumber(suxingqu->GetCableNumber());
	cable->setPitch(suxingqu->GetCableSpace() * tmp);
	cable->setSpace(suxingqu->GetCableSpace() *tmp);
	cable->setALength(suxingqu->GetCableAlength() * tmp);
}

int CLooseRangeDialog::GetMeasureWay()
{
	if (mRadioLooseRange.GetCheck()) return 1;
	if (mRadioMaoluo.GetCheck()) return 2;
	return 0;
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
	if (mRadioLooseRange.GetCheck() == TRUE) {
		mEdtLooseRange.EnableWindow(TRUE);
		mEdtPushiNumber.EnableWindow(FALSE);
	}
	if (mRadioMaoluo.GetCheck() == TRUE) {
		mEdtLooseRange.EnableWindow(FALSE);
		mEdtPushiNumber.EnableWindow(TRUE);
	}
}


void CLooseRangeDialog::OnBnClickedRadioLooseMeasure()
{
	// TODO: 在此添加控件通知处理程序代码
	if (mRadioLooseRange.GetCheck() == TRUE) {
		mEdtLooseRange.EnableWindow(TRUE);
		mEdtPushiNumber.EnableWindow(FALSE);
	}
	if(mRadioMaoluo.GetCheck() == TRUE) {
		mEdtLooseRange.EnableWindow(FALSE);
		mEdtPushiNumber.EnableWindow(TRUE);
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
