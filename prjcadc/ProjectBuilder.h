#pragma once
#include "StdAfx.h"
#include "ArcTunnel.h"
#include "CFileUtil.h"
#include "Bolt.h"
#include "Cable.h"
#include "SimpleIni.h"
#include "TunnelProject.h"
#include "TrapzoidTunnel.h"


class ProjectBuilder
{
public:

	ProjectBuilder() {
		filepath = CFileUtil::GetAppRegeditPath() + _T("\\ini\\bridge.ini");
	};
	~ProjectBuilder() {};

	virtual CTunnelProject* BuildProject() {
		CSimpleIni mProjectIni;
		CString strProject("Project");
		CString strPaperTitle("PaperTitle");
		CString strPaperDescription("PaperDescription");
		CString strScaleNumber("ScaleNumber");
		CString strPaperSize("PaperSize");
		CString strPaperNumber("PaperNumber");

		CString strDesigner("Designer");
		CString strDate("Date");
		CString strChecker("Checker");
		CString strCheckDate("CheckDate");
		CString strDesignApart("DesignApart");
		CString strDevelopApart("DevelopApart");

		CString strTunnelType("TunnelType");
		SI_Error rc = mProjectIni.LoadFile(filepath);
		if (rc < 0) return false; // 若加载文件出错，返回false
		mTunnelProject = new CTunnelProject();
		mTunnelProject->SetPaperTitle(mProjectIni.GetValue(strProject, _T("PaperTitle")));
		mTunnelProject->SetPaperDescription(mProjectIni.GetValue(strProject, _T("PaperDescription")));
		mTunnelProject->SetScaleNumber(mProjectIni.GetValue(strProject, _T("ScaleNumber")));
		mTunnelProject->SetPaperSize(mProjectIni.GetValue(strProject, _T("PaperSize")));
		mTunnelProject->SetPaperNumber(mProjectIni.GetValue(strProject, _T("PaperNumber")));

		mTunnelProject->SetDesigner(mProjectIni.GetValue(strProject, _T("Designer")));
		mTunnelProject->SetDate(mProjectIni.GetValue(strProject, _T("Date")));
		mTunnelProject->SetChecker(mProjectIni.GetValue(strProject, _T("Checker")));
		mTunnelProject->SetCheckDate(mProjectIni.GetValue(strProject, _T("CheckDate")));
		mTunnelProject->SetDesignApart(mProjectIni.GetValue(strProject, _T("DesignApart")));
		mTunnelProject->SetDevelopApart(mProjectIni.GetValue(strProject, _T("DevelopApart")));
		mTunnelProject->SetTunnelType(mProjectIni.GetLongValue(strProject, _T("TunnelType")));
		
		return mTunnelProject;
	};

	CCable * BuildCableFromIni() {
		CSimpleIni mProjectIni;
		SI_Error rc = mProjectIni.LoadFile(filepath);
		if (rc < 0) return nullptr; // 若加载文件出错，返回false

		CString strCable("Cable");
		CString strDiameter("Diameter");
		CString strLength("Length");
		CString strMaterial("Material");
		CString strTailing("Tailing");
		CString strNumber("Number");
		CString strSpace("Space");
		CString strPitch("Pitch");
		CString strALength("ALength");
		CString strTrayLength("TrayLength");
		CString strTrayMaterial("TrayMaterial");
		CString strShuDiameter("ShuDiameter");
		CString strShuLength("ShuLength");
		CString strShuMaterial("ShuMaterial");

		CCable * cable = new CCable();
		cable->setDiameter(mProjectIni.GetDoubleValue(strCable, strDiameter));
		cable->setLength(mProjectIni.GetDoubleValue(strCable, strLength));
		cable->setMaterial(mProjectIni.GetValue(strCable, strMaterial));
		cable->setTailing(mProjectIni.GetDoubleValue(strCable, strTailing));
		cable->setNumber(mProjectIni.GetLongValue(strCable, strNumber));
		cable->setSpace(mProjectIni.GetDoubleValue(strCable, strSpace));
		cable->setPitch(mProjectIni.GetDoubleValue(strCable, strPitch));
		cable->setALength(mProjectIni.GetDoubleValue(strCable, strALength));

		cable->setTrayLength(mProjectIni.GetDoubleValue(strCable, strTrayLength));
		cable->setTrayMaterial(mProjectIni.GetValue(strCable, strTrayMaterial));

		cable->setShuDiameter(mProjectIni.GetDoubleValue(strCable, strShuDiameter));
		cable->setShuLength(mProjectIni.GetDoubleValue(strCable, strShuLength));
		cable->setShuMaterial(mProjectIni.GetValue(strCable, strShuMaterial));
		return cable;

	};

	CBolt * BuildBoltFromIni(CString derection) {

		CSimpleIni mProjectIni;
		SI_Error rc = mProjectIni.LoadFile(filepath);
		if (rc < 0) return nullptr; // 若加载文件出错，返回false

		CString strDiameter("Diameter");
		CString strLength("Length");
		CString strMaterial("Material");
		CString strTailing("Tailing");
		CString strNumber("Number");
		CString strSpace("Space");
		CString strPitch("Pitch");
		CString strALength("ALength");
		CString strBeamWidth("BeamWidth");
		CString strBeamMaterial("BeamMaterial");
		CString strPortBeamWidth("PortBeamWidth");
		CString strPortBeamMaterial("PortBeamMaterial");
		CString strTrayLength("TrayLength");
		CString strTrayMaterial("TrayMaterial");
		CBolt * bolt = new CBolt();
		bolt->setDiameter(mProjectIni.GetDoubleValue(derection, strDiameter));
		bolt->setLength(mProjectIni.GetDoubleValue(derection, strLength));
		bolt->setMaterial(mProjectIni.GetValue(derection, strMaterial));
		bolt->setTailing(mProjectIni.GetDoubleValue(derection, strTailing));
		bolt->setNumber(mProjectIni.GetLongValue(derection, strNumber));
		bolt->setSpace(mProjectIni.GetDoubleValue(derection, strSpace));
		bolt->setPitch(mProjectIni.GetDoubleValue(derection, strPitch));
		bolt->setALength(mProjectIni.GetDoubleValue(derection, strALength));
		bolt->setBeamWidth(mProjectIni.GetDoubleValue(derection, strBeamWidth));
		bolt->setBeamMaterial(mProjectIni.GetValue(derection, strBeamMaterial));
		bolt->setPortBeamWidth(mProjectIni.GetDoubleValue(derection, strPortBeamWidth));
		bolt->setPortBeamMaterial(mProjectIni.GetValue(derection, strPortBeamWidth));
		bolt->setTrayLength(mProjectIni.GetValue(derection, strTrayLength));
		bolt->setTrayMaterial(mProjectIni.GetValue(derection, strTrayMaterial));
		return bolt;
	};
protected:
	CTunnelProject * mTunnelProject;
	CString filepath;
};

class CArcProjectBuilder : public ProjectBuilder
{
public:
	CArcProjectBuilder() {
		mArcTunnel = new CArcTunnel();
		//mTunnelProject = new CTunnelProject();
	};
	~CArcProjectBuilder() {
		delete mArcTunnel;
		delete mTunnelProject;
	};
	static CArcProjectBuilder * GetInstance() {
		static CArcProjectBuilder instance;
		return &instance;
	};

	void  SetArcTunnel(CArcTunnel * arc) { mArcTunnel = arc; };

	CArcTunnel * GetArcTunnel() const { return mArcTunnel; };
	CTunnelProject * GetTunnelProject() const { return mTunnelProject; };

	virtual bool BuildTunnelFlag() {
		CSimpleIni mProjectIni;
		CString strArc("Arc");
		CString strFlag("Flag");
		SI_Error rc = mProjectIni.LoadFile(filepath);
		if (rc < 0) return false; // 若加载文件出错，返回false

		// 初始化拱形巷道基本信息和 FLAG 标志
		mArcTunnel->SetWidth(mProjectIni.GetDoubleValue(strArc, _T("Width")));
		mArcTunnel->SetArcHeight(mProjectIni.GetDoubleValue(strArc, _T("ArcHeight")));
		mArcTunnel->SetWallHeight(mProjectIni.GetDoubleValue(strArc, _T("WallHeight")));
		mArcTunnel->SetNormalToArc(mProjectIni.GetBoolValue(strArc, _T("IsNormalToArc")));

		mArcTunnel->SetZhihuWay(mProjectIni.GetLongValue(strFlag, _T("ZhihuWay")));
		mArcTunnel->SetHasRevertAngle(mProjectIni.GetBoolValue(strFlag, _T("HasRevertAngle")));
		mArcTunnel->SetCalMethod(mProjectIni.GetLongValue(strFlag, _T("CalMethod")));

		mArcTunnel->SetHasTopBolt(mProjectIni.GetBoolValue(strFlag, _T("HasTopBolt")));
		mArcTunnel->SetHasLeftBolt(mProjectIni.GetBoolValue(strFlag, _T("HasLeftBolt")));
		mArcTunnel->SetHasRightBolt(mProjectIni.GetBoolValue(strFlag, _T("HasRightBolt")));
		mArcTunnel->SetHasCable(mProjectIni.GetBoolValue(strFlag, _T("HasCable")));


		CString strRevertAngle("RevertAngle");
		//mArcTunnel->SetTopAngle(mProjectIni.GetDoubleValue(strRevertAngle, _T("TopAngle")));
		mArcTunnel->SetBangLeftAngle(mProjectIni.GetDoubleValue(strRevertAngle, _T("LeftAngle")));
		mArcTunnel->SetBangRightAngle(mProjectIni.GetDoubleValue(strRevertAngle, _T("RightAngle")));
		
		if (mArcTunnel->GetZhihuWay() > 1) {
			CString strThickness("Thickness");
			CString strConcreteThickness("ConcreteThickness");
			CString strQiThickness("QiThickness");

			mArcTunnel->SetConcreteThickness(mProjectIni.GetLongValue(strThickness, strConcreteThickness));
			mArcTunnel->SetQiThickness(mProjectIni.GetLongValue(strThickness, strQiThickness));
		}

		return true;
	};

	virtual bool BuildParameters() {

		CString strTopBolt("TopBolt");
		mArcTunnel->SetTopBolt(BuildBoltFromIni(strTopBolt));

		CString strLeftBolt("LeftBolt");
		mArcTunnel->SetLeftBolt(BuildBoltFromIni(strLeftBolt));

		CString strRightBolt("RightBolt");
		mArcTunnel->SetRightBolt(BuildBoltFromIni(strRightBolt));

		mArcTunnel->SetCable(BuildCableFromIni());

		return true;
	};

private:
	CArcTunnel *mArcTunnel;
};

class CRecProjectBuilder : public ProjectBuilder {
private:
	CRectangleTunnel *mRecTunnel;
public:
	CRecProjectBuilder() {
		mRecTunnel = new CRectangleTunnel();
		//mTunnelProject = new CTunnelProject();
	};
	~CRecProjectBuilder() {
		delete mRecTunnel;
		delete mTunnelProject;
	};
	static CRecProjectBuilder * GetInstance() {
		static CRecProjectBuilder instance;
		return &instance;
	};

	void  SetRecTunnel(CRectangleTunnel * rec) { mRecTunnel = rec; };

	CRectangleTunnel * GetRecTunnel() const { return mRecTunnel; };
	CTunnelProject * GetTunnelProject() const { return mTunnelProject; };

	virtual bool BuildTunnelFlag() {
		CSimpleIni mProjectIni;
		CString strRec("Rectangle");
		CString strFlag("Flag");
		SI_Error rc = mProjectIni.LoadFile(filepath);
		if (rc < 0) return false; // 若加载文件出错，返回false

		// 初始化矩形巷道基本信息和 FLAG 标志
		mRecTunnel->SetWidth(mProjectIni.GetDoubleValue(strRec, _T("Width")));
		mRecTunnel->SetHeight(mProjectIni.GetDoubleValue(strRec, _T("Height")));

		mRecTunnel->SetZhihuWay(mProjectIni.GetLongValue(strFlag, _T("ZhihuWay")));
		mRecTunnel->SetHasRevertAngle(mProjectIni.GetBoolValue(strFlag, _T("HasRevertAngle")));
		mRecTunnel->SetCalMethod(mProjectIni.GetLongValue(strFlag, _T("CalMethod")));

		mRecTunnel->SetHasTopBolt(mProjectIni.GetBoolValue(strFlag, _T("HasTopBolt")));
		mRecTunnel->SetHasLeftBolt(mProjectIni.GetBoolValue(strFlag, _T("HasLeftBolt")));
		mRecTunnel->SetHasRightBolt(mProjectIni.GetBoolValue(strFlag, _T("HasRightBolt")));
		mRecTunnel->SetHasCable(mProjectIni.GetBoolValue(strFlag, _T("HasCable")));

		CString strRevertAngle("RevertAngle");
		mRecTunnel->SetTopBoltAngle(mProjectIni.GetDoubleValue(strRevertAngle, _T("TopAngle")));
		mRecTunnel->SetLeftBoltAngle(mProjectIni.GetDoubleValue(strRevertAngle, _T("LeftAngle")));
		mRecTunnel->SetRightBoltAngle(mProjectIni.GetDoubleValue(strRevertAngle, _T("RightAngle")));

		mRecTunnel->SetBangTopAngle(mProjectIni.GetDoubleValue(strRevertAngle, _T("LeftAngle")));
		mRecTunnel->SetBangBottomAngle(mProjectIni.GetDoubleValue(strRevertAngle, _T("RightAngle")));

		if (mRecTunnel->GetZhihuWay() > 1) {
			CString strThickness("Thickness");
			CString strConcreteThickness("ConcreteThickness");
			CString strQiThickness("QiThickness");

			mRecTunnel->SetConcreteThickness(mProjectIni.GetLongValue(strThickness, strConcreteThickness));
			mRecTunnel->SetQiThickness(mProjectIni.GetLongValue(strThickness, strQiThickness));
		}

		return true;
	};

	virtual bool BuildParameters() {

		CString strTopBolt("TopBolt");
		mRecTunnel->SetTopBolt(BuildBoltFromIni(strTopBolt));

		CString strLeftBolt("LeftBolt");
		mRecTunnel->SetLeftBolt(BuildBoltFromIni(strLeftBolt));

		CString strRightBolt("RightBolt");
		mRecTunnel->SetRightBolt(BuildBoltFromIni(strRightBolt));

		mRecTunnel->SetCable(BuildCableFromIni());

		return true;
	};
};

class CTrapProjectBuilder : public ProjectBuilder {
private:
	CTrapzoidTunnel *mTrapTunnel;
public:
	CTrapProjectBuilder() {
		mTrapTunnel = new CTrapzoidTunnel();
		//mTunnelProject = new CTunnelProject();
	};
	~CTrapProjectBuilder() {
		delete mTrapTunnel;
		delete mTunnelProject;
	};
	static CTrapProjectBuilder * GetInstance() {
		static CTrapProjectBuilder instance;
		return &instance;
	};

	void  SetTrapTunnel(CTrapzoidTunnel * rec) { mTrapTunnel = rec; };

	CTrapzoidTunnel * GetTrapTunnel() const { return mTrapTunnel; };
	CTunnelProject * GetTunnelProject() const { return mTunnelProject; };

	virtual bool BuildTunnelFlag() {
		CSimpleIni mProjectIni;
		CString strTrap("Trapzoid");
		CString strFlag("Flag");
		SI_Error rc = mProjectIni.LoadFile(filepath);
		if (rc < 0) return false; // 若加载文件出错，返回false

		// 初始化拱形巷道基本信息和 FLAG 标志
		mTrapTunnel->SetBottomWidth(mProjectIni.GetDoubleValue(strTrap, _T("BottomWidth")));
		mTrapTunnel->SetHeight(mProjectIni.GetDoubleValue(strTrap, _T("Height")));
		mTrapTunnel->SetTopWidth(mProjectIni.GetDoubleValue(strTrap, _T("TopWidth")));
		mTrapTunnel->SetTrapLeftAngle(mProjectIni.GetLongValue(strTrap, _T("LeftAngle")));
		mTrapTunnel->SetTrapRightAngle(mProjectIni.GetLongValue(strTrap, _T("RightAngle")));

		mTrapTunnel->SetZhihuWay(mProjectIni.GetLongValue(strFlag, _T("ZhihuWay")));
		mTrapTunnel->SetHasRevertAngle(mProjectIni.GetBoolValue(strFlag, _T("HasRevertAngle")));
		mTrapTunnel->SetCalMethod(mProjectIni.GetLongValue(strFlag, _T("CalMethod")));

		mTrapTunnel->SetHasTopBolt(mProjectIni.GetBoolValue(strFlag, _T("HasTopBolt")));
		mTrapTunnel->SetHasLeftBolt(mProjectIni.GetBoolValue(strFlag, _T("HasLeftBolt")));
		mTrapTunnel->SetHasRightBolt(mProjectIni.GetBoolValue(strFlag, _T("HasRightBolt")));
		mTrapTunnel->SetHasCable(mProjectIni.GetBoolValue(strFlag, _T("HasCable")));

		CString strRevertAngle("RevertAngle");
		//mTrapTunnel->SetTopBoltAngle(mProjectIni.GetLongValue(strRevertAngle, _T("TopAngle")));
		//mTrapTunnel->SetLeftBoltAngle(mProjectIni.GetLongValue(strRevertAngle, _T("LeftAngle")));
		//mTrapTunnel->SetRightBoltAngle(mProjectIni.GetLongValue(strRevertAngle, _T("RightAngle")));

		if (mTrapTunnel->GetZhihuWay() > 1) {
			CString strThickness("Thickness");
			CString strConcreteThickness("ConcreteThickness");
			CString strQiThickness("QiThickness");

			mTrapTunnel->SetConcreteThickness(mProjectIni.GetLongValue(strThickness, strConcreteThickness));
			mTrapTunnel->SetQiThickness(mProjectIni.GetLongValue(strThickness, strQiThickness));
		}

		return true;
	};

	virtual bool BuildParameters() {

		CString strTopBolt("TopBolt");
		mTrapTunnel->SetTopBolt(BuildBoltFromIni(strTopBolt));

		CString strLeftBolt("LeftBolt");
		mTrapTunnel->SetLeftBolt(BuildBoltFromIni(strLeftBolt));

		CString strRightBolt("RightBolt");
		mTrapTunnel->SetRightBolt(BuildBoltFromIni(strRightBolt));

		mTrapTunnel->SetCable(BuildCableFromIni());

		return true;
	};
};