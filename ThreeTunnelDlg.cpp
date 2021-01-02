// ThreeTunnelDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCad.h"
#include "ThreeTunnelDlg.h"
#include "afxdialogex.h"
#include "CTunnel.h"
#include "MFCUtil.h"
#include "DialogManager.h"
#include "ProjectBuilder.h"


// CThreeTunnelDlg 对话框

IMPLEMENT_DYNAMIC(CThreeTunnelDlg, CDialogEx)

CThreeTunnelDlg::CThreeTunnelDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_THREE_TUNNEL_DIALOG, pParent)
{

}

CThreeTunnelDlg::~CThreeTunnelDlg()
{
}

void CThreeTunnelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO_RECTANGLE, mRecTunnelOption);
	DDX_Control(pDX, IDC_RADIO_ARC, mArcTunnelOption);
	DDX_Control(pDX, IDC_RADIO_TRAPZOID, mTrapTunnelOption);
	DDX_Control(pDX, IDC_EDIT_REC_WIDTH, mEdtRecWidth);
	DDX_Control(pDX, IDC_EDIT_REC_HEIGHT, mEdtRecHeight);
	DDX_Control(pDX, IDC_EDIT_ARC_WIDTH, mEdtArcWidth);
	DDX_Control(pDX, IDC_EDIT_ARC_WALL_HEIGHT, mEdtArcWallHeight);
	DDX_Control(pDX, IDC_EDIT_ARC_HEIGHT, mEdtArcHeight);
	DDX_Control(pDX, IDC_RADIO_NORMAL_TO_ARC, mRadioNormalToArc);
	DDX_Control(pDX, IDC_RADIO_NORMAL_TO_GROUND, mRadioNormalToGround);
	DDX_Control(pDX, IDC_EDIT_TRAP_TOP_WIDTH, mEdtTrapTopWidth);
	DDX_Control(pDX, IDC_EDIT_TRAP_BOTTOM_WIDTH, mEdtTrapBottomWidth);
	DDX_Control(pDX, IDC_EDIT_TRAP_HEIGHT, mEdtTrapHeight);
	DDX_Control(pDX, IDC_EDIT_TRAP_LEFT_ANGLE, mEdtTrapLeftAngle);
	DDX_Control(pDX, IDC_EDIT_TRAP_RIGHT_ANGLE, mEdtTrapRightAngle);
	//DDX_Control(pDX, IDC_EDIT_BOLT_TOP_ANGLE, mEdtBoltTopAngle);
	DDX_Control(pDX, IDC_EDIT_BOLT_LEFT_ANGLE, mEdtBoltLeftAngle);
	DDX_Control(pDX, IDC_EDIT_BOLT_RIGHT_ANGLE, mEdtBoltRightAngle);
	DDX_Control(pDX, IDC_CHECK_BOLT_ANGLE, mCheckBoltAngle);
	DDX_Control(pDX, IDC_STATIC_TUNNEL_TITLE, mTunnelChooseTitle);
	DDX_Control(pDX, IDC_RADIO_ZHIHU_BOLT, mRadioDefaultWay);
	DDX_Control(pDX, IDC_RADIO_ZHIHU_BOLT_CONCRETE_QI, mRadioBoltConcreteWay);
	DDX_Control(pDX, IDC_RADIO_ZHIHU_BOLT_CONCRETE, mRadioJetConcreteWay);
	DDX_Control(pDX, IDC_RADIO_ZHIHU_CONCRETE_QI, mRadioConcreteQiWay);
	DDX_Text(pDX, IDC_EDIT_BOLT_LEFT_ANGLE, mLeftAngle);
	DDX_Text(pDX, IDC_EDIT_BOLT_RIGHT_ANGLE, mRightAngle);
}


BEGIN_MESSAGE_MAP(CThreeTunnelDlg, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK_BOLT_ANGLE, &CThreeTunnelDlg::OnBnClickedCheckBoltAngle)
	ON_BN_CLICKED(IDC_RADIO_RECTANGLE, &CThreeTunnelDlg::OnBnClickedRadioRectangle)
	ON_BN_CLICKED(IDC_RADIO_ARC, &CThreeTunnelDlg::OnBnClickedRadioArc)
	ON_BN_CLICKED(IDC_RADIO_TRAPZOID, &CThreeTunnelDlg::OnBnClickedRadioTrapzoid)
	ON_BN_CLICKED(ID_CHOOSE_CANCEL, &CThreeTunnelDlg::OnBnClickedChooseCancel)
	ON_BN_CLICKED(ID_CHOOSE_OK, &CThreeTunnelDlg::OnBnClickedChooseOk)
	ON_BN_CLICKED(IDC_BUTTON_PROJECT_DIALOG, &CThreeTunnelDlg::OnBnClickedButtonProjectDialog)
END_MESSAGE_MAP()


// CThreeTunnelDlg 消息处理程序
void CThreeTunnelDlg::InitButtonEdtArray() {
	mRectEdtArray.push_back(&mEdtRecWidth);
	mRectEdtArray.push_back(&mEdtRecHeight);
	mArcEdtArray.push_back(&mEdtArcWidth);
	mArcEdtArray.push_back(&mEdtArcWallHeight);
	mArcEdtArray.push_back(&mEdtArcHeight);
	mArcButtonArray.push_back(&mRadioNormalToArc);
	mArcButtonArray.push_back(&mRadioNormalToGround);
	mTrapEdtArray.push_back(&mEdtTrapHeight);
	mTrapEdtArray.push_back(&mEdtTrapBottomWidth);
	mTrapEdtArray.push_back(&mEdtTrapTopWidth);
	mTrapEdtArray.push_back(&mEdtTrapLeftAngle);
	mTrapEdtArray.push_back(&mEdtTrapRightAngle);

	//mAngleEdtArray.push_back(&mEdtBoltTopAngle);
	mAngleEdtArray.push_back(&mEdtBoltLeftAngle);
	mAngleEdtArray.push_back(&mEdtBoltRightAngle);

}

// 修改选中巷道的值
void CThreeTunnelDlg::setOptionDisabled()
{

	// auto &可以对容器中的元素进行读写 
	for (auto & it : mRectEdtArray)
	{
		it->EnableWindow((mRecTunnelOption.GetCheck() == TRUE) ? true : false);
	}

	for (auto & it : mArcEdtArray) {
		it->EnableWindow((mArcTunnelOption.GetCheck() == TRUE) ? true : false);

	}
	for (auto & it : mArcButtonArray) {
		it->EnableWindow((mArcTunnelOption.GetCheck() == TRUE) ? true : false);
	}
	for (auto * it : mTrapEdtArray)
	{
		it->EnableWindow((mTrapTunnelOption.GetCheck() == TRUE) ? true : false);
	}

}

void CThreeTunnelDlg::SetZhihuWay(int flag) {
	switch (flag)
	{
	case 1:
		mRadioDefaultWay.SetCheck(TRUE);
		mRadioBoltConcreteWay.SetCheck(FALSE);
		mRadioJetConcreteWay.SetCheck(FALSE);
		mRadioConcreteQiWay.SetCheck(FALSE);
		break;
	case 2:
		mRadioDefaultWay.SetCheck(FALSE);
		mRadioBoltConcreteWay.SetCheck(TRUE);
		mRadioJetConcreteWay.SetCheck(FALSE);
		mRadioConcreteQiWay.SetCheck(FALSE);
		break;
	case 3:
		mRadioDefaultWay.SetCheck(FALSE);
		mRadioBoltConcreteWay.SetCheck(FALSE);
		mRadioJetConcreteWay.SetCheck(TRUE);
		mRadioConcreteQiWay.SetCheck(FALSE);
		break;
	case 4:
		mRadioDefaultWay.SetCheck(FALSE);
		mRadioBoltConcreteWay.SetCheck(FALSE);
		mRadioJetConcreteWay.SetCheck(FALSE);
		mRadioConcreteQiWay.SetCheck(TRUE);
		break;
	default:
		break;
	}
}

int CThreeTunnelDlg::GetZhihuWayBtn() {
	if (mRadioDefaultWay.GetCheck() == TRUE)
	{
		return 1;
	}
	if (mRadioBoltConcreteWay.GetCheck() == TRUE)
	{
		return 2;
	}
	if (mRadioJetConcreteWay.GetCheck() == TRUE) {
		return 3;
	}
	if (mRadioConcreteQiWay.GetCheck() == TRUE) {
		return 4;
	}
	return 0;
}

void CThreeTunnelDlg::UpdateUI() {
	UpdateData(TRUE);

	CArcTunnel * pArc = CArcProjectBuilder::GetInstance()->GetArcTunnel();

	SetZhihuWay(pArc->GetZhihuWay());

	//设置拱形巷道的参数
	mEdtArcWidth.SetWindowText(MFCUtil::dtostr(pArc->GetWidth()));
	mEdtArcWallHeight.SetWindowText(MFCUtil::dtostr(pArc->GetWallHeight()));
	mEdtArcHeight.SetWindowText(MFCUtil::dtostr(pArc->GetArcHeight()));
	if (pArc->GetNormalToArc() == true)
	{
		mRadioNormalToArc.SetCheck(TRUE);
	}
	else {
		mRadioNormalToGround.SetCheck(TRUE);
	}

	mCheckBoltAngle.SetCheck(pArc->GetRevertAngle() ? TRUE : FALSE);
	OnBnClickedCheckBoltAngle();
	mLeftAngle = pArc->GetLeftAngle();
	mRightAngle = pArc->GetRightAngle();
	UpdateData(FALSE);
}

void CThreeTunnelDlg::OnBnClickedCheckBoltAngle()
{
	// TODO: 在此添加控件通知处理程序代码
	for (auto & it : mAngleEdtArray) {
		it->EnableWindow((mCheckBoltAngle.GetCheck() == TRUE) ? true : false);
	}
}


BOOL CThreeTunnelDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitButtonEdtArray();
	// 设置窗口居中显示
	CRect dlg;
	GetWindowRect(dlg);
	ScreenToClient(dlg);
	SetWindowPos(0, (GetSystemMetrics(SM_CXSCREEN) / 2) - (dlg.Width() / 2),
		(GetSystemMetrics(SM_CYSCREEN) / 2) - (dlg.Height() / 2), dlg.Width(), dlg.Height(),
		SW_SHOW);

	HICON hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_FOLDER));
	SetIcon(hIcon, FALSE);

	mRadioDefaultWay.SetCheck(TRUE);
	mArcTunnelOption.SetCheck(TRUE);
	setOptionDisabled();
	mEdtBoltLeftAngle.SetWindowText(_T("90"));
	mEdtBoltRightAngle.SetWindowText(_T("90"));
	mRadioNormalToArc.SetCheck(TRUE);
	mTunnelChooseTitle.SetFont(MFCUtil::GetTitleFont());

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CThreeTunnelDlg::OnBnClickedRadioRectangle()
{
	// TODO: 在此添加控件通知处理程序代码
	setOptionDisabled();
}


void CThreeTunnelDlg::OnBnClickedRadioArc()
{
	// TODO: 在此添加控件通知处理程序代码
	setOptionDisabled();
}


void CThreeTunnelDlg::OnBnClickedRadioTrapzoid()
{
	// TODO: 在此添加控件通知处理程序代码
	setOptionDisabled();
}


void CThreeTunnelDlg::OnBnClickedChooseCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_HIDE);
}


void CThreeTunnelDlg::OnBnClickedChooseOk()
{
	// TODO: 在此添加控件通知处理程序代码

	if (GetCheckedRadioButton(mRadioDefaultWay.GetDlgCtrlID(),
		mRadioConcreteQiWay.GetDlgCtrlID()) == 0)
	{
		MessageBox(_T("请选择一种支护方式"), _T("警告"), MB_ICONWARNING | MB_OK);
	}

	else {
		UpdateData(TRUE);

		if (mLeftAngle > 90 || mLeftAngle < 0 || mRightAngle > 90
			|| mRightAngle < 0) {
			MessageBox(_T("与帮的夹角应介于于0和90之间"), _T("警告"), MB_ICONWARNING | MB_OK);
		}
		else {
			TunnelSavepm();
			SuccessToMethodChooseDlg();
		}
		
	}
}

void CThreeTunnelDlg::SuccessToMethodChooseDlg() {

	ShowWindow(SW_HIDE);
	DialogManager::GetInstance().ShowMethodChooseDlg();

}


void CThreeTunnelDlg::ArcTunnelSavepm()
{
	// TODO: 在此添加控件通知处理程序代码
	// 新建，将arc信息保存到当前的 Project 单例中

	if (MFCUtil::VectorHasEmpty(mArcEdtArray) == true) {
		MessageBox(_T("拱形数据不能含有空值"), _T("警告"), MB_ICONWARNING | MB_OK);
	}
	else {
		CString strWidth;
		CString strWallHeight;
		CString strArcHeight;

		mEdtArcWidth.GetWindowText(strWidth);
		mEdtArcWallHeight.GetWindowText(strWallHeight);
		mEdtArcHeight.GetWindowText(strArcHeight);

		CArcProjectBuilder::GetInstance()->GetArcTunnel()->SetWidth(_ttof(strWidth));
		CArcProjectBuilder::GetInstance()->GetArcTunnel()->SetWallHeight(_ttof(strWallHeight));
		CArcProjectBuilder::GetInstance()->GetArcTunnel()->SetArcHeight(_ttof(strArcHeight));
		CArcProjectBuilder::GetInstance()->GetArcTunnel()->SetNormalToArc(
			mRadioNormalToArc.GetCheck() == TRUE ? true : false
		);

		// 设置巷道支护方式

		CArcProjectBuilder::GetInstance()->GetArcTunnel()
			->SetZhihuWay(GetZhihuWayBtn());
		std::cout << "zhihu way :" << GetZhihuWayBtn() << std::endl;
		CArcProjectBuilder::GetInstance()->GetArcTunnel()
			->SetHasRevertAngle((mCheckBoltAngle.GetCheck() == TRUE) ? true : false);

		CString strLeftAngle, strTopAngle(_T("90")), strRightAngle;

		mEdtBoltLeftAngle.GetWindowText(strLeftAngle);
		mEdtBoltRightAngle.GetWindowText(strRightAngle);


		CArcProjectBuilder::GetInstance()->GetArcTunnel()->SetTopAngle(_ttof(strTopAngle));
		CArcProjectBuilder::GetInstance()->GetArcTunnel()->SetLeftAngle(_ttof(strLeftAngle));
		CArcProjectBuilder::GetInstance()->GetArcTunnel()->SetRightAngle(_ttof(strRightAngle));

		std::cout << "instance left angle: " << CArcProjectBuilder::GetInstance()->GetArcTunnel()->GetLeftAngle() << std::endl;
		CArcProjectBuilder::GetInstance()->SetTunnelSaveToInstance(TRUE);

		//MessageBox(_T("本页参数保存成功"));
	}
}


void CThreeTunnelDlg::TunnelSavepm()
{
	if (mRecTunnelOption.GetCheck() == TRUE) {
		RecTunnelSavepm();
	}
	if (mArcTunnelOption.GetCheck() == TRUE) {
		ArcTunnelSavepm();
	}
	if (mTrapTunnelOption.GetCheck() == TRUE) {
		TrapTunelSavepm();
	}
}

void CThreeTunnelDlg::RecTunnelSavepm()
{

}

void CThreeTunnelDlg::TrapTunelSavepm()
{
}

void CThreeTunnelDlg::OnBnClickedButtonProjectDialog()
{
	// TODO: 在此添加控件通知处理程序代码
	DialogManager::GetInstance().HideTunnelChooseDlg();

	DialogManager::GetInstance().ShowProjectDialog();

}
