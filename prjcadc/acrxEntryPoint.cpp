// (C) Copyright 2002-2012 by Autodesk, Inc. 
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
//----- acrxEntryPoint.cpp
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "resource.h"
#include "DrawUtil.h"
#include "ProjectBuilder.h"
#include "DrawArcProject.h"


//-----------------------------------------------------------------------------
#define szRDS _RXST("ING")


//CDockControlBar* gDlgBar = NULL;



//-----------------------------------------------------------------------------
//----- ObjectARX EntryPoint
class CprjcadcApp : public AcRxArxApp {

public:
	CprjcadcApp () : AcRxArxApp () {}

	virtual AcRx::AppRetCode On_kInitAppMsg (void *pkt) {
		// TODO: Load dependencies here

		// You *must* call On_kInitAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kInitAppMsg (pkt) ;
		
		// TODO: Add your initialization code here
		
		INGMyGroupMyCommand();

		return (retCode) ;
	}

	virtual AcRx::AppRetCode On_kUnloadAppMsg (void *pkt) {
		// TODO: Add your code here

		// You *must* call On_kUnloadAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kUnloadAppMsg (pkt) ;

		// TODO: Unload dependencies here
		//手动销毁可停靠窗体
	

		return (retCode) ;
	}

	virtual void RegisterServerComponents () {
	}

	static void DrawRectanglePaper(CTunnelProject *project) {

		CRecProjectBuilder::GetInstance()->BuildTunnelFlag();
		CRecProjectBuilder::GetInstance()->BuildParameters();
		//CRecProjectBuilder::GetInstance()->BuildProject();

		CRectangleTunnel *pRec = CRecProjectBuilder::GetInstance()->GetRecTunnel();
		pRec->DrawProject(*project);
		pRec->DrawTableBoltPm();
		pRec->DrawTunnel();
		if (pRec->GetHasTopBolt() == true)
		{
			pRec->DrawTopBolt(*pRec->GetTopBolt());
			pRec->DrawTopTuoLiang(*pRec->GetTopBolt());
			pRec->DrawTopViewNet(*pRec->GetTopBolt());
		}
		// 右锚杆参数代表全锚索
		else if (pRec->GetHasRightBolt() == true) {
			pRec->DrawTopBolt(
				*pRec->GetRightBolt()
			);
			pRec->DrawTopTuoLiang(
				*pRec->GetRightBolt()
			);

			pRec->DrawTopViewNet(
				*pRec->GetRightBolt()
			);
		}

		if (pRec->GetHasLeftBolt() == true)
		{
			pRec->DrawBangBolt();
		}
		// 绘制锚索
		if (pRec->GetHasCable() == true) {
			pRec->DrawCable(*pRec->GetCable());
		}
		// 若支护方式不是默认的锚杆（索）支护
		if (pRec->GetZhihuWay() > 1) {
		pRec->DrawThickness();
		}
	}

	static void DrawArcPaper(CTunnelProject* project) {
		CArcProjectBuilder::GetInstance()->BuildTunnelFlag();
		CArcProjectBuilder::GetInstance()->BuildParameters();
		CArcTunnel *pArc = CArcProjectBuilder::GetInstance()->GetArcTunnel();
		pArc = CArcProjectBuilder::GetInstance()->GetArcTunnel();
		pArc->DrawProject(*project);
		pArc->DrawTunnel();
		pArc->DrawTableBoltPm();
		if (pArc->GetHasTopBolt() == true)
		{
			pArc->DrawTopBolt(*pArc->GetTopBolt());
			pArc->DrawTopTuoLiang(*pArc->GetTopBolt());
			pArc->DrawTopViewNet(*pArc->GetTopBolt());

		}
		// 右锚杆参数代表全锚索
		else if (pArc->GetHasRightBolt() == true) {
			pArc->DrawTopBolt(
				*pArc->GetRightBolt()
			);
			pArc->DrawTopTuoLiang(
				*pArc->GetRightBolt()
			);

			pArc->DrawTopViewNet(
				*pArc->GetRightBolt()
			);
		}

		if (pArc->GetHasLeftBolt() == true)
		{
			pArc->DrawBangBolt();
		}
		// 绘制锚索
		if (pArc->GetHasCable() == true) {
			pArc->DrawCable();
		}
		// 若支护方式不是默认的锚杆（索）支护
		if (pArc->GetZhihuWay() > 1) {
			pArc->DrawThickness();
		}
	}

	static void DrawTrapPaper(CTunnelProject* project) {
		CTrapProjectBuilder::GetInstance()->BuildTunnelFlag();
		CTrapProjectBuilder::GetInstance()->BuildParameters();
		//CTrapProjectBuilder::GetInstance()->BuildProject();

		CTrapzoidTunnel *pTrap = CTrapProjectBuilder::GetInstance()->GetTrapTunnel();
		pTrap->DrawProject(*project);
		pTrap->DrawTableBoltPm();
		pTrap->DrawTunnel();
		if (pTrap->GetHasTopBolt() == true)
		{
			pTrap->DrawTopBolt(*pTrap->GetTopBolt());
			pTrap->DrawTopTuoLiang(*pTrap->GetTopBolt());
			pTrap->DrawTopViewNet(*pTrap->GetTopBolt());
		}
		// 右锚杆参数代表全锚索
		else if (pTrap->GetHasRightBolt() == true) {
			pTrap->DrawTopBolt(
				*pTrap->GetRightBolt()
			);
			pTrap->DrawTopTuoLiang(
				*pTrap->GetRightBolt()
			);

			pTrap->DrawTopViewNet(
				*pTrap->GetRightBolt()
			);
		}

		if (pTrap->GetHasLeftBolt() == true)
		{
			pTrap->DrawBangBolt();
		}
		// 绘制锚索
		if (pTrap->GetHasCable() == true) {
			pTrap->DrawCable(*pTrap->GetCable());
		}
		// 若支护方式不是默认的锚杆（索）支护
		if (pTrap->GetZhihuWay() > 1) {
		pTrap->DrawThickness();
		}
	}
	
	// The ACED_ARXCOMMAND_ENTRY_AUTO macro can be applied to any static member 
	// function of the CprjcadcApp class.
	// The function should take no arguments and return nothing.
	//
	// NOTE: ACED_ARXCOMMAND_ENTRY_AUTO has overloads where you can provide resourceid and
	// have arguments to define context and command mechanism.
	
	// ACED_ARXCOMMAND_ENTRY_AUTO(classname, group, globCmd, locCmd, cmdFlags, UIContext)
	// ACED_ARXCOMMAND_ENTRYBYID_AUTO(classname, group, globCmd, locCmdId, cmdFlags, UIContext)
	// only differs that it creates a localized name using a string in the resource file
	//   locCmdId - resource ID for localized command

	// Modal Command with localized name
	// ACED_ARXCOMMAND_ENTRY_AUTO(CprjcadcApp, INGMyGroup, MyCommand, MyCommandLocal, ACRX_CMD_MODAL)
	static void INGMyGroupMyCommand () {
		// Put your command code here
		//防止资源冲突
		CAcModuleResourceOverride resOverride;

		//测试绘图代码
		AcGePoint2d ptStart(0, 0), ptEnd(100, 100);
		//CDrawUtil::AddPolyLine(ptStart, ptEnd, 1);
		AcGePoint2d ptLeftBottom(25,5);
		//绘制矩形外框
		CDrawUtil::AddRectangle(ptStart, 420, 297, 2);
		CDrawUtil::AddRectangle(ptLeftBottom, 390, 287, 0.3);

		CTunnelProject *project = ProjectBuilder().BuildProject();
		acutPrintf(_T(""), "tunnel type: %d\n", project->GetTunnelType());


		switch (project->GetTunnelType())
		{
		case 1:
			DrawRectanglePaper(project);
			break;
		case 2:
			DrawArcPaper(project);
			break;
		case 3:
			DrawTrapPaper(project);
			break;
		default:
			break;
		}


		
	}

	// 指定命令行
	static void INGMyGroupStartApp() {
		// Put your command code here
		//类似一个全局变量

		CAcModuleResourceOverride resOverride;

		//以非模态方式启动对话框

	}


	// Modal Command with pickfirst selection
	// ACED_ARXCOMMAND_ENTRY_AUTO(CprjcadcApp, INGMyGroup, MyPickFirst, MyPickFirstLocal, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET)
	static void INGMyGroupMyPickFirst () {
		ads_name result ;
		int iRet =acedSSGet (ACRX_T("_I"), NULL, NULL, NULL, result) ;
		if ( iRet == RTNORM )
		{
			// There are selected entities
			// Put your command using pickfirst set code here
		}
		else
		{
			// There are no selected entities
			// Put your command code here
		}
	}

	// Application Session Command with localized name
	// ACED_ARXCOMMAND_ENTRY_AUTO(CprjcadcApp, INGMyGroup, MySessionCmd, MySessionCmdLocal, ACRX_CMD_MODAL | ACRX_CMD_SESSION)
	static void INGMyGroupMySessionCmd () {
		// Put your command code here
	}

	// The ACED_ADSFUNCTION_ENTRY_AUTO / ACED_ADSCOMMAND_ENTRY_AUTO macros can be applied to any static member 
	// function of the CprjcadcApp class.
	// The function may or may not take arguments and have to return RTNORM, RTERROR, RTCAN, RTFAIL, RTREJ to AutoCAD, but use
	// acedRetNil, acedRetT, acedRetVoid, acedRetInt, acedRetReal, acedRetStr, acedRetPoint, acedRetName, acedRetList, acedRetVal to return
	// a value to the Lisp interpreter.
	//
	// NOTE: ACED_ADSFUNCTION_ENTRY_AUTO / ACED_ADSCOMMAND_ENTRY_AUTO has overloads where you can provide resourceid.
	
	//- ACED_ADSFUNCTION_ENTRY_AUTO(classname, name, regFunc) - this example
	//- ACED_ADSSYMBOL_ENTRYBYID_AUTO(classname, name, nameId, regFunc) - only differs that it creates a localized name using a string in the resource file
	//- ACED_ADSCOMMAND_ENTRY_AUTO(classname, name, regFunc) - a Lisp command (prefix C:)
	//- ACED_ADSCOMMAND_ENTRYBYID_AUTO(classname, name, nameId, regFunc) - only differs that it creates a localized name using a string in the resource file

	// Lisp Function is similar to ARX Command but it creates a lisp 
	// callable function. Many return types are supported not just string
	// or integer.
	// ACED_ADSFUNCTION_ENTRY_AUTO(CprjcadcApp, MyLispFunction, false)
	static int ads_MyLispFunction () {
		//struct resbuf *args =acedGetArgs () ;
		
		// Put your command code here

		//acutRelRb (args) ;
		
		// Return a value to the AutoCAD Lisp Interpreter
		// acedRetNil, acedRetT, acedRetVoid, acedRetInt, acedRetReal, acedRetStr, acedRetPoint, acedRetName, acedRetList, acedRetVal

		return (RTNORM) ;
	}
	
} ;

//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(CprjcadcApp)

ACED_ARXCOMMAND_ENTRY_AUTO(CprjcadcApp, INGMyGroup, MyCommand, MyCommandLocal, ACRX_CMD_MODAL, NULL)
//StartApp命令
ACED_ARXCOMMAND_ENTRY_AUTO(CprjcadcApp, INGMyGroup, StartApp, StartApp, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CprjcadcApp, INGMyGroup, MyPickFirst, MyPickFirstLocal, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CprjcadcApp, INGMyGroup, MySessionCmd, MySessionCmdLocal, ACRX_CMD_MODAL | ACRX_CMD_SESSION, NULL)
ACED_ADSSYMBOL_ENTRY_AUTO(CprjcadcApp, MyLispFunction, false)

