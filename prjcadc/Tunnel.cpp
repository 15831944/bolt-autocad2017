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
	project.GetPaperTitle(), 8.0);

	CDrawUtil::AddText(AcGePoint2d(383, 32) ,_T("±ÈÀý"));
	CDrawUtil::AddText(AcGePoint2d(404, 32), 
	project.GetScaleNumber());
	CDrawUtil::AddText(AcGePoint2d(383, 24),_T("±àºÅ"));
	CDrawUtil::AddText(AcGePoint2d(404, 24),
	project.GetPaperNumber());

	CDrawUtil::AddText(AcGePoint2d(260, 8),_T("ÉóºËÕß"));
	CDrawUtil::AddText(AcGePoint2d(275, 8),project.GetChecker());
	CDrawUtil::AddText(AcGePoint2d(296, 8),project.GetCheckDate(), 2.0);
	CDrawUtil::AddText(AcGePoint2d(260, 16),_T("Éè¼ÆÕß"));
	CDrawUtil::AddText(AcGePoint2d(275, 16),project.GetDesigner());
	CDrawUtil::AddText(AcGePoint2d(296, 16),project.GetDate(), 2.0);
	CDrawUtil::AddText(AcGePoint2d(330, 8),project.GetPaperDescription());

	CDrawUtil::AddText(AcGePoint2d(162, 43), project.GetPaperDescription() + " 1: " + project.GetScaleNumber(), 4.0);
	CDrawUtil::AddPolyLine(AcGePoint2d(162, 37), AcGePoint2d(225, 37), 0.5);
	CDrawUtil::AddPolyLine(AcGePoint2d(162, 35), AcGePoint2d(225, 35), 0.1);
}

void CTunnel::DrawTableBoltPm()
{
	double rowheight = 5, textheight = 1.4;
	AcDbTable * pFeatureTable = new AcDbTable();
	pFeatureTable->setNumColumns(9);
	pFeatureTable->setNumRows(4); // you can also use insertRows() at later point
	pFeatureTable->setTextHeight(3, AcDb::kTitleRow);
	pFeatureTable->setRowHeight(0, 7);
	pFeatureTable->setColumnWidth(12);
	for (int i = 1; i < 4; i++) {
		for (int j = 0; j < 9; j++) {
			pFeatureTable->setTextHeight(i, j, 2);
		}
	}
	for (int i = 1; i < 4; i++) {
		pFeatureTable->setRowHeight(i, 6);
	}
	pFeatureTable->setTextString(0, 0, _T("ÏïµÀ¶ÏÃæÌØÕ÷"));
	pFeatureTable->mergeCells(1, 2, 0, 0);
	pFeatureTable->mergeCells(1, 2, 1, 1);
	pFeatureTable->mergeCells(1, 1, 2, 4);
	pFeatureTable->mergeCells(1, 2, 5, 5);
	pFeatureTable->mergeCells(1, 1, 6, 7);
	pFeatureTable->mergeCells(1, 2, 8, 8);
	pFeatureTable->setTextString(1, 0, _T("Î§ÑÒ\nÀà±ð"));
	pFeatureTable->setTextString(1, 1, _T("Ö§»¤\n·½Ê½"));
	pFeatureTable->setTextString(1, 2, _T("¶ÏÃæ»ý£¨Æ½Ã×£©"));
	pFeatureTable->setTextString(2, 2, _T("¾»"));
	pFeatureTable->setTextString(2, 3, _T("¾ò"));
	pFeatureTable->setTextString(2, 4, _T("»ù´¡"));
	pFeatureTable->setTextString(1, 5, _T("ÅçÉäºñ¶È\n(mm)"));
	pFeatureTable->setTextString(1, 6, _T("¾ò½ø³ß´ç(mm)"));
	pFeatureTable->setTextString(2, 6, _T("¿í"));
	pFeatureTable->setTextString(2, 7, _T("¸ß"));
	pFeatureTable->setTextString(1, 8, _T("¾»ÖÜ³¤\n£¨m£©"));
	CDrawUtil::createTable(pFeatureTable, AcGePoint2d(280, 275), _T("Standard"), 9, 4);

	AcDbTable * pTbl = new AcDbTable();
	pTbl->setNumColumns(8);
	pTbl->setNumRows(16); // you can also use insertRows() at later point
	pTbl->setColumnWidth(15);
	pTbl->setTextHeight(3, AcDb::kTitleRow);
	pTbl->setRowHeight(0, 7);
	for (int i = 1; i < 16; i++) {
		for (int j = 0; j < 8; j++) {
			pTbl->setTextHeight(i, j, textheight);
		}
	}
	for(int i = 1; i < 16; i++){
		pTbl->setRowHeight(i, rowheight);
	}
	pTbl->setTextString(0, 0, _T("ÏïµÀ¶ÏÃæÃª¸Ë£¨Ë÷£©Ö§»¤²ÎÊý"));
	pTbl->setTextString(1, 0, _T("±íÏî"));
	pTbl->setTextString(1, 1, _T("Ö±¾¶(mm)"));
	pTbl->setTextString(1, 2, _T("³¤¶È(mm)"));
	pTbl->setTextString(1, 3, _T("²ÄÁÏÐÍºÅ"));
	pTbl->setTextString(1, 4, _T("Î²²¿ÂÝÎÆ³¤"));
	pTbl->setTextString(1, 5, _T("Ò©¾íÊýÁ¿(¸ù)"));
	pTbl->setTextString(1, 6, _T("¼ä¾à(mm)"));
	pTbl->setTextString(1, 7, _T("ÅÅ¾à(mm)"));
	pTbl->setTextString(1, 7, _T("ÅÅ¾à(mm)"));
	pTbl->setTextString(2, 0, _T("¶¥²¿Ãª¸Ë"));
	pTbl->setTextString(3, 0, _T("¶¥Ãª¸ËÍÐÁº"));
	pTbl->setTextString(4, 0, _T("¶¥Ãª¸ËÍÐÅÌ"));
	pTbl->setTextString(5, 0, _T("×ó°ïÃª¸Ë"));
	pTbl->setTextString(6, 0, _T("×ó°ïÃª¸ËÍÐÁº"));
	pTbl->setTextString(7, 0, _T("×ó°ïÃª¸ËÍÐÅÌ"));
	pTbl->setTextString(8, 0, _T("ÓÒ°ïÃª¸Ë"));
	pTbl->setTextString(9, 0, _T("ÓÒ°ïÃª¸ËÍÐÁº"));
	pTbl->setTextString(10, 0, _T("ÓÒ°ïÃª¸ËÍÐÅÌ"));
	pTbl->setTextString(11, 0, _T("ÃªË÷"));
	pTbl->setTextString(12, 0, _T("ÃªË÷ÍÐÅÌ"));
	pTbl->setTextString(13, 0, _T("¶¥²¿Íø"));
	pTbl->setTextString(14, 0, _T("°ï²¿Íø"));
	pTbl->setTextString(15, 0, _T("Ê÷Ö¬Ò©¾í"));
	pTbl->setTextString(2, 1, CDrawUtil::dtostr(pTopBolt->getDiameter()));
	pTbl->setTextString(2, 2, CDrawUtil::dtostr(pTopBolt->getLength()));
	pTbl->setTextString(2, 3, pTopBolt->getMaterial());
	pTbl->setTextString(2, 4, CDrawUtil::dtostr( pTopBolt->getTailing()));
	pTbl->setTextString(2, 5, CDrawUtil::itostr(pTopBolt->getNumber()));
	pTbl->setTextString(2, 6, CDrawUtil::dtostr(pTopBolt->getSpace()));
	pTbl->setTextString(2, 7, CDrawUtil::dtostr(pTopBolt->getPitch()));
	pTbl->setTextString(3, 3, pTopBolt->getBeamMaterial());
	pTbl->setTextString(4, 2, pTopBolt->getTrayLength());
	pTbl->setTextString(4, 3, pTopBolt->getTrayMaterial());
	// ×óÃª¸Ë²ÎÊý
	pTbl->setTextString(5, 1, CDrawUtil::dtostr(pLeftBolt->getDiameter()));
	pTbl->setTextString(5, 2, CDrawUtil::dtostr(pLeftBolt->getLength()));
	pTbl->setTextString(5, 3, pLeftBolt->getMaterial());
	pTbl->setTextString(5, 4, CDrawUtil::dtostr(pLeftBolt->getTailing()));
	pTbl->setTextString(5, 5, CDrawUtil::itostr(pLeftBolt->getNumber()));
	pTbl->setTextString(5, 6, CDrawUtil::dtostr(pLeftBolt->getSpace()));
	pTbl->setTextString(5, 7, CDrawUtil::dtostr(pLeftBolt->getPitch()));
	pTbl->setTextString(6, 3, pLeftBolt->getBeamMaterial());
	pTbl->setTextString(7, 2, pLeftBolt->getTrayLength());
	pTbl->setTextString(7, 3, pLeftBolt->getTrayMaterial());

	pTbl->setTextString(8, 1, CDrawUtil::dtostr(pLeftBolt->getDiameter()));
	pTbl->setTextString(8, 2, CDrawUtil::dtostr(pLeftBolt->getLength()));
	pTbl->setTextString(8, 3, pLeftBolt->getMaterial());
	pTbl->setTextString(8, 4, CDrawUtil::dtostr(pLeftBolt->getTailing()));
	pTbl->setTextString(8, 5, CDrawUtil::itostr(pLeftBolt->getNumber()));
	pTbl->setTextString(8, 6, CDrawUtil::dtostr(pLeftBolt->getSpace()));
	pTbl->setTextString(8, 7, CDrawUtil::dtostr(pLeftBolt->getPitch()));
	pTbl->setTextString(9, 3, pLeftBolt->getBeamMaterial());
	pTbl->setTextString(10, 2, pLeftBolt->getTrayLength());
	pTbl->setTextString(10, 3, pLeftBolt->getTrayMaterial());

	pTbl->setTextString(11, 1, CDrawUtil::dtostr(pCable->getDiameter()));
	pTbl->setTextString(11, 2, CDrawUtil::dtostr(pCable->getLength()));
	pTbl->setTextString(11, 3, pCable->getMaterial());
	pTbl->setTextString(11, 5, CDrawUtil::itostr(pCable->getNumber()));
	pTbl->setTextString(11, 6, CDrawUtil::dtostr(pCable->getSpace()));
	pTbl->setTextString(11, 7, CDrawUtil::dtostr(pCable->getPitch()));
	pTbl->setTextString(12, 3, pLeftBolt->getTrayMaterial());
	pTbl->setTextString(12, 2, pLeftBolt->getTrayLength());

	pTbl->setTextString(13, 3, _T("ÎÞ"));
	pTbl->setTextString(14, 3, _T("ÎÞ"));
	pTbl->setTextString(15, 1, CDrawUtil::dtostr(pCable->getShuDiameter()));
	pTbl->setTextString(15, 2, CDrawUtil::dtostr(pCable->getShuLength()));
	pTbl->setTextString(15, 3, pCable->getShuMaterial());
	CDrawUtil::createTable(pTbl, AcGePoint2d(280, 240),_T("Standard"), 8, 16);

	AcDbTable * pMaterialTable = new AcDbTable();
	pMaterialTable->setNumColumns(13);
	pMaterialTable->setNumRows(5); // you can also use insertRows() at later point
	pMaterialTable->setColumnWidth(12);
	pMaterialTable->setTextHeight(3, AcDb::kTitleRow);
	pMaterialTable->setRowHeight(0, 7);
	for (int i = 1; i < 5; i++) {
		for (int j = 0; j < 13; j++) {
			pMaterialTable->setTextHeight(i, j, 2);
		}
	}
	for (int i = 1; i < 5; i++) {
		pMaterialTable->setRowHeight(i, 6);
	}
	pMaterialTable->setRowHeight(3, 4.22);
	pMaterialTable->setRowHeight(4, 4.22);
	pMaterialTable->setTextString(0, 0, _T("ÏïµÀ²ÄÁÏÏûºÄ"));
	pMaterialTable->mergeCells(1, 1, 0, 5);
	pMaterialTable->mergeCells(1, 1, 7, 11);
	pMaterialTable->mergeCells(1, 3, 6, 6);
	pMaterialTable->mergeCells(1, 3, 12, 12);
	for(int i = 0; i < 13; i++){
		if (i != 6 && i != 12) {
			pMaterialTable->mergeCells(2, 3, i, i);
		}
	}

	pMaterialTable->setTextString(1, 0, _T("Ã¿Ã×²ÄÁÏÏûºÄÁ¿"));
	pMaterialTable->setTextString(1, 6, _T("·ÛË¢\nÃæ»ý\n(Æ½Ã×)"));
	pMaterialTable->setTextString(1, 7, _T("Ã¿Ã×»ìÄýÍÁÏûºÄÁ¿(Æ½Ã×)"));
	pMaterialTable->setTextString(1, 12, _T("Æ¬Ê¯\nÉ°½¬\n(Æ½Ã×)"));
	pMaterialTable->setTextString(2, 0, _T("Ãª¸Ë\n(¸ù)"));
	pMaterialTable->setTextString(2, 1, _T("ÍÐ°å\n(¸ö)"));
	pMaterialTable->setTextString(2, 2, _T("¸Ö½îÍø\n(Æ½Ã×)"));
	pMaterialTable->setTextString(2, 3, _T("Ê÷Ö¬\n(¾í)"));
	pMaterialTable->setTextString(2, 4, _T("ÅçÉä»ìÄýÍÁ\n(Æ½Ã×)"));
	pMaterialTable->setTextString(2, 5, _T("ÆÌµ×»ìÄýÍÁ\n(Æ½Ã×)"));
	pMaterialTable->setTextString(2, 7, _T("¹°"));
	pMaterialTable->setTextString(2, 8, _T("±Ú"));
	pMaterialTable->setTextString(2, 9, _T("»ù´¡"));
	pMaterialTable->setTextString(2, 10, _T("ÆÌµ×"));
	pMaterialTable->setTextString(2, 11, _T("Ð¡¼Æ"));
	CDrawUtil::createTable(pMaterialTable, AcGePoint2d(250, 150), _T("Standard"), 13, 5);
}

void CTunnel::DrawTopCastNet() {
	AcGePoint2d pt1Start(195, 210), pt1End(200, 207);
	for (int i = 0; i < 3; i++) {
		CDrawUtil::AddPolyLine(AcGePoint2d(pt1Start.x, pt1Start.y - i), AcGePoint2d(pt1End.x, pt1End.y - i), 0.05);
	}
	AcGePoint2d pt2Start(195, 207), pt2End(200, 210);
	for (int i = 0; i < 3; i++) {
		CDrawUtil::AddPolyLine(AcGePoint2d(pt2Start.x, pt2Start.y - i), AcGePoint2d(pt2End.x, pt2End.y - i), 0.05);
	}
}

void CTunnel::DrawBangCastNet() {
	AcGePoint2d pt1Start(75, 79), pt1End(80, 76);
	for (int i = 0; i < 3; i++) {
		CDrawUtil::AddPolyLine(AcGePoint2d(pt1Start.x, pt1Start.y - i), AcGePoint2d(pt1End.x, pt1End.y - i), 0.05);
	}
	AcGePoint2d pt2Start(75, 76), pt2End(80, 79);
	for (int i = 0; i < 3; i++) {
		CDrawUtil::AddPolyLine(AcGePoint2d(pt2Start.x, pt2Start.y - i), AcGePoint2d(pt2End.x, pt2End.y - i), 0.05);
	}
	AcGePoint2d pt3Start(310, 79), pt3End(315, 76);
	for (int i = 0; i < 3; i++) {
		CDrawUtil::AddPolyLine(AcGePoint2d(pt3Start.x, pt3Start.y - i), AcGePoint2d(pt3End.x, pt3End.y - i), 0.05);
	}
	AcGePoint2d pt4Start(310, 76), pt4End(315, 79);
	for (int i = 0; i < 3; i++) {
		CDrawUtil::AddPolyLine(AcGePoint2d(pt4Start.x, pt4Start.y - i), AcGePoint2d(pt4End.x, pt4End.y - i), 0.05);
	}
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

