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
//----- ParametersDialog.h : Declaration of the CParametersDialog
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
#include "acui.h"
#include "resource.h"
#include "afxwin.h"
#include "RectangleTunnel.h"
#include "ArcTunnel.h"
#include "TrapzoidTunnel.h"
#include "Bolt.h"
#include "Cable.h"

//-----------------------------------------------------------------------------

const int REC_TUNNEL_FLAG = 0;
const int ARC_TUNNEL_FLAG = 1;
const int TRAP_TUNNEL_FLAG = 2;
const int INIT_TOP_BOLT_INFO = 0;
const int INIT_LEFT_BOLT_INFO = 1;
const int INIT_RIGHT_BOLT_INFO = 2;

class CParametersDialog : public CAcUiDialog {
	DECLARE_DYNAMIC (CParametersDialog)

public:
	CParametersDialog (CWnd *pParent =NULL, HINSTANCE hInstance =NULL) ;

	enum { IDD = IDD_PARAMETERS_DIALOG} ;

protected:
	virtual void DoDataExchange (CDataExchange *pDX) ;
	afx_msg LRESULT OnAcadKeepFocus (WPARAM, LPARAM) ;

	DECLARE_MESSAGE_MAP()
private:
	CRectangleTunnel recTunnel;
	CArcTunnel arcTunnel ;
	CTrapzoidTunnel trapTunnel;
	CButton mCheckLeftBolt;
	CButton mCheckRightBolt;
	CButton mCheckCable;
	static int flag; // ½«flagÉèÖÃÎª¾²Ì¬³ÉÔ±±äÁ¿

public:
	afx_msg void OnBnClickedCheckLeftBolt();
	void setRecTunnel(CRectangleTunnel t);
	void setArcTunnel(CArcTunnel t);
	void setTrapTunnel(CTrapzoidTunnel t);
	void setTunnelFlag(int f) { flag = f; };
	int getTunnelFlag() const { return flag; };
private:
	/* ¶¥²¿Ãª¸Ë */
	CEdit mEdtTopBoltDiameter;
	CEdit mEdtTopBoltLength;
	CEdit mEdtTopBoltMaterial;
	CEdit mEdtTopBoltTailing;
	CEdit mEdtTopBoltNumber;
	CEdit mEdtTopBoltSpace;
	CEdit mEdtTopBoltPitch;
	CEdit mEdtTopBoltALength;
	CEdit mEdtTopBoltBeamWidth;
	CEdit mEdtTopBoltBeamMaterial;
	CEdit mEdtTopBoltPortraitBeamMaterial;
	CEdit mEdtTopBoltPortraitBeamWidth;
	CEdit mEdtTopBoltTrayLength;
	CEdit mEdtTopBoltTrayMaterial;
	/*×ó°ïÃª¸Ë*/
	CEdit mEdtLeftBoltDiameter;
	CEdit mEdtLeftBoltLength;
	CEdit mEdtLeftBoltMaterial;
	CEdit mEdtLeftBoltTailing;
	CEdit mEdtLeftBoltNumber;
	CEdit mEdtLeftBoltSpace;
	CEdit mEdtLeftBoltPitch;
	CEdit mEdtLeftBoltALength;
	CEdit mEdtLeftBoltBeamWidth;
	CEdit mEdtLeftBoltBeamMaterial;
	CEdit mEdtLeftBoltPortraitBeamMaterial;
	CEdit mEdtLeftBoltPortraitBeamWidth;
	CEdit mEdtLeftBoltTrayLength;
	CEdit mEdtLeftBoltTrayMaterial;

	/*ÓÒ°ïÃª¸Ë*/
	CEdit mEdtRightBoltDiameter;
	CEdit mEdtRightBoltLength;
	CEdit mEdtRightBoltMaterial;
	CEdit mEdtRightBoltTailing;
	CEdit mEdtRightBoltNumber;
	CEdit mEdtRightBoltSpace;
	CEdit mEdtRightBoltPitch;
	CEdit mEdtRightBoltALength;
	CEdit mEdtRightBoltBeamWidth;
	CEdit mEdtRightBoltBeamMaterial;
	CEdit mEdtRightBoltPortraitBeamMaterial;
	CEdit mEdtRightBoltPortraitBeamWidth;
	CEdit mEdtRightBoltTrayLength;
	CEdit mEdtRightBoltTrayMaterial;

	/*ÃªË÷*/
	CEdit mEdtCableDiameter;
	CEdit mEdtCableLength;
	CEdit mEdtCableMaterial;
	CEdit mEdtCableTailing;
	CEdit mEdtCableNumber;
	CEdit mEdtCableSpace;
	CEdit mEdtCablePitch;
	CEdit mEdtCableALength;
	CEdit mEdtCableTrayLength;
	CEdit mEdtCableTrayMaterial;
	CEdit mEdtCableShuDiameter;
	CEdit mEdtCableShuLength;
	CEdit mEdtCableShuMaterial;

public:
	afx_msg void OnBnClickedCheckRightBolt();
	afx_msg void OnBnClickedCheckCable();
	virtual BOOL OnInitDialog();
	afx_msg
	void OnBnClickedOk();
private:
	CBolt InitBoltInfo(int flag);
	CCable InitCableInfo();
	CButton mCheckTopBolt;
public:
	afx_msg void OnBnClickedCheckTopBolt();

} ;

