// ExperienceDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCad.h"
#include "ExperienceDialog.h"
#include "MethodChooseDialog.h"
#include "afxdialogex.h"
#include "ProjectBuilder.h"
#include "DataChecker.h"
#include "DialogManager.h"

// CExperienceDialog 对话框

IMPLEMENT_DYNAMIC(CExperienceDialog, CDialogEx)

CExperienceDialog::CExperienceDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PROGRAM_EXPERIENCE_DIALOG, pParent)
	, mBoltLength(0)
	, mBoltSpace(0)
	, mBoltPitch(0)
	, mBoltDiameter(0)
	, mBoltDeisgnNumber(0)
	, mBoltAttach(0)
	, mBoltShuLegnth(0)
	, mCableLength(0)
	, mCableDiameter(0)
	, mCableSpace(0)
	, mCablePitch(0)
	, mCableNumber(0)
	, mCableAttach(0)
	, mCableShuLength(0)
	, mConcreteThickness(0)
	, mQiThickness(0)
{

}

CExperienceDialog::~CExperienceDialog()
{
}

void CExperienceDialog::UpdateUI()
{
	CArcProjectBuilder::GetInstance()->BuildMethod();

	CProExpMethod * exp = CArcProjectBuilder::GetInstance()->GetExpMethod();

	UpdateData(TRUE);

	mBoltDiameter = exp->GetBoltDiameter();
	mBoltDeisgnNumber = exp->GetBoltDesignNumber();
	mBoltAttach = exp->GetBoltAttach();
	mBoltPitch = exp->GetBoltPitch();
	mBoltSpace = exp->GetBoltSpace();
	mBoltShuLegnth = exp->GetBoltShuLength();
	mBoltLength = exp->GetBoltLength();

	mCableDiameter = exp->GetCableDiameter();
	mCableLength = exp->GetCableLength();
	mCableAttach = exp->GetCableAttach();
	mCablePitch = exp->GetCablePitch();
	mCableNumber = exp->GetCableNumber();
	mCableSpace = exp->GetCableSpace();
	mCableShuLength = exp->GetCableShuLength();

	mConcreteThickness = CArcProjectBuilder::GetInstance()->GetMethod()->GetConcreteThickness();
	mQiThickness = CArcProjectBuilder::GetInstance()->GetMethod()->GetQiThickness();

	UpdateData(FALSE);
}



void CExperienceDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_EXP_BOLT_LENGTH, mBoltLength);
	DDX_Text(pDX, IDC_EDIT_EXP_BOLT_SPACE, mBoltSpace);
	DDX_Text(pDX, IDC_EDIT_EXP_BOLT_PITCH, mBoltPitch);
	DDX_Text(pDX, IDC_EDIT_EXP_BOLT_DIAMETER, mBoltDiameter);
	DDX_Text(pDX, IDC_EDIT_EXP_BOLT_DESIGN_NUMBER, mBoltDeisgnNumber);
	DDX_Text(pDX, IDC_EDIT_EXP_BOLT_ATTACH, mBoltAttach);
	DDX_Text(pDX, IDC_EDIT_EXP_BOLT_SHU_LENGTH, mBoltShuLegnth);
	DDX_Text(pDX, IDC_EDIT_EXP_CABLE_LENGTH, mCableLength);
	DDX_Text(pDX, IDC_EDIT_EXP_CABLE_DIAMETER, mCableDiameter);
	DDX_Text(pDX, IDC_EDIT_EXP_CABLE_SPACE, mCableSpace);
	DDX_Text(pDX, IDC_EDIT_EXP_CABLE_PITCH, mCablePitch);
	DDX_Text(pDX, IDC_EDIT_EXP_CABLE_NUMBER, mCableNumber);
	DDX_Text(pDX, IDC_EDIT_EXP_CABLE_ATTACH, mCableAttach);
	DDX_Text(pDX, IDC_EDIT_EXP_CABLE_SHU_LENGTH, mCableShuLength);
	DDX_Text(pDX, IDC_EDIT45, mConcreteThickness);
	DDX_Text(pDX, IDC_EDIT43, mQiThickness);
}


BEGIN_MESSAGE_MAP(CExperienceDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_BACK_METHOD_CHOOSE_DIALOG, &CExperienceDialog::OnBnClickedButtonBackMethodChooseDialog)
	ON_BN_CLICKED(IDOK, &CExperienceDialog::OnBnClickedOk)
	ON_WM_MOVING()
	ON_BN_CLICKED(IDC_BUTTON_EXP_SAVEPM, &CExperienceDialog::OnBnClickedButtonExpSavepm)
END_MESSAGE_MAP()


// CExperienceDialog 消息处理程序


void CExperienceDialog::OnBnClickedButtonBackMethodChooseDialog()
{
	// TODO: 在此添加控件通知处理程序代码

	OnBnClickedButtonExpSavepm();

	ShowWindow(SW_HIDE);

	DialogManager::GetInstance().ShowMethodChooseDlg();
}

void SetProExpertValue() {

	CProExpMethod * exp = CArcProjectBuilder::GetInstance()->GetExpMethod();

	CBolt * topBolt = CArcProjectBuilder::GetInstance()->GetArcTunnel()->GetTopBolt();
	CBolt  * leftBolt = CArcProjectBuilder::GetInstance()->GetArcTunnel()->GetLeftBolt();
	CCable *cable = CArcProjectBuilder::GetInstance()->GetArcTunnel()->GetCable();

	topBolt->setLength(exp->GetTopBoltLength() );
	topBolt->setDiameter(exp->GetBoltDiameter());
	topBolt->setPitch(exp->GetBoltPitch());
	topBolt->setSpace(exp->GetBoltSpace());
	
	cable->setDiameter(exp->GetCableDiameter());
	cable->setLength(exp->GetCableLength());
	cable->setNumber(exp->GetCableNumber());
	cable->setPitch(exp->GetCablePitch());
	cable->setSpace(exp->GetCableSpace());

};

void CExperienceDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	OnBnClickedButtonExpSavepm();

	if (pmLeagal == true) {
		ShowWindow(SW_HIDE);
		DialogManager::GetInstance().ShowResultDlg();
	}

}


BOOL CExperienceDialog::OnInitDialog()
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

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CExperienceDialog::OnMoving(UINT fwSide, LPRECT lpRect)
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

void CExperienceDialog::CheckThickness() {
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

void CExperienceDialog::OnBnClickedButtonExpSavepm()
{
	// TODO: 在此添加控件通知处理程序代码


	UpdateData(TRUE);


	std::vector<double> mVecValue = {
		mBoltLength, mBoltShuLegnth, mBoltSpace, mBoltPitch,
		mBoltDiameter, mBoltDeisgnNumber, mBoltAttach, mBoltShuLegnth, 
		mCableLength, mCableDiameter, mCableSpace, mCablePitch, mCableAttach,
		mCableShuLength
	};

	if (DataChecker::HasZeroOrNegativeValue(mVecValue) == true) {
		MessageBox(_T("参数不能含有0或负数"));
	}
	else {

		CProExpMethodFactory * factory = new CProExpMethodFactory();
		CMethod * method = factory->createMethod();

		// 静态转型
		CProExpMethod * project = static_cast<CProExpMethod *>(method);
		CArcProjectBuilder::GetInstance()->SetMethod(project);
		CProExpMethod * exp = CArcProjectBuilder::GetInstance()->GetExpMethod();
		CArcTunnel * pArc = CArcProjectBuilder::GetInstance()->GetArcTunnel();

		int tmp = 1000;

		exp->SetA(pArc->GetWidth() / tmp);
		exp->SetH(pArc->GetHeight() / tmp);
		exp->SetBoltLength(mBoltLength);
		exp->SetBoltSpace(mBoltSpace);
		exp->SetBoltPitch(mBoltPitch);
		exp->SetBoltDesignNumber(mBoltDeisgnNumber);
		exp->SetBoltAttach(mBoltAttach);
		exp->SetBoltShuLength(mBoltShuLegnth);
		exp->SetBoltDiameter(mBoltDiameter);
		exp->SetCableLength(mCableLength);
		exp->SetCableDiameter(mCableDiameter);
		exp->SetCableAttach(mCableAttach);
		exp->SetCablePitch(mCablePitch);
		exp->SetCableSpace(mCableSpace);
		exp->SetCableShuLength(mCableShuLength);
		exp->SetCableNumber(mCableNumber);

		CArcProjectBuilder::GetInstance()->GetMethod()->SetConcreteThickness(mConcreteThickness);
		CArcProjectBuilder::GetInstance()->GetMethod()->SetQiThickness(mQiThickness);

		CArcProjectBuilder::GetInstance()->SetCalMethodSaveToInstance(TRUE);
		CArcProjectBuilder::GetInstance()->GetArcTunnel()->SetHasCable(TRUE);
		SetProExpertValue();
		// 将界面中的厚度值赋值给Arc巷道
		CheckThickness();
		DialogManager::GetInstance().setHasCalculated(true);
		pmLeagal = true;
		MessageBox(_T("本页参数保存成功"));

	};



}
