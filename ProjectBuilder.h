#pragma once
#include "CTunnel.h"
#include "TunnelProject.h"
#include "CalMethod.h"
#include <iostream>
#include "SimpleIni.h"
#include "MFCUtil.h"
class CProjectBuilder
{
protected:
	CTunnelProject * mTunnelProject;
	CString fileUrl;
	CMethodFactory * factory;
	CMethod * method;
	CTheoryCalMethod * theory;
	CProExpMethod * project;
	CLooseRangeMethod * loose;
	CBalanceMethod * balance;
	CZuheliangMethod * zuheliang;

	BOOL IsSavedToFile = TRUE;
	BOOL IsProjectSaveToInstance = FALSE;
	BOOL IsTunnelSaveToInstance = FALSE;
	BOOL IsMethodSaveToInstance = FALSE;
	BOOL IsCalMethodSaveToInstance = FALSE;

public:
	virtual void SetFileUrl(CString url) { fileUrl = url; };
	virtual CString GetFileUrl() const { return fileUrl; };	
	virtual void SetTunnelProject(CTunnelProject * p) { mTunnelProject = p; };
	CTunnelProject * GetTunnelProejct() const { return mTunnelProject; };
	void SetSavedToFile(BOOL flag) { IsSavedToFile = flag; };
	BOOL GetSavedToFile() const { return IsSavedToFile; };
	void SetTunnelSaveToInstance(BOOL flag) { IsTunnelSaveToInstance = flag; };
	BOOL GetTunnelSaveToInstance() const { return IsTunnelSaveToInstance; };
	void SetProjectSaveToInstance(BOOL flag) { IsProjectSaveToInstance = flag; };
	BOOL GetProjectSaveToInstance() const { return IsProjectSaveToInstance; };
	void SetMethodSaveToInstance(BOOL flag) { IsMethodSaveToInstance = flag; };
	BOOL GetMethodSaveToInstance() const { return IsMethodSaveToInstance; };
	void SetCalMethodSaveToInstance(BOOL flag) { IsCalMethodSaveToInstance = flag; };
	BOOL GetCalMethodSaveToInstance() const { return IsCalMethodSaveToInstance; };
	CMethod * GetMethod() const { return method; };
	CTheoryCalMethod * GetTheoryMethod() const { return theory; };
	CProExpMethod * GetExpMethod() const { return project; };
	CLooseRangeMethod * GetLooseMethod() const { return loose; };
	CBalanceMethod * GetBalanceMethod() const { return balance; };
	CZuheliangMethod * GetZuheliangMethod() const { return zuheliang; };
	void SetMethod(CMethod * m) {
		method = m;
	}

	void InitSaveToInstance() {
		IsProjectSaveToInstance = FALSE;
		IsTunnelSaveToInstance = FALSE;
		IsMethodSaveToInstance = FALSE;
		IsCalMethodSaveToInstance = FALSE;
	};

	virtual bool BuildProject() { 
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
		SI_Error rc = mProjectIni.LoadFile(fileUrl);
		if (rc < 0) return false; // 若加载文件出错，返回false

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

		mTunnelProject->SetTunnelType(mProjectIni.GetLongValue(strProject, strTunnelType));
		return true;
	};
	virtual bool BuildTunnelFlag() { return false; };
	virtual bool BuildMethod() { 
		return false; 
	};
	virtual bool BuildParameters() { return false; };

	virtual bool SaveProjectToFile() {
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

		SI_Error rc = mProjectIni.LoadFile(fileUrl);
		if (rc < 0) return false; // 若加载文件出错，返回false
		mProjectIni.SetValue(strProject, strPaperTitle, mTunnelProject->GetPaperTitle());
		mProjectIni.SetValue(strProject, strPaperDescription, mTunnelProject->GetPaperDescription());
		mProjectIni.SetValue(strProject, strScaleNumber, mTunnelProject->GetScaleNumber());
		mProjectIni.SetValue(strProject, strPaperSize, mTunnelProject->GetPaperSize());
		mProjectIni.SetValue(strProject, strPaperNumber, mTunnelProject->GetPaperNumber());

		mProjectIni.SetValue(strProject, strDesigner, mTunnelProject->GetDesigner());
		mProjectIni.SetValue(strProject, strDate, mTunnelProject->GetDate());
		mProjectIni.SetValue(strProject, strCheckDate, mTunnelProject->GetCheckDate());
		mProjectIni.SetValue(strProject, strChecker, mTunnelProject->GetChecker());
		mProjectIni.SetValue(strProject, strDesignApart, mTunnelProject->GetDesignApart());
		mProjectIni.SetValue(strProject, strDevelopApart, mTunnelProject->GetDevelopApart());
		mProjectIni.SetLongValue(strProject, strTunnelType, mTunnelProject->GetTunnelType());

		SI_Error rc2 = mProjectIni.SaveFile(fileUrl);
		return rc2 < 0 ? false : true;
	}
	//virtual bool SaveMethodToFile() { 

	//	return SaveTheoryMethod() && SaveExpMethod() && SaveLooseRangeMethod();
	//};
	virtual bool SaveParametersToFile() { return false; };
	bool SaveTheoryMethod() {
		CSimpleIni mProjectIni;
		CString strTheoryMethod("TheoryMethod");

		CString strAvgGravity("AvgGravity");
		CString strCompressive("Compressive");
		CString strMaiDepth("MaiDepth");
		CString strInnerFriction("InnerFriction");
		CString strShuLength("ShuLength");
		CString	strStoneStrongNumber("StoneStrongNumber");
		CString strBoltDiameter("BoltDiameter");
		CString strBoltDisignNumber("BoltDesignNumber");

		CString strBoltAttach("BoltAttach");
		CString strBoltPitch("BoltPitch");
		CString strBoltNumber("BoltNumber");
		CString strBoltExperience("BoltExperience");
		CString strBoltCaiNumber("BoltCaiNumber");
		CString strCableDiameter("CableDiameter");
		CString strCableBreakForce("CableBreakForce");
		CString strCableAttach("CableAttach");
		CString strCablePitch("CablePitch");
		CString strCableNumber("CableNumber");
		CString strCableFreeNumber("CableFreeNumber");
		CString strCableCaiNumber("CableCaiNumber");

		CString strThickness("Thickness");
		CString strConcreteThickness("ConcreteThickness");
		CString strQiThickness("QiThickness");

		SI_Error rc = mProjectIni.LoadFile(fileUrl);
		if (rc < 0) return false; // 若加载文件出错，返回false

		mProjectIni.SetDoubleValue(strTheoryMethod, strMaiDepth, theory->GetMaiDepth() * 1000);
		mProjectIni.SetDoubleValue(strTheoryMethod, strCompressive, theory->GetCompressive());
		mProjectIni.SetDoubleValue(strTheoryMethod, strAvgGravity, theory->GetAvgGravity());
		mProjectIni.SetDoubleValue(strTheoryMethod, strInnerFriction, theory->GetInnerFriction());
		mProjectIni.SetDoubleValue(strTheoryMethod, strShuLength, theory->GetShuLength());
		mProjectIni.SetDoubleValue(strTheoryMethod, _T("StoneNianPower"), theory->GetStoneNianPower());
		mProjectIni.SetDoubleValue(strTheoryMethod, strStoneStrongNumber, theory->GetStoneStrongNumber());
		mProjectIni.SetDoubleValue(strTheoryMethod, strBoltDiameter, theory->GetBoltDiameter());
		mProjectIni.SetDoubleValue(strTheoryMethod, strBoltDisignNumber, theory->GetBoltDesignNumber());
		mProjectIni.SetDoubleValue(strTheoryMethod, strBoltAttach, theory->GetBoltAttach());
		mProjectIni.SetDoubleValue(strTheoryMethod, strBoltPitch, theory->GetBoltPitch());
		mProjectIni.SetDoubleValue(strTheoryMethod, strBoltExperience, theory->GetBoltExperienceNumber());
		mProjectIni.SetDoubleValue(strTheoryMethod, strBoltCaiNumber, theory->GetBoltCaiAffectNumber());
		mProjectIni.SetDoubleValue(strTheoryMethod, strCableDiameter, theory->GetCableDiameter());
		mProjectIni.SetDoubleValue(strTheoryMethod, strCableBreakForce, theory->GetCableBreakPower());
		mProjectIni.SetDoubleValue(strTheoryMethod, strCableAttach, theory->GetCableAttach());
		mProjectIni.SetDoubleValue(strTheoryMethod, strCablePitch, theory->GetCablePitch());
		mProjectIni.SetDoubleValue(strTheoryMethod, strCableFreeNumber, theory->GetCableFreeLength());
		mProjectIni.SetDoubleValue(strTheoryMethod, strCableCaiNumber, theory->GetCableCaiAffectNumber());
		mProjectIni.SetLongValue(strTheoryMethod, strBoltNumber, theory->GetBoltNumber());
		mProjectIni.SetLongValue(strTheoryMethod, strCableNumber, theory->GetCableNumber());

		SI_Error rc2 = mProjectIni.SaveFile(fileUrl);
		return rc2 < 0 ? false : true;
	};
	bool SaveExpMethod() { 
	 
		 CSimpleIni mProjectIni;
		 CString strExpMethod("ExperienceMethod");

		 CString strStoneType("StoneType");
		 CString strBoltShuLength("BoltShuLength");
		 CString strCableShuLength("CableShuLength");
		 CString strStoneStrongNumber("StoneStrongNumber");
		 CString strBoltDiameter("BoltDiameter");
		 CString strBoltDesignNumber("BoltDesignNumber");
		 CString strBoltAttach("BoltAttach");
		 CString	strBoltPitch("BoltPitch");
		 CString	strBoltNumber("BoltNumber");
		 CString	strBoltLength("BoltLength");
		 CString	strBoltSpace("BoltSpace");
		 CString	strBoltExperience("BoltExperience");
		 CString strBoltCaiNumber("BoltCaiNumber");
		 CString strCableLength("CableLength");
		 CString strCableDiameter("CableDiameter");
		 CString strCableBreakForce("CableBreakForce");
		 CString strCableAttach("CableAttach");
		 CString strCableSpace("CableSpace");
		 CString strCablePitch("CablePitch");
		 CString strCableNumber("CableNumber");
		 CString strCableFreeNumber("CableFreeNumber");
		 CString strCableCaiNumber("CableCaiNumber");
		 SI_Error rc = mProjectIni.LoadFile(fileUrl);
		 if (rc < 0) return false; // 若加载文件出错，返回false

		 //mProjectIni.SetLongValue(strExpMethod, strBoltNumber, project->GetBoltNumber());
		 mProjectIni.SetLongValue(strExpMethod, strCableNumber, project->GetCableNumber());
		 mProjectIni.SetLongValue(strExpMethod, strStoneType, project->GetStoneType());
		 mProjectIni.SetDoubleValue(strExpMethod, strBoltLength, project->GetBoltLength());
		 mProjectIni.SetDoubleValue(strExpMethod, strBoltSpace, project->GetBoltSpace());
		 mProjectIni.SetDoubleValue(strExpMethod, strBoltPitch, project->GetBoltPitch());
		 mProjectIni.SetDoubleValue(strExpMethod, strBoltDiameter, project->GetBoltDiameter());
		 mProjectIni.SetDoubleValue(strExpMethod, strBoltDesignNumber, project->GetBoltDesignNumber());
		 mProjectIni.SetDoubleValue(strExpMethod, strBoltAttach, project->GetBoltAttach());
		 mProjectIni.SetDoubleValue(strExpMethod, strBoltShuLength, project->GetBoltShuLength());
		 mProjectIni.SetDoubleValue(strExpMethod, strCableLength, project->GetCableLength());
		 mProjectIni.SetDoubleValue(strExpMethod, strCableSpace, project->GetCableSpace());
		 mProjectIni.SetDoubleValue(strExpMethod, strCablePitch, project->GetCablePitch());
		 mProjectIni.SetDoubleValue(strExpMethod, strCableDiameter, project->GetCableDiameter());
		 mProjectIni.SetDoubleValue(strExpMethod, strCableAttach, project->GetCableAttach());
		 mProjectIni.SetDoubleValue(strExpMethod, strCableShuLength, project->GetCableShuLength());


		 SI_Error rc2 = mProjectIni.SaveFile(fileUrl);
		 return rc2 < 0 ? false : true;
	 };
	bool SaveLooseRangeMethod() { 
	 
		 CString strLooseRangeMethod("LooseRangeMethod");

		 CString strMeasureWay("MeasureWay");
		 CString strLooseRange("LooseRange");

		 CSimpleIni mProjectIni;

		 SI_Error rc = mProjectIni.LoadFile(fileUrl);
		 if (rc < 0) return false; // 若加载文件出错，返回false

		 mProjectIni.SetLongValue(strLooseRangeMethod, strMeasureWay, loose->GetMeasureWay());
		 mProjectIni.SetLongValue(strLooseRangeMethod, strLooseRange, loose->GetLooseRange());

		 SI_Error rc2 = mProjectIni.SaveFile(fileUrl);
		 return rc2 < 0 ? false : true;
	 };
	bool SaveBalanceMethod() {
		 CString strBalanceMethod("BalanceMethod");

		 CString mGroundAvgGravity("GroundAvgGravity") ;
		 CString mMaiDepth("MaiDepth");
		 CString mCoalHardNumber("CoalHardNumber");
		 CString mCoalThickness("CoalThickness");
		 CString mCaiEffectNumber("CaiEffectNumber");
		 CString mInnerFriction("InnerFriction");
		 CString mCableSafeNumber("CableSafeNumber");
		 CString mBoltNumber("BoltNumber");
		 CString mBoltOutLength("BoltOutLength");
		 CString mBoltPower("BoltPower");
		 CString mBoltSafeNumber("BoltSafeNumber");
		 CString mBoltSpace("BoltSpace");
		 CString mBoltYieldNumber("BoltYieldNumber");
		 CString mCableAlength("CableAlength");
		 CString mCableOutLength("CableOutLength");
		 CString mCoalFriction("CoalFriction");
		 CString mMinBreakPower("MinBreakPower");
		 CString mCableStoneHeight("CableStoneHeight");
		 CString mStoneToughNumber("StoneToughNumber");
		 CString mStableNumber("StableNumber");
		 CString mTopAvgGravity("TopAvgGravity");
		 CSimpleIni mProjectIni;

		 SI_Error rc = mProjectIni.LoadFile(fileUrl);
		 if (rc < 0) return false; // 若加载文件出错，返回false

		 mProjectIni.SetLongValue(strBalanceMethod, mBoltNumber, balance->GetBoltNumber());
		 mProjectIni.SetDoubleValue(strBalanceMethod, mGroundAvgGravity, balance->GetAvgGravity());
		 mProjectIni.SetDoubleValue(strBalanceMethod, mInnerFriction, balance->GetInnerFriction());
		 mProjectIni.SetDoubleValue(strBalanceMethod, mCoalFriction, balance->GetCoalAngle());
		 mProjectIni.SetDoubleValue(strBalanceMethod, mMaiDepth, balance->GetMaiDepth());
		 mProjectIni.SetDoubleValue(strBalanceMethod, mCoalHardNumber, balance->GetCoalHardNumber_Fy());
		 mProjectIni.SetDoubleValue(strBalanceMethod, mCoalThickness, balance->GetCoalThickness());
		 mProjectIni.SetDoubleValue(strBalanceMethod, mCaiEffectNumber, balance->GetCaiEffectNumber());
		 mProjectIni.SetDoubleValue(strBalanceMethod, mBoltSafeNumber, balance->GetBoltSafeNumber());
		 mProjectIni.SetDoubleValue(strBalanceMethod, mCableSafeNumber, balance->GetCableSafeNumber());
		 mProjectIni.SetDoubleValue(strBalanceMethod, mBoltPower, balance->GetBoltStablePower());
		 mProjectIni.SetDoubleValue(strBalanceMethod, mBoltSpace, balance->GetBoltSpace());
		 mProjectIni.SetDoubleValue(strBalanceMethod, mBoltYieldNumber, balance->GetBoltYieldNumber());
		 mProjectIni.SetDoubleValue(strBalanceMethod, mCableAlength, balance->GetCableALength());
		 mProjectIni.SetDoubleValue(strBalanceMethod, mCableOutLength, balance->GetCableOutLength());
		 mProjectIni.SetDoubleValue(strBalanceMethod, mCableStoneHeight, balance->GetCableStoneHeight());
		 mProjectIni.SetDoubleValue(strBalanceMethod, mMinBreakPower, balance->GetMinBreakLoader());
		 mProjectIni.SetDoubleValue(strBalanceMethod, mStoneToughNumber, balance->GetStoneHardNumber());
		 mProjectIni.SetDoubleValue(strBalanceMethod, mStableNumber, balance->GetStableNumber());
		 mProjectIni.SetDoubleValue(strBalanceMethod, mTopAvgGravity, balance->GetTopAvgGravity());
		 mProjectIni.SetDoubleValue(strBalanceMethod, mBoltOutLength, balance->GetBoltOutLength());
		 SI_Error rc2 = mProjectIni.SaveFile(fileUrl);
		 return rc2 < 0 ? false : true;
	 };
	bool SaveZuheliangMethod() {

		CString strZuheliangMethod("Zuheliang");
		CString mGroundAvgGravity("GroundAvgGravity");
		CString mMaiDepth("MaiDepth");
		CString mCoalHardNumber("CoalHardNumber");
		CString mCoalThickness("CoalThickness");
		CString mCaiEffectNumber("CaiEffectNumber");
		CString mInnerFriction("InnerFriction");
		CString mBoltALength("BoltALength");
		CString mBoltDiameter("BoltDiameter");
		CString mBoltOutLength("BoltOutLength");
		CString mBoltSafeNumber("BoltSafeNumber");
		CString mCeyaliNumber("CeyaliNumber");
		CString mCoalFriction("CoalFriction");
		CString mKangjian("CoalFriction");
		CString mKangla("Kangla");
		CString mKuadu("Kuadu");
		CString mStableNumber("StableNumber");
		CString mStoneHardNumber("StoneHardNumber");
		CString mTopGravity("TopGravity");
		CString mTopSafeNumber("TopSafeNumber");
		CString mTopThickness("TopThickness");
		CString mZhejianNumber("ZhejianNumber");

		CSimpleIni mProjectIni;

		SI_Error rc = mProjectIni.LoadFile(fileUrl);
		if (rc < 0) return false; // 若加载文件出错，返回false

		mProjectIni.SetDoubleValue(strZuheliangMethod, mGroundAvgGravity, zuheliang->GetGroundAvgGravity());
		mProjectIni.SetDoubleValue(strZuheliangMethod, mMaiDepth, zuheliang->GetMaiDepth());
		mProjectIni.SetDoubleValue(strZuheliangMethod, mCoalHardNumber, zuheliang->GetCoalHardNumber());
		mProjectIni.SetDoubleValue(strZuheliangMethod, mCoalThickness, zuheliang->GetCoalThickness());
		mProjectIni.SetDoubleValue(strZuheliangMethod, mCaiEffectNumber, zuheliang->GetCaiEffectNumber());
		mProjectIni.SetDoubleValue(strZuheliangMethod, mInnerFriction, zuheliang->GetInnerFriction());
		mProjectIni.SetDoubleValue(strZuheliangMethod, mBoltALength, zuheliang->GetBoltALength());
		mProjectIni.SetDoubleValue(strZuheliangMethod, mBoltDiameter, zuheliang->GetBoltDiameter());
		mProjectIni.SetDoubleValue(strZuheliangMethod, mBoltOutLength, zuheliang->GetBoltOutLength());
		mProjectIni.SetDoubleValue(strZuheliangMethod, mBoltSafeNumber, zuheliang->GetBoltSafeNumber());
		mProjectIni.SetDoubleValue(strZuheliangMethod, mCeyaliNumber, zuheliang->GetCeyaliNumber());
		mProjectIni.SetDoubleValue(strZuheliangMethod, mCoalFriction, zuheliang->GetCoalFriction());
		mProjectIni.SetDoubleValue(strZuheliangMethod, mKangjian, zuheliang->GetKangjian());
		mProjectIni.SetDoubleValue(strZuheliangMethod, mKangla, zuheliang->GetKangla());
		mProjectIni.SetDoubleValue(strZuheliangMethod, mKuadu, zuheliang->GetKuadu());
		mProjectIni.SetDoubleValue(strZuheliangMethod, mStableNumber, zuheliang->GetStableNumber());
		mProjectIni.SetDoubleValue(strZuheliangMethod, mStoneHardNumber, zuheliang->GetStableNumber());
		mProjectIni.SetDoubleValue(strZuheliangMethod, mTopGravity, zuheliang->GetTopGravity());
		mProjectIni.SetDoubleValue(strZuheliangMethod, mTopSafeNumber, zuheliang->GetTopSafeNumber());
		mProjectIni.SetDoubleValue(strZuheliangMethod, mTopThickness, zuheliang->GetTopThickness());
		mProjectIni.SetDoubleValue(strZuheliangMethod, mZhejianNumber, zuheliang->GetZhejianNumber());

		SI_Error rc2 = mProjectIni.SaveFile(fileUrl);
		return rc2 < 0 ? false : true;
	};
	CProjectBuilder()
	{
		//mTunnelProject = new CTunnelProject();
	};

	static CProjectBuilder * GetInstance() {
		static CProjectBuilder instance;
		return &instance;
	};

	~CProjectBuilder()
	{
	};
};

class CArcProjectBuilder : public CProjectBuilder {
private:
	CArcTunnel * mArcTunnel;
public:
	CArcProjectBuilder() { 
		mArcTunnel = new CArcTunnel();
		mTunnelProject = new CTunnelProject(); 
		theory = new CTheoryCalMethod();
		project = new CProExpMethod();
		loose = new CLooseRangeMethod();
		balance = new CBalanceMethod();
		zuheliang = new CZuheliangMethod();
	};
	~CArcProjectBuilder() { 
		delete mArcTunnel; 
		delete mTunnelProject;
		delete theory;
		delete project;
		delete loose;
		delete balance;
	};
	static CArcProjectBuilder * GetInstance() {
		static CArcProjectBuilder instance;
		return &instance;
	}; 

	void  SetArcTunnel(CArcTunnel * arc)  { mArcTunnel = arc; };

	CArcTunnel * GetArcTunnel() const{ return mArcTunnel; };
	CTunnelProject * GetTunnelProject() const { return mTunnelProject; };

	bool BuildAll() {
		if ((BuildProject() == true)
			&& (BuildTunnelFlag() == true)
			&& (BuildMethod() == true)
			&& (BuildParameters() == true)
			)
			return true;
		else return false;
	}

	virtual bool BuildTunnelFlag() {
		CSimpleIni mProjectIni;
		CString strArc("Arc");
		CString strFlag("Flag");
		CString strRect("Rectangle");
		CString strTrap("Trapzoid");
		SI_Error rc = mProjectIni.LoadFile(fileUrl);
		if (rc < 0) return false; // 若加载文件出错，返回false
		
		switch (mTunnelProject->GetTunnelType())
		{
		case 1:
			// 用拱形巷道的属性存储矩形巷道的宽和高
			mArcTunnel->SetWidth(mProjectIni.GetDoubleValue(strRect, _T("Width")));
			mArcTunnel->SetWallHeight(mProjectIni.GetDoubleValue(strRect, _T("Height")));
			break;
		case 2:
			// 初始化拱形巷道基本信息和 FLAG 标志
			mArcTunnel->SetWidth(mProjectIni.GetDoubleValue(strArc, _T("Width")));
			mArcTunnel->SetArcHeight(mProjectIni.GetDoubleValue(strArc, _T("ArcHeight")));
			mArcTunnel->SetWallHeight(mProjectIni.GetDoubleValue(strArc, _T("WallHeight")));
			mArcTunnel->SetNormalToArc(mProjectIni.GetBoolValue(strArc, _T("IsNormalToArc")));
			break;
		case 3:
			mArcTunnel->SetWidth(mProjectIni.GetDoubleValue(strTrap, _T("TopWidth")));
			mArcTunnel->SetWallHeight(mProjectIni.GetDoubleValue(strTrap, _T("Height")));
			mArcTunnel->SetTrapBottomWidth(mProjectIni.GetDoubleValue(strTrap, _T("BottomWidth")));
			mArcTunnel->SetTrapLeftAngle(mProjectIni.GetLongValue(strTrap, _T("LeftAngle")));
			mArcTunnel->SetTrapRightAngle(mProjectIni.GetLongValue(strTrap, _T("RightAngle")));
			break;
		default:
			break;
		}

		mArcTunnel->SetZhihuWay(mProjectIni.GetLongValue(strFlag, _T("ZhihuWay")));
		mArcTunnel->SetHasRevertAngle(mProjectIni.GetBoolValue(strFlag, _T("HasRevertAngle")));
		mArcTunnel->SetCalMethod(mProjectIni.GetLongValue(strFlag, _T("CalMethod")));

		mArcTunnel->SetHasTopBolt(mProjectIni.GetBoolValue(strFlag, _T("HasTopBolt")));
		mArcTunnel->SetHasLeftBolt(mProjectIni.GetBoolValue(strFlag, _T("HasLeftBolt")));
		mArcTunnel->SetHasRightBolt(mProjectIni.GetBoolValue(strFlag, _T("HasRightBolt")));
		mArcTunnel->SetHasCable(mProjectIni.GetBoolValue(strFlag, _T("HasCable")));

		CString strRevertAngle("RevertAngle");
		mArcTunnel->SetTopAngle(mProjectIni.GetDoubleValue(strRevertAngle, _T("TopAngle")));
		mArcTunnel->SetLeftAngle(mProjectIni.GetDoubleValue(strRevertAngle, _T("LeftAngle")));
		std::cout << "build left angle: " << mArcTunnel->GetLeftAngle() << std::endl;
		mArcTunnel->SetRightAngle(mProjectIni.GetDoubleValue(strRevertAngle, _T("RightAngle")));

		return true;
	};

	virtual bool BuildParameters() {
	
		CString strTopBolt("TopBolt");
		mArcTunnel->SetTopBolt(BuildBoltFromIni( strTopBolt));

		CString strLeftBolt("LeftBolt");
		mArcTunnel->SetLeftBolt(BuildBoltFromIni( strLeftBolt));

		CString strRightBolt("RightBolt");
		mArcTunnel->SetRightBolt(BuildBoltFromIni( strRightBolt));

		mArcTunnel->SetCable(BuildCableFromIni());

		return true;
	};

	CCable * BuildCableFromIni() {
		CSimpleIni mProjectIni;
		SI_Error rc = mProjectIni.LoadFile(fileUrl);
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
		SI_Error rc = mProjectIni.LoadFile(fileUrl);
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

	virtual bool BuildMethod() {
		CSimpleIni mProjectIni;
		SI_Error rc = mProjectIni.LoadFile(fileUrl);
		if (rc < 0) return false; // 若加载文件出错，返回false
		
		CString strSec("TheoryMethod");
		CString strExp("ExperienceMethod");
		CString strLoose("LooseRangeMethod");
		CString strAvgGravity("AvgGravity");
		CString strCompressive("Compressive");
		CString strMaiDepth("MaiDepth");
		CString strInnerFriction("InnerFriction");
		CString strShuLength("ShuLength");
		CString strBoltShuLength("BoltShuLength");
		CString strCableShuLength("CableShuLength");
		CString strStoneStrongNumber("StoneStrongNumber");
		CString strBoltDiameter("BoltDiameter");
		CString strBoltDesignNumber("BoltDesignNumber");
		CString strBoltAttach("BoltAttach");
		CString	strBoltPitch("BoltPitch");
		CString	strBoltNumber("BoltNumber");
		CString	strBoltLength("BoltLength");
		CString	strBoltSpace("BoltSpace");
		CString	strBoltExperience("BoltExperience");
		CString strBoltCaiNumber("BoltCaiNumber");
		CString strCableDiameter("CableDiameter");
		CString strCableBreakForce("CableBreakForce");
		CString strCableAttach("CableAttach");
		CString strCableSpace("CableSpace");
		CString strCablePitch("CablePitch");
		CString strCableNumber("CableNumber");
		CString strCableFreeNumber("CableFreeNumber");
		CString strCableCaiNumber("CableCaiNumber");
		CString strMeasureWay("MeasureWay");
		CString strLooseRange("LooseRange");
		CString strThickness("Thickness");
		CString strConcreteThickness("ConcreteThickness");
		CString strQiThickness("QiThickness");

		CString strBalanceMethod("BalanceMethod");
		CString mGroundAvgGravity("GroundAvgGravity");
		CString mMaiDepth("MaiDepth");
		CString mCoalHardNumber("CoalHardNumber");
		CString mCoalThickness("CoalThickness");
		CString mCaiEffectNumber("CaiEffectNumber");
		CString mInnerFriction("InnerFriction");
		CString mCableSafeNumber("CableSafeNumber");
		CString mBoltNumber("BoltNumber");
		CString mBoltOutLength("BoltOutLength");
		CString mBoltPower("BoltPower");
		CString mBoltSafeNumber("BoltSafeNumber");
		CString mBoltSpace("BoltSpace");
		CString mBoltYieldNumber("BoltYieldNumber");
		CString mCableAlength("CableAlength");
		CString mCableOutLength("CableOutLength");
		CString mCoalFriction("CoalFriction");
		CString mMinBreakPower("MinBreakPower");
		CString mCableStoneHeight("CableStoneHeight");
		CString mStoneToughNumber("StoneToughNumber");
		CString mStableNumber("StableNumber");
		CString mTopAvgGravity("TopAvgGravity");

		CString strZuheliangMethod("Zuheliang");
		//CString mGroundAvgGravity("GroundAvgGravity");
		//CString mMaiDepth("MaiDepth");
		//CString mCoalHardNumber("CoalHardNumber");
		//CString mCoalThickness("CoalThickness");
		//CString mCaiEffectNumber("CaiEffectNumber");
		//CString mInnerFriction("InnerFriction") ;
		CString mBoltALength("BoltALength") ;
		CString mBoltDiameter("BoltDiameter") ;
		//CString mBoltOutLength("BoltOutLength");
		//CString mBoltSafeNumber("BoltSafeNumber");
		CString mCeyaliNumber("CeyaliNumber");
		//CString mCoalFriction("CoalFriction");
		CString mKangjian("CoalFriction");
		CString mKangla("Kangla");
		CString mKuadu("Kuadu");
		//CString mStableNumber("StableNumber");
		CString mStoneHardNumber("StoneHardNumber");
		CString mTopGravity("TopGravity");
		CString mTopSafeNumber("TopSafeNumber");
		CString mTopThickness("TopThickness");
		CString mZhejianNumber("ZhejianNumber");
		switch (mArcTunnel->GetCalMethod())
		{
		case 1:
			factory = new CTheroyMethodFactory();
			method = factory->createMethod();
		 
			std::cout << "theory factory init\n";

			// 静态转型
			theory = static_cast<CTheoryCalMethod *>(method);
			std::cout << "theory factory type cast\n";
			theory->SetAvgGravity(mProjectIni.GetDoubleValue(strSec, strAvgGravity));
			theory->SetCompressive(mProjectIni.GetDoubleValue(strSec, strCompressive));
			theory->SetMaiDepth(mProjectIni.GetDoubleValue(strSec, strMaiDepth));
			theory->SetInnerFriction(mProjectIni.GetDoubleValue(strSec, strInnerFriction));
			theory->SetStoneStrongNumber(mProjectIni.GetDoubleValue(strSec, strStoneStrongNumber));
			theory->SetStoneNianPower(mProjectIni.GetDoubleValue(strSec, _T("StoneNianPower")));
			theory->SetShuLength(mProjectIni.GetDoubleValue(strSec, strShuLength));
			theory->SetBoltDiameter(mProjectIni.GetDoubleValue(strSec, strBoltDiameter));
			theory->SetBoltDesignNumber(mProjectIni.GetDoubleValue(strSec, strBoltDesignNumber));
			theory->SetBoltAttach(mProjectIni.GetDoubleValue(strSec, strBoltAttach));
			theory->SetBoltPitch(mProjectIni.GetDoubleValue(strSec, strBoltPitch));
			theory->SetBoltNumber(mProjectIni.GetLongValue(strSec, strBoltNumber));
			theory->SetBoltExperienceNumber(mProjectIni.GetDoubleValue(strSec, strBoltExperience));
			theory->SetBoltCaiAffectNumber(mProjectIni.GetDoubleValue(strSec, strBoltCaiNumber));
			theory->SetCableDiameter(mProjectIni.GetDoubleValue(strSec, strCableDiameter));
			theory->SetCableBreakPower(mProjectIni.GetDoubleValue(strSec, strCableBreakForce));
			theory->SetCableAttach(mProjectIni.GetDoubleValue(strSec, strCableAttach));
			theory->SetCableNumber(mProjectIni.GetLongValue(strSec, strCableNumber));
			theory->SetCableCaiAffectNumber(mProjectIni.GetDoubleValue(strSec, strCableCaiNumber));
			theory->SetCablePitch(mProjectIni.GetDoubleValue(strSec, strCablePitch));
			theory->SetCableFreeLength(mProjectIni.GetDoubleValue(strSec, strCableFreeNumber));
			
			mArcTunnel->SetConcreteThickness(mProjectIni.GetLongValue(strThickness, strConcreteThickness));
			mArcTunnel->SetQiThickness(mProjectIni.GetLongValue(strThickness, strQiThickness));

			break;
		case 2:
			factory = new CProExpMethodFactory();
			method = factory->createMethod();

			// 静态转型
			project = static_cast<CProExpMethod *>(method);
			project->SetStoneType(mProjectIni.GetLongValue(strExp, _T("StoneType")));
			project->SetBoltLength(mProjectIni.GetDoubleValue(strExp, _T("BoltLength")));
			project->SetBoltSpace(mProjectIni.GetDoubleValue(strExp, strBoltSpace));
			project->SetBoltPitch(mProjectIni.GetDoubleValue(strExp, strBoltPitch));
			project->SetBoltDiameter(mProjectIni.GetDoubleValue(strExp, strBoltDiameter));
			project->SetBoltDesignNumber(mProjectIni.GetDoubleValue(strExp, strBoltDesignNumber));
			project->SetBoltAttach(mProjectIni.GetDoubleValue(strExp, strBoltAttach));
			project->SetBoltShuLength(mProjectIni.GetDoubleValue(strExp, strBoltShuLength));
			project->SetCableLength(mProjectIni.GetDoubleValue(strExp, _T("CableLength")));
			project->SetCableDiameter(mProjectIni.GetDoubleValue(strExp, strCableDiameter));
			project->SetCableSpace(mProjectIni.GetDoubleValue(strExp, strCableSpace));
			project->SetCablePitch(mProjectIni.GetDoubleValue(strExp, strCablePitch));
			project->SetCableNumber(mProjectIni.GetLongValue(strExp, strCableNumber));
			project->SetCableAttach(mProjectIni.GetDoubleValue(strExp, strCableAttach));
			project->SetCableShuLength(mProjectIni.GetDoubleValue(strExp, strCableShuLength)); 

			mArcTunnel->SetConcreteThickness(mProjectIni.GetLongValue(strThickness, strConcreteThickness));
			mArcTunnel->SetQiThickness(mProjectIni.GetLongValue(strThickness, strQiThickness));
			break;
		case 3:
			factory = new CLooseRangeMethodFactory();
			method = factory->createMethod();

			loose = static_cast<CLooseRangeMethod *>(method);
			loose->SetMeasureWay(mProjectIni.GetLongValue(strLoose, strMeasureWay));
			switch(loose->GetMeasureWay() ) {
			case 1:
				loose->SetLooseRange(mProjectIni.GetDoubleValue(strLoose, strLooseRange));
				break;
			case 2:
				loose->SetStoneStrongNumber(mProjectIni.GetDoubleValue(strLoose, strStoneStrongNumber));
				break;
			default:
				break;
			}
			mArcTunnel->SetConcreteThickness(mProjectIni.GetLongValue(strThickness, strConcreteThickness));
			mArcTunnel->SetQiThickness(mProjectIni.GetLongValue(strThickness, strQiThickness));

			break;
		case 4:
			factory = new CTheroyMethodFactory();
			method = factory->createMethod();
			mArcTunnel->SetConcreteThickness(mProjectIni.GetLongValue(strThickness, strConcreteThickness));
			mArcTunnel->SetQiThickness(mProjectIni.GetLongValue(strThickness, strQiThickness));
			break;
		case 5:
			factory = new CBalanceMethodFactory();
			method = factory->createMethod();

			balance = static_cast<CBalanceMethod *>(method);
			balance->SetAvgGravity(mProjectIni.GetDoubleValue(strBalanceMethod, mGroundAvgGravity));
			balance->SetMaiDepth(mProjectIni.GetDoubleValue(strBalanceMethod, mMaiDepth));
			balance->SetCoalHardNumber_Fy(mProjectIni.GetDoubleValue(strBalanceMethod, mCoalHardNumber));
			balance->SetInnerFriction(mProjectIni.GetDoubleValue(strBalanceMethod, mInnerFriction));
			balance->SetCoalAngle(mProjectIni.GetDoubleValue(strBalanceMethod, mCoalFriction));
			balance->SetCaiEffectNumber(mProjectIni.GetDoubleValue(strBalanceMethod, mCaiEffectNumber));
			balance->SetCoalThickness(mProjectIni.GetDoubleValue(strBalanceMethod, mCoalThickness));
			balance->SetStableNumber(mProjectIni.GetDoubleValue(strBalanceMethod, mStableNumber));
			balance->SetStoneHardNumber(mProjectIni.GetDoubleValue(strBalanceMethod, mStoneToughNumber));
			balance->SetBoltOutLength(mProjectIni.GetDoubleValue(strBalanceMethod, mBoltOutLength));
			balance->SetBoltSpace(mProjectIni.GetDoubleValue(strBalanceMethod, mBoltSpace));
			// 锚固力
			balance->SetBoltStablePower(mProjectIni.GetDoubleValue(strBalanceMethod, mBoltPower));
			balance->SetBoltSafeNumber(mProjectIni.GetDoubleValue(strBalanceMethod, mBoltSafeNumber));
			balance->SetBoltYieldNumber(mProjectIni.GetDoubleValue(strBalanceMethod, mBoltYieldNumber));
			balance->SetTopAvgGravity(mProjectIni.GetDoubleValue(strBalanceMethod, mTopAvgGravity));
			balance->SetBoltNumber(mProjectIni.GetLongValue(strBalanceMethod, mBoltNumber));
			balance->SetCableALength(mProjectIni.GetDoubleValue(strBalanceMethod, mCableAlength));
			balance->SetCableOutLength(mProjectIni.GetDoubleValue(strBalanceMethod, mCableOutLength));
			balance->SetCableStoneHeight(mProjectIni.GetDoubleValue(strBalanceMethod, mCableStoneHeight));
			balance->SetMinBreakLoader(mProjectIni.GetDoubleValue(strBalanceMethod, mMinBreakPower));
			balance->SetCableSafeNumber(mProjectIni.GetDoubleValue(strBalanceMethod, mCableSafeNumber));
			
			mArcTunnel->SetConcreteThickness(mProjectIni.GetLongValue(strThickness, strConcreteThickness));
			mArcTunnel->SetQiThickness(mProjectIni.GetLongValue(strThickness, strQiThickness));
			break;

		case 6:
			factory = new CZuheliangFactory();
			method = factory->createMethod();

			zuheliang = static_cast<CZuheliangMethod *>(method);
			zuheliang->SetGroundAvgGravity(mProjectIni.GetDoubleValue(strZuheliangMethod, mGroundAvgGravity));
			zuheliang->SetMaiDepth(mProjectIni.GetDoubleValue(strZuheliangMethod, mMaiDepth));
			zuheliang->SetCoalHardNumber(mProjectIni.GetDoubleValue(strZuheliangMethod, mCoalHardNumber));
			zuheliang->SetCoalThickness(mProjectIni.GetDoubleValue(strZuheliangMethod, mCoalThickness));
			zuheliang->SetCaiEffectNumber(mProjectIni.GetDoubleValue(strZuheliangMethod, mCaiEffectNumber));
			zuheliang->SetInnerFriction(mProjectIni.GetDoubleValue(strZuheliangMethod, mInnerFriction));
			zuheliang->SetBoltALength(mProjectIni.GetDoubleValue(strZuheliangMethod, mBoltALength));
			zuheliang->SetBoltDiameter(mProjectIni.GetDoubleValue(strZuheliangMethod, mBoltDiameter));
			zuheliang->SetBoltOutLength(mProjectIni.GetDoubleValue(strZuheliangMethod, mBoltOutLength));
			zuheliang->SetBoltSafeNumber(mProjectIni.GetDoubleValue(strZuheliangMethod, mBoltSafeNumber));
			zuheliang->SetCeyaliNumber(mProjectIni.GetDoubleValue(strZuheliangMethod, mCeyaliNumber));
			zuheliang->SetCoalFriction(mProjectIni.GetDoubleValue(strZuheliangMethod, mCoalFriction));
			zuheliang->SetKangjian(mProjectIni.GetDoubleValue(strZuheliangMethod, mKangjian));
			zuheliang->SetKangla(mProjectIni.GetDoubleValue(strZuheliangMethod, mKangla));
			zuheliang->SetKuadu(mProjectIni.GetDoubleValue(strZuheliangMethod, mKuadu));
			zuheliang->SetStableNumber(mProjectIni.GetDoubleValue(strZuheliangMethod, mStableNumber));
			zuheliang->SetStoneHardNumber(mProjectIni.GetDoubleValue(strZuheliangMethod, mStoneHardNumber));
			zuheliang->SetTopGravity(mProjectIni.GetDoubleValue(strZuheliangMethod, mTopGravity));
			zuheliang->SetTopSafeNumber(mProjectIni.GetDoubleValue(strZuheliangMethod, mTopSafeNumber));
			zuheliang->SetTopThickness(mProjectIni.GetDoubleValue(strZuheliangMethod, mTopThickness));
			zuheliang->SetZhejianNumber(mProjectIni.GetDoubleValue(strZuheliangMethod, mZhejianNumber));

			mArcTunnel->SetConcreteThickness(mProjectIni.GetLongValue(strThickness, strConcreteThickness));
			mArcTunnel->SetQiThickness(mProjectIni.GetLongValue(strThickness, strQiThickness));
			break;
		default:
			break;
		}

		return true;

	}

	bool SaveBoltToFile(CString strSection, CBolt * bolt) {
		CSimpleIni mProjectIni;
		SI_Error rc = mProjectIni.LoadFile(fileUrl);
		if (rc < 0) return false; // 若加载文件出错，返回false

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

		mProjectIni.SetDoubleValue(strSection, strDiameter, bolt->getDiameter());
		mProjectIni.SetDoubleValue(strSection, strLength, bolt->getLength());
		mProjectIni.SetDoubleValue(strSection, strTailing, bolt->getTailing());
		mProjectIni.SetDoubleValue(strSection, strALength, bolt->getALength());
		mProjectIni.SetDoubleValue(strSection, strSpace, bolt->getSpace());
		mProjectIni.SetDoubleValue(strSection, strPitch, bolt->getPitch());
		mProjectIni.SetDoubleValue(strSection, strBeamWidth, bolt->getBeamWidth());
		mProjectIni.SetDoubleValue(strSection, strPortBeamWidth, bolt->getPortBeamWidth());
		mProjectIni.SetLongValue(strSection, strNumber, bolt->getNumber());
		mProjectIni.SetValue(strSection, strMaterial, bolt->getMaterial());
		mProjectIni.SetValue(strSection, strBeamMaterial, bolt->getBeamMaterial());
		mProjectIni.SetValue(strSection, strPortBeamMaterial, bolt->getBeamMaterial());
		mProjectIni.SetValue(strSection, strTrayLength, bolt->getTrayLength());
		mProjectIni.SetValue(strSection, strTrayMaterial, bolt->getTrayMaterial());

		SI_Error rc2 = mProjectIni.SaveFile(fileUrl);
		return rc2 < 0 ? false : true;
	};

	bool SaveCableToFile(CCable * cable) {
		CSimpleIni mProjectIni;
		SI_Error rc = mProjectIni.LoadFile(fileUrl);
		if (rc < 0) return false; // 若加载文件出错，返回false

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

		mProjectIni.SetDoubleValue(strCable, strDiameter, cable->getDiameter());
		mProjectIni.SetDoubleValue(strCable, strLength, cable->getLength());
		mProjectIni.SetDoubleValue(strCable, strTailing, cable->getTailing());
		mProjectIni.SetDoubleValue(strCable, strSpace, cable->getSpace());
		mProjectIni.SetDoubleValue(strCable, strPitch, cable->getPitch());
		mProjectIni.SetDoubleValue(strCable, strALength, cable->getALength());
		mProjectIni.SetDoubleValue(strCable, strTrayLength, cable->getTrayLength());
		mProjectIni.SetDoubleValue(strCable, strShuDiameter, cable->getShuDiameter());
		mProjectIni.SetDoubleValue(strCable, strShuLength, cable->getShuLength());
		mProjectIni.SetLongValue(strCable, strNumber, cable->getNumber());
		mProjectIni.SetValue(strCable, strMaterial, cable->getMaterial());
		mProjectIni.SetValue(strCable, strTrayMaterial, cable->getTrayMaterial());
		mProjectIni.SetValue(strCable, strShuMaterial, cable->getShuMaterial());

		SI_Error rc2 = mProjectIni.SaveFile(fileUrl);
		return rc2 < 0 ? false : true;

	};

	virtual bool SaveParametersToFile(){
		CSimpleIni mProjectIni;
		SI_Error rc = mProjectIni.LoadFile(fileUrl);
		if (rc < 0) return false; // 若加载文件出错，返回false

		bool res = true;

		res = SaveBoltToFile(CString("TopBolt"), mArcTunnel->GetTopBolt());
		if (res == false) return res;

		res =  SaveBoltToFile(CString("LeftBolt"), mArcTunnel->GetLeftBolt());
		if (res == false) return res;
		
		res = SaveBoltToFile(CString("RightBolt"), mArcTunnel->GetRightBolt());
		if (res == false) return res;

		res = SaveCableToFile(mArcTunnel->GetCable());
		if (res == false) return res;

		CString strThickness("Thickness");
		CString strConcreteThickness("ConcreteThickness");
		CString strQiThickness("QiThickness");

		switch (mArcTunnel->GetZhihuWay())
		{
		case 2:
		case 3:
		case 4:
			mProjectIni.SetLongValue(strThickness, strConcreteThickness, mArcTunnel->GetConcreteThickness());
			mProjectIni.SetLongValue(strThickness, strQiThickness, mArcTunnel->GetQiThickness());
			mProjectIni.SaveFile(fileUrl);
			res = true;
			break;
		default:
			break;
		}
		return res;
	};

	bool SaveTunnelInfoToFile() {
		CSimpleIni mProjectIni;
		SI_Error rc = mProjectIni.LoadFile(fileUrl);
		if (rc < 0) return false; // 若加载文件出错，返回false

		CString strArc("Arc");
		CString strWidth("Width");
		CString strArcHeight("ArcHeight");
		CString strWallHeight("WallHeight");
		CString strNormal("IsNormalToArc");
		CString strRect("Rectangle");
		CString strTrap("Trapzoid");
		CString strHeight("Height");
		
		switch (mTunnelProject->GetTunnelType())
		{
		case 1:
			mProjectIni.SetDoubleValue(strRect, strWidth, mArcTunnel->GetWidth());
			mProjectIni.SetDoubleValue(strRect, strHeight, mArcTunnel->GetWallHeight());
			break;
		case 2:
			mProjectIni.SetDoubleValue(strArc, strWidth, mArcTunnel->GetWidth());
			mProjectIni.SetDoubleValue(strArc, strArcHeight, mArcTunnel->GetArcHeight());
			mProjectIni.SetDoubleValue(strArc, strWallHeight, mArcTunnel->GetWallHeight());
			mProjectIni.SetBoolValue(strArc, strNormal, mArcTunnel->GetNormalToArc());
			break;
		case 3:
			//上底宽度
			mProjectIni.SetDoubleValue(strTrap, _T("TopWidth"), mArcTunnel->GetWidth());
			//下底宽度
			mProjectIni.SetDoubleValue(strTrap, _T("BottomWidth"), mArcTunnel->GetTrapBottomWidth());
			mProjectIni.SetDoubleValue(strTrap, strHeight, mArcTunnel->GetWallHeight());
			mProjectIni.SetLongValue(strTrap, _T("LeftAngle"), mArcTunnel->GetTrapLeftAngle());
			mProjectIni.SetLongValue(strTrap, _T("RightAngle"), mArcTunnel->GetTrapLeftAngle());
			break;
		default:
			break;
		}

		SI_Error rc2 = mProjectIni.SaveFile(fileUrl);
		return rc2 < 0 ? false : true;
	}

	virtual bool SaveTunnelFlagToFile() {
		CSimpleIni mProjectIni;
		CString strFlag("Flag");
		SI_Error rc = mProjectIni.LoadFile(fileUrl);
		if (rc < 0) return false; // 若加载文件出错，返回false

		CString strZhihuWay("ZhihuWay");
		CString strHasRevertAngle("HasRevertAngle");
		CString strCalMethod("CalMethod");
		CString strHasTopBolt("HasTopBolt");
		CString strHasLeftBolt("HasLeftBolt");
		CString strHasRightBolt("HasRightBolt");
		CString strHasCable("HasCable");

		std::cout << "bridge file zhihu way: " << strZhihuWay << std::endl;
		mProjectIni.SetLongValue(strFlag, strZhihuWay, mArcTunnel->GetZhihuWay());
		mProjectIni.SetBoolValue(strFlag, strHasRevertAngle, mArcTunnel->GetRevertAngle());
		mProjectIni.SetLongValue(strFlag, strCalMethod, mArcTunnel->GetCalMethod());
		mProjectIni.SetBoolValue(strFlag, strHasTopBolt, mArcTunnel->GetHasTopBolt());
		mProjectIni.SetBoolValue(strFlag, strHasLeftBolt, mArcTunnel->GetHasLeftBolt());
		mProjectIni.SetBoolValue(strFlag, strHasRightBolt, mArcTunnel->GetHasRightBolt());
		mProjectIni.SetBoolValue(strFlag, strHasCable, mArcTunnel->GetHasCable());

		std::cout << "going to save revert angle\n";
		CString strRevertAngle("RevertAngle");
		mProjectIni.SetDoubleValue(strRevertAngle, _T("TopAngle"), mArcTunnel->GetTopAngle());
		mProjectIni.SetDoubleValue(strRevertAngle, _T("LeftAngle"), mArcTunnel->GetLeftAngle());
		std::cout << "the save left angle value: " << mArcTunnel->GetLeftAngle() << std::endl;
		mProjectIni.SetDoubleValue(strRevertAngle, _T("RightAngle"), mArcTunnel->GetRightAngle());

		SI_Error rc2 = mProjectIni.SaveFile(fileUrl);
		return rc2 < 0 ? false : true;
	};

	virtual bool SaveMethodToFile() {
		switch (mArcTunnel->GetCalMethod())
		{
		case 1:
			return SaveTheoryMethod();
		case 2:
			return SaveExpMethod();
		case 3:
			return SaveLooseRangeMethod();
		case 4:
			return true;
		case 5:
			return SaveBalanceMethod();
		case 6:
			return SaveZuheliangMethod();
		default:
			return false;
		}
	}


	/* 保存工程信息 0：全部保存成功，1：保存工程信息失败 2：保存flag信息失败
		3. 保存巷道参数失败 4：保存锚杆参数失败 5：保存方法数据失败
	*/
	virtual int ProjectSaver() {

		int res = 0; 
		if ((SaveProjectToFile() == false)) {
			return res++;
		}
		if (SaveTunnelFlagToFile() == false) {
			return res++;
		}
		if (SaveTunnelInfoToFile() == false) {
			return res++;
		}
		if (SaveParametersToFile() == false) {
			return res++;
		}
		if (SaveMethodToFile() == false)
			return res++;
		return res;
	};

	bool SaveBridgeFile() {
		return SaveProjectToFile() && SaveTunnelFlagToFile() && SaveTunnelInfoToFile() && SaveParametersToFile();
	};

};

