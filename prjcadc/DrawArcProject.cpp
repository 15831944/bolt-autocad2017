#include "stdafx.h"
#include "DrawArcProject.h"


CDrawArcProject::CDrawArcProject()
{
}


CDrawArcProject::~CDrawArcProject()
{
}

void CDrawArcProject::DrawArcTunnel()
{
	CSimpleIni ini;
	ini.SetUnicode();
	ini.LoadFile("D:\\Program Files\\Autodesk\\AutoCAD 2017\\ini\\test.ini");
	 double width = ini.GetDoubleValue(_T("arc"),_T("width"), NULL );
	 double wallHeight = ini.GetDoubleValue(_T("arc"), _T("wallHeight"), NULL);
	 double arcHeight = ini.GetDoubleValue(_T("arc"), _T("arcHeight"), NULL);
	 int normalToArc = ini.GetLongValue(_T("arc"), _T("isNormalToArc "), NULL);
	 CArcTunnel* arcTunnel = new CArcTunnel(width, wallHeight, arcHeight, BOOL(normalToArc));

	 arcTunnel ->DrawTunnel();
}
