#include "stdafx.h"
#include "DrawUtil.h"

CDrawUtil::CDrawUtil()
{
}

CDrawUtil::~CDrawUtil()
{
}

CFont * CDrawUtil::GetTitleFont()
{
	CFont * font = new CFont;
	font->CreateFont(20, 0, 0, 0, FW_BOLD, TRUE, FALSE, 0,
		ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial"));
	return nullptr;
}

//创建直线: 起点，终止点，宽度
AcDbObjectId CDrawUtil::AddPolyLine( AcGePoint2d &startPoint
	,  AcGePoint2d &endPoint, double width)
{
	AcGePoint2dArray points;
	points.append(startPoint);
	points.append(endPoint);
	return CDrawUtil::AddPolyLine(points, width);
}

AcDbObjectId CDrawUtil::AddPolyLine(AcGePoint2dArray points, double width) {
	//points个点共创建point.length-1条直线
	int numVertices = points.length();
	AcDbPolyline *pPolyLine = new AcDbPolyline(numVertices);
	for (int  i = 0; i < numVertices; i++)
	{
		pPolyLine->addVertexAt(i, points.at(i), 0, width, width);
	}
	return CDrawUtil::PostToModelSpace(pPolyLine);
}

//创建矩形
AcDbObjectId CDrawUtil::AddRectangle(const AcGePoint2d &leftBottom,const double width,const double height, double border)
{
	AcGePoint2d ptLeftBottom = leftBottom;
	AcGePoint2d ptLeftTop(leftBottom.x, leftBottom.y + height);
	AcGePoint2d ptRightBottom(leftBottom.x + width, leftBottom.y);
	AcGePoint2d ptRightTop(ptLeftBottom.x+width, ptLeftBottom.y + height);
	AcDbPolyline *pPoly = new AcDbPolyline(4);
	pPoly->addVertexAt(0, ptLeftBottom, 0, border, border);
	pPoly->addVertexAt(1, ptRightBottom, 0, border, border);
	pPoly->addVertexAt(2, ptRightTop, 0, border, border);
	pPoly->addVertexAt(3, ptLeftTop, 0, border, border);
	pPoly->setClosed(Adesk::kTrue);

	return CDrawUtil::PostToModelSpace(pPoly);
}

// 标注直线的长度 pt1: 标注起点 pt2: 标注终点 ptLine: 标注线上的点 length：直线长度，在方法中转为CString输出 angle：偏转角度
AcDbObjectId CDrawUtil::CreateDimAligned(AcGePoint2d pt1, AcGePoint2d pt2, AcGePoint2d ptLine, double length, int angle)
{
	AcCmColor colors;
	colors.setRGB(0, 164, 0);

	CString text;
	text.Format(_T("%.0lf"), length);
	AcGePoint3d ptStart(pt1.x, pt1.y, 0);
	AcGePoint3d ptEnd(pt2.x, pt2.y, 0);
	AcGePoint3d ptLine1(ptLine.x, ptLine.y, 0);
	AcDbAlignedDimension * dimension = new AcDbAlignedDimension(ptStart, ptEnd, ptLine1, text);
	dimension->setColor(colors);
	dimension->setDimtxt(1); // 设置文字大小
	dimension->setDimasz(1); // 设置箭头大小
	
	return CDrawUtil::PostToModelSpace(dimension);
}

AcDbObjectId CDrawUtil::CreateDimRotated(AcGePoint2d pt1Start, AcGePoint2d pt1End,
	AcGePoint2d pt2Start, AcGePoint2d pt2End,  AcGePoint2d ptArcCenter, double rotation)
{
	AcCmColor colors;
	colors.setRGB(252, 247, 135);

	CString text;

	text.Format(_T("%.1lf°"), arcToAngle(rotation));

	AcGePoint3d ptStart(pt1Start.x, pt1Start.y, 0);
	AcGePoint3d ptEnd(pt1End.x, pt1End.y, 0);
	AcGePoint3d ptStart2(pt2Start.x, pt2Start.y, 0);
	AcGePoint3d ptEnd2(pt2End.x, pt2End.y, 0);
	AcGePoint3d ptCenter(ptArcCenter.x, ptArcCenter.y, 0);

	AcDb2LineAngularDimension *pDim = new AcDb2LineAngularDimension(
		ptStart, ptEnd, ptStart2, ptEnd2, ptCenter, text
	);
	pDim->setDimtxt(1); // 设置文字大小
	pDim->setDimasz(0.1); // 设置箭头大小
	pDim->setColor(colors);

	return CDrawUtil::PostToModelSpace(pDim);
}





AcDbObjectId CDrawUtil::AddTrapzoid(AcGePoint2d & leftBottom, double width, double height, int leftAngle, int rightAngle, double border)
{
	AcGePoint2d ptLeftBottom = leftBottom;
	AcGePoint2d ptLeftTop(leftBottom.x + (height/ tan(angleToArc(leftAngle))), leftBottom.y + height);
	AcGePoint2d ptRightBottom(leftBottom.x + width, leftBottom.y);
	AcGePoint2d ptRightTop(ptRightBottom.x -( height / tan(angleToArc(rightAngle))), ptLeftTop.y);
	AcDbPolyline *pPoly = new AcDbPolyline(4);
	pPoly->addVertexAt(0, ptLeftBottom, 0, border, border);
	pPoly->addVertexAt(1, ptRightBottom, 0, border, border);
	pPoly->addVertexAt(2, ptRightTop, 0, border, border);
	pPoly->addVertexAt(3, ptLeftTop, 0, border, border);
	pPoly->setClosed(Adesk::kTrue);
	return CDrawUtil::PostToModelSpace(pPoly);
}

AcDbObjectId CDrawUtil::AddArc(AcGePoint2d ptStart, AcGePoint2d pt, AcGePoint2d ptEnd, double width)
{
	AcGeCircArc2d pArc(ptStart, pt, ptEnd);


	AcGePoint3d ptCenter(AcGePlane::kXYPlane, pArc.center());
	AcGeVector2d vecStart(ptStart.x - ptCenter.x, ptStart.y - ptCenter.y);
	AcGeVector2d vecEnd(ptEnd.x - ptCenter.x, ptEnd.y - ptCenter.y);
	double startAngle = vecStart.angle();
	double endAngle = vecEnd.angle();

	return CDrawUtil::AddArc(pArc.center(), pArc.radius(), startAngle, endAngle, width);
}


AcDbObjectId CDrawUtil::AddArc(AcGePoint2d ptCenter, double radius, double angleStart, double angleEnd, double width)
{
	AcGePoint2d pt1, pt2;

	pt1.x = ptCenter.x + radius * cos(angleStart);
	pt1.y = ptCenter.y + radius * sin(angleStart);
	pt2.x = ptCenter.x + radius * cos(angleEnd);
	pt2.y = ptCenter.y + radius * sin(angleEnd);

	// 创建多段线X
	AcDbPolyline *pPoly = new AcDbPolyline(3);
	pPoly->addVertexAt(0, pt1, tan((angleEnd - angleStart) / 4), width, width);
	pPoly->addVertexAt(1, pt2, 0, width, width);

	return CDrawUtil::PostToModelSpace(pPoly);
}

AcDbObjectId CDrawUtil::AddCircle(AcGePoint2d ptCenter, double radius)
{
	AcGePoint3d ptC(ptCenter.x, ptCenter.y, 0);
	AcGeVector3d vec(0, 0, 0.1);
	AcDbCircle *pCricle = new AcDbCircle(ptC, vec, radius);
	return CDrawUtil::PostToModelSpace(pCricle);
}



AcDbObjectId CDrawUtil::AddText(AcGePoint2d ptStart, CString str)
{
	AcGePoint3d pt(ptStart.x, ptStart.y, 0);
	AcDbText  *pTextEntity = new AcDbText(pt, str);
	return CDrawUtil::PostToModelSpace(pTextEntity);
}

AcDbObjectId CDrawUtil::AddText(AcGePoint2d ptStart, CString str, double height)
{
	AcGePoint3d pt(ptStart.x, ptStart.y, 0);
	AcDbText  *pTextEntity = new AcDbText(pt, str, AcDbObjectId::kNull, height, 0);
	return CDrawUtil::PostToModelSpace(pTextEntity);
}

AcDbObjectId CDrawUtil::AddHatch(const AcDbObjectIdArray & loopids, const TCHAR * patName, double patternScale, bool associative)
{
	AcDbHatch *pHatch = new AcDbHatch();
	AcGeVector3d vec(0, 0, 1);
	pHatch->setNormal(vec);
	pHatch->setElevation(0);
	pHatch->setAssociative(associative);
	pHatch->setPatternScale(patternScale);
	pHatch->setPattern(AcDbHatch::kPreDefined, patName);
	auto es = pHatch->appendLoop(AcDbHatch::kExternal, loopids);
	es = pHatch->evaluateHatch();

	AcDbObjectId hatchid = CDrawUtil::PostToModelSpace(pHatch);
	
	if (acdbOpenObject(pHatch, hatchid) == Acad::eOk)
	{
		AcDbObjectIdArray assocentids;
		pHatch->getAssocObjIds(assocentids);
		for (auto i = 0; i < assocentids.length(); i++)
		{
			AcDbEntity *pEntity = NULL;
			if (acdbOpenObject(pEntity, assocentids[i], AcDb::kForWrite) == Acad::eOk)
			{
				pEntity->addPersistentReactor(hatchid);
				pEntity->close();
			}
		}
		pHatch->close();
	}

	return hatchid;
}



AcDbObjectId CDrawUtil::AddTwoBoundaryHatch(const AcDbObjectIdArray & outter, const AcDbObjectIdArray & inner, const TCHAR * patName, double patternScale)
{
	AcDbHatch *pHatch = new AcDbHatch();
	AcGeVector3d vec(0, 0, 1);
	pHatch->setNormal(vec);
	pHatch->setElevation(0);
	pHatch->setAssociative(true);
	pHatch->setPatternScale(patternScale);
	pHatch->setPattern(AcDbHatch::kPreDefined, patName);
	auto es = pHatch->appendLoop(AcDbHatch::kExternal, outter);
	es = pHatch->appendLoop(AcDbHatch::kDefault, inner);
	es = pHatch->evaluateHatch();

	AcDbObjectId hatchid = CDrawUtil::PostToModelSpace(pHatch);

	if (acdbOpenObject(pHatch, hatchid) == Acad::eOk)
	{
		AcDbObjectIdArray assocentids;
		pHatch->getAssocObjIds(assocentids);
		for (auto i = 0; i < assocentids.length(); i++)
		{
			AcDbEntity *pEntity = NULL;
			if (acdbOpenObject(pEntity, assocentids[i], AcDb::kForWrite) == Acad::eOk)
			{
				pEntity->addPersistentReactor(hatchid);
				pEntity->close();
			}
		}
		pHatch->close();
	}

	return hatchid;
}

AcGePoint2d CDrawUtil::GetArcCenter(AcGePoint2d ptStart, AcGePoint2d ptLine, AcGePoint2d ptEnd)
{
	AcGeCircArc2d pArc(ptStart, ptLine, ptEnd);

	return pArc.center();
}


//将实体添加到模型空间
AcDbObjectId CDrawUtil::PostToModelSpace(AcDbEntity * pEnt)
{
	//检查输入参数的有效性
	assert(pEnt);

	//获得当前图形数据库的块表
	AcDbBlockTable *pBlkTbl = NULL;
	acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlkTbl, AcDb::kForRead);

	//获得模型空间对应的块表记录
	AcDbBlockTableRecord *pBLkTblRcd = NULL;
	pBlkTbl->getAt(ACDB_MODEL_SPACE, pBLkTblRcd, AcDb::kForWrite);
	pBlkTbl->close();

	//将实体添加到模型空间的块表记录
	AcDbObjectId entId;
	Acad::ErrorStatus errorStatus = pBLkTblRcd->appendAcDbEntity(entId, pEnt);
	if (errorStatus != Acad::eOk)
	{
		pBLkTblRcd->close();
		delete pEnt;
		pEnt = NULL;
		return AcDbObjectId::kNull;
	}

	//关闭模型空间表记录和实体
	pBLkTblRcd->close();
	pEnt->close();
	return entId;
}

// 角度转弧度用于计算
double CDrawUtil::angleToArc(double angle)
{
	double pi = asin(0.5) * 6;
	return angle *pi / 180;
}

// 弧度转角度
double CDrawUtil::arcToAngle(double arc) {
	double pi = asin(0.5) * 6;
	return arc * 180 / pi;
}

AcDbObjectId CDrawUtil::createTable(AcDbTable *&pTbl, AcGePoint2d ptPosition, const TCHAR *pTblStyle,
	const int nColLen, const int nRowLen)
{
	//pTbl = new AcDbTable();
	Acad::ErrorStatus es;

	// Set the Table Style
	AcDbDictionary *pDict = NULL;
	AcDbObjectId idTblStyle;
	acdbHostApplicationServices()->workingDatabase()->getTableStyleDictionary(pDict, AcDb::kForRead);
	es = pDict->getAt(pTblStyle, idTblStyle);
	pDict->close();

	if (Acad::eOk == es)	pTbl->setTableStyle(idTblStyle);
	AcGePoint3d ptStart(ptPosition.x, ptPosition.y, 0);
	pTbl->setPosition(ptStart);
	pTbl->setNumColumns(nColLen);
	pTbl->setNumRows(nRowLen); // you can also use insertRows() at later point
	pTbl->generateLayout(); // Very very important, else expect crashes later on
	//pTbl->setAutoScale(1, 1, true);
	return CDrawUtil::PostToModelSpace(pTbl);
}

CString CDrawUtil::dtostr(double d)
{
	CString str;
	str.Format(_T("%.2lf"), d);
	return str;
}

CString CDrawUtil::itostr(int i)
{
	CString str;
	str.Format(_T("%d"), i);
	return str;
}
