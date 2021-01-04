#include "stdafx.h"
#include "Tunnel.h"
#include "DrawUtil.h"
#include "ProjectBuilder.h"



CTunnel::CTunnel()
{
}


CTunnel::~CTunnel()
{
}

void CTunnel::DrawProject(CTunnelProject project)
{
	AcGePoint2d ptLeftBottom(255, 5);
	double border = 0.3;
	CDrawUtil::AddRectangle(ptLeftBottom, 160, 32, border);
	AcGePoint2d ptLeftMid(ptLeftBottom.x, ptLeftBottom.y + 16);
	CDrawUtil::AddPolyLine(ptLeftMid,
			AcGePoint2d(ptLeftMid.x + 160, ptLeftMid.y), border);
	CDrawUtil::AddPolyLine(AcGePoint2d(380, 21), AcGePoint2d(380, 37), border);
	CDrawUtil::AddPolyLine(AcGePoint2d(395, 21), AcGePoint2d(395, 37), border);
	CDrawUtil::AddPolyLine(AcGePoint2d(255, 13), AcGePoint2d(320, 13), border);
	CDrawUtil::AddPolyLine(AcGePoint2d(270, 5), AcGePoint2d(270, 21), border);
	CDrawUtil::AddPolyLine(AcGePoint2d(295, 5), AcGePoint2d(295, 21), border);
	CDrawUtil::AddPolyLine(AcGePoint2d(320, 5), AcGePoint2d(320, 21), border);
	CDrawUtil::AddPolyLine(AcGePoint2d(380, 29), AcGePoint2d(415, 29), border);
	CDrawUtil::AddText(AcGePoint2d(275, 25),
	project.GetPaperTitle(), 10.0);

	
	CDrawUtil::AddText(AcGePoint2d(383, 32) ,_T("比例"));
	CDrawUtil::AddText(AcGePoint2d(404, 32), 
		project.GetScaleNumber());
	CDrawUtil::AddText(AcGePoint2d(383, 24),_T("编号"));
	CDrawUtil::AddText(AcGePoint2d(404, 24),
		project.GetPaperNumber());

	CDrawUtil::AddText(AcGePoint2d(260, 8),_T("审核者"));
	CDrawUtil::AddText(AcGePoint2d(275, 8),
		project.GetChecker());
	CDrawUtil::AddText(AcGePoint2d(296, 8),
		project.GetCheckDate());
	CDrawUtil::AddText(AcGePoint2d(260, 16),_T("设计者"));
	CDrawUtil::AddText(AcGePoint2d(275, 16),
		project.GetDesigner());
	CDrawUtil::AddText(AcGePoint2d(296, 16),
		project.GetDate());
	CDrawUtil::AddText(AcGePoint2d(330, 8),
		project.GetPaperDescription());

}

void CTunnel::DrawTunnel()
{
}

void CTunnel::DrawTopTuoLiang(CBolt bolt)
{
}

void CTunnel::DrawTopBolt(CBolt bolt)
{
}

void CTunnel::DrawTopViewNet(CBolt bolt)
{
}

void CTunnel::DrawLeftBolt(CBolt bolt)
{

}

void CTunnel::DrawLeftTuoLiang(CBolt bolt)
{
}

void CTunnel::DrawLeftViewNet(CBolt bolt)
{
}

void CTunnel::DrawRightBolt(CBolt bolt)
{
}

void CTunnel::DrawRightTuoLiang(CBolt bolt)
{
}

void CTunnel::DrawRightViewNet(CBolt bolt)
{
}

void CTunnel::DrawCable(CCable cable)
{
}

