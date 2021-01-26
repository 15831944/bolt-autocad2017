// ParametersDialog.cpp : 实现文件
//
#include "stdafx.h"
#include "MFCad.h"
#include "ParametersDialog.h"
#include "MethodChooseDialog.h"
#include "afxdialogex.h"
#include "ProjectBuilder.h"
#include "FileUtil.h"
#include "CADService.h"
#include "MFCadDlg.h"
#include "DataChecker.h"
#include "DialogManager.h"

#include <iostream>
// CParametersDialog 对话框

IMPLEMENT_DYNAMIC(CParametersDialog, CDialogEx)

CParametersDialog::CParametersDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PARAMETERS_DIALOG, pParent)
	, mTopBoltLength(0)
	, mTopBoltNumber(0)
	, mTopBoltPitch(0)
	, mTopBoltALength(0)
	, mTopBoltSpace(0)
	, mLeftBoltNumber(0)
	, mLeftBoltSpace(0)
	, mRightBoltNumber(0)
	, mRightBoltSpace(0)
	, mCableNumber(0)
	, mCableSpace(0)
{

}

CParametersDialog::~CParametersDialog()
{
}

void CParametersDialog::UpdateUI()
{
	mCheckTopBolt.SetCheck(CArcProjectBuilder::GetInstance()->GetArcTunnel()->GetHasTopBolt());
	mCheckLeftBolt.SetCheck(CArcProjectBuilder::GetInstance()->GetArcTunnel()->GetHasLeftBolt());
	mCheckRightBolt.SetCheck(CArcProjectBuilder::GetInstance()->GetArcTunnel()->GetHasRightBolt());
	mCheckCable.SetCheck(CArcProjectBuilder::GetInstance()->GetArcTunnel()->GetHasCable());

	SetMfcBoltCableFormIni();
	OnBnClickedCheckCable();
	OnBnClickedCheckLeftBolt();
	OnBnClickedCheckTopBolt();
	OnBnClickedCheckRightBolt();
	UpdateCastnetUI(CArcProjectBuilder::GetInstance()->GetArcTunnel()->GetTopNet(), CArcProjectBuilder::GetInstance()->GetArcTunnel()->GetBangNet());
	std::cout << "set bolt info successfully!\n";
}

void CParametersDialog::SetThikcnessEdit()
{
	if (CArcProjectBuilder::GetInstance()->GetArcTunnel()->GetZhihuWay() > 1)
	{
		mEdtConcreteThickness.EnableWindow(TRUE);
		mEdtQiThickness.EnableWindow(TRUE);
	}
	else {
		mEdtConcreteThickness.EnableWindow(FALSE);
		mEdtQiThickness.EnableWindow(FALSE);
	}
}


void CParametersDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_LEFT_BOLT, mCheckLeftBolt);
	DDX_Control(pDX, IDC_CHECK_RIGHT_BOLT, mCheckRightBolt);
	DDX_Control(pDX, IDC_CHECK_CABLE, mCheckCable);
	DDX_Control(pDX, IDC_EDIT_TOP_BOLT_DIAMETER, mEdtTopBoltDiameter);
	DDX_Control(pDX, IDC_EDIT_TOP_BOLT_LENGTH, mEdtTopBoltLength);
	DDX_Control(pDX, IDC_EDIT_TOP_BOLT_MATERIAL, mEdtTopBoltMaterial);
	DDX_Control(pDX, IDC_EDIT_TOP_BOLT_TAILING, mEdtTopBoltTailing);
	DDX_Control(pDX, IDC_EDIT_TOP_BOLT_NUMBER, mEdtTopBoltNumber);
	DDX_Control(pDX, IDC_EDIT_TOP_BOLT_SPACE, mEdtTopBoltSpace);
	DDX_Control(pDX, IDC_EDIT_TOP_BOLT_PITCH, mEdtTopBoltPitch);
	DDX_Control(pDX, IDC_EDIT_TOP_BOLT_ALENGTH, mEdtTopBoltALength);
	DDX_Control(pDX, IDC_EDIT_TOP_BOLT_BEAM_WIDTH, mEdtTopBoltBeamWidth);
	DDX_Control(pDX, IDC_EDIT_TOP_BOLT_BEAM_MATERIAL, mEdtTopBoltBeamMaterial);
	DDX_Control(pDX, IDC_EDIT_TOP_BOLT_TRAY_HEIGHT, mEdtTopBoltTrayLength);
	DDX_Control(pDX, IDC_EDIT_TOP_BOLT_TRAY_MATERIAL, mEdtTopBoltTrayMaterial);
	DDX_Control(pDX, IDC_EDIT_LEFT_BOLT_DIAMETER, mEdtLeftBoltDiameter);
	DDX_Control(pDX, IDC_EDIT_LEFT_BOLT_LENGTH, mEdtLeftBoltLength);
	DDX_Control(pDX, IDC_EDIT_LEFT_BOLT_MATERIAL, mEdtLeftBoltMaterial);
	DDX_Control(pDX, IDC_EDIT_LEFT_BOLT_TAILING, mEdtLeftBoltTailing);
	DDX_Control(pDX, IDC_EDIT_LEFT_BOLT_NUMBER, mEdtLeftBoltNumber);
	DDX_Control(pDX, IDC_EDIT_LEFT_BOLT_SPACE, mEdtLeftBoltSpace);
	DDX_Control(pDX, IDC_EDIT_LEFT_BOLT_PITCH, mEdtLeftBoltPitch);
	DDX_Control(pDX, IDC_EDIT_LEFT_BOLT_ALENGTH, mEdtLeftBoltALength);
	DDX_Control(pDX, IDC_EDIT_LEFT_BOLT_BEAM_WIDTH, mEdtLeftBoltBeamWidth);
	DDX_Control(pDX, IDC_EDIT_LEFT_BOLT_BEAM_MATERIAL, mEdtLeftBoltBeamMaterial);
	DDX_Control(pDX, IDC_EDIT_LEFT_BOLT_TRAY_HEIGHT, mEdtLeftBoltTrayLength);
	DDX_Control(pDX, IDC_EDIT_LEFT_BOLT_TRAY_MATERIAL, mEdtLeftBoltTrayMaterial);
	DDX_Control(pDX, IDC_EDIT_RIGHT_BOLT_DIAMETER, mEdtRightBoltDiameter);
	DDX_Control(pDX, IDC_EDIT_RIGHT_BOLT_LENGTH, mEdtRightBoltLength);
	DDX_Control(pDX, IDC_EDIT_RIGHT_BOLT_MATERIAL, mEdtRightBoltMaterial);
	DDX_Control(pDX, IDC_EDIT_RIGHT_BOLT_TAILING, mEdtRightBoltTailing);
	DDX_Control(pDX, IDC_EDIT_RIGHT_BOLT_NUMBER, mEdtRightBoltNumber);
	DDX_Control(pDX, IDC_EDIT_RIGHT_BOLT_SPACE, mEdtRightBoltSpace);
	DDX_Control(pDX, IDC_EDIT_RIGHT_BOLT_PITCH, mEdtRightBoltPitch);
	DDX_Control(pDX, IDC_EDIT_RIGHT_BOLT_ALENGTH, mEdtRightBoltALength);
	DDX_Control(pDX, IDC_EDIT_RIGHT_BOLT_BEAM_WIDTH, mEdtRightBoltBeamWidth);
	DDX_Control(pDX, IDC_EDIT_RIGHT_BOLT_BEAM_MATERIAL, mEdtRightBoltBeamMaterial);
	DDX_Control(pDX, IDC_EDIT_RIGHT_BOLT_TRAY_HEIGHT, mEdtRightBoltTrayLength);
	DDX_Control(pDX, IDC_EDIT_RIGHT_BOLT_TRAY_MATERIAL, mEdtRightBoltTrayMaterial);
	DDX_Control(pDX, IDC_EDIT_CABLE_DIAMETER, mEdtCableDiameter);
	DDX_Control(pDX, IDC_EDIT_CABLE_LENGTH, mEdtCableLength);
	DDX_Control(pDX, IDC_EDIT_CABLE_MATERIAL, mEdtCableMaterial);
	DDX_Control(pDX, IDC_EDIT_CABLE_TAILING, mEdtCableTailing);
	DDX_Control(pDX, IDC_EDIT_CABLE_NUMBER, mEdtCableNumber);
	DDX_Control(pDX, IDC_EDIT_CABLE_SPACE, mEdtCableSpace);
	DDX_Control(pDX, IDC_EDIT_CABLE_PITCH, mEdtCablePitch);
	DDX_Control(pDX, IDC_EDIT_CABLE_ALENGTH, mEdtCableALength);
	DDX_Control(pDX, IDC_EDIT_CABLE_TRAY_LENGTH, mEdtCableTrayLength);
	DDX_Control(pDX, IDC_EDIT_CABLE_TRAY_MATERIAL, mEdtCableTrayMaterial);
	DDX_Control(pDX, IDC_EDIT_CABLE_SHU_DIAMETER, mEdtCableShuDiameter);
	DDX_Control(pDX, IDC_EDIT_CABLE_SHU_LENGTH, mEdtCableShuLength);
	DDX_Control(pDX, IDC_EDIT_CABLE_SHU_MATERIAL, mEdtCableShuMaterial);
	DDX_Control(pDX, IDC_CHECK_TOP_BOLT, mCheckTopBolt);
	DDX_Control(pDX, IDC_EDIT_LEFT_BOLT_PORTRAIT_BEAM_MATERIAL, mEdtLeftBoltPortraitBeamMaterial);
	DDX_Control(pDX, IDC_EDIT_LEFT_BOLT_PORTRAIT_BEAM_WIDTH, mEdtLeftBoltPortraitBeamWidth);
	DDX_Control(pDX, IDC_EDIT_RIGHT_BOLT_PORTRAIT_BEAM_MATERIAL, mEdtRightBoltPortraitBeamMaterial);
	DDX_Control(pDX, IDC_EDIT_RIGHT_BOLT_PORTRAIT_BEAM_WIDTH, mEdtRightBoltPortraitBeamWidth);
	DDX_Control(pDX, IDC_EDIT_TOP_BOLT_PORTRAIT_BEAM_MATERIAL, mEdtTopBoltPortraitBeamMaterial);
	DDX_Control(pDX, IDC_EDIT_TOP_BOLT_PORTRAIT_BEAM_WIDTH, mEdtTopBoltPortraitBeamWidth);
	DDX_Text(pDX, IDC_EDIT_TOP_BOLT_LENGTH, mTopBoltLength);
	DDX_Text(pDX, IDC_EDIT_TOP_BOLT_NUMBER, mTopBoltNumber);
	DDX_Text(pDX, IDC_EDIT_TOP_BOLT_PITCH, mTopBoltPitch);
	DDX_Text(pDX, IDC_EDIT_TOP_BOLT_ALENGTH, mTopBoltALength);
	DDX_Control(pDX, IDC_EDIT_CONCRETE_THICKNESS, mEdtConcreteThickness);
	DDX_Control(pDX, IDC_EDIT_QIXUAN_THICKNESS, mEdtQiThickness);
	DDX_Text(pDX, IDC_EDIT_TOP_BOLT_SPACE, mTopBoltSpace);
	DDX_Text(pDX, IDC_EDIT_LEFT_BOLT_NUMBER, mLeftBoltNumber);
	DDX_Text(pDX, IDC_EDIT_LEFT_BOLT_SPACE, mLeftBoltSpace);
	DDX_Text(pDX, IDC_EDIT_RIGHT_BOLT_NUMBER, mRightBoltNumber);
	DDX_Text(pDX, IDC_EDIT_RIGHT_BOLT_SPACE, mRightBoltSpace);
	DDX_Text(pDX, IDC_EDIT_CABLE_NUMBER, mCableNumber);
	DDX_Text(pDX, IDC_EDIT_CABLE_SPACE, mCableSpace);
	DDX_Control(pDX, IDC_EDIT_TOP_NET_SIZE, mEdtTopNetSize);
	DDX_Control(pDX, IDC_EDIT_LEFT_NET_SIZE, mEdtBangNetSize);
	DDX_Control(pDX, IDC_RADIO_NO_TOPNET, mRadioNoTopnet);
	DDX_Control(pDX, IDC_RADIO_NO_BANGNET, mRadioNoBangnet);
	DDX_Control(pDX, IDC_RADIO_METAL_TOPNET, mRadioMetalTopnet);
	DDX_Control(pDX, IDC_RADIO_REBAR_TOPNET, mRadioRebarTopnet);
	DDX_Control(pDX, IDC_RADIO_PLASTIC_TOPNET, mRadioPlasticTopnet);
	DDX_Control(pDX, IDC_RADIO_METAL_BANGNET, mRadioMetalBangnet);
	DDX_Control(pDX, IDC_RADIO_REBAR_BANGNET, mRadioRebarBangnet);
	DDX_Control(pDX, IDC_RADIO_PLASTIC_BANGNET, mRadioPlasticBangnet);
}


BEGIN_MESSAGE_MAP(CParametersDialog, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK_LEFT_BOLT, &CParametersDialog::OnBnClickedCheckLeftBolt)
	ON_BN_CLICKED(IDC_CHECK_RIGHT_BOLT, &CParametersDialog::OnBnClickedCheckRightBolt)
	ON_BN_CLICKED(IDC_CHECK_CABLE, &CParametersDialog::OnBnClickedCheckCable)
	ON_BN_CLICKED(IDOK, &CParametersDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK_TOP_BOLT, &CParametersDialog::OnBnClickedCheckTopBolt)
	ON_BN_CLICKED(IDOK, &CParametersDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_PM, &CParametersDialog::OnBnClickedButtonSavePm)
	ON_BN_CLICKED(IDC_BUTTON_BACK_METHOD_CHOOSE, &CParametersDialog::OnBnClickedButtonBackMethodChoose)
	ON_WM_MOVING()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CParametersDialog 消息处理程序

void CParametersDialog::InitEdtVector() {
	mVectorEdtTopBolt.push_back(&mEdtTopBoltDiameter);
	mVectorEdtTopBolt.push_back(&mEdtTopBoltLength);
	mVectorEdtTopBolt.push_back(&mEdtTopBoltMaterial);
	mVectorEdtTopBolt.push_back(&mEdtTopBoltTailing);
	mVectorEdtTopBolt.push_back(&mEdtTopBoltNumber);
	mVectorEdtTopBolt.push_back(&mEdtTopBoltSpace);
	mVectorEdtTopBolt.push_back(&mEdtTopBoltPitch);
	mVectorEdtTopBolt.push_back(&mEdtTopBoltALength);
	mVectorEdtTopBolt.push_back(&mEdtTopBoltBeamWidth);
	mVectorEdtTopBolt.push_back(&mEdtTopBoltBeamMaterial);
	mVectorEdtTopBolt.push_back(&mEdtTopBoltPortraitBeamMaterial);
	mVectorEdtTopBolt.push_back(&mEdtTopBoltPortraitBeamWidth);
	mVectorEdtTopBolt.push_back(&mEdtTopBoltTrayLength);
	mVectorEdtTopBolt.push_back(&mEdtTopBoltTrayMaterial);

	mVectorEdtLeftBolt.push_back(&mEdtLeftBoltDiameter);
	mVectorEdtLeftBolt.push_back(&mEdtLeftBoltLength);
	mVectorEdtLeftBolt.push_back(&mEdtLeftBoltMaterial);
	mVectorEdtLeftBolt.push_back(&mEdtLeftBoltTailing);
	mVectorEdtLeftBolt.push_back(&mEdtLeftBoltNumber);
	mVectorEdtLeftBolt.push_back(&mEdtLeftBoltSpace);
	mVectorEdtLeftBolt.push_back(&mEdtLeftBoltPitch);
	mVectorEdtLeftBolt.push_back(&mEdtLeftBoltALength);
	mVectorEdtLeftBolt.push_back(&mEdtLeftBoltBeamWidth);
	mVectorEdtLeftBolt.push_back(&mEdtLeftBoltBeamMaterial);
	mVectorEdtLeftBolt.push_back(&mEdtLeftBoltPortraitBeamMaterial);
	mVectorEdtLeftBolt.push_back(&mEdtLeftBoltPortraitBeamWidth);
	mVectorEdtLeftBolt.push_back(&mEdtLeftBoltTrayLength);
	mVectorEdtLeftBolt.push_back(&mEdtLeftBoltTrayMaterial);

	mVectorEdtRightBolt.push_back(&mEdtRightBoltDiameter);
	mVectorEdtRightBolt.push_back(&mEdtRightBoltLength);
	mVectorEdtRightBolt.push_back(&mEdtRightBoltMaterial);
	mVectorEdtRightBolt.push_back(&mEdtRightBoltTailing);
	mVectorEdtRightBolt.push_back(&mEdtRightBoltNumber);
	mVectorEdtRightBolt.push_back(&mEdtRightBoltSpace);
	mVectorEdtRightBolt.push_back(&mEdtRightBoltPitch);
	mVectorEdtRightBolt.push_back(&mEdtRightBoltALength);
	mVectorEdtRightBolt.push_back(&mEdtRightBoltBeamWidth);
	mVectorEdtRightBolt.push_back(&mEdtRightBoltBeamMaterial);
	mVectorEdtRightBolt.push_back(&mEdtRightBoltPortraitBeamMaterial);
	mVectorEdtRightBolt.push_back(&mEdtRightBoltPortraitBeamWidth);
	mVectorEdtRightBolt.push_back(&mEdtRightBoltTrayLength);
	mVectorEdtRightBolt.push_back(&mEdtRightBoltTrayMaterial);

	mVectorCable.push_back(&mEdtCableDiameter);
	mVectorCable.push_back(&mEdtCableLength);
	mVectorCable.push_back(&mEdtCableMaterial);
	mVectorCable.push_back(&mEdtCableTailing);
	mVectorCable.push_back(&mEdtCableNumber);
	mVectorCable.push_back(&mEdtCableSpace);
	mVectorCable.push_back(&mEdtCablePitch);
	mVectorCable.push_back(&mEdtCableALength);
	mVectorCable.push_back(&mEdtCableTrayLength);
	mVectorCable.push_back(&mEdtCableTrayMaterial);
	mVectorCable.push_back(&mEdtCableShuDiameter);
	mVectorCable.push_back(&mEdtCableShuLength);
	mVectorCable.push_back(&mEdtCableShuMaterial);
}

BOOL CParametersDialog::OnInitDialog()
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

	InitEdtVector();

	mCheckTopBolt.SetCheck(true);
	mCheckLeftBolt.SetCheck(true);
	mCheckCable.SetCheck(true);

	SetMfcBoltCableFormIni();
	OnBnClickedCheckCable();
	OnBnClickedCheckLeftBolt();
	OnBnClickedCheckTopBolt();
	OnBnClickedCheckRightBolt();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CParametersDialog::OnBnClickedCheckLeftBolt()
{
	// TODO: 在此添加控件通知处理程序代码
	for (auto &it : mVectorEdtLeftBolt)
	{
		it->EnableWindow((mCheckLeftBolt.GetCheck() == TRUE) ? true : false);
	}
	if (!CArcProjectBuilder::GetInstance()->GetFileUrl().IsEmpty())
		SetMfcBoltCableFormIni();

}

void CParametersDialog::OnBnClickedCheckRightBolt()
{
	// TODO: 在此添加控件通知处理程序代码
	/*右帮锚杆disabled切换*/
	if (mCheckRightBolt.GetCheck() == TRUE)
	{
		
		for (auto & it : mVectorEdtRightBolt) {
			it->EnableWindow(true);
		}
		mCheckTopBolt.SetCheck(false);
		mCheckTopBolt.EnableWindow(false);
		OnBnClickedCheckTopBolt();
	}
	else {
		for (auto & it : mVectorEdtRightBolt) {
			it->EnableWindow(false);
		}

		mCheckTopBolt.SetCheck(true);
		mCheckTopBolt.EnableWindow(true);

		OnBnClickedCheckTopBolt();

	}
	if (!CArcProjectBuilder::GetInstance()->GetFileUrl().IsEmpty()) {
		SetMfcBoltCableFormIni();
	}
}

void CParametersDialog::OnBnClickedCheckCable()
{
	// TODO: 在此添加控件通知处理程序代码
	for (auto & it : mVectorCable) {
		it->EnableWindow((mCheckCable.GetCheck() == TRUE) ? true : false);
	}
	if (!CArcProjectBuilder::GetInstance()->GetFileUrl().IsEmpty()) {
		SetMfcBoltCableFormIni();
	}
}

// 从界面中获取锚杆数据，返回一个锚杆对象
CBolt * CParametersDialog::InitBoltInfo(int flag) {
	CString diameter, length, material, tailing, number, space, pitch,
		aLength, beamWidth, beamMaterial, portBeamWidth, portBeamMaterial,
		trayLength, trayMaterial;
	CBolt * bolt = nullptr;
	switch (flag)
	{
	case 1:
		if (mCheckTopBolt.GetCheck() == TRUE)
		{
			mEdtTopBoltDiameter.GetWindowText(diameter);
			mEdtTopBoltLength.GetWindowText(length);
			mEdtTopBoltMaterial.GetWindowText(material);
			mEdtTopBoltTailing.GetWindowText(tailing);
			mEdtTopBoltNumber.GetWindowText(number);
			mEdtTopBoltSpace.GetWindowText(space);
			mEdtTopBoltPitch.GetWindowText(pitch);
			mEdtTopBoltALength.GetWindowText(aLength);
			mEdtTopBoltBeamWidth.GetWindowText(beamWidth);
			mEdtTopBoltBeamMaterial.GetWindowText(beamMaterial);
			mEdtTopBoltPortraitBeamWidth.GetWindowText(portBeamWidth);
			mEdtTopBoltPortraitBeamMaterial.GetWindowText(portBeamMaterial);
			mEdtTopBoltTrayLength.GetWindowText(trayLength);
			mEdtTopBoltTrayMaterial.GetWindowText(trayMaterial);
			bolt = new CBolt(_ttof(diameter), _ttof(length), material, _ttof(tailing), _ttoi(number), _ttof(space), _ttof(pitch),
				_ttof(aLength), _ttof(beamWidth), beamMaterial, _ttof(portBeamWidth), portBeamMaterial, trayLength, trayMaterial);
		}
		else {
			bolt = new CBolt();
		}
		break;
	case 2:
		if (mCheckLeftBolt.GetCheck() == TRUE) {
			std::cout << " new  left bolt;" << std::endl;

			mEdtLeftBoltDiameter.GetWindowText(diameter);
			mEdtLeftBoltLength.GetWindowText(length);
			mEdtLeftBoltMaterial.GetWindowText(material);
			mEdtLeftBoltTailing.GetWindowText(tailing);
			mEdtLeftBoltNumber.GetWindowText(number);
			mEdtLeftBoltSpace.GetWindowText(space);
			mEdtLeftBoltPitch.GetWindowText(pitch);
			mEdtLeftBoltALength.GetWindowText(aLength);
			mEdtLeftBoltBeamWidth.GetWindowText(beamWidth);
			mEdtLeftBoltBeamMaterial.GetWindowText(beamMaterial);
			mEdtLeftBoltPortraitBeamWidth.GetWindowText(portBeamWidth);
			mEdtLeftBoltPortraitBeamMaterial.GetWindowText(portBeamMaterial);
			mEdtLeftBoltTrayLength.GetWindowText(trayLength);
			mEdtLeftBoltTrayMaterial.GetWindowText(trayMaterial);
			bolt = new CBolt(_ttof(diameter), _ttof(length), material, _ttof(tailing), _ttoi(number), _ttof(space), _ttof(pitch),
				_ttof(aLength), _ttof(beamWidth), beamMaterial, _ttof(portBeamWidth), portBeamMaterial, trayLength, trayMaterial);
		}
		else {
			bolt = new CBolt();
		}

		break;
	case 3:

		if (mCheckRightBolt.GetCheck() == TRUE) {

			mEdtRightBoltDiameter.GetWindowText(diameter);
			mEdtRightBoltLength.GetWindowText(length);
			mEdtRightBoltMaterial.GetWindowText(material);
			mEdtRightBoltTailing.GetWindowText(tailing);
			mEdtRightBoltNumber.GetWindowText(number);
			mEdtRightBoltSpace.GetWindowText(space);
			mEdtRightBoltPitch.GetWindowText(pitch);
			mEdtRightBoltALength.GetWindowText(aLength);
			mEdtRightBoltBeamWidth.GetWindowText(beamWidth);
			mEdtRightBoltBeamMaterial.GetWindowText(beamMaterial);
			mEdtRightBoltPortraitBeamWidth.GetWindowText(portBeamWidth);
			mEdtRightBoltPortraitBeamMaterial.GetWindowText(portBeamMaterial);
			mEdtRightBoltTrayLength.GetWindowText(trayLength);
			mEdtRightBoltTrayMaterial.GetWindowText(trayMaterial);
			std::cout << " new  right bolt;" << std::endl;
			bolt = new CBolt(_ttof(diameter), _ttof(length), material, _ttof(tailing), _ttoi(number), _ttof(space), _ttof(pitch),
				_ttof(aLength), _ttof(beamWidth), beamMaterial, _ttof(portBeamWidth), portBeamMaterial, trayLength, trayMaterial);
		}
		else {
			bolt = new CBolt();
		}

		break;
	default:
		break;
	}
	return bolt;
}

// 从界面中获取锚索数据，返回一个锚索对象
CCable * CParametersDialog::InitCableInfo()
{
	CString diameter, length, material, tailing, number, space, pitch,
		aLength, trayLength, trayMaterial, shuDiameter, shuLength, shuMaterial;

	CCable * cable = nullptr;

	if (mCheckCable.GetCheck() == TRUE)
	{
		mEdtCableDiameter.GetWindowText(diameter);
		mEdtCableLength.GetWindowText(length);
		mEdtCableMaterial.GetWindowText(material);
		mEdtCableTailing.GetWindowText(tailing);
		mEdtCableNumber.GetWindowText(number);
		mEdtCableSpace.GetWindowText(space);
		mEdtCablePitch.GetWindowText(pitch);
		mEdtCableALength.GetWindowText(aLength);
		mEdtCableTrayLength.GetWindowText(trayLength);
		mEdtCableTrayMaterial.GetWindowText(trayMaterial);
		mEdtCableShuDiameter.GetWindowText(shuDiameter);
		mEdtCableShuLength.GetWindowText(shuLength);
		mEdtCableShuMaterial.GetWindowText(shuMaterial);

		cable = new CCable(_ttof(diameter), _ttof(length), material, _ttof(tailing), _ttoi(number), _ttof(space), _ttof(pitch),
			_ttof(aLength), _ttof(trayLength), trayMaterial, _ttof(shuDiameter), _ttof(shuLength), shuMaterial);
	}
	else {
		cable = new CCable();
		_ftprintf(stdout, cable->getMaterial());
	}

	return cable;
}

void CParametersDialog::OnBnClickedCheckTopBolt()
{
	// TODO: 在此添加控件通知处理程序代码
	for (auto & it : mVectorEdtTopBolt)
	{
		it->EnableWindow((mCheckTopBolt.GetCheck() == TRUE) ? true : false);
	}
}

void CParametersDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	if ((mCheckTopBolt.GetCheck() == TRUE && MFCUtil::VectorHasEmpty(mVectorEdtTopBolt))
		|| (mCheckLeftBolt.GetCheck() == TRUE && MFCUtil::VectorHasEmpty(mVectorEdtLeftBolt))
		|| (mCheckRightBolt.GetCheck() == TRUE && MFCUtil::VectorHasEmpty(mVectorEdtRightBolt))
		|| (mCheckCable.GetCheck() == TRUE && MFCUtil::VectorHasEmpty(mVectorCable)))
	{
		MessageBox(_T("不能含有空参数"), _T("警告"), MB_ICONWARNING);
	}
	else {
		OnBnClickedButtonSavePm();

		if (pmLeagal == true) {

			//向桥接文件写入参数
			CArcProjectBuilder::GetInstance()->SetFileUrl(CFileUtil::GetAppRegeditPath() + _T("ini\\bridge.ini"));
			CString dir = CFileUtil::GetAppRegeditPath() + _T("ini");
			if (!PathIsDirectory(dir))
			{
				::CreateDirectory(dir, NULL);//创建目录,已有的话不影响
			}
			if (CFileUtil::AddFile(CFileUtil::GetAppRegeditPath() + _T("ini\\bridge.ini")) == TRUE) {
				if (CArcProjectBuilder::GetInstance()->SaveBridgeFile() == true) {
					//MessageBox(_T("桥接文件保存成功！"));
					CArcProjectBuilder::GetInstance()->SetFileUrl(_T(""));
					CArcProjectBuilder::GetInstance()->SetSavedToFile(FALSE);
					CADService::WriteAcadRx();
					CADService::LaunchACad();
					MessageBox(_T("绘制成功，AutoCad已启动！"), _T("绘图成功"));
				}
				else {
					MessageBox(_T("桥接文件保存失败！"), _T("错误"));
				}
			}
		}
		else {
			MessageBox(_T("参数错误，无法绘图"), _T("错误"), MB_ICONERROR);
		}
	}
}
 
// 从文件中获取 Cable 和 Bolt 信息，并展示到对话框中
void CParametersDialog::SetMfcBoltCableFormIni() {

	CArcTunnel *pArc = CArcProjectBuilder::GetInstance()->GetArcTunnel();
	CBolt * bTop = pArc->GetTopBolt();
	CBolt * bLeft= pArc->GetLeftBolt();
	CBolt * bRight =pArc->GetRightBolt();
	CCable * cable = pArc->GetCable();
	
	if (mCheckTopBolt.GetCheck() == TRUE)
	{
		mEdtTopBoltDiameter.SetWindowText(MFCUtil::dtostr(bTop->getDiameter()));
		mEdtTopBoltLength.SetWindowText(MFCUtil::dtostr(bTop->getLength()));
		mEdtTopBoltMaterial.SetWindowText(bTop->getMaterial());
		mEdtTopBoltTailing.SetWindowText(MFCUtil::dtostr(bTop->getTailing()));
		mEdtTopBoltNumber.SetWindowText(MFCUtil::itostr(bTop->getNumber()));
		mEdtTopBoltSpace.SetWindowText(MFCUtil::dtostr(bTop->getSpace()));
		mEdtTopBoltPitch.SetWindowText(MFCUtil::dtostr(bTop->getPitch()));
		mEdtTopBoltALength.SetWindowText(MFCUtil::dtostr(bTop->getALength()));
		mEdtTopBoltBeamWidth.SetWindowText(MFCUtil::dtostr(bTop->getBeamWidth()));
		mEdtTopBoltBeamMaterial.SetWindowText(bTop->getBeamMaterial());
		mEdtTopBoltPortraitBeamWidth.SetWindowText(MFCUtil::dtostr(bTop->getPortBeamWidth()));
		mEdtTopBoltPortraitBeamMaterial.SetWindowText(bTop->getPortBeamMaterial());
		mEdtTopBoltTrayLength.SetWindowText(bTop->getTrayLength());
		mEdtTopBoltTrayMaterial.SetWindowText(bTop->getTrayMaterial());
	}

	if (mCheckLeftBolt.GetCheck() == TRUE) {

		mEdtLeftBoltDiameter.SetWindowText(MFCUtil::dtostr(bLeft->getDiameter()));
		mEdtLeftBoltLength.SetWindowText(MFCUtil::dtostr(bLeft->getLength()));
		mEdtLeftBoltMaterial.SetWindowText(bLeft->getMaterial());
		mEdtLeftBoltTailing.SetWindowText(MFCUtil::dtostr(bLeft->getTailing()));
		mEdtLeftBoltNumber.SetWindowText(MFCUtil::itostr(bLeft->getNumber()));
		mEdtLeftBoltSpace.SetWindowText(MFCUtil::dtostr(bLeft->getSpace()));
		mEdtLeftBoltPitch.SetWindowText(MFCUtil::dtostr(bLeft->getPitch()));
		mEdtLeftBoltALength.SetWindowText(MFCUtil::dtostr(bLeft->getALength()));
		mEdtLeftBoltBeamWidth.SetWindowText(MFCUtil::dtostr(bLeft->getBeamWidth()));
		mEdtLeftBoltBeamMaterial.SetWindowText(bLeft->getBeamMaterial());
		mEdtLeftBoltPortraitBeamWidth.SetWindowText(MFCUtil::dtostr(bLeft->getPortBeamWidth()));
		mEdtLeftBoltPortraitBeamMaterial.SetWindowText(bLeft->getPortBeamMaterial());
		mEdtLeftBoltTrayLength.SetWindowText(bLeft->getTrayLength());
		mEdtLeftBoltTrayMaterial.SetWindowText(bLeft->getTrayMaterial());
	}

	if (mCheckRightBolt.GetCheck() == TRUE) {
		mEdtRightBoltDiameter.SetWindowText(MFCUtil::dtostr(bRight->getDiameter()));
		mEdtRightBoltLength.SetWindowText(MFCUtil::dtostr(bRight->getLength()));
		mEdtRightBoltMaterial.SetWindowText(bRight->getMaterial());
		mEdtRightBoltTailing.SetWindowText(MFCUtil::dtostr(bRight->getTailing()));
		mEdtRightBoltNumber.SetWindowText(MFCUtil::itostr(bRight->getNumber()));
		mEdtRightBoltSpace.SetWindowText(MFCUtil::dtostr(bRight->getSpace()));
		mEdtRightBoltPitch.SetWindowText(MFCUtil::dtostr(bRight->getPitch()));
		mEdtRightBoltALength.SetWindowText(MFCUtil::dtostr(bRight->getALength()));
		mEdtRightBoltBeamWidth.SetWindowText(MFCUtil::dtostr(bRight->getBeamWidth()));
		mEdtRightBoltBeamMaterial.SetWindowText(bRight->getBeamMaterial());
		mEdtRightBoltPortraitBeamWidth.SetWindowText(MFCUtil::dtostr(bRight->getPortBeamWidth()));
		mEdtRightBoltPortraitBeamMaterial.SetWindowText(bRight->getPortBeamMaterial());
		mEdtRightBoltTrayLength.SetWindowText(bRight->getTrayLength());
		mEdtRightBoltTrayMaterial.SetWindowText(bRight->getTrayMaterial());
	}

	if (mCheckCable.GetCheck() == TRUE) {

		mEdtCableDiameter.SetWindowText(MFCUtil::dtostr(cable->getDiameter()));
		mEdtCableLength.SetWindowText(MFCUtil::dtostr(cable->getLength()));
		mEdtCableMaterial.SetWindowText(cable->getMaterial());
		mEdtCableTailing.SetWindowText(MFCUtil::dtostr(cable->getTailing()));
		mEdtCableNumber.SetWindowText(MFCUtil::itostr(cable->getNumber()));
		mEdtCableSpace.SetWindowText(MFCUtil::dtostr(cable->getSpace()));
		mEdtCablePitch.SetWindowText(MFCUtil::dtostr(cable->getPitch()));
		mEdtCableALength.SetWindowText(MFCUtil::dtostr(cable->getALength()));
		mEdtCableTrayLength.SetWindowText(MFCUtil::dtostr(cable->getTrayLength()));
		mEdtCableTrayMaterial.SetWindowText(cable->getTrayMaterial());
		mEdtCableShuDiameter.SetWindowText(MFCUtil::dtostr(cable->getShuDiameter()));
		mEdtCableShuLength.SetWindowText(MFCUtil::dtostr(cable->getShuLength()));
		mEdtCableShuMaterial.SetWindowText(cable->getShuMaterial());
	}

	if (pArc->GetZhihuWay() > 1)
	{
		mEdtConcreteThickness.SetWindowText(MFCUtil::dtostr(
			pArc->GetConcreteThickness()));
		mEdtQiThickness.SetWindowText(MFCUtil::dtostr(
			pArc->GetQiThickness()));
	}
}

int CParametersDialog::CheckBoltOrCableLeagal() {

	CArcTunnel * pArc = CArcProjectBuilder::GetInstance()->GetArcTunnel();

	if (mCheckTopBolt.GetCheck() == TRUE) {
		if (DataChecker::IsBoltNumberLeagal(pArc->GetWidth(), mTopBoltNumber, mTopBoltSpace) == false) {
			return 1;
		}
	}
	if (mCheckLeftBolt.GetCheck() == TRUE) {
		if (DataChecker::IsBoltNumberLeagal(pArc->GetWallHeight(), mLeftBoltNumber, mLeftBoltSpace) == false) {
			return 2;
		}
	}
	if (mCheckRightBolt.GetCheck() == TRUE) {
		if (DataChecker::IsBoltNumberLeagal(pArc->GetWidth(), mRightBoltNumber, mRightBoltSpace) == false) {
			return 3;
		}
	}
	if (mCheckCable.GetCheck() == TRUE) {
		if (DataChecker::IsBoltNumberLeagal(pArc->GetWidth(), mCableNumber, mCableSpace) == false) {
			return 4;
		}
	}
	return 0;
}

void CParametersDialog::OnBnClickedButtonSavePm()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if (CheckBoltOrCableLeagal() != 0) {
		switch (CheckBoltOrCableLeagal())
		{
		case 1:
			MessageBox(_T("请调整顶部锚杆间距或根数"), _T("警告"), MB_ICONWARNING);
			pmLeagal = false;
			break;
		case 2:
			MessageBox(_T("请调整帮部锚杆间距或根数"), _T("警告"), MB_ICONWARNING);
			pmLeagal = false;
			break;
		case 3:
			MessageBox(_T("请调整全锚索间距或根数"), _T("警告"), MB_ICONWARNING);
			pmLeagal = false;
			break;
		case 4:
			MessageBox(_T("请调整锚索间距或根数"), _T("警告"), MB_ICONWARNING);
			pmLeagal = false;
			break;
		default:
			break;
		}
	}
	else {
		// 检查无错误
		CArcProjectBuilder::GetInstance()
			->GetArcTunnel()->SetHasTopBolt(mCheckTopBolt.GetCheck() == TRUE ? true : false);
		CArcProjectBuilder::GetInstance()->GetArcTunnel()->SetHasLeftBolt(
			mCheckLeftBolt.GetCheck() == TRUE ? true : false);
		CArcProjectBuilder::GetInstance()->GetArcTunnel()->SetHasRightBolt(
			mCheckRightBolt.GetCheck() == TRUE ? true : false);
		CArcProjectBuilder::GetInstance()->GetArcTunnel()->SetHasCable(
			mCheckCable.GetCheck() == TRUE ? true : false);

		CArcProjectBuilder::GetInstance()->GetArcTunnel()->SetTopBolt(InitBoltInfo(1));
		CArcProjectBuilder::GetInstance()->GetArcTunnel()->SetLeftBolt(InitBoltInfo(2));
		CArcProjectBuilder::GetInstance()->GetArcTunnel()->SetRightBolt(InitBoltInfo(3));
		CArcProjectBuilder::GetInstance()->GetArcTunnel()->SetCable(InitCableInfo());

		if (CArcProjectBuilder::GetInstance()->GetArcTunnel()->GetZhihuWay() > 1)
		{
			CString strQi, strConcrete;
			mEdtConcreteThickness.GetWindowText(strConcrete);
			mEdtQiThickness.GetWindowText(strQi);
			CArcProjectBuilder::GetInstance()->GetArcTunnel()->SetQiThickness(_ttoi(strQi));
			CArcProjectBuilder::GetInstance()->GetArcTunnel()->SetConcreteThickness(_ttoi(strConcrete));
		}
		SaveCastnetInfo();
		MessageBox(_T("本页参数已保存"), _T("成功"));
		pmLeagal = true;
	}
}

void CParametersDialog::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

}

void CParametersDialog::OnBnClickedButtonBackMethodChoose()
{

	OnBnClickedButtonSavePm();

	CDialogEx::OnOK();

	// TODO: 在此添加控件通知处理程序代码
	DialogManager::GetInstance().ShowMethodChooseDlg();
}


void CParametersDialog::SaveCastnetInfo()
{
	// 记录顶部网和帮部网的状态
	int topnet = 0, bangnet = 0;
	if (mRadioNoTopnet.GetCheck()) topnet = 0;
	if (mRadioMetalTopnet.GetCheck()) topnet = 1;
	if(mRadioRebarTopnet.GetCheck()) topnet = 2;
	if(mRadioPlasticTopnet.GetCheck()) topnet = 3;
	if(mRadioNoBangnet.GetCheck()) bangnet = 0;
	if(mRadioMetalBangnet.GetCheck()) bangnet = 1;
	if(mRadioRebarBangnet.GetCheck()) bangnet = 2;
	if(mRadioPlasticBangnet.GetCheck()) bangnet = 3;
	CArcTunnel *pArc = CArcProjectBuilder::GetInstance()->GetArcTunnel();
	pArc->SetTopNet(topnet);
	pArc->SetBangNet(bangnet);
	mEdtTopNetSize.GetWindowText(pArc->GetTopnetSize());
	mEdtBangNetSize.GetWindowText(pArc->GetBangnetSize());
}

void CParametersDialog::UpdateCastnetUI(int topnet, int bangnet)
{
	switch (topnet) {
	case 0:
		mRadioNoTopnet.SetCheck(TRUE);
		mRadioMetalTopnet.SetCheck(FALSE);
		mRadioRebarTopnet.SetCheck(FALSE);
		mRadioPlasticTopnet.SetCheck(FALSE);
		break;
	case 1:
		mRadioNoTopnet.SetCheck(FALSE);
		mRadioMetalTopnet.SetCheck(TRUE);
		mRadioRebarTopnet.SetCheck(FALSE);
		mRadioPlasticTopnet.SetCheck(FALSE);
		break;
	case 2:
		mRadioNoTopnet.SetCheck(FALSE);
		mRadioMetalTopnet.SetCheck(FALSE);
		mRadioRebarTopnet.SetCheck(TRUE);
		mRadioPlasticTopnet.SetCheck(FALSE);
		break;
	case 3:
		mRadioNoTopnet.SetCheck(FALSE);
		mRadioMetalTopnet.SetCheck(FALSE);
		mRadioRebarTopnet.SetCheck(FALSE);
		mRadioPlasticTopnet.SetCheck(TRUE);
		break;
	default:
		break;
	}
	switch (bangnet)
	{
	case 0:
		mRadioNoBangnet.SetCheck(TRUE);
		mRadioMetalBangnet.SetCheck(FALSE);
		mRadioRebarBangnet.SetCheck(FALSE);
		mRadioPlasticBangnet.SetCheck(FALSE);
		break;
	case 1:
		mRadioNoBangnet.SetCheck(FALSE);
		mRadioMetalBangnet.SetCheck(TRUE);
		mRadioRebarBangnet.SetCheck(FALSE);
		mRadioPlasticBangnet.SetCheck(FALSE);
		break;
	case 2:		
		mRadioNoBangnet.SetCheck(FALSE);
		mRadioMetalBangnet.SetCheck(FALSE);
		mRadioRebarBangnet.SetCheck(TRUE);
		mRadioPlasticBangnet.SetCheck(FALSE);
		break;
	case 3:		
		mRadioNoBangnet.SetCheck(FALSE);
		mRadioMetalBangnet.SetCheck(FALSE);
		mRadioRebarBangnet.SetCheck(FALSE);
		mRadioPlasticBangnet.SetCheck(TRUE);
		break;
	default:
		break;
	}
}

void CParametersDialog::OnMoving(UINT fwSide, LPRECT lpRect)
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


HBRUSH CParametersDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	switch (pWnd->GetDlgCtrlID()) {
		case IDC_EDIT_TOP_BOLT_LENGTH:
		case IDC_EDIT_TOP_BOLT_NUMBER:
		case IDC_EDIT_TOP_BOLT_SPACE:
		case IDC_EDIT_TOP_BOLT_PITCH:
		case IDC_EDIT_TOP_BOLT_ALENGTH:
		case IDC_EDIT_LEFT_BOLT_LENGTH:
		case IDC_EDIT_LEFT_BOLT_NUMBER:
		case IDC_EDIT_LEFT_BOLT_SPACE:
		case IDC_EDIT_LEFT_BOLT_PITCH:
		case IDC_EDIT_LEFT_BOLT_ALENGTH:
		case IDC_EDIT_RIGHT_BOLT_LENGTH:
		case IDC_EDIT_RIGHT_BOLT_NUMBER:
		case IDC_EDIT_RIGHT_BOLT_SPACE:
		case IDC_EDIT_RIGHT_BOLT_PITCH:
		case IDC_EDIT_RIGHT_BOLT_ALENGTH:
		case IDC_EDIT_CABLE_LENGTH:
		case IDC_EDIT_CABLE_NUMBER:
		case IDC_EDIT_CABLE_SPACE:
		case IDC_EDIT_CABLE_PITCH:
		case IDC_EDIT_CABLE_ALENGTH:
			pDC->SetTextColor(RGB(255, 0, 0));
			break;
	}


	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
