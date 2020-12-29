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
//----- MethodChooseDialog.h : Declaration of the CMethodChooseDialog
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
#include "acui.h"
#include "afxwin.h"
#include "TheoreticalDialog.h"
#include "ExperienceDialog.h"
#include "LooseRangeDialog.h"
#include "TunnelChooseDialog.h"

//-----------------------------------------------------------------------------
class CMethodChooseDialog : public CAcUiDialog {
	DECLARE_DYNAMIC (CMethodChooseDialog)

public:
	CMethodChooseDialog (CWnd *pParent =NULL, HINSTANCE hInstance =NULL) ;

	enum { IDD = IDD_METHOD_CHOOSE_DIALOG} ;

protected:
	virtual void DoDataExchange (CDataExchange *pDX) ;
	afx_msg LRESULT OnAcadKeepFocus (WPARAM, LPARAM) ;

	DECLARE_MESSAGE_MAP()
private:
	CButton mRadioTheoretical;
	CButton mRadioExperience;
	CButton mRadioLooseRange;
	CButton mRadioExpert;
	CStatic mMethodChooseTitle;
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();

} ;
