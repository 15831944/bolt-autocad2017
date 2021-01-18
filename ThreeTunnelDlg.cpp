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
#include "ThicknessDialog.h"


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
	ON_EN_CHANGE(IDC_EDIT_TRAP_BOTTOM_WIDTH, &CThreeTunnelDlg::OnEnChangeEditTrapBottomWidth)
	ON_EN_CHANGE(IDC_EDIT_TRAP_LEFT_ANGLE, &CThreeTunnelDlg::OnEnChangeEditTrapLeftAngle)
	ON_EN_CHANGE(IDC_EDIT_TRAP_RIGHT_ANGLE, &CThreeTunnelDlg::OnEnChangeEditTrapRightAngle)
	ON_EN_CHANGE(IDC_EDIT_TRAP_HEIGHT, &CThreeTunnelDlg::OnEnChangeEditTrapHeight)
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
		mRadioDefaultWay.SetCheck(FALSE);
		mRadioBoltConcreteWay.SetCheck(FALSE);
		mRadioJetConcreteWay.SetCheck(FALSE);
		mRadioConcreteQiWay.SetCheck(FALSE);
	}
}

void CThreeTunnelDlg::SetTunnelTypeRadio(int type)
{
	CArcTunnel * pArc = CArcProjectBuilder::GetInstance()->GetArcTunnel();

	switch (type)
	{
	case 1:
		mRecTunnelOption.SetCheck(TRUE);
		mArcTunnelOption.SetCheck(FALSE);
		mTrapTunnelOption.SetCheck(FALSE);

		//设置矩形巷道的参数
		mEdtRecWidth.SetWindowText(MFCUtil::dtostr(pArc->GetWidth()));
		mEdtRecHeight.SetWindowText(MFCUtil::dtostr(pArc->GetWallHeight()));
		break;
	case 2:
		mRecTunnelOption.SetCheck(FALSE);
		mArcTunnelOption.SetCheck(TRUE);
		mTrapTunnelOption.SetCheck(FALSE);

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
		break;
	case 3:
		mRecTunnelOption.SetCheck(FALSE);
		mArcTunnelOption.SetCheck(FALSE);
		mTrapTunnelOption.SetCheck(TRUE);

		mEdtTrapTopWidth.SetWindowText(MFCUtil::dtostr(pArc->GetWidth()));
		mEdtTrapBottomWidth.SetWindowText(MFCUtil::dtostr(pArc->GetTrapBottomWidth()));
		mEdtTrapHeight.SetWindowText(MFCUtil::dtostr(pArc->GetWallHeight()));
		mEdtTrapLeftAngle.SetWindowText(MFCUtil::itostr(pArc->GetTrapLeftAngle()));
		mEdtTrapRightAngle.SetWindowText(MFCUtil::itostr(pArc->GetTrapRightAngle()));
		break;
	case 0:
		mRecTunnelOption.SetCheck(FALSE);
		mArcTunnelOption.SetCheck(FALSE);
		mTrapTunnelOption.SetCheck(FALSE);

		mEdtRecWidth.SetWindowText(_T(""));
		mEdtRecHeight.SetWindowText(_T(""));
		mEdtArcWidth.SetWindowText(_T(""));
		mEdtArcWallHeight.SetWindowText(_T(""));
		mEdtArcHeight.SetWindowText(_T(""));
		mEdtTrapTopWidth.SetWindowText(_T(""));
		mEdtTrapBottomWidth.SetWindowText(_T(""));
		mEdtTrapHeight.SetWindowText(_T(""));
		mEdtTrapLeftAngle.SetWindowText(_T(""));
		mEdtTrapRightAngle.SetWindowText(_T(""));
	default:
		break;
	}
	setOptionDisabled();
}

int CThreeTunnelDlg::GetTunnelOption() {
	if (mRecTunnelOption.GetCheck() == TRUE) {
		return 1;
	}
	if (mArcTunnelOption.GetCheck() == TRUE) {
		return 2;
	}
	if (mTrapTunnelOption.GetCheck() == TRUE) {
		return 3;
	}
	return 0;
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
//	UpdateData(TRUE);

	int mTunnelType = CArcProjectBuilder::GetInstance()->GetTunnelProejct()->GetTunnelType();
	CArcTunnel * pArc = CArcProjectBuilder::GetInstance()->GetArcTunnel();

	SetZhihuWay(pArc->GetZhihuWay());
	std::cout << "tunnel type: " << mTunnelType << std::endl;
	SetTunnelTypeRadio(mTunnelType);

	mCheckBoltAngle.SetCheck(pArc->GetRevertAngle() ? TRUE : FALSE);
	OnBnClickedCheckBoltAngle();
	mLeftAngle = pArc->GetLeftAngle();
	mRightAngle = pArc->GetRightAngle();
	//UpdateData(FALSE);
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
		isPmLeagal = false;
	}
	else{

		UpdateData(TRUE);

		if (mLeftAngle > 90 || mLeftAngle < 0 || mRightAngle > 90
			|| mRightAngle < 0) {
			MessageBox(_T("与帮的夹角应介于于0和90之间"), _T("警告"), MB_ICONWARNING | MB_OK);
			isPmLeagal = false;
		}
		else {
			TunnelSavepm();
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
			
			if(isPmLeagal == true)
				SuccessToMethodChooseDlg();
		}
		
	}
}

void CThreeTunnelDlg::SuccessToMethodChooseDlg() {

	ShowWindow(SW_HIDE);
	if (GetZhihuWayBtn() == 4) {
		DialogManager::GetInstance().ShowThicknessDlg();
	}
	else {
		DialogManager::GetInstance().ShowMethodChooseDlg();
	}

}


void CThreeTunnelDlg::TunnelSavepm()
{
	// TODO: 在此添加控件通知处理程序代码
	// 新建，将arc信息保存到当前的 Project 单例中

	int type = GetTunnelOption();

	CArcTunnel * pTunnel = CArcProjectBuilder::GetInstance()->GetArcTunnel();

	CString strWidth;
	CString strWallHeight;
	CString strArcHeight;
	CString strTrapBottomWidth;
	CString strTrapLeftAngle;
	CString strTrapRightAngle;

	switch (type) {
	case 0:
		MessageBox(_T("请选择一种巷道类型"), _T("警告"), MB_ICONWARNING | MB_OK);
		break;
	case 1:
		CArcProjectBuilder::GetInstance()->GetTunnelProejct()->SetTunnelType(1);
		if (MFCUtil::VectorHasEmpty(mRectEdtArray) == true) {
			MessageBox(_T("矩形巷道数据不能含有空值"), _T("警告"), MB_ICONWARNING | MB_OK);
		}
		else {
			mEdtRecWidth.GetWindowText(strWidth);
			mEdtRecHeight.GetWindowText(strWallHeight);

			pTunnel->SetWidth(_ttof(strWidth));
			pTunnel->SetWallHeight(_ttof(strWallHeight));
			pTunnel->SetArcHeight(0);
			isPmLeagal = true;
		}
		break;
	case 2:
		CArcProjectBuilder::GetInstance()->GetTunnelProejct()->SetTunnelType(2);
		if (MFCUtil::VectorHasEmpty(mArcEdtArray) == true) {
			MessageBox(_T("拱形巷道数据不能含有空值"), _T("警告"), MB_ICONWARNING | MB_OK);
		}
		else {

			mEdtArcWidth.GetWindowText(strWidth);
			mEdtArcWallHeight.GetWindowText(strWallHeight);
			mEdtArcHeight.GetWindowText(strArcHeight);

			pTunnel->SetWidth(_ttof(strWidth));
			pTunnel->SetWallHeight(_ttof(strWallHeight));
			pTunnel->SetArcHeight(_ttof(strArcHeight));
			pTunnel->SetNormalToArc(
				mRadioNormalToArc.GetCheck() == TRUE ? true : false
			);
			isPmLeagal = true;
			break;
	case 3:
		CArcProjectBuilder::GetInstance()->GetTunnelProejct()->SetTunnelType(3);
		if (MFCUtil::VectorHasEmpty(mTrapEdtArray) == true) {
			MessageBox(_T("梯形巷道数据不能含有空值"), _T("警告"), MB_ICONWARNING | MB_OK);
		}
		else {
			mEdtTrapTopWidth.GetWindowText(strWidth);
			mEdtTrapHeight.GetWindowText(strWallHeight);
			mEdtTrapBottomWidth.GetWindowText(strTrapBottomWidth);
			mEdtTrapLeftAngle.GetWindowText(strTrapLeftAngle);
			mEdtTrapRightAngle.GetWindowText(strTrapRightAngle);
			
			pTunnel->SetArcHeight(0);
			pTunnel->SetWidth(_ttof(strWidth));
			pTunnel->SetWallHeight(_ttof(strWallHeight));
			pTunnel->SetTrapBottomWidth(_ttof(strTrapBottomWidth));
			pTunnel->SetTrapLeftAngle(_ttoi(strTrapLeftAngle));
			pTunnel->SetTrapRightAngle(_ttoi(strTrapRightAngle));
			isPmLeagal = true;
		}
		break;
	default:
		break;
	}
	}
}

void CThreeTunnelDlg::OnBnClickedButtonProjectDialog()
{
	// TODO: 在此添加控件通知处理程序代码
	DialogManager::GetInstance().HideTunnelChooseDlg();

	DialogManager::GetInstance().ShowProjectDialog();

}

int CalTrapTopWidth(double bottomWidth, double height, int leftAngle, int right) {
	int topWidth = bottomWidth - (height / tan(MFCUtil::AngleToArc(leftAngle)))
		- (height / tan(MFCUtil::AngleToArc(right)));
	return topWidth;
};

void CThreeTunnelDlg::OnEnChangeEditTrapBottomWidth()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	
	CString strWallHeight;
	CString strTrapBottomWidth;
	CString strTrapLeftAngle;
	CString strTrapRightAngle;

	mEdtTrapHeight.GetWindowText(strWallHeight);
	mEdtTrapBottomWidth.GetWindowText(strTrapBottomWidth);
	mEdtTrapLeftAngle.GetWindowText(strTrapLeftAngle);
	mEdtTrapRightAngle.GetWindowText(strTrapRightAngle);

	if (!strWallHeight.IsEmpty() && !strTrapBottomWidth.IsEmpty()
		&& !strTrapLeftAngle.IsEmpty() && !strTrapRightAngle.IsEmpty()) {
		mEdtTrapTopWidth.SetWindowText(MFCUtil::itostr(
			CalTrapTopWidth(
				_ttof(strTrapBottomWidth),
				_ttof(strWallHeight),
				_ttof(strTrapLeftAngle),
				_ttof(strTrapRightAngle)
			)));
	}
}



void CThreeTunnelDlg::OnEnChangeEditTrapLeftAngle()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString strWallHeight;
	CString strTrapBottomWidth;
	CString strTrapLeftAngle;
	CString strTrapRightAngle;

	mEdtTrapHeight.GetWindowText(strWallHeight);
	mEdtTrapBottomWidth.GetWindowText(strTrapBottomWidth);
	mEdtTrapLeftAngle.GetWindowText(strTrapLeftAngle);
	mEdtTrapRightAngle.GetWindowText(strTrapRightAngle);

	if (!strWallHeight.IsEmpty() && !strTrapBottomWidth.IsEmpty()
		&& !strTrapLeftAngle.IsEmpty() && !strTrapRightAngle.IsEmpty()) {
		mEdtTrapTopWidth.SetWindowText(MFCUtil::itostr(
			CalTrapTopWidth(
				_ttof(strTrapBottomWidth),
				_ttof(strWallHeight),
				_ttof(strTrapLeftAngle),
				_ttof(strTrapRightAngle)
			)));
	}
}


void CThreeTunnelDlg::OnEnChangeEditTrapRightAngle()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString strWallHeight;
	CString strTrapBottomWidth;
	CString strTrapLeftAngle;
	CString strTrapRightAngle;

	mEdtTrapHeight.GetWindowText(strWallHeight);
	mEdtTrapBottomWidth.GetWindowText(strTrapBottomWidth);
	mEdtTrapLeftAngle.GetWindowText(strTrapLeftAngle);
	mEdtTrapRightAngle.GetWindowText(strTrapRightAngle);

	if (!strWallHeight.IsEmpty() && !strTrapBottomWidth.IsEmpty()
		&& !strTrapLeftAngle.IsEmpty() && !strTrapRightAngle.IsEmpty()) {
		mEdtTrapTopWidth.SetWindowText(MFCUtil::itostr(
			CalTrapTopWidth(
				_ttof(strTrapBottomWidth),
				_ttof(strWallHeight),
				_ttof(strTrapLeftAngle),
				_ttof(strTrapRightAngle)
			)));
	}
}


void CThreeTunnelDlg::OnEnChangeEditTrapHeight()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString strWallHeight;
	CString strTrapBottomWidth;
	CString strTrapLeftAngle;
	CString strTrapRightAngle;

	mEdtTrapHeight.GetWindowText(strWallHeight);
	mEdtTrapBottomWidth.GetWindowText(strTrapBottomWidth);
	mEdtTrapLeftAngle.GetWindowText(strTrapLeftAngle);
	mEdtTrapRightAngle.GetWindowText(strTrapRightAngle);

	if (!strWallHeight.IsEmpty() && !strTrapBottomWidth.IsEmpty()
		&& !strTrapLeftAngle.IsEmpty() && !strTrapRightAngle.IsEmpty()) {
		mEdtTrapTopWidth.SetWindowText(MFCUtil::itostr(
			CalTrapTopWidth(
				_ttof(strTrapBottomWidth),
				_ttof(strWallHeight),
				_ttof(strTrapLeftAngle),
				_ttof(strTrapRightAngle)
			)));
	}
}
