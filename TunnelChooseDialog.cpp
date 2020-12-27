// TunnelChooseDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCad.h"
#include "TunnelChooseDialog.h"
#include "afxdialogex.h"
#include "ProjectDialog.h"
#include "ProjectBuilder.h"
#include "DataChecker.h"

// CTunnelChooseDialog 对话框

IMPLEMENT_DYNAMIC(CTunnelChooseDialog, CDialogEx)

BEGIN_MESSAGE_MAP(CTunnelChooseDialog, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO_RECTANGLE, &CTunnelChooseDialog::OnBnClickedRadioRectangle)
	ON_BN_CLICKED(IDC_RADIO_ARC, &CTunnelChooseDialog::OnBnClickedRadioArc)
	ON_BN_CLICKED(IDC_RADIO_TRAPZOID, &CTunnelChooseDialog::OnBnClickedRadioTrapzoid)
	ON_BN_CLICKED(IDC_CHECK_BOLT_ANGLE, &CTunnelChooseDialog::OnBnClickedCheckBoltAngle)
	ON_BN_CLICKED(ID_CHOOSE_OK, &CTunnelChooseDialog::OnBnClickedChooseOk)
	ON_BN_CLICKED(IDC_BUTTON_PROJECT_DIALOG, &CTunnelChooseDialog::OnBnClickedButtonProjectDialog)
	ON_BN_CLICKED(ID_CHOOSE_CANCEL, &CTunnelChooseDialog::OnBnClickedChooseCancel)
	ON_WM_MOVING()
	ON_BN_CLICKED(IDC_BUTTON_TUNNEL_SAVEPM, &CTunnelChooseDialog::OnBnClickedButtonTunnelSavepm)
END_MESSAGE_MAP()

CTunnelChooseDialog::CTunnelChooseDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TUNNEL_CHOOSE_DIALOG, pParent)
	, mTopAngle(0)
	, mLeftAngle(0)
	, mRightAngle(0)
{

}

CTunnelChooseDialog::~CTunnelChooseDialog()
{
}

void CTunnelChooseDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_RADIO_RECTANGLE, mRecTunnelOption);
	//DDX_Control(pDX, IDC_RADIO_ARC, mArcTunnelOption);
	//DDX_Control(pDX, IDC_RADIO_TRAPZOID, mTrapTunnelOption);
	//DDX_Control(pDX, IDC_EDIT_REC_WIDTH, mEdtRecWidth);
	//DDX_Control(pDX, IDC_EDIT_REC_HEIGHT, mEdtRecHeight);
	DDX_Control(pDX, IDC_EDIT_ARC_WIDTH, mEdtArcWidth);
	DDX_Control(pDX, IDC_EDIT_ARC_WALL_HEIGHT, mEdtArcWallHeight);
	DDX_Control(pDX, IDC_EDIT_ARC_HEIGHT, mEdtArcHeight);
	DDX_Control(pDX, IDC_RADIO_NORMAL_TO_ARC, mRadioNormalToArc);
	DDX_Control(pDX, IDC_RADIO_NORMAL_TO_GROUND, mRadioNormalToGround);
	//DDX_Control(pDX, IDC_EDIT_TRAP_TOP_WIDTH, mEdtTrapTopWidth);
	//DDX_Control(pDX, IDC_EDIT_TRAP_BOTTOM_WIDTH, mEdtTrapBottomWidth);
	//DDX_Control(pDX, IDC_EDIT_TRAP_HEIGHT, mEdtTrapHeight);
	//DDX_Control(pDX, IDC_EDIT_TRAP_LEFT_ANGLE, mEdtTrapLeftAngle);
	//DDX_Control(pDX, IDC_EDIT_TRAP_RIGHT_ANGLE, mEdtTrapRightAngle);
	//DDX_Control(pDX, IDC_EDIT_BOLT_TOP_ANGLE, mEdtBoltTopAngle);
	DDX_Control(pDX, IDC_EDIT_BOLT_LEFT_ANGLE, mEdtBoltLeftAngle);
	DDX_Control(pDX, IDC_EDIT_BOLT_RIGHT_ANGLE, mEdtBoltRightAngle);
	DDX_Control(pDX, IDC_CHECK_BOLT_ANGLE, mCheckBoltAngle);
	DDX_Control(pDX, IDC_STATIC_TUNNEL_TITLE, mTunnelChooseTitle);
	DDX_Control(pDX, IDC_RADIO_ZHIHU_BOLT, mRadioDefaultWay);
	DDX_Control(pDX, IDC_RADIO_ZHIHU_BOLT_CONCRETE_QI, mRadioBoltConcreteWay);
	DDX_Control(pDX, IDC_RADIO_ZHIHU_BOLT_CONCRETE, mRadioJetConcreteWay);
	DDX_Control(pDX, IDC_RADIO_ZHIHU_CONCRETE_QI, mRadioConcreteQiWay);
	//DDX_Text(pDX, IDC_EDIT_BOLT_TOP_ANGLE, mTopAngle);
	DDX_Text(pDX, IDC_EDIT_BOLT_LEFT_ANGLE, mLeftAngle);
	DDX_Text(pDX, IDC_EDIT_BOLT_RIGHT_ANGLE, mRightAngle);

}

void CTunnelChooseDialog::OnBnClickedRadioRectangle()
{
	// TODO: 在此添加控件通知处理程序代码

	//setOptionDisabled();
}

void CTunnelChooseDialog::SetZhihuWay(int flag) {
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

int CTunnelChooseDialog::GetZhihuWayBtn() {
	if (mRadioDefaultWay.GetCheck() == TRUE)
	{
		return 1;
	}
	if (mRadioBoltConcreteWay.GetCheck()==TRUE)
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

BOOL CTunnelChooseDialog::OnInitDialog()
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

	if (CArcProjectBuilder::GetInstance()->GetFileUrl().IsEmpty() &&
		CArcProjectBuilder::GetInstance()->GetTunnelSaveToInstance() == FALSE)
	{	
		// 当前为第一次进入巷道参数输入界面
		SetZhihuWay(1);
		//mEdtBoltTopAngle.SetWindowText(_T("90"));
		mEdtBoltLeftAngle.SetWindowText(_T("90"));
		mEdtBoltRightAngle.SetWindowText(_T("90"));
		mRadioNormalToArc.SetCheck(TRUE);
	}
	else {

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
		mTopAngle = pArc->GetTopAngle();
		mLeftAngle = pArc->GetLeftAngle();
		mRightAngle = pArc->GetRightAngle();
		UpdateData(FALSE);
		//mEdtBoltTopAngle.SetWindowText(MFCUtil::dtostr(pArc->GetTopAngle()));
		//mEdtBoltLeftAngle.SetWindowText(MFCUtil::dtostr(pArc->GetLeftAngle()));
		//mEdtBoltRightAngle.SetWindowText(MFCUtil::dtostr(pArc->GetRightAngle()));

	}

	CString strTmp;

	mArcTunnelOption.SetCheck(TRUE);
	
	mTunnelChooseTitle.SetFont(MFCUtil::GetTitleFont());
	// 设置矩形巷道的参数
	/*mEdtRecWidth.SetWindowText(_T("4800"));
	mEdtRecHeight.SetWindowText(_T("3000"));
	 
	mEdtTrapBottomWidth.SetWindowText(_T("4800"));
	mEdtTrapHeight.SetWindowText(_T("3000"));
	mEdtTrapLeftAngle.SetWindowText(_T("85"));
	mEdtTrapRightAngle.SetWindowText(_T("80"));
*/


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CTunnelChooseDialog::OnBnClickedRadioArc()
{
	// TODO: 在此添加控件通知处理程序代码
	//setOptionDisabled();
}


void CTunnelChooseDialog::OnBnClickedRadioTrapzoid()
{
	// TODO: 在此添加控件通知处理程序代码
	/*setOptionDisabled();*/
}


void CTunnelChooseDialog::OnBnClickedCheckBoltAngle()
{
	// TODO: 在此添加控件通知处理程序代码
	for (auto & it:  mAngleEdtArray) {
		it->EnableWindow((mCheckBoltAngle.GetCheck() == TRUE) ? true : false);
	}
}


void CTunnelChooseDialog::OnBnClickedChooseOk()
{
	// TODO: 在此添加专用代码和/或调用基类


	if (MFCUtil::VectorHasEmpty(mArcEdtArray) == true) {
		MessageBox(_T("拱形数据不能含有空值"));
	}
	else {

		if (GetCheckedRadioButton(mRadioDefaultWay.GetDlgCtrlID(),
			mRadioConcreteQiWay.GetDlgCtrlID()) == 0)
		{
			MessageBox(_T("请选择一种支护方式"));
		}

		else {
			UpdateData(TRUE);

			if (mLeftAngle > 90 || mLeftAngle < 0 || mRightAngle > 90
				|| mRightAngle < 0) {
				MessageBox(_T("与帮的夹角应介于于0和90之间"));
			}
			else {
				SuccessToMethodChooseDlg();
			}
		}

	}

}

void  CTunnelChooseDialog::SuccessToMethodChooseDlg() {

	OnBnClickedButtonTunnelSavepm();

	CDialogEx::OnOK();
	// 跳转计算方法选择界面
	CMethodChooseDialog *pMethodChooseDlg = new CMethodChooseDialog();
	pMethodChooseDlg->Create(IDD_METHOD_CHOOSE_DIALOG, this->GetParent());
	pMethodChooseDlg->ShowWindow(SW_SHOW);
}


// CTunnelChooseDialog 消息处理程序




void CTunnelChooseDialog::OnBnClickedButtonProjectDialog()
{
	// TODO: 在此添加控件通知处理程序代码

	OnBnClickedButtonTunnelSavepm();

	CDialogEx::OnOK();

	CProjectDialog *pDlg = new CProjectDialog();
	pDlg->Create(IDD_PROJECT_DIALOG, this->GetParent());
	pDlg->ShowWindow(SW_SHOW);
}


void CTunnelChooseDialog::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	if (CArcProjectBuilder::GetInstance()->GetTunnelSaveToInstance() == FALSE)
	{
		if (IDYES == MessageBox(_T("当前页面参数尚未保存，仍要关闭此页面？"), 0, MB_YESNO))
		{
			CDialogEx::OnCancel();
		}
	}
	else {
		CDialogEx::OnCancel();
	}
}


void CTunnelChooseDialog::OnBnClickedChooseCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}


void CTunnelChooseDialog::OnMoving(UINT fwSide, LPRECT lpRect)
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


void CTunnelChooseDialog::OnBnClickedButtonTunnelSavepm()
{
	// TODO: 在此添加控件通知处理程序代码
	// 新建，将arc信息保存到当前的 Project 单例中
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

	CString strLeftAngle, strTopAngle, strRightAngle;

	mEdtBoltTopAngle.GetWindowText(strTopAngle);
	mEdtBoltLeftAngle.GetWindowText(strLeftAngle);
	mEdtBoltRightAngle.GetWindowText(strRightAngle);


	CArcProjectBuilder::GetInstance()->GetArcTunnel()->SetTopAngle(_ttof(strTopAngle));
	CArcProjectBuilder::GetInstance()->GetArcTunnel()->SetLeftAngle(_ttof(strLeftAngle));
	CArcProjectBuilder::GetInstance()->GetArcTunnel()->SetRightAngle(_ttof(strRightAngle));

	std::cout << "instance left angle: " << CArcProjectBuilder::GetInstance()->GetArcTunnel()->GetLeftAngle() << std::endl;
	CArcProjectBuilder::GetInstance()->SetTunnelSaveToInstance(TRUE);

	MessageBox(_T("本页参数保存成功"));
}
