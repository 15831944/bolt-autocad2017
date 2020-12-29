// TheoreticalDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCad.h"
#include "ProjectBuilder.h"
#include "TheoreticalDialog.h"
#include "afxdialogex.h"
#include "DataChecker.h"
#include "AverageDialog.h"
#include "MethodChooseDialog.h"
#include "CalMethod.h"
#include "DialogManager.h"

// CTheoreticalDialog 对话框

IMPLEMENT_DYNAMIC(CTheoreticalDialog, CDialogEx)

CTheoreticalDialog::CTheoreticalDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_THEORETICAL_CALCULATION_DIALOG, pParent)
	, mAvgGrivity(0)
	, mCompressive(0)
	, mDepth(0)
	, mInnerFirction(0)
	, mStoneStrongNumber(1.7)
	, mShuLength(0)
	, mBoltDiameter(0)
	, mBoltDesignNumber(0)
	, mBoltAttach(0)
	, mBoltPitch(0)
	, mBoltNumber(0)
	, mBoltExperienceNumber(1.37)
	, mBoltCaiNumber(1.5)
	, mCableDiameter(0)
	, mCableBreakPower(0)
	, mCableAttach(0)
	, mCablePitch(0)
	, mCableNumber(0)
	, mCableFreeLength(0)
	, mCableCaiNumber(2.0)
	, mConcreteThickness(0)
	, mQiThickness(0)
	, mAttach(0)
{

	mAvgGrivity = 7.3;
	mDepth = 2000;
	mCompressive = 14.8;
	mInnerFirction = 35.75;
	mAttach = 4.29;
	mShuLength = 20;
	mStoneStrongNumber = 1.7;

	mBoltDiameter = 16;
	mBoltDesignNumber = 50;
	mBoltAttach = 20;
	mBoltPitch = 700;
	mBoltNumber = 5;
	mBoltExperienceNumber = 1.37;
	mBoltCaiNumber = 1.5;
	mCableDiameter = 17.8;
	mCableBreakPower = 260;
	mCableAttach = 20;
	mCablePitch = 1400;
	mCableNumber = 2;
	mCableFreeLength = 5500;
	mCableCaiNumber = 2.0;
	
}
static UINT WM_MSG_UPDATE_AVERAGE = RegisterWindowMessage(_T("update average"));
 
CTheoreticalDialog::~CTheoreticalDialog()
{
}

void CTheoreticalDialog::UpdateUI()
{
	
	CArcProjectBuilder::GetInstance()->BuildMethod();

	CTheoryCalMethod * theory = CArcProjectBuilder::GetInstance()->GetTheoryMethod();
	UpdateData(TRUE);
	mAvgGrivity = theory->GetAvgGravity();
	mAttach = theory->GetStoneNianPower();
	mCompressive = theory->GetCompressive();
	mDepth = theory->GetMaiDepth();
	mShuLength = theory->GetShuLength();
	mInnerFirction = theory->GetInnerFriction();
	mStoneStrongNumber = theory->GetStoneStrongNumber();
	mBoltDiameter = theory->GetBoltDiameter();
	mBoltDesignNumber = theory->GetBoltDesignNumber();
	mBoltAttach = theory->GetBoltAttach();
	mBoltPitch = theory->GetBoltPitch();
	mBoltNumber = theory->GetBoltNumber();
	mBoltExperienceNumber = theory->GetBoltExperienceNumber();
	mBoltCaiNumber = theory->GetBoltCaiAffectNumber();
	mCableDiameter = theory->GetCableDiameter();
	mCableBreakPower = theory->GetCableBreakPower();
	mCableAttach = theory->GetCableAttach();
	mCablePitch = theory->GetCablePitch();
	mCableNumber = theory->GetCableNumber();
	mCableFreeLength = theory->GetCableFreeLength();
	mCableCaiNumber = theory->GetCableCaiAffectNumber();

	mConcreteThickness = CArcProjectBuilder::GetInstance()->GetArcTunnel()->GetConcreteThickness();
	mQiThickness = CArcProjectBuilder::GetInstance()->GetArcTunnel()->GetQiThickness();

	UpdateData(FALSE);	
}

void CTheoreticalDialog::UpdateThickness()
{
	//UpdateData(TRUE);
	//mConcreteThickness = CArcProjectBuilder::GetInstance()->GetArcTunnel()->GetConcreteThickness();
	//mQiThickness = CArcProjectBuilder::GetInstance()->GetArcTunnel()->GetQiThickness();
	//UpdateData(FALSE);
}

void CTheoreticalDialog::CheckThickness()
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

void CTheoreticalDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_THE_AVG_GRIVITY, mAvgGrivity);
	DDX_Text(pDX, IDC_EDIT_THE_COMPRESSIVE, mCompressive);
	DDX_Text(pDX, IDC_EDIT_THE_DEPTH, mDepth);
	DDX_Text(pDX, IDC_EDIT_THE_FRICTION, mInnerFirction);
	DDX_Text(pDX, IDC_EDIT_THE_STONE_STRONG_NUMBER, mStoneStrongNumber);
	DDV_MinMaxDouble(pDX, mStoneStrongNumber, 1.3, 2.3);
	DDX_Text(pDX, IDC_EDIT_THE_SHU_LENGTH, mShuLength);
	DDX_Text(pDX, IDC_EDIT_THE_BOLT_DIAMETER, mBoltDiameter);
	DDX_Text(pDX, IDC_EDIT_THE_BOLT_DESIGN, mBoltDesignNumber);
	DDX_Text(pDX, IDC_EDIT_THE_BOLT_ATTACH, mBoltAttach);
	DDX_Text(pDX, IDC_EDIT_THE_BOLT_PITCH, mBoltPitch);
	DDX_Text(pDX, IDC_EDIT_THE_BOLT_NUMBER, mBoltNumber);
	DDX_Text(pDX, IDC_EDIT_THE_BOLT_EXPERIENCE_NUMBER, mBoltExperienceNumber);
	DDV_MinMaxDouble(pDX, mBoltExperienceNumber, 1.2, 1.5);
	DDX_Text(pDX, IDC_EDIT_THE_BOLT_CAI_NUMBER, mBoltCaiNumber);
	DDV_MinMaxDouble(pDX, mBoltCaiNumber, 1.3, 2.5);
	DDX_Text(pDX, IDC_EDIT_THE_CABLE_DIAMETER, mCableDiameter);
	DDX_Text(pDX, IDC_EDIT_THE_CABLE_BREAK_POWER, mCableBreakPower);
	DDX_Text(pDX, IDC_EDIT_THE_CABLE_ATTACH, mCableAttach);
	DDX_Text(pDX, IDC_EDIT_THE_CABLE_PITCH, mCablePitch);
	DDX_Text(pDX, IDC_EDIT_THE_CABLE_NUMBER, mCableNumber);
	DDX_Text(pDX, IDC_EDIT_THE_CABLE_FREE_LENGTH, mCableFreeLength);
	DDX_Text(pDX, IDC_EDIT_THE_CABLE_CAI_NUMBER, mCableCaiNumber);
	DDV_MinMaxDouble(pDX, mCableCaiNumber, 1.3, 2.5);
	DDX_Text(pDX, IDC_EDIT_THE_CONCRETE_THICKNESS, mConcreteThickness);
	DDX_Text(pDX, IDC_EDIT_THE_QI_THICKNESS, mQiThickness);
	DDX_Text(pDX, IDC_EDIT_THE_ATTACH, mAttach);
	DDV_MinMaxInt(pDX, mBoltPitch, 700, 1500);
}


BEGIN_MESSAGE_MAP(CTheoreticalDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_AVERAGE, &CTheoreticalDialog::OnBnClickedButtonAverage)
	ON_BN_CLICKED(IDC_BUTTON_BACK_METHOD_CHOOSE_DIALOG, &CTheoreticalDialog::OnBnClickedButtonBackMethodChooseDialog)
	ON_BN_CLICKED(IDOK, &CTheoreticalDialog::OnBnClickedOk)
	ON_REGISTERED_MESSAGE(WM_MSG_UPDATE_AVERAGE,OnMsgReceive)  //为消息添加映射函数
	ON_WM_MOVING()
	ON_BN_CLICKED(IDC_BUTTON_THEORY_SAVEPM, &CTheoreticalDialog::OnBnClickedButtonTheorySavepm)
END_MESSAGE_MAP()


// CTheoreticalDialog 消息处理程序

void CTheoreticalDialog::OnBnClickedButtonAverage()
{
	// TODO: 在此添加控件通知处理程序代码
	CAverageDialog *  dlgAvg = new CAverageDialog();
	dlgAvg->DoModal();
}

void CTheoreticalDialog::OnBnClickedButtonBackMethodChooseDialog()
{
	OnBnClickedButtonTheorySavepm();

	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_HIDE);
	DialogManager::GetInstance().ShowMethodChooseDlg();
}

void SetExpertValue() {
	std::cout << "set expert value\n";
	int tmp = 1000; // m 与 毫米的进制转换
	CTheoryCalMethod * theory = CArcProjectBuilder::GetInstance()->GetTheoryMethod();

	CBolt * topBolt = CArcProjectBuilder::GetInstance()->GetArcTunnel()->GetTopBolt();
	CBolt  * leftBolt = CArcProjectBuilder::GetInstance()->GetArcTunnel()->GetLeftBolt();
	CCable *cable = CArcProjectBuilder::GetInstance()->GetArcTunnel()->GetCable();

	topBolt->setALength(theory->GetTopBoltALength() * tmp);
	topBolt->setLength(theory->GetTopBoltLength() * tmp);
	topBolt->setDiameter(theory->GetBoltDiameter());
	topBolt->setNumber(theory->GetTopBoltNumber());
	topBolt->setPitch(theory->GetBoltPitch());
	leftBolt->setLength(theory->GetBangBoltLength() * tmp);
	leftBolt->setALength(theory->GetTopBoltALength() * tmp);
	leftBolt->setPitch(theory->GetBoltPitch());

	cable->setDiameter(theory->GetCableDiameter());
	cable->setALength(theory->GetCableALength() * tmp);
	cable->setLength(theory->GetCableLength() * tmp);
	cable->setNumber(theory->GetCableNumber()); 
	cable->setPitch(theory->GetCablePitch());

};

void CTheoreticalDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	OnBnClickedButtonTheorySavepm();

	if (pmLeagal) {
		DialogManager::GetInstance().setHasCalculated(true);
		CArcProjectBuilder::GetInstance()->GetArcTunnel()->SetHasLeftBolt(true);
		CArcProjectBuilder::GetInstance()->GetArcTunnel()->SetHasCable(true);

		DialogManager::GetInstance().ShowResultDlg();
		ShowWindow(SW_HIDE);
	}

}


LRESULT CTheoreticalDialog::OnMsgReceive(WPARAM wParam, LPARAM lParam)
{
	//要做的事，其中 wParam 和  lParam 是消息发送过来的参数，用自定义指针强转一下就可以得到传递的值了

	CTheoryCalMethod * theory = CArcProjectBuilder::GetInstance()->GetTheoryMethod();
	
	UpdateData(TRUE);
	mCompressive = theory->GetCompressive();
	mInnerFirction = theory->GetInnerFriction();
	mAttach = theory->GetStoneNianPower();
	std::cout << CArcProjectBuilder::GetInstance()->GetTheoryMethod()->GetCompressive()<< std::endl;
	std::cout << "update avg data" << std::endl;
	UpdateData(FALSE);
	return 0;
}


BOOL CTheoreticalDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	std::cout << "init theory dialog\n";

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

	std::cout << "init theory dialog\n";

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CTheoreticalDialog::OnMoving(UINT fwSide, LPRECT lpRect)
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


void CTheoreticalDialog::OnBnClickedButtonTheorySavepm()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);

	std::vector<double> mVecValue = { mAvgGrivity, mDepth,mShuLength,
		mBoltDiameter,mBoltDesignNumber,mBoltAttach,
		mBoltPitch, mCableDiameter, mCableBreakPower, mCableAttach,
		mCablePitch, mCableFreeLength, mCableCaiNumber,
		mAttach, mCompressive, mInnerFirction
	};

	if (DataChecker::HasZeroOrNegativeValue(mVecValue) == true) {
		
		MessageBox(_T("参数必须大于等于0"));
		pmLeagal = false;
	}
	else {

		//CArcProjectBuilder::GetInstance()->BuildMethod();
		std::cout << "build theory method\n";

		CTheroyMethodFactory * factory = new CTheroyMethodFactory();
		CMethod * method = factory->createMethod();

		std::cout << "theory factory init\n";

		// 静态转型
		CTheoryCalMethod* theory1 = static_cast<CTheoryCalMethod *>(method);

		CArcProjectBuilder::GetInstance()->SetMethod(theory1);

		CTheoryCalMethod * theory = CArcProjectBuilder::GetInstance()->GetTheoryMethod();
		CArcTunnel * pArc = CArcProjectBuilder::GetInstance()->GetArcTunnel();

		theory->SetA(pArc->GetWidth() / 1000);
		theory->SetH(pArc->GetHeight() / 1000);
		theory->SetAvgGravity(mAvgGrivity);
		theory->SetCompressive(mCompressive);
		theory->SetMaiDepth(mDepth/1000);
		theory->SetShuLength(mShuLength);
		theory->SetInnerFriction(mInnerFirction);
		theory->SetStoneStrongNumber(mStoneStrongNumber);
		theory->SetStoneNianPower(mAttach);
		theory->SetBoltDiameter(mBoltDiameter);
		theory->SetBoltDesignNumber(mBoltDesignNumber);
		theory->SetBoltAttach(mBoltAttach);
		theory->SetBoltPitch(mBoltPitch);
		theory->SetBoltNumber(mBoltNumber);
		theory->SetBoltExperienceNumber(mBoltExperienceNumber);
		theory->SetBoltCaiAffectNumber(mBoltCaiNumber);
		theory->SetCableDiameter(mCableDiameter);
		theory->SetCableBreakPower(mCableBreakPower);
		theory->SetCableAttach(mCableAttach);
		theory->SetCablePitch(mCablePitch);
		theory->SetCableNumber(mCableNumber);
		theory->SetCableFreeLength(mCableFreeLength);
		theory->SetCableCaiAffectNumber(mCableCaiNumber);

		
		//theory->SetConcreteThickness(mConcreteThickness);
		//theory->SetQiThickness(mQiThickness);
		CArcProjectBuilder::GetInstance()->GetMethod()->SetConcreteThickness(mConcreteThickness);
		CArcProjectBuilder::GetInstance()->GetMethod()->SetQiThickness(mQiThickness);
		std::cout << "theory method value\n";
		CArcProjectBuilder::GetInstance()->SetCalMethodSaveToInstance(TRUE);

		// 将理论计算得到的值传给专家界面

		SetExpertValue();
		CheckThickness();
		pmLeagal = true;

		//MessageBox(_T("本页参数保存成功"));
		
	}


}
