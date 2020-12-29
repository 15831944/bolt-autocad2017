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
//----- AverageDialog.h : Declaration of the CAverageDialog
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
#include "acui.h"
#include "afxwin.h"
#include "DrawUtil.h"

//-----------------------------------------------------------------------------
class CAverageDialog : public CAcUiDialog {
	DECLARE_DYNAMIC (CAverageDialog)

public:
	CAverageDialog (CWnd *pParent =NULL, HINSTANCE hInstance =NULL) ;

	enum { IDD = IDD_AVERAGE_DIALOG} ;

private:
	CEdit mEdtTopCompressive;
	CEdit mEdtTopCohesion;
	CEdit mEdtTopInternalFriction;
	CEdit mEdtTunnelCohesion;
	CEdit mEdtTunnelCompressive;
	CEdit mEdtTunnelInternal;
	CEdit mEdtTunnelLithology;
	CEdit mEdtTunnelThickness;
	CEdit mEdtBottomCohesion;
	CEdit mEdtBottomCompressive;
	CEdit mEdtBottomElasticity;
	CEdit mEdtBottomLithology;
	CEdit mEdtBottomPoisson;
	CEdit mEdtBottomThickness;
protected:
	virtual void DoDataExchange (CDataExchange *pDX) ;
	afx_msg LRESULT OnAcadKeepFocus (WPARAM, LPARAM) ;

	DECLARE_MESSAGE_MAP()
private:
	CStatic mAverageTitle;
public:
	virtual BOOL OnInitDialog();
} ;
