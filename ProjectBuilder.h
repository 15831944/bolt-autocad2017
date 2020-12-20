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

	BOOL IsSavedToFile = TRUE;
	BOOL IsProjectSaveToInstance = FALSE;
	BOOL IsTunnelSaveToInstance = FALSE;
	BOOL IsMethodSaveToInstance = FALSE;
	BOOL IsCalMethodSaveToInstance = FALSE;

public:
	virtual void SetFileUrl(CString url) { fileUrl = url; };
	virtual CString GetFileUrl() const { return fileUrl; };	
	virtual void SetTunnelProject(CTunnelProject * p) { mTunnelProject = p; };
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
		SI_Error rc = mProjectIni.LoadFile(fileUrl);
		if (rc < 0) return false; // �������ļ�����������false

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

		SI_Error rc = mProjectIni.LoadFile(fileUrl);
		if (rc < 0) return false; // �������ļ�����������false
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

		SI_Error rc2 = mProjectIni.SaveFile(fileUrl);
		return rc2 < 0 ? false : true;
	}
	virtual bool SaveMethodToFile() { 
		return SaveTheoryMethod() || SaveExpMethod() || SaveLooseRangeMethod();
	};
	virtual bool SaveTunnelFlagToFile() {
		return false;
	};
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
		if (rc < 0) return false; // �������ļ�����������false

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
		 if (rc < 0) return false; // �������ļ�����������false

		 mProjectIni.SetLongValue(strExpMethod, strBoltNumber, project->GetBoltNumber());
		 mProjectIni.SetLongValue(strExpMethod, strCableNumber, project->GetCableNumber());
		 mProjectIni.SetLongValue(strExpMethod, strStoneType, project->GetStoneType());
		 mProjectIni.SetDoubleValue(strExpMethod, strBoltLength, project->GetBoltLength());
		 mProjectIni.SetDoubleValue(strExpMethod, strBoltDiameter, project->GetBoltDiameter());
		 mProjectIni.SetDoubleValue(strExpMethod, strBoltDesignNumber, project->GetBoltDesignNumber());
		 mProjectIni.SetDoubleValue(strExpMethod, strBoltAttach, project->GetBoltAttach());
		 mProjectIni.SetDoubleValue(strExpMethod, strBoltShuLength, project->GetBoltShuLength());
		 mProjectIni.SetDoubleValue(strExpMethod, strCableLength, project->GetCableLength());
		 mProjectIni.SetDoubleValue(strExpMethod, strCableSpace, project->GetCableSpace());
		 mProjectIni.SetDoubleValue(strExpMethod, strCablePitch, project->GetCablePitch());
		 mProjectIni.SetDoubleValue(strExpMethod, strCableAttach, project->GetCableAttach());
		 mProjectIni.SetDoubleValue(strExpMethod, strCableShuLength, project->GetCableShuLength());
		 mProjectIni.SetDoubleValue(strExpMethod, strCableBreakForce, project->GetCableBreakPower());

		 SI_Error rc2 = mProjectIni.SaveFile(fileUrl);
		 return rc2 < 0 ? false : true;
	 };
	 bool SaveLooseRangeMethod() { 
	 
		 CString strLooseRangeMethod("LooseRangeMethod");


		 CString strMeasureWay("MeasureWay");
		 CString strLooseRange("LooseRange");

		 CSimpleIni mProjectIni;

		 SI_Error rc = mProjectIni.LoadFile(fileUrl);
		 if (rc < 0) return false; // �������ļ�����������false

		 mProjectIni.SetLongValue(strLooseRangeMethod, strMeasureWay, loose->GetMeasureWay());
		 mProjectIni.SetLongValue(strLooseRangeMethod, strLooseRange, loose->GetLooseRange());

		 SI_Error rc2 = mProjectIni.SaveFile(fileUrl);
		 return rc2 < 0 ? false : true;
	 };
	
	CProjectBuilder()
	{
		//pProject = new CTunnelProject();
	}

	~CProjectBuilder()
	{
	}
};

class CArcProjectBuilder : public CProjectBuilder {
private:
	CArcTunnel * mArcTunnel;
public:
	CArcProjectBuilder() { mArcTunnel = new CArcTunnel();
	mTunnelProject = new CTunnelProject(); 
	theory = new CTheoryCalMethod();
	project = new CProExpMethod();
	loose = new CLooseRangeMethod();
	};
	~CArcProjectBuilder() { delete mArcTunnel; 
	delete mTunnelProject;
	delete theory;
	delete project;
	delete loose;
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
		SI_Error rc = mProjectIni.LoadFile(fileUrl);
		if (rc < 0) return false; // �������ļ�����������false
		 
		// ��ʼ���������������Ϣ�� FLAG ��־
		mArcTunnel->SetWidth(mProjectIni.GetDoubleValue(strArc, _T("Width")));
		mArcTunnel->SetArcHeight(mProjectIni.GetDoubleValue(strArc, _T("ArcHeight")));
		mArcTunnel->SetWallHeight(mProjectIni.GetDoubleValue(strArc, _T("WallHeight")));
		mArcTunnel->SetNormalToArc(mProjectIni.GetBoolValue(strArc, _T("IsNormalToArc")));

		mArcTunnel->SetZhihuWay(mProjectIni.GetLongValue(strFlag, _T("ZhihuWay")));
		mArcTunnel->SetHasRevertAngle(mProjectIni.GetBoolValue(strFlag, _T("HasRevertAngle")));
		mArcTunnel->SetCalMethod(mProjectIni.GetLongValue(strFlag, _T("CalMethod")));

		std::cout << "cal method: " << mArcTunnel->GetCalMethod() << std::endl;

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
		if (rc < 0) return nullptr; // �������ļ�����������false

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
		if (rc < 0) return nullptr; // �������ļ�����������false

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
		if (rc < 0) return false; // �������ļ�����������false
		
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
		switch (mArcTunnel->GetCalMethod())
		{
		case 1:
			factory = new CTheroyMethodFactory();
			method = factory->createMethod();
		 
			std::cout << "theory factory init\n";

			// ��̬ת��
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
			
			method->SetConcreteThickness(mProjectIni.GetLongValue(strThickness, strConcreteThickness));
			method->SetQiThickness(mProjectIni.GetLongValue(strThickness, strQiThickness));

			break;
		case 2:
			factory = new CProExpMethodFactory();
			method = factory->createMethod();

			// ��̬ת��
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
			method->SetConcreteThickness(mProjectIni.GetLongValue(strThickness, strConcreteThickness));
			method->SetQiThickness(mProjectIni.GetLongValue(strThickness, strQiThickness));
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
			method->SetConcreteThickness(mProjectIni.GetLongValue(strThickness, strConcreteThickness));
			method->SetQiThickness(mProjectIni.GetLongValue(strThickness, strQiThickness));

			break;
		case 4:
			factory = new CTheroyMethodFactory();
			method = factory->createMethod();

			method->SetConcreteThickness(mProjectIni.GetLongValue(strThickness, strConcreteThickness));
			method->SetQiThickness(mProjectIni.GetLongValue(strThickness, strQiThickness));
			break;
		default:

			break;
		}

		return true;

	}

	bool SaveBoltToFile(CString strSection, CBolt * bolt) {
		CSimpleIni mProjectIni;
		SI_Error rc = mProjectIni.LoadFile(fileUrl);
		if (rc < 0) return false; // �������ļ�����������false

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
		if (rc < 0) return false; // �������ļ�����������false

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
		if (rc < 0) return false; // �������ļ�����������false

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

			switch (mArcTunnel->GetCalMethod())
			{
			case 1:
			case 2:
			case 3:
			case 4:
				mProjectIni.SetLongValue(strThickness, strConcreteThickness, method->GetConcreteThickness());
				mProjectIni.SetLongValue(strThickness, strConcreteThickness, method->GetQiThickness());
				break;
			default:
				break;
			}
		return res;
	};

	bool SaveArcTunnelInfoToFile() {
		CSimpleIni mProjectIni;
		SI_Error rc = mProjectIni.LoadFile(fileUrl);
		if (rc < 0) return false; // �������ļ�����������false

		CString strArc("Arc");
		CString strWidth("Width");
		CString strArcHeight("ArcHeight");
		CString strWallHeight("WallHeight");
		CString strNormal("IsNormalToArc");

		mProjectIni.SetDoubleValue(strArc, strWidth, mArcTunnel->GetWidth());
		mProjectIni.SetDoubleValue(strArc, strArcHeight, mArcTunnel->GetArcHeight());
		mProjectIni.SetDoubleValue(strArc, strWallHeight, mArcTunnel->GetWallHeight());
		mProjectIni.SetBoolValue(strArc, strNormal, mArcTunnel->GetNormalToArc());
		SI_Error rc2 = mProjectIni.SaveFile(fileUrl);
		return rc2 < 0 ? false : true;
	}

	virtual bool SaveTunnelFlagToFile() {
		CSimpleIni mProjectIni;
		CString strFlag("Flag");
		SI_Error rc = mProjectIni.LoadFile(fileUrl);
		if (rc < 0) return false; // �������ļ�����������false

		CString strZhihuWay("ZhihuWay");
		CString strHasRevertAngle("HasRevertAngle");
		CString strCalMethod("CalMethod");
		CString strHasTopBolt("HasTopBolt");
		CString strHasLeftBolt("HasLeftBolt");
		CString strHasRightBolt("HasRightBolt");
		CString strHasCable("HasCable");

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
		default:
			return false;
		}
	}


	/* ���湤����Ϣ 0��ȫ������ɹ���1�����湤����Ϣʧ�� 2������flag��Ϣʧ��
		3. �����������ʧ�� 4������ê�˲���ʧ�� 5�����淽������ʧ��
	*/
	virtual int ProjectSaver() {

		int res = 0; 
		if ((SaveProjectToFile() == false)) {
			return res++;
		}
		if (SaveTunnelFlagToFile() == false) {
			return res++;
		}
		if (SaveArcTunnelInfoToFile() == false) {
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

		return SaveProjectToFile() && SaveTunnelFlagToFile() && SaveArcTunnelInfoToFile() && SaveParametersToFile();
		
	};

};