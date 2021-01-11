#include "stdafx.h"
#include "RectangleTunnel.h"

CRectangleTunnel::CRectangleTunnel(double w, double h)
{
	// UI 中的坐标是以毫米为单位，图中的坐标全部/pScaleNumber
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
	// UI 中的坐标是以毫米为单位，图中的坐标全部/pScaleNumber
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

	AcGePoint2d ptLeftBottom(ptTunnelStart->x, ptTunnelStart->y); //巷道矩形的起始绘制点
	
	CDrawUtil::AddRectangle(ptLeftBottom, width, height, border);

	//绘制矩形断面长和宽的标注
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

	// 矩形断面左下点坐标为（170,60），故上边中点坐标为（170+width/2, 60 + height / 2)
	int number = bolt.getNumber();
	double space = double(bolt.getSpace() / pScaleNumber);
	double length = double(bolt.getLength() / pScaleNumber);
	double alength = double(bolt.getALength() / pScaleNumber);
	double beamWidth = double(bolt.getBeamWidth()) / pScaleNumber;
	AcGePoint2d ptTopMid(ptTunnelStart->x + (width / 2), ptTunnelStart->y + height);


	// 初始化 mTopBoltsArr 数组, 即顶部锚杆在巷道边上的坐标点
	if (number % 2 == 0)
	{
		// 偶数根锚杆,
		for (int i = 1; i <= (number / 2); i++)
		{
			AcGePoint2d ptLeft(ptTopMid.x - (0.5 * i * space), ptTopMid.y);
			AcGePoint2d ptRight(ptTopMid.x + (0.5 * i * space), ptTopMid.y);
			mTopBoltsArr->append(ptLeft);
			mTopBoltsArr->append(ptRight);
		}
	}
	else {
		// 奇数根锚杆
		mTopBoltsArr->append(ptTopMid);
		for (int i = 1; i <= (number / 2); i++)
		{
			AcGePoint2d ptLeft(ptTopMid.x - (i * space), ptTopMid.y);
			AcGePoint2d ptRight(ptTopMid.x + (i * space), ptTopMid.y);
			mTopBoltsArr->append(ptLeft);
			mTopBoltsArr->append(ptRight);
		}
	}
	// 绘制锚杆
	for (int i = 0; i < mTopBoltsArr->length(); i++)
	{
		AcGePoint2d ptStart = mTopBoltsArr->at(i);
		AcGePoint2d ptEnd(ptStart.x - (cos(mTopBoltAngle) * length), ptStart.y + (sin(mTopBoltAngle) * length));
		CDrawUtil::AddPolyLine(ptStart, ptEnd, 0.3);
		AcGePoint2d ptAEnd(ptEnd.x + (alength * cos(mTopBoltAngle)), ptEnd.y - (sin(mTopBoltAngle) * alength));

		CDrawUtil::AddPolyLine(ptEnd, ptAEnd, 0.5); //绘制左边的锚固长
		if (i == 0)
		{
			// 经过标注线的点，设置为锚杆横坐标 - 2
			AcGePoint2d ptDimLine(ptStart.x - 2, ptStart.y);
			CDrawUtil::CreateDimAligned(ptStart, ptEnd, ptDimLine, bolt.getLength());
			// 标注锚固头长度
			AcGePoint2d ptADimLine(ptStart.x + 2, ptEnd.y);
			CDrawUtil::CreateDimAligned(ptEnd, ptAEnd, ptADimLine, bolt.getALength());
		}

		AcGePoint2d ptTrayLeftBottom(ptStart.x - 0.5, ptStart.y - beamWidth - 0.5);  // 绘制托盘
		CDrawUtil::AddRectangle(ptTrayLeftBottom, 1, 0.5, 0.1);
	}
}

void CRectangleTunnel::InitTopBoltPointArr(CBolt bolt) {

}

void CRectangleTunnel::DrawTopTuoLiang(CBolt bolt)
{
	//绘制托梁：设最左边的锚杆坐标为(x,y), 则托梁矩形的左下坐标为(x-2,double(y - beamWidth/pScaleNumber))，
	// 宽度为 (number-1) * 间距，高度为 beamWidth/pScaleNumber
	// 最左边的锚杆横坐标为 mid-(number / 2 - 0.5) * space
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
	AcGePoint2d ptLeftestBolt(ptTopMid.x - (tmp * space), ptTopMid.y); //最左边锚杆的坐标
	AcGePoint2d ptLeftBottom(ptLeftestBolt.x - 2, double(ptLeftestBolt.y - 0.5)); // 托梁矩形的左下角坐标
	CDrawUtil::AddRectangle(ptLeftBottom, space*(number-1) + 4, beamWidth, 0.1);
	
	// 在顶视图中绘制托梁矩形
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

	//顶视图的左下角起始点
	AcGePoint2d ptNetCrossBase(170, 170);
	AcGePoint2d ptNetRowBase(ptNetCrossBase.x - 3, ptNetCrossBase.y);
	AcGePoint2d ptNetColBase(ptNetCrossBase.x, ptNetCrossBase.y-10);
	
	//竖线的绘制方法与绘制顶部锚杆的方式相同
	double space = double(bolt.getSpace()) / pScaleNumber;
	double pitch = double(bolt.getPitch()) / pScaleNumber;
	for (int i = 0; i < 8; i++)
	{
		AcGePoint2d ptNetRowStart(ptNetRowBase.x, ptNetRowBase.y + (i * pitch));
		AcGePoint2d ptNetRowEnd(ptNetRowStart.x + width + 6, ptNetRowStart.y);
		// 绘制八条横线
		CDrawUtil::AddPolyLine(ptNetRowStart, ptNetRowEnd, 0.05);
		if (i != 0) {
			CDrawUtil::CreateDimAligned(ptNetRowStart, AcGePoint2d(ptNetRowStart.x, ptNetRowStart.y - pitch),
				AcGePoint2d(ptNetRowStart.x - 2, ptNetRowStart.y), pitch * pScaleNumber, 0);
		}
	}
	// 绘制矩形的两条竖边
	for (int i = 0; i < 2; i++)
	{
		AcGePoint2d ptNetColStart(ptNetColBase.x + (i * width), ptNetColBase.y);
		AcGePoint2d ptNetColEnd(ptNetColStart.x, ptNetColStart.y + (pitch * 7) + 15);
		CDrawUtil::AddPolyLine(ptNetColStart, ptNetColEnd, 0.05);
	}
	// 绘制与锚杆对应的网格竖线
	for (int i = 0; i < mTopBoltsArr->length(); i++)
	{
		AcGePoint2d point = mTopBoltsArr->at(i);
		AcGePoint2d ptNetColStart(point.x, ptNetColBase.y);
		AcGePoint2d ptNetColEnd(point.x, ptNetColBase.y + (pitch * 7) + 15);
		CDrawUtil::AddPolyLine(ptNetColStart, ptNetColEnd, 0.05);
		if (i != mTopBoltsArr->length() - 1 ) {
			// 间距标注
			CDrawUtil::CreateDimAligned(ptNetColStart, AcGePoint2d(ptNetColStart.x + space, ptNetColStart.y ),
				AcGePoint2d(ptNetColStart.x, ptNetColStart.y + 5), space * pScaleNumber, 0);
		}
		else
		{
			// 最右边锚杆要绘制与巷道的距离标注
			// 最后一个点为最右边的点
			CDrawUtil::CreateDimAligned(ptNetColStart, AcGePoint2d(ptNetColBase.x + width, ptNetColStart.y),
				AcGePoint2d(ptNetColStart.x, ptNetColStart.y + 5),
				(width - (space * (mTopBoltsArr->length() - 1))) / 2 * pScaleNumber, 0);
		}
		 if (i == mTopBoltsArr->length() - 2)
		{
			// 倒数第二个点为最左边的点
		CDrawUtil::CreateDimAligned(ptNetColStart, AcGePoint2d(ptNetColBase.x, ptNetColStart.y),
				AcGePoint2d(ptNetColStart.x, ptNetColStart.y + 5),
				(width - (space * (mTopBoltsArr->length() - 1))) / 2 * pScaleNumber, 0);
		 }
	}

	// 在顶视图中绘制锚杆托盘小矩形
	for (int i = 0; i < mTopBoltsArr->length(); i++)
	{
		// 绘制每一列的托盘
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
	
	// 初始化 mLeftBoltArr 数组
	if (number % 2 == 0)
	{
		// 偶数根锚杆,
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
		CDrawUtil::AddPolyLine(ptStart, ptEnd, 0.3); //绘制左锚杆
		AcGePoint2d ptAEnd(ptEnd.x +( alength* sin(mLeftBoltAngle)), ptEnd.y - (alength * cos(mLeftBoltAngle)));
		CDrawUtil::AddPolyLine(ptAEnd, ptEnd, 0.5); //绘制锚固头

		if (i == 0)
		{
			CDrawUtil::CreateDimAligned(ptStart, ptEnd, AcGePoint2d(ptStart.x, ptStart.y + 2), bolt.getLength());
			CDrawUtil::CreateDimAligned(ptEnd, ptAEnd, AcGePoint2d(ptEnd.x, ptEnd.y - 2), bolt.getALength());
		}
		AcGePoint2d ptTrayLeftBottom(ptStart.x + beamWidth, ptStart.y - 0.5);
		CDrawUtil::AddRectangle(ptTrayLeftBottom, 0.5, 1, 0.1);
	}
}


// 铜川矿业绘制左帮锚杆的方式，此处的所有角度都为弧度制
void CRectangleTunnel::DrawTongLeftBolt(CBolt bolt)
{
	int number = bolt.getNumber();
	double space = double(bolt.getSpace()) / pScaleNumber;
	double length = double(bolt.getLength()) / pScaleNumber;
	double alength = double(bolt.getALength()) / pScaleNumber;
	double beamWidth = double(bolt.getBeamWidth()) / pScaleNumber;
	AcGePoint2d ptLeftMid(170, 60 + (height / 2));

	// 初始化 mLeftBoltArr 数组
	if (number % 2 == 0)
	{
		// 偶数根锚杆,
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
			CDrawUtil::AddPolyLine(ptStart, ptEnd, 0.3); //绘制左锚杆
			AcGePoint2d ptAEnd(ptEnd.x + (alength* sin(mBangTopAngle)), ptEnd.y - (alength * cos(mBangTopAngle)));
			CDrawUtil::AddPolyLine(ptAEnd, ptEnd, 0.5); //绘制锚固头

			AcGePoint2d ptTrayLeftBottom(ptStart.x + beamWidth, ptStart.y - 0.5);
			CDrawUtil::AddRectangle(ptTrayLeftBottom, 0.5, 1, 0.1);

			AcGePoint2d ptLine(ptStart.x - (2 * sin(mBangTopAngle)), ptStart.y + (2 * cos(mBangTopAngle)));
			CDrawUtil::CreateDimRotated(
				ptEnd, ptStart, ptStart, AcGePoint2d(ptStart.x, ptStart.y + 50), AcGePoint2d(ptStart.x - 1, ptStart.y + 1), mBangTopAngle);
		}
		else if (i == bottomPointId) {
			AcGePoint2d ptStart = mLeftBoltArr->at(i);
			AcGePoint2d ptEnd(ptStart.x - (length * sin(mBangBottomAngle)), ptStart.y - (length * cos(0-mBangBottomAngle)));
			CDrawUtil::AddPolyLine(ptStart, ptEnd, 0.3); //绘制左锚杆
			AcGePoint2d ptAEnd(ptEnd.x + (alength* sin(mBangBottomAngle)), ptEnd.y + (alength * cos(mBangBottomAngle)));
			CDrawUtil::AddPolyLine(ptAEnd, ptEnd, 0.5); //绘制锚固头

			AcGePoint2d ptTrayLeftBottom(ptStart.x + beamWidth, ptStart.y - 0.5);
			CDrawUtil::AddRectangle(ptTrayLeftBottom, 0.5, 1, 0.1);

			AcGePoint2d ptLine(ptStart.x - (2 * sin(mBangTopAngle)), ptStart.y - (2 * cos(mBangTopAngle)));
			CDrawUtil::CreateDimRotated(ptStart, AcGePoint2d(ptStart.x, ptStart.y - 50),
				ptEnd, ptStart, AcGePoint2d(ptStart.x-1, ptStart.y - 1), mBangBottomAngle);
		}
		else {

			AcGePoint2d ptStart = mLeftBoltArr->at(i);
			AcGePoint2d ptEnd(ptStart.x - (length * sin(CDrawUtil::angleToArc(90))), ptStart.y + (length * cos(CDrawUtil::angleToArc(90))));
			CDrawUtil::AddPolyLine(ptStart, ptEnd, 0.3); //绘制左锚杆
			AcGePoint2d ptAEnd(ptEnd.x + (alength* sin(CDrawUtil::angleToArc(90))), ptEnd.y - (alength * cos(CDrawUtil::angleToArc(90))));
			CDrawUtil::AddPolyLine(ptAEnd, ptEnd, 0.5); //绘制锚固头
			// 在中点的锚杆绘制标注
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
	// 绘制左托梁
	int minId = GetMinPointId(mLeftBoltArr); //找到最下面锚杆点的纵坐标
	double min = mLeftBoltArr->at(minId).y;

	AcGePoint2d ptLeftBottom(mLeftBoltArr->at(minId).x, min - 2);
	CDrawUtil::AddRectangle(ptLeftBottom, beamWidth, space * (number-1) + 4, 0.1);

	AcGePoint2d ptCrossBase(ptTunnelStart->x - (width * 1.5), ptTunnelStart->y);
	// 在左视图网格线中绘制托梁
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
	// 绘制矩形巷道的两条宽对应的线
	for (int i = 0; i < 2; i++)
	{
		AcGePoint2d ptStart(ptCrossBase.x + 5, ptCrossBase.y + (i * height));
		AcGePoint2d ptEnd(ptStart.x - (6 * pitch) - 5, ptStart.y);
		CDrawUtil::AddPolyLine(ptStart, ptEnd, 0.05);
	}

	int minId = GetMinPointId(mLeftBoltArr);
	// 绘制与锚杆对应的横线
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


	// 绘制竖线，竖线长度为巷道宽度 + 10,间隔为排距
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

	// 在左视图中绘制锚杆托盘小矩形
	for (int i = 0; i < mLeftBoltArr->length(); i++)
	{
		// 绘制每一列的托盘
		for (int j = 0; j < 6; j++)
		{
			AcGePoint2d ptLeftBottom(ptCrossBase.x - beamWidth - (j*pitch), mLeftBoltArr->at(i).y -beamWidth);
			CDrawUtil::AddRectangle(ptLeftBottom, beamWidth * 2, beamWidth * 2, 0.05);
		}
	}
}

int CRectangleTunnel::GetMaxPointId(AcGePoint2dArray * arr) {
	double max = arr->at(0).y;
	int maxId = 0; //找到最下面锚杆点的纵坐标
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
	int minId = 0; //找到最下面锚杆点的纵坐标
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

	// 初始化 mRightBoltArr 数组
	if (number % 2 == 0)
	{
		// 偶数根锚杆,
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
		CDrawUtil::AddPolyLine(ptStart, ptEnd, 0.3); //绘制右锚杆
		AcGePoint2d ptAEnd(ptEnd.x - (alength * sin(mRightBoltAngle)), ptEnd.y - (alength * cos(mRightBoltAngle)));
		CDrawUtil::AddPolyLine(ptAEnd, ptEnd, 0.5); //绘制锚固头

		if (i == 0)
		{
			CDrawUtil::CreateDimAligned(ptStart, ptEnd, AcGePoint2d(ptStart.x, ptStart.y + 2), bolt.getLength());
			CDrawUtil::CreateDimAligned(ptEnd, ptAEnd, AcGePoint2d(ptEnd.x, ptEnd.y - 2), bolt.getALength());
		}

		AcGePoint2d ptTrayLeftBottom(ptStart.x - beamWidth - 0.5, ptStart.y - 0.5);
		CDrawUtil::AddRectangle(ptTrayLeftBottom, 0.5, 1, 0.1); //绘制托盘
	}

}


// 铜川矿业绘制右帮锚杆的方式
void CRectangleTunnel::DrawTongRightBolt(CBolt bolt)
{

	int number = bolt.getNumber();
	double space = double(bolt.getSpace()) / pScaleNumber;
	double length = double(bolt.getLength()) / pScaleNumber;
	double alength = double(bolt.getALength()) / pScaleNumber;
	double beamWidth = double(bolt.getBeamWidth()) / pScaleNumber;
	AcGePoint2d ptRightMid(ptTunnelStart->x + width, ptTunnelStart->y + (height / 2));

	// 初始化 mRightBoltArr 数组
	if (number % 2 == 0)
	{
		// 偶数根锚杆,
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
			CDrawUtil::AddPolyLine(ptStart, ptEnd, 0.3); //绘制右锚杆
			AcGePoint2d ptAEnd(ptEnd.x - (alength * sin(mBangTopAngle)), ptEnd.y - (alength * cos(mBangTopAngle)));
			CDrawUtil::AddPolyLine(ptAEnd, ptEnd, 0.5); //绘制锚固头

			AcGePoint2d ptTrayLeftBottom(ptStart.x - beamWidth - 0.5, ptStart.y - 0.5);
			CDrawUtil::AddRectangle(ptTrayLeftBottom, 0.5, 1, 0.1); //绘制托盘
		}
		else if (i == bottomPointId) {
			AcGePoint2d ptStart = mRightBoltArr->at(i);
			AcGePoint2d ptEnd(ptStart.x + (length * sin(mBangBottomAngle)), ptStart.y - (length * cos(mBangBottomAngle)));
			CDrawUtil::AddPolyLine(ptStart, ptEnd, 0.3); //绘制右锚杆
			AcGePoint2d ptAEnd(ptEnd.x - (alength * sin(mBangBottomAngle)), ptEnd.y + (alength * cos(mBangBottomAngle)));
			CDrawUtil::AddPolyLine(ptAEnd, ptEnd, 0.5); //绘制锚固头

			AcGePoint2d ptTrayLeftBottom(ptStart.x - beamWidth - 0.5, ptStart.y - 0.5);
			CDrawUtil::AddRectangle(ptTrayLeftBottom, 0.5, 1, 0.1); //绘制托盘
		}
		else {
			AcGePoint2d ptStart = mRightBoltArr->at(i);
			AcGePoint2d ptEnd(ptStart.x + (length * sin(CDrawUtil::angleToArc(90))), ptStart.y + (length * cos(CDrawUtil::angleToArc(90))));
			CDrawUtil::AddPolyLine(ptStart, ptEnd, 0.3); //绘制右锚杆
			AcGePoint2d ptAEnd(ptEnd.x - (alength * sin(CDrawUtil::angleToArc(90))), ptEnd.y - (alength * cos(CDrawUtil::angleToArc(90))));
			CDrawUtil::AddPolyLine(ptAEnd, ptEnd, 0.5); //绘制锚固头

			AcGePoint2d ptTrayLeftBottom(ptStart.x - beamWidth - 0.5, ptStart.y - 0.5);
			CDrawUtil::AddRectangle(ptTrayLeftBottom, 0.5, 1, 0.1); //绘制托盘

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
	// 绘制右托梁
	double min = mRightBoltArr->at(0).y;
	int minId = 0; //找到最下面锚杆点的纵坐标
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
	// 在右视图网格线中绘制托梁
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

	// 绘制矩形巷道的两条宽对应的线
	for (int i = 0; i < 2; i++)
	{
		AcGePoint2d ptStart(ptCrossBase.x - 5, ptCrossBase.y + (i * height));
		AcGePoint2d ptEnd(ptStart.x + (6 * pitch) + 5, ptStart.y);
		CDrawUtil::AddPolyLine(ptStart, ptEnd, 0.05);
	}

	int minId = GetMinPointId(mRightBoltArr);
	// 绘制与锚杆对应的横线，直接调用mRightBoltArr 的纵坐标即可
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
	// 绘制竖线，竖线长度为巷道宽度 + 10,间隔为排距
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

	// 在右视图中绘制锚杆托盘小矩形
	for (int i = 0; i < mRightBoltArr->length(); i++)
	{
		// 绘制每一列的托盘
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
	// 初始化 mCableArr 数组, 即锚索在巷道边上的坐标点
	if (number % 2 == 0)
	{
		// 偶数根锚杆,
		for (int i = 1; i <= (number / 2); i++)
		{
			AcGePoint2d ptLeft(ptTopMid.x - (0.5 * i * space), ptTopMid.y);
			AcGePoint2d ptRight(ptTopMid.x + (0.5 * i * space), ptTopMid.y);
			mCableArr->append(ptLeft);
			mCableArr->append(ptRight);
		}
	}
	else {
		// 奇数根锚索
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
			// 用数组记录省略符的四个点
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

		CDrawUtil::AddPolyLine(ptEnd, ptAEnd, 0.5); //绘制锚固头
		if (i == 0)
		{
			// 经过标注线的点，设置为锚杆横坐标 - 2
			AcGePoint2d ptDimLine(ptStart.x - 2, ptStart.y);
			CDrawUtil::CreateDimAligned(ptStart, ptEnd, ptDimLine, cable.getLength());
			// 标注锚固头长度
			AcGePoint2d ptADimLine(ptStart.x + 2, ptEnd.y);
			CDrawUtil::CreateDimAligned(ptEnd, ptAEnd, ptADimLine, cable.getALength());
		}
		AcGePoint2d ptTrayLeftBottom(ptStart.x - 0.5, ptStart.y - beamWidth - 0.5);  // 绘制托盘
		CDrawUtil::AddRectangle(ptTrayLeftBottom, 1, 0.5, 0.1);

		// 在顶视图中绘制锚索视图

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

// 先绘制最外面巷道矩形，设置填充方式为混凝土方式；
// 再绘制中间混凝土巷道，设置填充方式为砌煊方式；
// 最后绘制最内侧矩形，设置填充方式为solid
void CRectangleTunnel::DrawThickness()
{
	double conThickness = pConcreteThickness / pScaleNumber;
	double qiThickness = pQiThickness / pScaleNumber;

	// 混凝土填充的边界对象id
	AcDbObjectIdArray conArray = AcDbObjectIdArray();
	AcDbObjectIdArray tunnelArray = AcDbObjectIdArray();
	AcGePoint2d ptLeftBottom(ptTunnelStart->x, ptTunnelStart->y); //巷道矩形的起始绘制点
	//巷道id
	AcDbObjectId tunnelId = CDrawUtil::AddRectangle(ptLeftBottom, width, height, border);
	AcGePoint2d ptConLeftBottom(ptLeftBottom.x + conThickness, ptLeftBottom.y + conThickness);
	double conwidth = width - conThickness - conThickness,
		conheight = height - conThickness - conThickness;
	//混凝土矩形的id
	AcDbObjectId conRecId = CDrawUtil::AddRectangle(ptConLeftBottom, conwidth, conheight, border);
	conArray.append(conRecId);
	tunnelArray.append(tunnelId);
	CDrawUtil::AddTwoBoundaryHatch(tunnelArray, conArray, _T("AR-CONC"), 0.015);

	// 砌煊填充的边界对象id
	AcDbObjectIdArray qiArray = AcDbObjectIdArray();
	AcGePoint2d ptQiLeftBottom(ptConLeftBottom.x + qiThickness, ptConLeftBottom.y + qiThickness);
	double qiwidth = conwidth - qiThickness - qiThickness,
		qiheight = conheight - qiThickness - qiThickness;
	qiArray.append(CDrawUtil::AddRectangle(ptQiLeftBottom, qiwidth, qiheight, border));
	CDrawUtil::AddTwoBoundaryHatch(conArray,qiArray, _T("EARTH"), 0.2);


	//绘制厚度批注
	if (conThickness != 0) {
		CDrawUtil::CreateDimAligned(ptLeftBottom, AcGePoint2d(ptConLeftBottom.x, ptLeftBottom.y), AcGePoint2d(ptLeftBottom.x, ptLeftBottom.y - 3), conThickness * pScaleNumber);
	}
	if (qiThickness != 0) {
		CDrawUtil::CreateDimAligned(AcGePoint2d(ptQiLeftBottom.x + qiwidth, ptLeftBottom.y),
			AcGePoint2d(ptConLeftBottom.x+conwidth, ptLeftBottom.y), AcGePoint2d(ptQiLeftBottom.x, ptLeftBottom.y - 3), qiThickness * pScaleNumber);
	}
}


//根据计算得出的托梁坐标纵坐标在改变绘制顶视图的托梁，锚杆托盘也是同理
