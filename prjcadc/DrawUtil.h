#pragma once
class CDrawUtil
//���ƻ���ͼ�εĹ����ֱࣺ�ߡ����Ρ����ε�
{
public:
	CDrawUtil();
	~CDrawUtil();
	static CFont* GetTitleFont();
	static AcDbObjectId AddArc(AcGePoint2d ptStart, AcGePoint2d pt, AcGePoint2d ptEnd, double width);
	static AcDbObjectId AddPolyLine(AcGePoint2d & startPoint, AcGePoint2d & endPoint, double width);
	static AcDbObjectId AddPolyLine(AcGePoint2dArray points, double width);
	static AcDbObjectId AddRectangle(const AcGePoint2d & leftBottom, const double width, const double height, double border);
	static AcDbObjectId CreateDimAligned(AcGePoint2d pt1, AcGePoint2d pt2, AcGePoint2d ptLine, double length, int angle = 0);
	// ���ƽǶȱ�ע
	static AcDbObjectId CreateDimRotated(AcGePoint2d pt1Start, AcGePoint2d pt1End,
		AcGePoint2d pt2Start, AcGePoint2d pt2End, AcGePoint2d ptArcCenter, double rotation);
	static AcDbObjectId AddTrapzoid(AcGePoint2d &leftBottom,double width, double height, int leftAngle, int rightAngle, double border);
	// ���߻���
	static AcDbObjectId AddArc(AcGePoint2d ptCenter, double radius, double angleStart, double angleEnd, double width);
	static AcDbObjectId AddCircle(AcGePoint2d ptCenter, double radius);
	// ��ӵ����ı�
	static AcDbObjectId AddText(AcGePoint2d ptStart, CString str);
	static AcDbObjectId AddText(AcGePoint2d ptStart, CString str, double height);
	// ������
	static AcDbObjectId AddHatch(const AcDbObjectIdArray & loopids, const TCHAR * patName, double patternScale, bool associative);
	// ��������߽�����Ч��
	static AcDbObjectId AddTwoBoundaryHatch(const AcDbObjectIdArray & loopid1,
		const AcDbObjectIdArray & loopid2, const TCHAR * patName, double patternScale);
	static AcGePoint2d GetArcCenter(AcGePoint2d ptStart, AcGePoint2d ptLine, AcGePoint2d ptEnd);

	static AcDbObjectId PostToModelSpace(AcDbEntity *pEnt);
	static double angleToArc(double angle);
	static double arcToAngle(double arc);

	static AcDbObjectId createTable(AcDbTable *& pTbl, AcGePoint2d ptPosition,const TCHAR * pTblStyle, const int nColLen, const int nRowLen);
	static CString dtostr(double d);
	static CString itostr(int i);
};