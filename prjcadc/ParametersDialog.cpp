// (C) Copyright 2002-2007 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//

//-----------------------------------------------------------------------------
//----- ParametersDialog.cpp : Implementation of CParametersDialog
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "resource.h"
#include "ParametersDialog.h"

//-----------------------------------------------------------------------------
IMPLEMENT_DYNAMIC (CParametersDialog, CAcUiDialog)

BEGIN_MESSAGE_MAP(CParametersDialog, CAcUiDialog)
	ON_MESSAGE(WM_ACAD_KEEPFOCUS, OnAcadKeepFocus)
	ON_BN_CLICKED(IDC_CHECK_LEFT_BOLT, &CParametersDialog::OnBnClickedCheckLeftBolt)
	ON_BN_CLICKED(IDC_CHECK_RIGHT_BOLT, &CParametersDialog::OnBnClickedCheckRightBolt)
	ON_BN_CLICKED(IDC_CHECK_CABLE, &CParametersDialog::OnBnClickedCheckCable)
	ON_BN_CLICKED(IDOK, &CParametersDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK_TOP_BOLT, &CParametersDialog::OnBnClickedCheckTopBolt)
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------
CParametersDialog::CParametersDialog (CWnd *pParent /*=NULL*/, HINSTANCE hInstance /*=NULL*/): CAcUiDialog (CParametersDialog::IDD, pParent, hInstance) {
}

//-----------------------------------------------------------------------------
void CParametersDialog::DoDataExchange (CDataExchange *pDX) {
	CAcUiDialog::DoDataExchange(pDX);
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
}

//-----------------------------------------------------------------------------
//----- Needed for modeless dialogs to keep focus.
//----- Return FALSE to not keep the focus, return TRUE to keep the focus
LRESULT CParametersDialog::OnAcadKeepFocus (WPARAM, LPARAM) {
	return (TRUE) ;
}




void CParametersDialog::OnBnClickedCheckLeftBolt()
{
	// TODO: 在此添加控件通知处理程序代码
	if (mCheckLeftBolt.GetCheck() == TRUE)
	{
		  mEdtLeftBoltDiameter.EnableWindow(true);
		  mEdtLeftBoltLength.EnableWindow(true);
		  mEdtLeftBoltMaterial.EnableWindow(true);
		  mEdtLeftBoltTailing.EnableWindow(true);
		  mEdtLeftBoltNumber.EnableWindow(true);
		  mEdtLeftBoltSpace.EnableWindow(true);
		  mEdtLeftBoltPitch.EnableWindow(true);
		  mEdtLeftBoltALength.EnableWindow(true);
		  mEdtLeftBoltBeamWidth.EnableWindow(true);
		  mEdtLeftBoltBeamMaterial.EnableWindow(true);
		  mEdtLeftBoltPortraitBeamMaterial.EnableWindow(false);
		  mEdtLeftBoltPortraitBeamWidth.EnableWindow(false);
		  mEdtLeftBoltTrayLength.EnableWindow(true);
		  mEdtLeftBoltTrayMaterial.EnableWindow(true);
	}
	else
	{
		mEdtLeftBoltDiameter.EnableWindow(false);
		mEdtLeftBoltLength.EnableWindow(false);
		mEdtLeftBoltMaterial.EnableWindow(false);
		mEdtLeftBoltTailing.EnableWindow(false);
		mEdtLeftBoltNumber.EnableWindow(false);
		mEdtLeftBoltSpace.EnableWindow(false);
		mEdtLeftBoltPitch.EnableWindow(false);
		mEdtLeftBoltALength.EnableWindow(false);
		mEdtLeftBoltBeamWidth.EnableWindow(false);
		mEdtLeftBoltBeamMaterial.EnableWindow(false);
		mEdtLeftBoltTrayLength.EnableWindow(false);
		mEdtLeftBoltTrayMaterial.EnableWindow(false);
	}
}

void CParametersDialog::setRecTunnel(CRectangleTunnel t)
{
	recTunnel = t;
}

void CParametersDialog::setArcTunnel(CArcTunnel t)
{
	arcTunnel = t;
}

void CParametersDialog::setTrapTunnel(CTrapzoidTunnel t)
{
	trapTunnel = t;
}


void CParametersDialog::OnBnClickedCheckRightBolt()
{
	// TODO: 在此添加控件通知处理程序代码
	/*右帮锚杆disabled切换*/
	if (mCheckRightBolt.GetCheck() == TRUE)
	{
		mEdtRightBoltDiameter.EnableWindow(true);
		mEdtRightBoltLength.EnableWindow(true);
		mEdtRightBoltMaterial.EnableWindow(true);
		mEdtRightBoltTailing.EnableWindow(true);
		mEdtRightBoltNumber.EnableWindow(true);
		mEdtRightBoltSpace.EnableWindow(true);
		mEdtRightBoltPitch.EnableWindow(true);
		mEdtRightBoltALength.EnableWindow(true);
		mEdtRightBoltBeamWidth.EnableWindow(true);
		mEdtRightBoltBeamMaterial.EnableWindow(true);
		 mEdtRightBoltPortraitBeamMaterial.EnableWindow(true);
		 mEdtRightBoltPortraitBeamWidth.EnableWindow(true);
		mEdtRightBoltTrayLength.EnableWindow(true);
		mEdtRightBoltTrayMaterial.EnableWindow(true);

		CString cableLength, boltLength, cableAlength, cableDiameter;
		mEdtCableLength.GetWindowText(cableLength);
		mEdtCableDiameter.GetWindowText(cableDiameter);
		mEdtCableALength.GetWindowText(cableAlength);
		boltLength.Format(_T("%.0lf"), _ttoi(cableLength) / 2);
		mEdtRightBoltLength.SetWindowText(boltLength);
		mEdtRightBoltDiameter.SetWindowText(cableDiameter);
		mEdtRightBoltALength.SetWindowText(cableAlength);
		 mCheckTopBolt.SetCheck(false);
		 mCheckTopBolt.EnableWindow(false);

		 OnBnClickedCheckTopBolt();
	}
	else {
	  mEdtRightBoltDiameter.EnableWindow(false);
	  mEdtRightBoltLength.EnableWindow(false);
	  mEdtRightBoltMaterial.EnableWindow(false);
	  mEdtRightBoltTailing.EnableWindow(false);
	  mEdtRightBoltNumber.EnableWindow(false);
	  mEdtRightBoltSpace.EnableWindow(false);
	  mEdtRightBoltPitch.EnableWindow(false);
	  mEdtRightBoltALength.EnableWindow(false);
	  mEdtRightBoltBeamWidth.EnableWindow(false);
	  mEdtRightBoltBeamMaterial.EnableWindow(false);
	  mEdtRightBoltPortraitBeamMaterial.EnableWindow(false);
	  mEdtRightBoltPortraitBeamWidth.EnableWindow(false);
	  mEdtRightBoltTrayLength.EnableWindow(false);
	  mEdtRightBoltTrayMaterial.EnableWindow(false);

	  mCheckTopBolt.SetCheck(true);
	  mCheckTopBolt.EnableWindow(true);

	  OnBnClickedCheckTopBolt();

	}

}


void CParametersDialog::OnBnClickedCheckCable()
{
	// TODO: 在此添加控件通知处理程序代码
	if (mCheckCable.GetCheck() == TRUE)
	{
		  mEdtCableDiameter.EnableWindow(true);
		  mEdtCableLength.EnableWindow(true);
		  mEdtCableMaterial.EnableWindow(true);
		  mEdtCableTailing.EnableWindow(true);
		  mEdtCableNumber.EnableWindow(true);
		  mEdtCableSpace.EnableWindow(true);
		  mEdtCablePitch.EnableWindow(true);
		  mEdtCableALength.EnableWindow(true);
		  mEdtCableTrayLength.EnableWindow(true);
		  mEdtCableTrayMaterial.EnableWindow(true);
		  mEdtCableShuDiameter.EnableWindow(true);
		  mEdtCableShuLength.EnableWindow(true);
		  mEdtCableShuMaterial.EnableWindow(true);
	}
	else
	{
		  mEdtCableDiameter.EnableWindow(false);
		  mEdtCableLength.EnableWindow(false);
		  mEdtCableMaterial.EnableWindow(false);
		  mEdtCableTailing.EnableWindow(false);
		  mEdtCableNumber.EnableWindow(false);
		  mEdtCableSpace.EnableWindow(false);
		  mEdtCablePitch.EnableWindow(false);
		  mEdtCableALength.EnableWindow(false);
		  mEdtCableTrayLength.EnableWindow(false);
		  mEdtCableTrayMaterial.EnableWindow(false);
		  mEdtCableShuDiameter.EnableWindow(false);
		  mEdtCableShuLength.EnableWindow(false);
		  mEdtCableShuMaterial.EnableWindow(false);
	}
}


BOOL CParametersDialog::OnInitDialog()
{
	CAcUiDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	// 设置对话框居中显示
	CRect dlg;
	GetWindowRect(dlg);
	ScreenToClient(dlg);
	SetWindowPos(&wndTopMost, (GetSystemMetrics(SM_CXSCREEN) / 2) - (dlg.Width() / 2),
		(GetSystemMetrics(SM_CYSCREEN) / 2) - (dlg.Height() / 2), dlg.Width(), dlg.Height(),
		SWP_SHOWWINDOW);

	 mEdtTopBoltDiameter.SetWindowText(_T("18"));
	 mEdtTopBoltLength.SetWindowText(_T("1800"));
	 mEdtTopBoltMaterial.SetWindowText(_T("螺旋纹钢"));
	 mEdtTopBoltTailing.SetWindowText(_T("120"));
	 mEdtTopBoltNumber.SetWindowText(_T("7"));
	 mEdtTopBoltSpace.SetWindowText(_T("700"));
	 mEdtTopBoltPitch.SetWindowText(_T("800"));
	 mEdtTopBoltALength.SetWindowText(_T("700"));
	 mEdtTopBoltBeamWidth.SetWindowText(_T("50"));
	 mEdtTopBoltBeamMaterial.SetWindowText(_T("14号圆钢焊接"));
	 mEdtTopBoltTrayLength.SetWindowText(_T("150*150*10"));
	 mEdtTopBoltTrayMaterial.SetWindowText(_T("10mm拱形钢板"));
	 // 左帮锚杆
	 mEdtLeftBoltDiameter.SetWindowText(_T("18"));
	 mEdtLeftBoltLength.SetWindowText(_T("2000"));
	 mEdtLeftBoltMaterial.SetWindowText(_T("螺旋纹钢"));
	 mEdtLeftBoltTailing.SetWindowText(_T("120"));
	 mEdtLeftBoltNumber.SetWindowText(_T("3"));
	 mEdtLeftBoltSpace.SetWindowText(_T("1000"));
	 mEdtLeftBoltPitch.SetWindowText(_T("1000"));
	 mEdtLeftBoltALength.SetWindowText(_T("700"));
	 mEdtLeftBoltBeamWidth.SetWindowText(_T("50"));
	 mEdtLeftBoltBeamMaterial.SetWindowText(_T("14号圆钢焊接"));
	 mEdtLeftBoltTrayLength.SetWindowText(_T("150*150*10"));
	 mEdtLeftBoltTrayMaterial.SetWindowText(_T("10mm槽钢"));
	 // 右帮锚杆
	 mEdtRightBoltDiameter.SetWindowText(_T("18"));
	 mEdtRightBoltLength.SetWindowText(_T("2000"));
	 mEdtRightBoltMaterial.SetWindowText(_T("螺旋纹钢"));
	 mEdtRightBoltTailing.SetWindowText(_T("120"));
	 mEdtRightBoltNumber.SetWindowText(_T("3"));
	 mEdtRightBoltSpace.SetWindowText(_T("1000"));
	 mEdtRightBoltPitch.SetWindowText(_T("1000"));
	 mEdtRightBoltALength.SetWindowText(_T("700"));
	 mEdtRightBoltBeamWidth.SetWindowText(_T("50"));
	 mEdtRightBoltBeamMaterial.SetWindowText(_T("14号圆钢焊接"));
	 mEdtRightBoltTrayLength.SetWindowText(_T("150*150*10"));
	 mEdtRightBoltTrayMaterial.SetWindowText(_T("10mm槽钢"));
	 // 锚索
	 mEdtCableDiameter.SetWindowText(_T("15.24"));
	 mEdtCableLength.SetWindowText(_T("4500"));
	 mEdtCableMaterial.SetWindowText(_T("钢绞线"));
	 mEdtCableTailing.SetWindowText(_T("120"));
	 mEdtCableNumber.SetWindowText(_T("2"));
	 mEdtCableSpace.SetWindowText(_T("1200"));
	 mEdtCablePitch.SetWindowText(_T("2400"));
	 mEdtCableALength.SetWindowText(_T("1400"));
	 mEdtCableTrayLength.SetWindowText(_T("500"));
	 mEdtCableTrayMaterial.SetWindowText(_T("12槽钢"));
	 mEdtCableShuDiameter.SetWindowText(_T("28"));
	 mEdtCableShuLength.SetWindowText(_T("350"));
	 mEdtCableShuMaterial.SetWindowText(_T("Z2835"));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

// 初始化锚杆信息
CBolt CParametersDialog::InitBoltInfo(int flag) {
	CString diameter, length, material, tailing, number, space, pitch,
		aLength, beamWidth, beamMaterial,
		trayLength, trayMaterial;
	switch (flag)
	{
	case INIT_TOP_BOLT_INFO:
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
		mEdtTopBoltTrayLength.GetWindowText(trayLength);
		mEdtTopBoltTrayMaterial.GetWindowText(trayMaterial);
		break;
	case INIT_LEFT_BOLT_INFO:
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
		mEdtLeftBoltTrayLength.GetWindowText(trayLength);
		mEdtLeftBoltTrayMaterial.GetWindowText(trayMaterial);
		break;
	case INIT_RIGHT_BOLT_INFO:
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
		mEdtRightBoltTrayLength.GetWindowText(trayLength);
		mEdtRightBoltTrayMaterial.GetWindowText(trayMaterial);
		break;
	default:
		break;
	}

	CBolt bolt(_ttof(diameter), _ttof(length), material, _ttof(tailing), _ttoi(number), _ttof(space), _ttof(pitch),
		_ttof(aLength), _ttof(beamWidth), beamMaterial, trayLength, trayMaterial);
	return bolt;
}

// 初始化锚杆信息
CCable CParametersDialog::InitCableInfo()
{
	CString diameter, length, material, tailing, number, space, pitch,
		aLength, trayLength, trayMaterial, shuDiameter, shuLength, shuMaterial;
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
	return CCable(_ttof(diameter), _ttof(length), material, _ttof(tailing), _ttoi(number), _ttof(space), _ttof(pitch),
		_ttof(aLength), _ttof(trayLength), trayMaterial, _ttof(shuDiameter), _ttof(shuLength), shuMaterial);
}

void CParametersDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	acutPrintf(_T("\n button clicked!"));
	CBolt topBolt = InitBoltInfo(INIT_TOP_BOLT_INFO);
	switch (flag)
	{
	case REC_TUNNEL_FLAG:
		acutPrintf(_T("\n choose res tunnel;"));
		recTunnel.DrawTunnel();
		recTunnel.DrawTopBolt(topBolt);
		recTunnel.DrawTopTuoLiang(topBolt);
		recTunnel.DrawTopViewNet(topBolt);
		if (mCheckLeftBolt.GetCheck() == TRUE)
		{
			CBolt leftBolt = InitBoltInfo(INIT_LEFT_BOLT_INFO);
			recTunnel.DrawLeftBolt(leftBolt);
			recTunnel.DrawLeftTuoLiang(leftBolt);
			recTunnel.DrawLeftViewNet(leftBolt);
		}
		if (mCheckRightBolt.GetCheck() == TRUE)
		{
			CBolt RightBolt = InitBoltInfo(INIT_RIGHT_BOLT_INFO);
			recTunnel.DrawRightBolt(RightBolt);
			recTunnel.DrawRightTuoLiang(RightBolt);
			recTunnel.DrawRightViewNet(RightBolt);
		}
		if (mCheckCable.GetCheck() == TRUE) {
			CCable mCable = InitCableInfo();
			recTunnel.DrawCable(mCable);
		}
		break;
	case ARC_TUNNEL_FLAG:
		acutPrintf(_T("\n choose arc tunnel;"));

		arcTunnel.DrawTunnel();
		arcTunnel.DrawTopBolt(topBolt);
		arcTunnel.DrawTopTuoLiang(topBolt);
		arcTunnel.DrawTopViewNet(topBolt);
		if (mCheckLeftBolt.GetCheck() == TRUE || mCheckRightBolt.GetCheck() == TRUE)
		{
			CRectangleTunnel * tRecTunnel = new CRectangleTunnel(arcTunnel.GetWidth(), arcTunnel.GetWallHeight(),
				arcTunnel.GetTopBoltAngle(), arcTunnel.GetLeftBoltAngle(), arcTunnel.GetRightBoltAngle());
			if (mCheckLeftBolt.GetCheck() == TRUE) {
				CBolt leftBolt = InitBoltInfo(INIT_LEFT_BOLT_INFO);

				tRecTunnel->DrawLeftBolt(leftBolt);
				tRecTunnel->DrawLeftTuoLiang(leftBolt);
				tRecTunnel->DrawLeftViewNet(leftBolt);
			}
			if (mCheckRightBolt.GetCheck() == TRUE)
			{
				CBolt RightBolt = InitBoltInfo(INIT_RIGHT_BOLT_INFO);
				tRecTunnel->DrawRightBolt(RightBolt);
				tRecTunnel->DrawRightTuoLiang(RightBolt);
				tRecTunnel->DrawRightViewNet(RightBolt);
			}
		}
		if (mCheckCable.GetCheck() == TRUE) {
			CCable mCable = InitCableInfo();
			arcTunnel.DrawCable(mCable);
		}
		break;
	case TRAP_TUNNEL_FLAG:
		acutPrintf(_T("\n choose trap tunnel;"));

		trapTunnel.DrawTunnel();
		trapTunnel.DrawTopBolt(topBolt);
		trapTunnel.DrawTopTuoLiang(topBolt);
		trapTunnel.DrawTopViewNet(topBolt);
		if (mCheckLeftBolt.GetCheck() == TRUE)
		{
			CBolt leftBolt = InitBoltInfo(INIT_LEFT_BOLT_INFO);
			trapTunnel.DrawLeftBolt(leftBolt);
			trapTunnel.DrawLeftTuoLiang(leftBolt);
			trapTunnel.DrawLeftViewNet(leftBolt);
		}
		if (mCheckRightBolt.GetCheck() == TRUE)
		{
			CBolt RightBolt = InitBoltInfo(INIT_RIGHT_BOLT_INFO);
			trapTunnel.DrawRightBolt(RightBolt);
			trapTunnel.DrawRightTuoLiang(RightBolt);
			trapTunnel.DrawRightViewNet(RightBolt);
		}
		if (mCheckCable.GetCheck() == TRUE) {
			CCable mCable = InitCableInfo();
			trapTunnel.DrawCable(mCable);
		}
		break;
	default:
		break;
	}
}


void CParametersDialog::OnBnClickedCheckTopBolt()
{
	// TODO: 在此添加控件通知处理程序代码
	if (mCheckTopBolt.GetCheck() == TRUE)
	{
		mEdtTopBoltDiameter.EnableWindow(true);
		mEdtTopBoltLength.EnableWindow(true);
		mEdtTopBoltMaterial.EnableWindow(true);
		mEdtTopBoltTailing.EnableWindow(true);
		mEdtTopBoltNumber.EnableWindow(true);
		mEdtTopBoltSpace.EnableWindow(true);
		mEdtTopBoltPitch.EnableWindow(true);
		mEdtTopBoltALength.EnableWindow(true);
		mEdtTopBoltBeamWidth.EnableWindow(true);
		mEdtTopBoltBeamMaterial.EnableWindow(true);
		mEdtTopBoltPortraitBeamMaterial.EnableWindow(true);
		mEdtTopBoltPortraitBeamWidth.EnableWindow(true);
		mEdtTopBoltTrayLength.EnableWindow(true);
		mEdtTopBoltTrayMaterial.EnableWindow(true);
	}
	else {
		mEdtTopBoltDiameter.EnableWindow(false);
		mEdtTopBoltLength.EnableWindow(false);
		mEdtTopBoltMaterial.EnableWindow(false);
		mEdtTopBoltTailing.EnableWindow(false);
		mEdtTopBoltNumber.EnableWindow(false);
		mEdtTopBoltSpace.EnableWindow(false);
		mEdtTopBoltPitch.EnableWindow(false);
		mEdtTopBoltALength.EnableWindow(false);
		mEdtTopBoltBeamWidth.EnableWindow(false);
		mEdtTopBoltBeamMaterial.EnableWindow(false);
		mEdtTopBoltPortraitBeamMaterial.EnableWindow(false);
		mEdtTopBoltPortraitBeamWidth.EnableWindow(false);
		mEdtTopBoltTrayLength.EnableWindow(false);
		mEdtTopBoltTrayMaterial.EnableWindow(false);
	}
}
