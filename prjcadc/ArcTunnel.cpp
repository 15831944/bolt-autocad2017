#include "stdafx.h"
#include "ArcTunnel.h"


CArcTunnel::CArcTunnel()
{
}

CArcTunnel::CArcTunnel(double w, double wh, double ah, bool flag)
{
	width = w / pScaleNumber;
	wallHeight = wh / pScaleNumber;
	arcHeight = ah / pScaleNumber;
	isCableNormalToArc = flag;
}

CArcTunnel::CArcTunnel(double w, double wh, double ah, bool flag, int tba, int lba, int rba)
{
	width = w / pScaleNumber;
	wallHeight = wh / pScaleNumber;
	arcHeight = ah / pScaleNumber;
	isCableNormalToArc = flag;
	pTopAngle = tba;
	pLeftAngle = lba;
	pRightAngle = rba;
}


CArcTunnel::~CArcTunnel()
{
}

void CArcTunnel::DrawTunnel()
{
	// ���������������
	AcGePoint2dArray ptArr =  AcGePoint2dArray();
	AcGePoint2d ptA(ptTunnelStart->x, ptTunnelStart->y + wallHeight);
	AcGePoint2d ptC(ptTunnelStart->x + width, ptTunnelStart->y);
	AcGePoint2d ptD(ptTunnelStart->x + width, ptTunnelStart->y + wallHeight);
	ptArr.append(ptA);
	ptArr.append(* ptTunnelStart);
	ptArr.append(ptC);
	ptArr.append(ptD);
	CDrawUtil::AddPolyLine(ptArr, border);
	// ���ƿ�ȡ�ֱǽ�߶Ⱥ͹��θ߶ȱ�ע

	if (pZhihuWay == 1) {
		CDrawUtil::CreateDimAligned(ptA, *ptTunnelStart, AcGePoint2d(ptA.x + 5, ptA.y), wallHeight * pScaleNumber, 0);
	}
	else {
		double conThickness = pConcreteThickness / pScaleNumber;
		double qiThickness = pQiThickness / pScaleNumber;
		
		CDrawUtil::CreateDimAligned(ptA, *ptTunnelStart, 
			AcGePoint2d(ptA.x + +conThickness + qiThickness+ 5, ptA.y), 
			wallHeight * pScaleNumber, 0);
	}
	
	CDrawUtil::CreateDimAligned(ptC, *ptTunnelStart, AcGePoint2d(ptC.x, ptC.y - 5), width * pScaleNumber, 0);
	// ���ƹ���
	AcGePoint2d ptE(ptTunnelStart->x + (width / 2), ptTunnelStart->y + wallHeight + arcHeight);
	CDrawUtil::AddArc(ptD, ptE, ptA, 0.2); // �ӻ�
	// ���Ʊ�ע
	CDrawUtil::CreateDimAligned(ptE,  AcGePoint2d(ptE.x, ptD.y), 
		AcGePoint2d(ptD.x, ptE.y),arcHeight * pScaleNumber
		, 0);

	AcGeCircArc2d pArc(ptD, ptE, ptA);
	AcGePoint2d tCenter = pArc.center();
	ptCenter->x = tCenter.x;
	ptCenter->y = tCenter.y;
	radius = pArc.radius();
	AcGeVector2d vecStart(ptD.x - tCenter.x, ptD.y - tCenter.y);
	AcGeVector2d vecEnd(ptA.x - tCenter.x, ptA.y - tCenter.y);
	 startAngle = vecStart.angle();
	 endAngle = vecEnd.angle();
}

void CArcTunnel::DrawTopBolt(CBolt bolt)
{

	int number = bolt.getNumber();
	double space = bolt.getSpace() / pScaleNumber;
	double length = bolt.getLength() / pScaleNumber;
	double alength = bolt.getALength() / pScaleNumber;
	double beamWidth = bolt.getBeamWidth() / pScaleNumber;
	AcGePoint2d ptArcMid(ptTunnelStart->x + (width / 2), ptTunnelStart->y + wallHeight + arcHeight);

	if (number % 2 == 0)
	{
		// ż����ê��
		for (int i = 1; i <= (number / 2); i++)
		{
			AcGePoint2d ptLeft(ptArcMid.x - (0.5 * i * space),
				ptCenter->y + sqrt((radius * radius) - ((0.5 * i * space) * (0.5 * i * space))) );
			AcGePoint2d ptRight(ptArcMid.x + (0.5 * i * space),
				ptCenter->y + sqrt((radius * radius) - ((0.5 * i * space) * (0.5 * i * space))));
			mTopBoltsArr->append(ptLeft);
			mTopBoltsArr->append(ptRight);
		}
	}
	else
	{
		mTopBoltsArr->append(ptArcMid);
		for (int i = 1; i <= (number / 2); i++)
		{
			AcGePoint2d ptLeft(ptArcMid.x - (i * space), ptCenter->y + 
				sqrt((radius * radius) - (i * space * i * space)));
			AcGePoint2d ptRight(ptArcMid.x + (i * space), ptCenter->y +
				sqrt((radius * radius) - (i * space * i * space)));
			mTopBoltsArr->append(ptLeft);
			mTopBoltsArr->append(ptRight);
		}
	}
	
	// ����ê��

	for (int i = 0; i < mTopBoltsArr->length(); i++)
	{
		if (isCableNormalToArc == TRUE)
		{
			pTopAngle = atan((mTopBoltsArr->at(i).x - ptCenter->x) / (mTopBoltsArr->at(i).y - ptCenter->y)) +( asin(0.5) * 3);
		}
		else
		{
			pTopAngle = CDrawUtil::angleToArc(90);
		}

		AcGePoint2d ptStart = mTopBoltsArr->at(i);
		AcGePoint2d ptEnd(ptStart.x - (cos(pTopAngle) * length), ptStart.y + (sin(pTopAngle) * length));
		CDrawUtil::AddPolyLine(ptStart, ptEnd, 0.3);
		AcGePoint2d ptAEnd(ptEnd.x + (alength * cos(pTopAngle)), ptEnd.y - (sin(pTopAngle) * alength));

		CDrawUtil::AddPolyLine(ptEnd, ptAEnd, 0.5); //����ê�̳�
		if (i == 0)
		{
			// ������ע�ߵĵ㣬����Ϊê�˺����� - 2
			AcGePoint2d ptDimLine(ptStart.x - 2, ptStart.y);
			CDrawUtil::CreateDimAligned(ptStart, ptEnd, ptDimLine, bolt.getLength());
			// ��עê��ͷ����
			AcGePoint2d ptADimLine(ptStart.x + 2, ptEnd.y);
			CDrawUtil::CreateDimAligned(ptEnd, ptAEnd, ptADimLine, bolt.getALength());
		}

		AcGePoint2d ptTrayLeftBottom(ptStart.x - 0.5, ptStart.y - beamWidth - 0.5);  // ��������
		CDrawUtil::AddRectangle(ptTrayLeftBottom, 1, 0.5, 0.1);
	}

}

void CArcTunnel::DrawTopTuoLiang(CBolt bolt)
{
	double beamWidth = bolt.getBeamWidth() / pScaleNumber;
	double pitch = bolt.getPitch() / pScaleNumber;
	int number = bolt.getNumber();
	double space = bolt.getSpace() / pScaleNumber;
	double min = mTopBoltsArr->at(0).x;
	int minId = 0; //�ҵ������ê�˵������
	double max = mTopBoltsArr->at(0).x;
	int maxId = 0;
	for (int i = 1; i < mTopBoltsArr->length(); i++)
	{
		if (mTopBoltsArr->at(i).x < min)
		{
			min = mTopBoltsArr->at(i).x;
			minId = i;
		}
		if (mTopBoltsArr->at(i). x > max)
		{
			max = mTopBoltsArr->at(i).x;
			maxId = i;
		}
	}


	AcGePoint2d ptA(min, mTopBoltsArr->at(minId).y - beamWidth);
	AcGePoint2d ptB(ptTunnelStart->x + (width / 2), ptTunnelStart->y + wallHeight + arcHeight - beamWidth);
	AcGePoint2d ptC(max, mTopBoltsArr->at(maxId).y - beamWidth);

	CDrawUtil::AddArc(ptC, ptB, ptA, 0.05);

	//CDrawUtil::AddArc(*ptCenter, radius - beamWidth, startAngle, endAngle, 0.05);
	CDrawUtil::AddPolyLine(ptA, mTopBoltsArr->at(minId), 0.1);
	CDrawUtil::AddPolyLine(ptC, mTopBoltsArr->at(maxId), 0.1);

	// �ڶ���ͼ�л�����������
	AcGePoint2d ptNetCrossBase(170, 170);
	for (int i = 0; i < 8; i++)
	{
		AcGePoint2d ptTopViewTrayLeftBottom(ptA.x, ptNetCrossBase.y + (i*pitch) - 0.5);
		CDrawUtil::AddRectangle(ptTopViewTrayLeftBottom, space*(number - 1) + 4, beamWidth * 2, 0.07);
	}
}

void CArcTunnel::DrawTopViewNet(CBolt bolt)
{
	double beamWidth = double(bolt.getBeamWidth()) / pScaleNumber - 0.1;

	//����ͼ�����½���ʼ��
	AcGePoint2d ptNetCrossBase(170, 170);
	AcGePoint2d ptNetRowBase(ptNetCrossBase.x - 3, ptNetCrossBase.y);
	AcGePoint2d ptNetColBase(ptNetCrossBase.x, ptNetCrossBase.y - 10);

	//���ߵĻ��Ʒ�������ƶ���ê�˵ķ�ʽ��ͬ
	double space = double(bolt.getSpace()) / pScaleNumber;
	double pitch = double(bolt.getPitch()) / pScaleNumber;
	for (int i = 0; i < 8; i++)
	{
		AcGePoint2d ptNetRowStart(ptNetRowBase.x, ptNetRowBase.y + (i * pitch));
		AcGePoint2d ptNetRowEnd(ptNetRowStart.x + width + 6, ptNetRowStart.y);
		// ���ư�������
		CDrawUtil::AddPolyLine(ptNetRowStart, ptNetRowEnd, 0.05);
		if (i != 0) {
			CDrawUtil::CreateDimAligned(ptNetRowStart, AcGePoint2d(ptNetRowStart.x, ptNetRowStart.y - pitch),
				AcGePoint2d(ptNetRowStart.x - 2, ptNetRowStart.y), pitch * pScaleNumber, 0);
		}
	}
	// ���ƾ��ε���������
	for (int i = 0; i < 2; i++)
	{
		AcGePoint2d ptNetColStart(ptNetColBase.x + (i * width), ptNetColBase.y);
		AcGePoint2d ptNetColEnd(ptNetColStart.x, ptNetColStart.y + (pitch * 7) + 15);
		CDrawUtil::AddPolyLine(ptNetColStart, ptNetColEnd, 0.05);
	}
	// ������ê�˶�Ӧ����������
	for (int i = 0; i < mTopBoltsArr->length(); i++)
	{
		AcGePoint2d point = mTopBoltsArr->at(i);
		AcGePoint2d ptNetColStart(point.x, ptNetColBase.y);
		AcGePoint2d ptNetColEnd(point.x, ptNetColBase.y + (pitch * 7) + 15);
		CDrawUtil::AddPolyLine(ptNetColStart, ptNetColEnd, 0.05);
		if (i != mTopBoltsArr->length() - 1) {
			// ����ע
			CDrawUtil::CreateDimAligned(ptNetColStart, AcGePoint2d(ptNetColStart.x + space, ptNetColStart.y),
				AcGePoint2d(ptNetColStart.x, ptNetColStart.y + 5), space *pScaleNumber, 0);
		}
		else
		{
			// ���ұ�ê��Ҫ����������ľ����ע
			// ���һ����Ϊ���ұߵĵ�
			CDrawUtil::CreateDimAligned(ptNetColStart, AcGePoint2d(ptNetColBase.x + width, ptNetColStart.y),
				AcGePoint2d(ptNetColStart.x, ptNetColStart.y + 5),
				(width - (space * (mTopBoltsArr->length() - 1))) / 2 * pScaleNumber, 0);
		}
		if (i == mTopBoltsArr->length() - 2)
		{
			// �����ڶ�����Ϊ����ߵĵ�
			CDrawUtil::CreateDimAligned(ptNetColStart, AcGePoint2d(ptNetColBase.x, ptNetColStart.y),
				AcGePoint2d(ptNetColStart.x, ptNetColStart.y + 5),
				(width - (space * (mTopBoltsArr->length() - 1))) / 2 * pScaleNumber, 0);
		}
	}

	// �ڶ���ͼ�л���ê������С����
	for (int i = 0; i < mTopBoltsArr->length(); i++)
	{
		// ����ÿһ�е�����
		for (int j = 0; j < 8; j++)
		{
			AcGePoint2d ptLeftBottom(mTopBoltsArr->at(i).x - beamWidth, ptNetCrossBase.y - beamWidth + (j * pitch));
			CDrawUtil::AddRectangle(ptLeftBottom, beamWidth * 2, beamWidth * 2, 0.05);
		}
	}
}

// ͭ����ҵ������Ϊ���Ұ���ͬ
void CArcTunnel::DrawBangBolt()
{ 
	// �˴���LeftAngle Ϊͼ�еİ���ϼнǣ�RightAngle Ϊͼ�������¼н�
	CRectangleTunnel * mRecTunnel = new CRectangleTunnel(
		width * pScaleNumber, wallHeight * pScaleNumber,
		 mBangLeftAngle, mBangRightAngle);

	mRecTunnel->DrawTongLeftBolt(*pLeftBolt);
	mRecTunnel->DrawLeftTuoLiang(*pLeftBolt);
	mRecTunnel->DrawLeftViewNet(*pLeftBolt);

	mRecTunnel->DrawTongRightBolt(*pLeftBolt);
	mRecTunnel->DrawRightTuoLiang(*pLeftBolt);
	mRecTunnel->DrawRightViewNet(*pLeftBolt);

}

void CArcTunnel::DrawCable()
{
	int number = pCable->getNumber();
	double space = pCable->getSpace() / pScaleNumber;
	double length = pCable->getLength() / pScaleNumber;
	double alength = pCable->getALength() / pScaleNumber;
	double beamWidth = pTopBolt->getBeamWidth() / pScaleNumber;
	double pitch = pCable->getPitch() / pScaleNumber;
	AcGePoint2d ptArcMid(ptTunnelStart->x + (width / 2), ptTunnelStart->y + wallHeight + arcHeight);

	if (number % 2 == 0)
	{
		// ż����ê��
		for (int i = 1; i <= (number / 2); i++)
		{

			AcGePoint2d ptLeft(ptArcMid.x - (0.5 * i * space),
				ptCenter->y + sqrt((radius * radius) - ((0.5 * i * space) * (0.5 * i * space))));
			AcGePoint2d ptRight(ptArcMid.x + (0.5 * i * space),
				ptCenter->y + sqrt((radius * radius) - ((0.5 * i * space) * (0.5 * i * space))));
			mCableArr->append(ptLeft);
			mCableArr->append(ptRight);
		}
	}
	else
	{
		mCableArr->append(ptArcMid);
		for (int i = 1; i <= (number / 2); i++)
		{
			AcGePoint2d ptLeft(ptArcMid.x - (i * space), ptCenter->y +
				sqrt((radius * radius) - (i * space * i * space)));
			AcGePoint2d ptRight(ptArcMid.x + (i * space), ptCenter->y +
				sqrt((radius * radius) - (i * space * i * space)));
			mCableArr->append(ptLeft);
			mCableArr->append(ptRight);
		}
	}

	// ����ê��
	for (int i = 0; i < mCableArr->length(); i++)
	{
		if (isCableNormalToArc == TRUE)
		{
			pTopAngle = atan((mCableArr->at(i).x - ptCenter->x) / (mCableArr->at(i).y - ptCenter->y)) + (asin(0.5) * 3);
		}
		else
		{
			pTopAngle = CDrawUtil::angleToArc(90);
		}

		AcGePoint2d ptStart = mCableArr->at(i);
		AcGePoint2d ptTrayLeftBottom(ptStart.x - 0.5, ptStart.y - beamWidth - 0.5);  // ��������
		CDrawUtil::AddRectangle(ptTrayLeftBottom, 1, 0.5, 0.1);
		

		AcGePoint2d ptEnd(ptStart.x - (cos(pTopAngle) * length), ptStart.y + (sin(pTopAngle) * length));
		CDrawUtil::AddPolyLine(ptStart, ptEnd, 0.3);
		AcGePoint2d ptAEnd(ptEnd.x + (alength * cos(pTopAngle)), ptEnd.y - (sin(pTopAngle) * alength));

		CDrawUtil::AddPolyLine(ptEnd, ptAEnd, 0.5); //����ê�̳�
		
		
		
		if (i == 0)
		{
			// ������ע�ߵĵ㣬����Ϊê�˺����� - 2
			AcGePoint2d ptDimLine(ptStart.x - 2, ptStart.y);
			CDrawUtil::CreateDimAligned(ptStart, ptEnd, ptDimLine, pCable->getLength());
			// ��עê��ͷ����
			AcGePoint2d ptADimLine(ptStart.x + 2, ptEnd.y);
			CDrawUtil::CreateDimAligned(ptEnd, ptAEnd, ptADimLine, pCable->getALength());
		}

		
		

		// �ڶ���ͼ�л���ê����ͼ

		AcGePoint2d ptNetCrossBase(170, 170);
		double yMid = ptNetCrossBase.y + (56 / 2);
		double radius = 0.5;
		for (int i = 0; i < mCableArr->length(); i++)
		{

			for (int j = 0; j < 2; j++)
			{
				AcGePoint2d ptCenter(mCableArr->at(i).x, yMid + (j * pitch));

				CDrawUtil::AddCircle(ptCenter, radius);
				CDrawUtil::AddRectangle(AcGePoint2d(ptCenter.x - 2.5, ptCenter.y - 1.25), 5, 2.5, 0.05);
				ptCenter.y = yMid - (j * pitch);
				CDrawUtil::AddCircle(ptCenter, radius);
				CDrawUtil::AddRectangle(AcGePoint2d(ptCenter.x - 2.5, ptCenter.y - 1.25), 5, 2.5, 0.05);
			}

		}
		AcGePoint2d ptMidCenter(mCableArr->at(0).x, yMid);
		CDrawUtil::CreateDimAligned(ptMidCenter, AcGePoint2d(mCableArr->at(0).x, yMid + pitch),
			AcGePoint2d(mCableArr->at(0).x + 3, yMid), pitch * pScaleNumber, 0);
		CDrawUtil::CreateDimAligned(ptMidCenter, AcGePoint2d(mCableArr->at(0).x, yMid - pitch),
			AcGePoint2d(mCableArr->at(0).x + 3, yMid), pitch * pScaleNumber, 0);
	}

}

void CArcTunnel::DrawThickness()
{
	double conThickness = pConcreteThickness / pScaleNumber;
	double qiThickness = pQiThickness / pScaleNumber;

	// ���������ı߽����id
	AcDbObjectIdArray conArray = AcDbObjectIdArray();

	// ��Ȧ������������Ͻ� A ���½�B ���½�C ���Ͻ�D
	AcGePoint2dArray ptArr = AcGePoint2dArray();
	AcGePoint2d ptA(ptTunnelStart->x, ptTunnelStart->y + wallHeight);
	AcGePoint2d ptC(ptTunnelStart->x + width, ptTunnelStart->y);
	AcGePoint2d ptD(ptTunnelStart->x + width, ptTunnelStart->y + wallHeight);

	//����������
	AcGePoint2dArray ptConArray = AcGePoint2dArray();
	AcGePoint2d ptLeftBottomLine(ptTunnelStart->x + conThickness, ptTunnelStart->y);
	AcGePoint2d ptLeftTopLine(ptTunnelStart->x + conThickness, ptTunnelStart->y + wallHeight),
		ptRightBottomLine(ptC.x - conThickness, ptC.y),
		ptRightTopLine(ptD.x - conThickness, ptD.y);

	
	ptArr.append(ptA);
	ptArr.append(*ptTunnelStart);
	ptArr.append(ptLeftBottomLine);
	ptArr.append(ptLeftTopLine);
	conArray.append(CDrawUtil::AddPolyLine(ptArr, border));

	// ���ƹ���
	AcGePoint2d ptE(ptTunnelStart->x + (width / 2), ptTunnelStart->y + wallHeight + arcHeight);
	conArray.append(CDrawUtil::AddArc(ptD, ptE, ptA, 0.2)); // �ӻ�

	ptConArray.append(ptRightTopLine);
	ptConArray.append(ptRightBottomLine);
	ptConArray.append(ptC);
	ptConArray.append(ptD);
	conArray.append(CDrawUtil::AddPolyLine(ptConArray, border));
	AcGePoint2d ptConArcTop(ptE.x, ptE.y - conThickness);
	conArray.append(CDrawUtil::AddArc(ptRightTopLine
		, ptConArcTop, ptLeftTopLine, 0.2)); // �ӻ�

	CDrawUtil::AddHatch(conArray, _T("AR-CONC"), 0.015, true);

	// �������ı߽����id
	AcDbObjectIdArray QiArray = AcDbObjectIdArray();
	AcGePoint2dArray ptQiLeftArray = AcGePoint2dArray();

	AcGePoint2d ptQiLeftBottomLine(ptTunnelStart->x + conThickness + qiThickness, ptTunnelStart->y);
	AcGePoint2d ptQiLeftTopLine(ptTunnelStart->x + conThickness + qiThickness, ptTunnelStart->y + wallHeight),
		ptQiRightBottomLine(ptC.x - conThickness - qiThickness, ptC.y),
		ptQiRightTopLine(ptD.x - conThickness - qiThickness, ptD.y);

	ptQiLeftArray.append(ptLeftTopLine);
	ptQiLeftArray.append(ptLeftBottomLine);
	ptQiLeftArray.append(ptQiLeftBottomLine);
	ptQiLeftArray.append(ptQiLeftTopLine);

	QiArray.append(CDrawUtil::AddPolyLine(ptQiLeftArray, 0.2));
	QiArray.append(CDrawUtil::AddArc(ptRightTopLine
		, ptConArcTop, ptLeftTopLine, 0.2));
	AcGePoint2dArray prQiRightArray = AcGePoint2dArray();
	
	prQiRightArray.append(ptQiRightTopLine);
	prQiRightArray.append(ptQiRightBottomLine);
	prQiRightArray.append(ptRightBottomLine);
	prQiRightArray.append(ptRightTopLine);
	QiArray.append(CDrawUtil::AddPolyLine(prQiRightArray, border));
	AcGePoint2d ptQiArcTop(ptE.x, ptE.y - conThickness - qiThickness);
	QiArray.append(CDrawUtil::AddArc(ptQiRightTopLine
		, ptQiArcTop, ptQiLeftTopLine, 0.2)); // �ӻ�

	CDrawUtil::AddHatch(QiArray, _T("EARTH"), 0.2, true);

	//���ƺ����ע
	if (conThickness != 0) {
		CDrawUtil::CreateDimAligned(*ptTunnelStart, AcGePoint2d(ptLeftBottomLine.x, ptTunnelStart->y) ,
			AcGePoint2d(ptTunnelStart->x, ptTunnelStart->y - 3), 
			conThickness * pScaleNumber);
	}
	if (qiThickness != 0) {
		CDrawUtil::CreateDimAligned(AcGePoint2d(ptRightBottomLine.x, ptTunnelStart->y), 
			AcGePoint2d(ptQiRightBottomLine.x, ptTunnelStart->y), AcGePoint2d(ptQiLeftBottomLine.x, ptTunnelStart->y - 3), qiThickness * pScaleNumber);
	}
}
