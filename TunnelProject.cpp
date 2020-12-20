#include "stdafx.h"
#include "TunnelProject.h"


CTunnelProject::CTunnelProject()
{
}

CTunnelProject::CTunnelProject(CString title,
CString Description,
CString ScaleNumber,
CString PaperNumber,
CString PaperSize, CString Designer,
CString Date,
CString Checker,
CString CheckDate,
CString DesignApart,
CString DevelopApart)
{
	mPaperTitle = title;
	mPaperDescription = Description;
	mScaleNumber = ScaleNumber;
	mPaperNumber = PaperNumber;
	mPaperSize = PaperSize;
	mDesigner = Designer;
	mDate = Date;
	mChecker = Checker;
	mCheckDate = CheckDate;
	mDesignApart = DesignApart;
	mDevelopApart = DevelopApart;
}

CTunnelProject::~CTunnelProject()
{
}
