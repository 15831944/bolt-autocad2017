#include "stdafx.h"
#include "RectangleTunnel.h"

CRectangleTunnel::CRectangleTunnel(double w, double h)
{
	// UI �е��������Ժ���Ϊ��λ��ͼ�е�����ȫ��/pScaleNumber
	width = w / pScaleNumber;
	height = h / pScaleNumber;
	mTopBoltAngle = CDrawUtil::angleToArc(mTopBoltAngle);
	mLeftBoltAngle = CDrawUtil::angleToArc(mLeftBoltAngle);
	mRightBoltAngle = CDrawUtil::angleToArc(mRightBoltAngle);
}

CRectangleTunnel::CRectangleTunnel(double w, double h, double tba, double lba, double rba)
{
	width = w / pScaleNumber;
	height = h / pScaleNumber;	
	mTopBoltAngle = CDrawUtil::angleToArc(tba);
	mLeftBoltAngle = CDrawUtil::angleToArc(lba);
	mRightBoltAngle = CDrawUtil::angleToArc(rba);
}


CRectangleTunnel::CRectangleTunnel(double w, double h, CBolt TopBolt)
{
	// UI �е��������Ժ���Ϊ��λ��ͼ�е�����ȫ��/pScaleNumber
	width = w/pScaleNumber;
	height = h/pScaleNumber;
	InitTopBoltPointArr(TopBolt);
}

CRectangleTunnel::CRectangleTunnel(double w, double h, double bta, double bba)
{
	width = w / pScaleNumber;
	height = h / pScaleNumber;
	mBangTopAngle = CDrawUtil::angleToArc(bta);
	mBangBottomAngle = CDrawUtil::angleToArc(bba);
}

CRectangleTunnel::CRectangleTunnel()
{
}

CRectangleTunnel::~CRectangleTunnel()
{
}

void CRectangleTunnel::DrawTunnel()
{

	AcGePoint2d ptLeftBottom(ptTunnelStart->x, ptTunnelStart->y); //������ε���ʼ���Ƶ�
	
	CDrawUtil::AddRectangle(ptLeftBottom, width, height, border);

	//���ƾ��ζ��泤�Ϳ�ı�ע
	AcGePoint2d ptLeftTop(ptLeftBottom.x, ptLeftBottom.y + height);
	AcGePoint2d ptRightBottom(ptLeftBottom.x + width, ptLeftBottom.y);
	AcGePoint2d ptWidth((ptLeftBottom.x + ptRightBottom.x) / 2, ptLeftBottom.y - 5);
	if (pZhihuWay == 1) {
		CDrawUtil::CreateDimAligned(ptLeftTop, *ptTunnelStart, AcGePoint2d(ptLeftTop.x + 5, ptLeftTop.y),
			height * pScaleNumber, 0);
	}
	else {
		double conThickness = pConcreteThickness / pScaleNumber;
		double qiThickness = pQiThickness / pScaleNumber;

		CDrawUtil::CreateDimAligned(ptLeftTop, *ptTunnelStart,
			AcGePoint2d(ptLeftTop.x + +conThickness + qiThickness + 5, ptLeftTop.y),
			height * pScaleNumber, 0);
	}
	CDrawUtil::CreateDimAligned(ptLeftBottom, ptRightBottom, ptWidth,width * pScaleNumber, 0);
}

void CRectangleTunnel::DrawTopBolt(CBolt bolt)
{

	// ���ζ������µ�����Ϊ��170,60�������ϱ��е�����Ϊ��170+width/2, 60 + height / 2)
	int number = bolt.getNumber();
	double space = double(bolt.getSpace() / pScaleNumber);
	double length = double(bolt.getLength() / pScaleNumber);
	double alength = double(bolt.getALength() / pScaleNumber);
	double beamWidth = double(bolt.getBeamWidth()) / pScaleNumber;
	AcGePoint2d ptTopMid(ptTunnelStart->x + (width / 2), ptTunnelStart->y + height);


	// ��ʼ�� mTopBoltsArr ����, ������ê����������ϵ������
	if (number % 2 == 0)
	{
		// ż����ê��,
		for (int i = 1; i <= (number / 2); i++)
		{
			AcGePoint2d ptLeft(ptTopMid.x - (0.5 * i * space), ptTopMid.y);
			AcGePoint2d ptRight(ptTopMid.x + (0.5 * i * space), ptTopMid.y);
			mTopBoltsArr->append(ptLeft);
			mTopBoltsArr->append(ptRight);
		}
	}
	else {
		// ������ê��
		mTopBoltsArr->append(ptTopMid);
		for (int i = 1; i <= (number / 2); i++)
		{
			AcGePoint2d ptLeft(ptTopMid.x - (i * space), ptTopMid.y);
			AcGePoint2d ptRight(ptTopMid.x + (i * space), ptTopMid.y);
			mTopBoltsArr->append(ptLeft);
			mTopBoltsArr->append(ptRight);
		}
	}
	// ����ê��
	for (int i = 0; i < mTopBoltsArr->length(); i++)
	{
		AcGePoint2d ptStart = mTopBoltsArr->at(i);
		AcGePoint2d ptEnd(ptStart.x - (cos(mTopBoltAngle) * length), ptStart.y + (sin(mTopBoltAngle) * length));
		CDrawUtil::AddPolyLine(ptStart, ptEnd, 0.3);
		AcGePoint2d ptAEnd(ptEnd.x + (alength * cos(mTopBoltAngle)), ptEnd.y - (sin(mTopBoltAngle) * alength));

		CDrawUtil::AddPolyLine(ptEnd, ptAEnd, 0.5); //������ߵ�ê�̳�
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

void CRectangleTunnel::InitTopBoltPointArr(CBolt bolt) {

}

void CRectangleTunnel::DrawTopTuoLiang(CBolt bolt)
{
	//����������������ߵ�ê������Ϊ(x,y), ���������ε���������Ϊ(x-2,double(y - beamWidth/pScaleNumber))��
	// ���Ϊ (number-1) * ��࣬�߶�Ϊ beamWidth/pScaleNumber
	// ����ߵ�ê�˺�����Ϊ mid-(number / 2 - 0.5) * space
	int number = bolt.getNumber();
	double pitch = double(bolt.getPitch()) / pScaleNumber;
	double beamWidth = double(bolt.getBeamWidth()) / pScaleNumber;
	double space = bolt.getSpace()/pScaleNumber;
	AcGePoint2d ptTopMid(ptTunnelStart->x + (width / 2), ptTunnelStart->y + height);
	double tmp = 0;
	if (number % 2 == 0)
	{
		tmp = number / 2 - 0.5;
	}
	else
	{
		tmp = number / 2;
	}
	AcGePoint2d ptLeftestBolt(ptTopMid.x - (tmp * space), ptTopMid.y); //�����ê�˵�����
	AcGePoint2d ptLeftBottom(ptLeftestBolt.x - 2, double(ptLeftestBolt.y - 0.5)); // �������ε����½�����
	CDrawUtil::AddRectangle(ptLeftBottom, space*(number-1) + 4, beamWidth, 0.1);
	
	// �ڶ���ͼ�л�����������
	AcGePoint2d ptNetCrossBase(170, 170);
	for (int i = 0; i < 8; i++)
	{
		AcGePoint2d ptTopViewTrayLeftBottom(ptLeftBottom.x, ptNetCrossBase.y + (i*pitch)-0.5);
		CDrawUtil::AddRectangle(ptTopViewTrayLeftBottom, space*(number - 1) + 4, beamWidth * 2, 0.07);
	}
}

void CRectangleTunnel::DrawTopViewNet(CBolt bolt)
{
	double beamWidth = double(bolt.getBeamWidth()) / pScaleNumber - 0.1;

	//����ͼ�����½���ʼ��
	AcGePoint2d ptNetCrossBase(170, 170);
	AcGePoint2d ptNetRowBase(ptNetCrossBase.x - 3, ptNetCrossBase.y);
	AcGePoint2d ptNetColBase(ptNetCrossBase.x, ptNetCrossBase.y-10);
	
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
		if (i != mTopBoltsArr->length() - 1 ) {
			// ����ע
			CDrawUtil::CreateDimAligned(ptNetColStart, AcGePoint2d(ptNetColStart.x + space, ptNetColStart.y ),
				AcGePoint2d(ptNetColStart.x, ptNetColStart.y + 5), space * pScaleNumber, 0);
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


void CRectangleTunnel::DrawLeftBolt(CBolt bolt)
{
	int number = bolt.getNumber();
	double space = double(bolt.getSpace()) / pScaleNumber;
	double length = double(bolt.getLength()) / pScaleNumber;
	double alength = double(bolt.getALength()) / pScaleNumber;
	double beamWidth = double(bolt.getBeamWidth()) / pScaleNumber;
	AcGePoint2d ptLeftMid(170, 60 + (height / 2));
	
	// ��ʼ�� mLeftBoltArr ����
	if (number % 2 == 0)
	{
		// ż����ê��,
		for (int i = 1; i <= (number/2); i++)
		{
			AcGePoint2d ptTop(ptLeftMid.x, ptLeftMid.y + (0.5 * i * space));
			AcGePoint2d ptBottom(ptLeftMid.x, ptLeftMid.y - (0.5 * i * space));
			mLeftBoltArr->append(ptTop);
			mLeftBoltArr->append(ptBottom);
		}
	}
	else {
		mLeftBoltArr->append(ptLeftMid);
		for (int i = 1; i <= ( number / 2); i++)
		{
			AcGePoint2d ptTop(ptLeftMid.x, ptLeftMid.y + ( i * space));
			AcGePoint2d ptBottom(ptLeftMid.x, ptLeftMid.y - ( i * space));
			mLeftBoltArr->append(ptTop);
			mLeftBoltArr->append(ptBottom);
		}
	}
	for (int i = 0; i < mLeftBoltArr->length(); i++)
	{
		AcGePoint2d ptStart = mLeftBoltArr->at(i);
		AcGePoint2d ptEnd(ptStart.x - (length * sin(mLeftBoltAngle)), ptStart.y + (length * cos(mLeftBoltAngle)));
		CDrawUtil::AddPolyLine(ptStart, ptEnd, 0.3); //������ê��
		AcGePoint2d ptAEnd(ptEnd.x +( alength* sin(mLeftBoltAngle)), ptEnd.y - (alength * cos(mLeftBoltAngle)));
		CDrawUtil::AddPolyLine(ptAEnd, ptEnd, 0.5); //����ê��ͷ

		if (i == 0)
		{
			CDrawUtil::CreateDimAligned(ptStart, ptEnd, AcGePoint2d(ptStart.x, ptStart.y + 2), bolt.getLength());
			CDrawUtil::CreateDimAligned(ptEnd, ptAEnd, AcGePoint2d(ptEnd.x, ptEnd.y - 2), bolt.getALength());
		}
		AcGePoint2d ptTrayLeftBottom(ptStart.x + beamWidth, ptStart.y - 0.5);
		CDrawUtil::AddRectangle(ptTrayLeftBottom, 0.5, 1, 0.1);
	}
}


// ͭ����ҵ�������ê�˵ķ�ʽ���˴������нǶȶ�Ϊ������
void CRectangleTunnel::DrawTongLeftBolt(CBolt bolt)
{
	int number = bolt.getNumber();
	double space = double(bolt.getSpace()) / pScaleNumber;
	double length = double(bolt.getLength()) / pScaleNumber;
	double alength = double(bolt.getALength()) / pScaleNumber;
	double beamWidth = double(bolt.getBeamWidth()) / pScaleNumber;
	AcGePoint2d ptLeftMid(170, 60 + (height / 2));

	// ��ʼ�� mLeftBoltArr ����
	if (number % 2 == 0)
	{
		// ż����ê��,
		for (int i = 1; i <= (number / 2); i++)
		{
			AcGePoint2d ptTop(ptLeftMid.x, ptLeftMid.y + (0.5 * i * space));
			AcGePoint2d ptBottom(ptLeftMid.x, ptLeftMid.y - (0.5 * i * space));
			mLeftBoltArr->append(ptTop);
			mLeftBoltArr->append(ptBottom);
		}
	}
	else {
		mLeftBoltArr->append(ptLeftMid);
		for (int i = 1; i <= (number / 2); i++)
		{
			AcGePoint2d ptTop(ptLeftMid.x, ptLeftMid.y + (i * space));
			AcGePoint2d ptBottom(ptLeftMid.x, ptLeftMid.y - (i * space));
			mLeftBoltArr->append(ptTop);
			mLeftBoltArr->append(ptBottom);
		}
	}

	int topPointId = GetMaxPointId(mLeftBoltArr);
	int bottomPointId = GetMinPointId(mLeftBoltArr);

	for (int i = 0; i < mLeftBoltArr->length(); i++)
	{

		if (i == topPointId) {
			AcGePoint2d ptStart = mLeftBoltArr->at(i);
			AcGePoint2d ptEnd(ptStart.x - (length * sin(mBangTopAngle)), ptStart.y + (length * cos(mBangTopAngle)));
			CDrawUtil::AddPolyLine(ptStart, ptEnd, 0.3); //������ê��
			AcGePoint2d ptAEnd(ptEnd.x + (alength* sin(mBangTopAngle)), ptEnd.y - (alength * cos(mBangTopAngle)));
			CDrawUtil::AddPolyLine(ptAEnd, ptEnd, 0.5); //����ê��ͷ

			AcGePoint2d ptTrayLeftBottom(ptStart.x + beamWidth, ptStart.y - 0.5);
			CDrawUtil::AddRectangle(ptTrayLeftBottom, 0.5, 1, 0.1);

			AcGePoint2d ptLine(ptStart.x - (2 * sin(mBangTopAngle)), ptStart.y + (2 * cos(mBangTopAngle)));
			CDrawUtil::CreateDimRotated(
				ptEnd, ptStart, ptStart, AcGePoint2d(ptStart.x, ptStart.y + 50), AcGePoint2d(ptStart.x - 1, ptStart.y + 1), mBangTopAngle);
		}
		else if (i == bottomPointId) {
			AcGePoint2d ptStart = mLeftBoltArr->at(i);
			AcGePoint2d ptEnd(ptStart.x - (length * sin(mBangBottomAngle)), ptStart.y - (length * cos(0-mBangBottomAngle)));
			CDrawUtil::AddPolyLine(ptStart, ptEnd, 0.3); //������ê��
			AcGePoint2d ptAEnd(ptEnd.x + (alength* sin(mBangBottomAngle)), ptEnd.y + (alength * cos(mBangBottomAngle)));
			CDrawUtil::AddPolyLine(ptAEnd, ptEnd, 0.5); //����ê��ͷ

			AcGePoint2d ptTrayLeftBottom(ptStart.x + beamWidth, ptStart.y - 0.5);
			CDrawUtil::AddRectangle(ptTrayLeftBottom, 0.5, 1, 0.1);

			AcGePoint2d ptLine(ptStart.x - (2 * sin(mBangTopAngle)), ptStart.y - (2 * cos(mBangTopAngle)));
			CDrawUtil::CreateDimRotated(ptStart, AcGePoint2d(ptStart.x, ptStart.y - 50),
				ptEnd, ptStart, AcGePoint2d(ptStart.x-1, ptStart.y - 1), mBangBottomAngle);
		}
		else {

			AcGePoint2d ptStart = mLeftBoltArr->at(i);
			AcGePoint2d ptEnd(ptStart.x - (length * sin(CDrawUtil::angleToArc(90))), ptStart.y + (length * cos(CDrawUtil::angleToArc(90))));
			CDrawUtil::AddPolyLine(ptStart, ptEnd, 0.3); //������ê��
			AcGePoint2d ptAEnd(ptEnd.x + (alength* sin(CDrawUtil::angleToArc(90))), ptEnd.y - (alength * cos(CDrawUtil::angleToArc(90))));
			CDrawUtil::AddPolyLine(ptAEnd, ptEnd, 0.5); //����ê��ͷ
			// ���е��ê�˻��Ʊ�ע
			if (i == 0)
			{
				CDrawUtil::CreateDimAligned(ptStart, ptEnd, AcGePoint2d(ptStart.x, ptStart.y + 2), bolt.getLength());
				CDrawUtil::CreateDimAligned(ptEnd, ptAEnd, AcGePoint2d(ptEnd.x, ptEnd.y - 2), bolt.getALength());
			}

			AcGePoint2d ptTrayLeftBottom(ptStart.x + beamWidth, ptStart.y - 0.5);
			CDrawUtil::AddRectangle(ptTrayLeftBottom, 0.5, 1, 0.1);
		}

	}
}




void CRectangleTunnel::DrawLeftTuoLiang(CBolt bolt)
{
	double beamWidth = double(bolt.getBeamWidth()) / pScaleNumber;
	double space = double(bolt.getSpace()) / pScaleNumber;
	double pitch = double(bolt.getPitch()) / pScaleNumber;
	int number = bolt.getNumber();
	// ����������
	int minId = GetMinPointId(mLeftBoltArr); //�ҵ�������ê�˵��������
	double min = mLeftBoltArr->at(minId).y;

	AcGePoint2d ptLeftBottom(mLeftBoltArr->at(minId).x, min - 2);
	CDrawUtil::AddRectangle(ptLeftBottom, beamWidth, space * (number-1) + 4, 0.1);

	AcGePoint2d ptCrossBase(ptTunnelStart->x - (width * 1.5), ptTunnelStart->y);
	// ������ͼ�������л�������
	for (int i = 0; i < 6; i++)
	{
		AcGePoint2d ptBeamLeftBottom(ptCrossBase.x - (i * pitch) - beamWidth, ptLeftBottom.y);
		CDrawUtil::AddRectangle(ptBeamLeftBottom, beamWidth * 2, space * (number - 1) + 4, 0.1);
	}
}

void CRectangleTunnel::DrawLeftViewNet(CBolt bolt)
{

	double beamWidth = double(bolt.getBeamWidth()) / pScaleNumber - 0.1;
	double space = double(bolt.getSpace()) / pScaleNumber;
	double pitch = double(bolt.getPitch()) / pScaleNumber;

	AcGePoint2d ptCrossBase(ptTunnelStart->x - (width * 1.5), ptTunnelStart->y);
	// ���ƾ���������������Ӧ����
	for (int i = 0; i < 2; i++)
	{
		AcGePoint2d ptStart(ptCrossBase.x + 5, ptCrossBase.y + (i * height));
		AcGePoint2d ptEnd(ptStart.x - (6 * pitch) - 5, ptStart.y);
		CDrawUtil::AddPolyLine(ptStart, ptEnd, 0.05);
	}

	int minId = GetMinPointId(mLeftBoltArr);
	// ������ê�˶�Ӧ�ĺ���
	for (int i = 0; i < mLeftBoltArr->length(); i++)
	{
		AcGePoint2d ptStart(ptCrossBase.x + 5, mLeftBoltArr->at(i).y);
		AcGePoint2d ptEnd(ptStart.x - (6 * pitch) - 5, ptStart.y);
		CDrawUtil::AddPolyLine(ptStart, ptEnd, 0.05);
		if (i != minId)
		{
			CDrawUtil::CreateDimAligned(ptStart, AcGePoint2d(ptStart.x , ptStart.y - space),
				AcGePoint2d(ptStart.x + 5, ptStart.y), space * pScaleNumber, 0);
		}
	}


	// �������ߣ����߳���Ϊ������ + 10,���Ϊ�ž�
	for (int i = 0; i < 6; i++)
	{
		AcGePoint2d ptStart(ptCrossBase.x - (i * pitch), ptCrossBase.y - 5);
		AcGePoint2d ptEnd(ptStart.x, ptStart.y + height + 10);
		CDrawUtil::AddPolyLine(ptStart, ptEnd, 0.05);
		if (i != 0)
		{
			CDrawUtil::CreateDimAligned(ptStart, AcGePoint2d(ptStart.x + pitch, ptStart.y),
				AcGePoint2d(ptStart.x, ptStart.y - 5), pitch * pScaleNumber, 0);
		}
	}

	// ������ͼ�л���ê������С����
	for (int i = 0; i < mLeftBoltArr->length(); i++)
	{
		// ����ÿһ�е�����
		for (int j = 0; j < 6; j++)
		{
			AcGePoint2d ptLeftBottom(ptCrossBase.x - beamWidth - (j*pitch), mLeftBoltArr->at(i).y -beamWidth);
			CDrawUtil::AddRectangle(ptLeftBottom, beamWidth * 2, beamWidth * 2, 0.05);
		}
	}
}

int CRectangleTunnel::GetMaxPointId(AcGePoint2dArray * arr) {
	double max = arr->at(0).y;
	int maxId = 0; //�ҵ�������ê�˵��������
	for (int i = 1; i < arr->length(); i++)
	{
		if (arr->at(i).y > max)
		{
			max = arr->at(i).y;
			maxId = i;
		}
	}
	return maxId;
}


int CRectangleTunnel::GetMinPointId(AcGePoint2dArray * arr) {
	double min = arr->at(0).y;
	int minId = 0; //�ҵ�������ê�˵��������
	for (int i = 1; i < arr->length(); i++)
	{
		if (arr->at(i).y < min)
		{
			min = arr->at(i).y;
			minId = i;
		}
	}
	return minId;
}

void CRectangleTunnel::DrawRightBolt(CBolt bolt)
{

	int number = bolt.getNumber();
	double space = double(bolt.getSpace()) / pScaleNumber;
	double length = double(bolt.getLength()) / pScaleNumber;
	double alength = double(bolt.getALength()) / pScaleNumber;
	double beamWidth = double(bolt.getBeamWidth()) / pScaleNumber;
	AcGePoint2d ptRightMid(ptTunnelStart->x + width, ptTunnelStart->y + (height / 2));

	// ��ʼ�� mRightBoltArr ����
	if (number % 2 == 0)
	{
		// ż����ê��,
		for (int i = 1; i <= (number / 2); i++)
		{
			AcGePoint2d ptTop(ptRightMid.x, ptRightMid.y + (0.5 * i * space));
			AcGePoint2d ptBottom(ptRightMid.x, ptRightMid.y - (0.5 * i * space));
			mRightBoltArr->append(ptTop);
			mRightBoltArr->append(ptBottom);
		}
	}
	else {
		mRightBoltArr->append(ptRightMid);
		for (int i = 1; i <= (number / 2); i++)
		{
			AcGePoint2d ptTop(ptRightMid.x, ptRightMid.y + (i * space));
			AcGePoint2d ptBottom(ptRightMid.x, ptRightMid.y - (i * space));
			mRightBoltArr->append(ptTop);
			mRightBoltArr->append(ptBottom);
		}
	}
	for (int i = 0; i < mRightBoltArr->length(); i++)
	{
		AcGePoint2d ptStart = mRightBoltArr->at(i);
		AcGePoint2d ptEnd(ptStart.x + (length * sin(mRightBoltAngle)), ptStart.y + (length * cos(mRightBoltAngle)));
		CDrawUtil::AddPolyLine(ptStart, ptEnd, 0.3); //������ê��
		AcGePoint2d ptAEnd(ptEnd.x - (alength * sin(mRightBoltAngle)), ptEnd.y - (alength * cos(mRightBoltAngle)));
		CDrawUtil::AddPolyLine(ptAEnd, ptEnd, 0.5); //����ê��ͷ

		if (i == 0)
		{
			CDrawUtil::CreateDimAligned(ptStart, ptEnd, AcGePoint2d(ptStart.x, ptStart.y + 2), bolt.getLength());
			CDrawUtil::CreateDimAligned(ptEnd, ptAEnd, AcGePoint2d(ptEnd.x, ptEnd.y - 2), bolt.getALength());
		}

		AcGePoint2d ptTrayLeftBottom(ptStart.x - beamWidth - 0.5, ptStart.y - 0.5);
		CDrawUtil::AddRectangle(ptTrayLeftBottom, 0.5, 1, 0.1); //��������
	}

}


// ͭ����ҵ�����Ұ�ê�˵ķ�ʽ
void CRectangleTunnel::DrawTongRightBolt(CBolt bolt)
{

	int number = bolt.getNumber();
	double space = double(bolt.getSpace()) / pScaleNumber;
	double length = double(bolt.getLength()) / pScaleNumber;
	double alength = double(bolt.getALength()) / pScaleNumber;
	double beamWidth = double(bolt.getBeamWidth()) / pScaleNumber;
	AcGePoint2d ptRightMid(ptTunnelStart->x + width, ptTunnelStart->y + (height / 2));

	// ��ʼ�� mRightBoltArr ����
	if (number % 2 == 0)
	{
		// ż����ê��,
		for (int i = 1; i <= (number / 2); i++)
		{
			AcGePoint2d ptTop(ptRightMid.x, ptRightMid.y + (0.5 * i * space));
			AcGePoint2d ptBottom(ptRightMid.x, ptRightMid.y - (0.5 * i * space));
			mRightBoltArr->append(ptTop);
			mRightBoltArr->append(ptBottom);
		}
	}
	else {
		mRightBoltArr->append(ptRightMid);
		for (int i = 1; i <= (number / 2); i++)
		{
			AcGePoint2d ptTop(ptRightMid.x, ptRightMid.y + (i * space));
			AcGePoint2d ptBottom(ptRightMid.x, ptRightMid.y - (i * space));
			mRightBoltArr->append(ptTop);
			mRightBoltArr->append(ptBottom);
		}
	}

	int topPointId = GetMaxPointId(mRightBoltArr);
	int bottomPointId = GetMinPointId(mRightBoltArr);

	for (int i = 0; i < mRightBoltArr->length(); i++)
	{

		if (i == topPointId) {
			AcGePoint2d ptStart = mRightBoltArr->at(i);
			AcGePoint2d ptEnd(ptStart.x + (length * sin(mBangTopAngle)), ptStart.y + (length * cos(mBangTopAngle)));
			CDrawUtil::AddPolyLine(ptStart, ptEnd, 0.3); //������ê��
			AcGePoint2d ptAEnd(ptEnd.x - (alength * sin(mBangTopAngle)), ptEnd.y - (alength * cos(mBangTopAngle)));
			CDrawUtil::AddPolyLine(ptAEnd, ptEnd, 0.5); //����ê��ͷ

			AcGePoint2d ptTrayLeftBottom(ptStart.x - beamWidth - 0.5, ptStart.y - 0.5);
			CDrawUtil::AddRectangle(ptTrayLeftBottom, 0.5, 1, 0.1); //��������
		}
		else if (i == bottomPointId) {
			AcGePoint2d ptStart = mRightBoltArr->at(i);
			AcGePoint2d ptEnd(ptStart.x + (length * sin(mBangBottomAngle)), ptStart.y - (length * cos(mBangBottomAngle)));
			CDrawUtil::AddPolyLine(ptStart, ptEnd, 0.3); //������ê��
			AcGePoint2d ptAEnd(ptEnd.x - (alength * sin(mBangBottomAngle)), ptEnd.y + (alength * cos(mBangBottomAngle)));
			CDrawUtil::AddPolyLine(ptAEnd, ptEnd, 0.5); //����ê��ͷ

			AcGePoint2d ptTrayLeftBottom(ptStart.x - beamWidth - 0.5, ptStart.y - 0.5);
			CDrawUtil::AddRectangle(ptTrayLeftBottom, 0.5, 1, 0.1); //��������
		}
		else {
			AcGePoint2d ptStart = mRightBoltArr->at(i);
			AcGePoint2d ptEnd(ptStart.x + (length * sin(CDrawUtil::angleToArc(90))), ptStart.y + (length * cos(CDrawUtil::angleToArc(90))));
			CDrawUtil::AddPolyLine(ptStart, ptEnd, 0.3); //������ê��
			AcGePoint2d ptAEnd(ptEnd.x - (alength * sin(CDrawUtil::angleToArc(90))), ptEnd.y - (alength * cos(CDrawUtil::angleToArc(90))));
			CDrawUtil::AddPolyLine(ptAEnd, ptEnd, 0.5); //����ê��ͷ

			AcGePoint2d ptTrayLeftBottom(ptStart.x - beamWidth - 0.5, ptStart.y - 0.5);
			CDrawUtil::AddRectangle(ptTrayLeftBottom, 0.5, 1, 0.1); //��������

			if (i == 0)
			{
				CDrawUtil::CreateDimAligned(ptStart, ptEnd, AcGePoint2d(ptStart.x, ptStart.y + 2), bolt.getLength());
				CDrawUtil::CreateDimAligned(ptEnd, ptAEnd, AcGePoint2d(ptEnd.x, ptEnd.y - 2), bolt.getALength());
			}
		}
	}

}

void CRectangleTunnel::DrawRightTuoLiang(CBolt bolt)
{
	double beamWidth = double(bolt.getBeamWidth()) / pScaleNumber;
	double space = double(bolt.getSpace()) / pScaleNumber;
	int number = bolt.getNumber();
	double pitch = double(bolt.getPitch()) / pScaleNumber;
	// ����������
	double min = mRightBoltArr->at(0).y;
	int minId = 0; //�ҵ�������ê�˵��������
	for (int i = 1; i < mRightBoltArr->length(); i++)
	{
		if (mRightBoltArr->at(i).y < min)
		{
			min = mRightBoltArr->at(i).y;
			minId = i;
		}
	}
	AcGePoint2d ptLeftBottom(mRightBoltArr->at(minId).x - beamWidth, min - 2);
	CDrawUtil::AddRectangle(ptLeftBottom, beamWidth, space * (number-1) + 4, 0.1);

	AcGePoint2d ptCrossBase(ptTunnelStart->x + (width *2.5), ptTunnelStart->y);
	// ������ͼ�������л�������
	for (int i = 0; i < 6; i++)
	{
		AcGePoint2d ptBeamLeftBottom(ptCrossBase.x + (i * pitch) - beamWidth, ptLeftBottom.y);
		CDrawUtil::AddRectangle(ptBeamLeftBottom, beamWidth * 2, space * (number - 1) + 4, 0.1);
	}

}



void CRectangleTunnel::DrawRightViewNet(CBolt bolt)
{
	AcGePoint2d ptCrossBase(ptTunnelStart->x + (width *2.5), ptTunnelStart->y);
	double beamWidth = double(bolt.getBeamWidth()) / pScaleNumber - 0.1;
	double space = double(bolt.getSpace()) / pScaleNumber;
	double pitch = double(bolt.getPitch()) / pScaleNumber;

	// ���ƾ���������������Ӧ����
	for (int i = 0; i < 2; i++)
	{
		AcGePoint2d ptStart(ptCrossBase.x - 5, ptCrossBase.y + (i * height));
		AcGePoint2d ptEnd(ptStart.x + (6 * pitch) + 5, ptStart.y);
		CDrawUtil::AddPolyLine(ptStart, ptEnd, 0.05);
	}

	int minId = GetMinPointId(mRightBoltArr);
	// ������ê�˶�Ӧ�ĺ��ߣ�ֱ�ӵ���mRightBoltArr �������꼴��
	for (int i = 0; i < mRightBoltArr->length(); i++)
	{
		AcGePoint2d ptStart(ptCrossBase.x - 5, mRightBoltArr->at(i).y);
		AcGePoint2d ptEnd(ptStart.x + (6 * pitch) + 5, ptStart.y);
		CDrawUtil::AddPolyLine(ptStart, ptEnd, 0.05);
		if (i != minId)
		{
			CDrawUtil::CreateDimAligned(ptStart, AcGePoint2d(ptStart.x, ptStart.y - space),
				AcGePoint2d(ptStart.x + 5, ptStart.y), space * pScaleNumber, 0);
		}
		
	}
	// �������ߣ����߳���Ϊ������ + 10,���Ϊ�ž�
	for (int i = 0; i < 6; i++)
	{
		AcGePoint2d ptStart(ptCrossBase.x + (i * pitch), ptCrossBase.y - 5);
		AcGePoint2d ptEnd(ptStart.x, ptStart.y + height + 10);
		CDrawUtil::AddPolyLine(ptStart, ptEnd, 0.05);
		if (i != 5)
		{
			CDrawUtil::CreateDimAligned(ptStart, AcGePoint2d(ptStart.x + pitch, ptStart.y),
				AcGePoint2d(ptStart.x, ptStart.y - 5), pitch * pScaleNumber, 0);
		}
	}

	// ������ͼ�л���ê������С����
	for (int i = 0; i < mRightBoltArr->length(); i++)
	{
		// ����ÿһ�е�����
		for (int j = 0; j < 6; j++)
		{
			AcGePoint2d ptLeftBottom(ptCrossBase.x - beamWidth + (j*pitch), mLeftBoltArr->at(i).y - beamWidth);
			CDrawUtil::AddRectangle(ptLeftBottom, beamWidth * 2, beamWidth * 2, 0.05);
		}
	}
}

void CRectangleTunnel::DrawCable(CCable cable)
{
	AcGePoint2d ptTopMid(ptTunnelStart->x + (width / 2), ptTunnelStart->y + height);
	
	int number = cable.getNumber();
	double space = cable.getSpace() / pScaleNumber;
	double length = cable.getLength() / pScaleNumber;
	double alength = cable.getALength() / pScaleNumber;
	double beamWidth = cable.getTrayLength();
	double pitch = cable.getPitch() / pScaleNumber;
	// ��ʼ�� mCableArr ����, ��ê����������ϵ������
	if (number % 2 == 0)
	{
		// ż����ê��,
		for (int i = 1; i <= (number / 2); i++)
		{
			AcGePoint2d ptLeft(ptTopMid.x - (0.5 * i * space), ptTopMid.y);
			AcGePoint2d ptRight(ptTopMid.x + (0.5 * i * space), ptTopMid.y);
			mCableArr->append(ptLeft);
			mCableArr->append(ptRight);
		}
	}
	else {
		// ������ê��
		mCableArr->append(ptTopMid);
		for (int i = 1; i <= (number / 2); i++)
		{
			AcGePoint2d ptLeft(ptTopMid.x - (i * space), ptTopMid.y);
			AcGePoint2d ptRight(ptTopMid.x + (i * space), ptTopMid.y);
			mCableArr->append(ptLeft);
			mCableArr->append(ptRight);
		}
	}

	for (int i = 0; i < mCableArr->length(); i++)
	{
		AcGePoint2d ptStart = mCableArr->at(i);
		AcGePoint2d ptEnd(0,0);
		if ( length <= 40)
		{
			ptEnd.x = ptStart.x - (cos(mTopBoltAngle) * length);
			ptEnd.y = ptStart.y + (sin(mTopBoltAngle) * length);
		}
		else {
			ptEnd.x = ptStart.x - (cos(mTopBoltAngle) * 40);
			ptEnd.y = ptStart.y + (sin(mTopBoltAngle) * 40);
			AcGePoint2d ptMid((ptEnd.x + ptStart.x) / 2, (ptStart.y + ptEnd.y) / 2);
			// �������¼ʡ�Է����ĸ���
			AcGePoint2d ptA(ptMid.x - 1, ptMid.y);
			AcGePoint2d ptB(ptMid.x + 1, ptMid.y);
			AcGePoint2d ptC(ptA.x, ptMid.y - 1);
			AcGePoint2d ptD(ptB.x, ptMid.y - 1);
			AcGePoint2dArray arr(4);
			arr.append(ptA);
			arr.append(ptB);
			arr.append(ptC);
			arr.append(ptD);
			CDrawUtil::AddPolyLine(arr, 0.3);
		}
		CDrawUtil::AddPolyLine(ptStart, ptEnd, 0.3);
		AcGePoint2d ptAEnd(ptEnd.x + (alength * cos(mTopBoltAngle)), ptEnd.y - (sin(mTopBoltAngle) * alength));

		CDrawUtil::AddPolyLine(ptEnd, ptAEnd, 0.5); //����ê��ͷ
		if (i == 0)
		{
			// ������ע�ߵĵ㣬����Ϊê�˺����� - 2
			AcGePoint2d ptDimLine(ptStart.x - 2, ptStart.y);
			CDrawUtil::CreateDimAligned(ptStart, ptEnd, ptDimLine, cable.getLength());
			// ��עê��ͷ����
			AcGePoint2d ptADimLine(ptStart.x + 2, ptEnd.y);
			CDrawUtil::CreateDimAligned(ptEnd, ptAEnd, ptADimLine, cable.getALength());
		}
		AcGePoint2d ptTrayLeftBottom(ptStart.x - 0.5, ptStart.y - beamWidth - 0.5);  // ��������
		CDrawUtil::AddRectangle(ptTrayLeftBottom, 1, 0.5, 0.1);

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
		AcGePoint2d ptMidCenter(mCableArr->at(0).x, yMid );
		CDrawUtil::CreateDimAligned(ptMidCenter, AcGePoint2d(mCableArr->at(0).x, yMid + pitch),
					AcGePoint2d(mCableArr->at(0).x + 3, yMid), pitch * pScaleNumber, 0);
		CDrawUtil::CreateDimAligned(ptMidCenter, AcGePoint2d(mCableArr->at(0).x, yMid - pitch),
					AcGePoint2d(mCableArr->at(0).x + 3, yMid), pitch * pScaleNumber, 0);
	}
	
}

void CRectangleTunnel::DrawBangBolt()
{
	DrawTongLeftBolt(*pLeftBolt);
	DrawLeftTuoLiang(*pLeftBolt);
	DrawLeftViewNet(*pLeftBolt);

	DrawTongRightBolt(*pLeftBolt);
	DrawRightTuoLiang(*pLeftBolt);
	DrawRightViewNet(*pLeftBolt);
}

// �Ȼ���������������Σ�������䷽ʽΪ��������ʽ��
// �ٻ����м�����������������䷽ʽΪ���ӷ�ʽ��
// ���������ڲ���Σ�������䷽ʽΪsolid
void CRectangleTunnel::DrawThickness()
{
	double conThickness = pConcreteThickness / pScaleNumber;
	double qiThickness = pQiThickness / pScaleNumber;

	// ���������ı߽����id
	AcDbObjectIdArray conArray = AcDbObjectIdArray();
	AcDbObjectIdArray tunnelArray = AcDbObjectIdArray();
	AcGePoint2d ptLeftBottom(ptTunnelStart->x, ptTunnelStart->y); //������ε���ʼ���Ƶ�
	//���id
	AcDbObjectId tunnelId = CDrawUtil::AddRectangle(ptLeftBottom, width, height, border);
	AcGePoint2d ptConLeftBottom(ptLeftBottom.x + conThickness, ptLeftBottom.y + conThickness);
	double conwidth = width - conThickness - conThickness,
		conheight = height - conThickness - conThickness;
	//���������ε�id
	AcDbObjectId conRecId = CDrawUtil::AddRectangle(ptConLeftBottom, conwidth, conheight, border);
	conArray.append(conRecId);
	tunnelArray.append(tunnelId);
	CDrawUtil::AddTwoBoundaryHatch(tunnelArray, conArray, _T("AR-CONC"), 0.015);

	// �������ı߽����id
	AcDbObjectIdArray qiArray = AcDbObjectIdArray();
	AcGePoint2d ptQiLeftBottom(ptConLeftBottom.x + qiThickness, ptConLeftBottom.y + qiThickness);
	double qiwidth = conwidth - qiThickness - qiThickness,
		qiheight = conheight - qiThickness - qiThickness;
	qiArray.append(CDrawUtil::AddRectangle(ptQiLeftBottom, qiwidth, qiheight, border));
	CDrawUtil::AddTwoBoundaryHatch(conArray,qiArray, _T("EARTH"), 0.2);


	//���ƺ����ע
	if (conThickness != 0) {
		CDrawUtil::CreateDimAligned(ptLeftBottom, AcGePoint2d(ptConLeftBottom.x, ptLeftBottom.y), AcGePoint2d(ptLeftBottom.x, ptLeftBottom.y - 3), conThickness * pScaleNumber);
	}
	if (qiThickness != 0) {
		CDrawUtil::CreateDimAligned(AcGePoint2d(ptQiLeftBottom.x + qiwidth, ptLeftBottom.y),
			AcGePoint2d(ptConLeftBottom.x+conwidth, ptLeftBottom.y), AcGePoint2d(ptQiLeftBottom.x, ptLeftBottom.y - 3), qiThickness * pScaleNumber);
	}
}


//���ݼ���ó������������������ڸı���ƶ���ͼ��������ê������Ҳ��ͬ��
