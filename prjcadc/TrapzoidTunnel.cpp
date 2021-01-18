#include "stdafx.h"
#include "TrapzoidTunnel.h"


CTrapzoidTunnel::CTrapzoidTunnel()
{
}

CTrapzoidTunnel::CTrapzoidTunnel(double bw, double h, int la, int ra)
{
	mTopBoltAngle = CDrawUtil::angleToArc(90);
	mLeftBoltAngle = CDrawUtil::angleToArc(90);
	mRightBoltAngle = CDrawUtil::angleToArc(90);
	bottomWidth = bw/100;
	height = h/100;
	leftAngle = la;
	rightAngle = ra;
	topWidth = bottomWidth - (height / tan(CDrawUtil::angleToArc(la))) - (height / tan(CDrawUtil::angleToArc(ra)));
}

CTrapzoidTunnel::CTrapzoidTunnel(double bw, double h, int la, int ra, double tba, double lba, double rba)
{

	bottomWidth = bw / 100;
	height = h / 100;
	leftAngle = la;
	rightAngle = ra;
	topWidth = bottomWidth - (height / tan(CDrawUtil::angleToArc(la))) - (height / tan(CDrawUtil::angleToArc(ra)));
	mTopBoltAngle = CDrawUtil::angleToArc(tba);
	mLeftBoltAngle = CDrawUtil::angleToArc(lba);
	mRightBoltAngle = CDrawUtil::angleToArc(rba);
}


CTrapzoidTunnel::~CTrapzoidTunnel()
{
}

void CTrapzoidTunnel::DrawTunnel()
{
	AcGePoint2d ptLeftBottom(170, 60);
	CDrawUtil::AddTrapzoid(ptLeftBottom, bottomWidth, height, leftAngle, rightAngle, border);

	AcGePoint2d ptRightBottom(ptLeftBottom.x + bottomWidth, ptLeftBottom.y);
	AcGePoint2d ptWidthLine(ptRightBottom.x, ptLeftBottom.y - 5); //标注线经过的点
	CDrawUtil::CreateDimAligned(ptLeftBottom, ptRightBottom, ptWidthLine, bottomWidth * 100, 0);

	AcGePoint2d ptRightTop(ptRightBottom.x - (height / tan(CDrawUtil::angleToArc(rightAngle))), ptLeftBottom.y + height);
	AcGePoint2d ptHeightDimEnd(ptRightTop.x, ptLeftBottom.y);
	AcGePoint2d ptHeightDimLine(ptHeightDimEnd.x - 5, ptLeftBottom.y);
	if (pZhihuWay > 1)
	{
		double conThickness = pConcreteThickness / pScaleNumber;
		double qiThickness = pQiThickness / pScaleNumber;
		ptHeightDimLine.x = ptHeightDimEnd.x - 10 - conThickness - qiThickness;
	}
	CDrawUtil::CreateDimAligned(ptRightTop, ptHeightDimEnd, ptHeightDimLine, height * 100, 0);

	AcGePoint2d ptLeftTop(ptLeftBottom.x + (height / tan(CDrawUtil::angleToArc(rightAngle))), ptLeftBottom.y + height);

	CDrawUtil::CreateDimRotated(ptLeftBottom, ptRightBottom, 
		ptLeftBottom, ptLeftTop, ptLeftBottom ,CDrawUtil::angleToArc(leftAngle));
	CDrawUtil::CreateDimRotated(ptRightBottom, ptLeftBottom,
		ptRightBottom, ptRightTop, ptRightBottom, CDrawUtil::angleToArc(rightAngle));
}


void CTrapzoidTunnel::DrawTopBolt(CBolt bolt)
{
	//直接复用矩形的，将中点坐标改为bottom即可
	int number = bolt.getNumber();
	double space = double(bolt.getSpace() / 100);
	double length = double(bolt.getLength() / 100);
	double alength = double(bolt.getALength() / 100);
	double beamWidth = double(bolt.getBeamWidth()) / 100.0;
	AcGePoint2d ptTopMid(ptTunnelStart->x + (bottomWidth / 2), ptTunnelStart->y + height);

	// 初始化 mTopBoltsArr 数组, 即顶部锚杆在巷道边上的坐标点
	if (number % 2 == 0)
	{
		// 偶数根锚杆,
		for (int i = 1; i <= (number / 2); i++)
		{
			AcGePoint2d ptLeft(ptTopMid.x - (0.5 * i * space), ptTopMid.y );
			AcGePoint2d ptRight(ptTopMid.x + (0.5 * i * space), ptTopMid.y);
			mTopBoltsArr->append(ptLeft);
			mTopBoltsArr->append(ptRight);
		}
	}
	else {
		mTopBoltsArr->append(ptTopMid);
		for (int i = 1; i <= (number / 2); i++)
		{
			AcGePoint2d ptLeft(ptTopMid.x - (i * space), ptTopMid.y);
			AcGePoint2d ptRight(ptTopMid.x + ( i * space), ptTopMid.y);
			mTopBoltsArr->append(ptLeft);
			mTopBoltsArr->append(ptRight);
		}
	}
	// 绘制锚杆
	for (int i = 0; i < mTopBoltsArr->length(); i++)
	{
		AcGePoint2d ptStart = mTopBoltsArr->at(i);
		AcGePoint2d ptEnd(ptStart.x - (cos(mTopBoltAngle) * length), ptStart.y +( sin(mTopBoltAngle) * length));
		CDrawUtil::AddPolyLine(ptStart, ptEnd, 0.3);
		AcGePoint2d ptAEnd(ptEnd.x + (alength * cos(mTopBoltAngle)), ptEnd.y -( sin(mTopBoltAngle) * alength));

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

void CTrapzoidTunnel::DrawTopTuoLiang(CBolt bolt)
{
	//绘制托梁：设最左边的锚杆坐标为(x,y), 则托梁矩形的左下坐标为(x-2,double(y - beamWidth/100))，
	// 宽度为 (number-1) * 间距，高度为 beamWidth/100
	// 最左边的锚杆横坐标为 mid-(number / 2 - 0.5) * space
	int number = bolt.getNumber();
	double beamWidth = double(bolt.getBeamWidth()) / 100.0;
	double space = bolt.getSpace() / 100;
	double pitch = double(bolt.getPitch() )/ 100;
	AcGePoint2d ptTopMid(170 + (bottomWidth / 2), 60 + height);
	double tmp = 0;
	if (number % 2 == 0)
	{
		tmp = number / 2 - 0.5;
	}
	else
	{
		tmp = number / 2;
	}
	AcGePoint2d ptLeftestBolt(ptTopMid.x - (tmp * space), ptTopMid.y);
	AcGePoint2d ptLeftBottom(ptLeftestBolt.x - 2, double(ptLeftestBolt.y - 0.5));
	CDrawUtil::AddRectangle(ptLeftBottom, space*(number - 1) + 4, beamWidth, 0.1);

	// 在顶视图中绘制托梁
	AcGePoint2d ptNetCrossBase(170, 170);
	for (int i = 0; i < 8; i++)
	{
		AcGePoint2d ptNewLeftBottom(ptLeftBottom.x, ptNetCrossBase.y + i * (pitch)-0.5);
		CDrawUtil::AddRectangle(ptNewLeftBottom, space*(number - 1) + 4, beamWidth * 2, 0.1);
	}
}

void CTrapzoidTunnel::DrawTopViewNet(CBolt bolt)
{
	double beamWidth = double(bolt.getBeamWidth()) / 100.0 - 0.1;

	//顶视图的左下角起始点
	AcGePoint2d ptNetCrossBase(170, 170);
	AcGePoint2d ptNetRowBase(ptNetCrossBase.x - 3, ptNetCrossBase.y);
	AcGePoint2d ptNetColBase(ptNetCrossBase.x, ptNetCrossBase.y - 10);

	//竖线的绘制方法与绘制顶部锚杆的方式相同
	double space = double(bolt.getSpace()) / 100.0;
	double pitch = double(bolt.getPitch()) / 100.0;
	for (int i = 0; i < 8; i++)
	{
		AcGePoint2d ptNetRowStart(ptNetRowBase.x, ptNetRowBase.y + (i * pitch));
		AcGePoint2d ptNetRowEnd(ptNetRowStart.x + topWidth + 10, ptNetRowStart.y);
		// 绘制八条横线
		CDrawUtil::AddPolyLine(ptNetRowStart, ptNetRowEnd, 0.05);
	}
	// 绘制与梯形顶边左右对应的两条竖线
		AcGePoint2d ptNetLeftColStart(ptNetColBase.x + height / tan(CDrawUtil::angleToArc(leftAngle)), ptNetColBase.y);
		AcGePoint2d ptNetLeftColEnd(ptNetLeftColStart.x, ptNetLeftColStart.y + (pitch * 7) + 15);
		CDrawUtil::AddPolyLine(ptNetLeftColStart, ptNetLeftColEnd, 0.05);

		AcGePoint2d ptNetRightColStart(ptNetLeftColStart.x + topWidth, ptNetColBase.y);
		AcGePoint2d ptNetRightColEnd(ptNetRightColStart.x, ptNetRightColStart.y + (pitch * 7) + 15);
		CDrawUtil::AddPolyLine(ptNetRightColStart, ptNetRightColEnd, 0.05);

	// 绘制与锚杆对应的网格竖线
	for (int i = 0; i < mTopBoltsArr->length(); i++)
	{
		AcGePoint2d point = mTopBoltsArr->at(i);
		AcGePoint2d ptNetColStart(point.x, ptNetColBase.y);
		AcGePoint2d ptNetColEnd(point.x, ptNetColBase.y + (pitch * 7) + 15);
		CDrawUtil::AddPolyLine(ptNetColStart, ptNetColEnd, 0.05);
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

void CTrapzoidTunnel::DrawLeftBolt(CBolt bolt)
{
	AcGePoint2d ptLeftMid(ptTunnelStart->x + (height / 2 / tan(CDrawUtil::angleToArc(leftAngle))),
		ptTunnelStart->y + (height / 2));

	int number = bolt.getNumber();
	double space = double(bolt.getSpace()) / 100.0;
	double length = double(bolt.getLength() / 100);
	double alength = double(bolt.getALength() / 100);
	double beamWidth = double(bolt.getBeamWidth()) / 100.0;
	if (number % 2 == 0)
	{
		// 偶数根锚杆,
		for (int i = 1; i <= (number / 2); i++)
		{
			AcGePoint2d ptUp(ptLeftMid.x +(space  * (i - 0.5) / tan(CDrawUtil::angleToArc(leftAngle))), ptLeftMid.y + (0.5 * i * space));
			AcGePoint2d ptBottom(ptLeftMid.x - (space  * (i - 0.5) / tan(CDrawUtil::angleToArc(leftAngle))), ptLeftMid.y - (0.5 * i * space));
			mLeftBoltArr->append(ptUp);
			mLeftBoltArr->append(ptBottom);
		}
	}
	else
	{
		mLeftBoltArr->append(ptLeftMid);
		for (int i = 1; i <= (number / 2); i++)
		{
			AcGePoint2d ptUp(ptLeftMid.x + (i * space / (tan(CDrawUtil::angleToArc(leftAngle)))), ptLeftMid.y + (i * space));
			AcGePoint2d ptBottom(ptLeftMid.x - (i * space / (tan(CDrawUtil::angleToArc(leftAngle)))), ptLeftMid.y - (i * space));
			mLeftBoltArr->append(ptUp);
			mLeftBoltArr->append(ptBottom);
		}
	}

	for (int i = 0; i < mLeftBoltArr->length(); i++)
	{
		AcGePoint2d ptStart = mLeftBoltArr->at(i);
		AcGePoint2d ptEnd(ptStart.x - (length * sin(mLeftBoltAngle)), ptStart.y + (length * cos(mLeftBoltAngle)));
		CDrawUtil::AddPolyLine(ptStart, ptEnd, 0.3); //绘制左锚杆
		AcGePoint2d ptAEnd(ptEnd.x + (alength* sin(mLeftBoltAngle)), ptEnd.y - (alength * cos(mLeftBoltAngle)));
		CDrawUtil::AddPolyLine(ptAEnd, ptEnd, 0.5); //绘制锚固头

		if (i == 0)
		{
			CDrawUtil::CreateDimAligned(ptStart, ptEnd, AcGePoint2d(ptStart.x, ptStart.y + 2), bolt.getLength());
			CDrawUtil::CreateDimAligned(ptEnd, ptAEnd, AcGePoint2d(ptEnd.x, ptEnd.y - 2), bolt.getALength());
		}

		AcGePoint2d ptTrayLeftBottom(ptStart.x + beamWidth, ptStart.y - 0.5);
		CDrawUtil::AddRectangle(ptTrayLeftBottom, 0.5, 1, 0.1); // 绘制托盘
	}
}

void CTrapzoidTunnel::DrawLeftTuoLiang(CBolt bolt)
{
	double beamWidth = double(bolt.getBeamWidth()) / 100.0;
	double space = double(bolt.getSpace()) / 100.0;
	double pitch = double(bolt.getPitch()) / 100.0;
	int number = bolt.getNumber();
	// 绘制左托梁

	int minId = GetMinPointId(mLeftBoltArr); //找到最下面锚杆点的纵坐标
	int maxId = GetMaxPointId(mLeftBoltArr);
	double min = mLeftBoltArr->at(minId).y;
	double max = mLeftBoltArr->at(maxId).y;
	AcGePoint2d ptLeftBottom(mLeftBoltArr->at(minId).x, min - 2);
	AcGePoint2d ptRightBottom(ptLeftBottom.x + beamWidth, ptLeftBottom.y);
	AcGePoint2d ptLeftTop(mLeftBoltArr->at(maxId).x + (2 / tan(CDrawUtil::angleToArc(leftAngle))), max + 2);
	AcGePoint2d ptRightTop(ptLeftTop.x + beamWidth, ptLeftTop.y);
	AcGePoint2dArray points(4);
	points.append(ptLeftBottom);
	points.append(ptRightBottom);
	points.append(ptRightTop);
	points.append(ptLeftTop);
	CDrawUtil::AddPolyLine(points, 0.1);

	AcGePoint2d ptCrossBase(ptTunnelStart->x - (bottomWidth * 1.5), ptTunnelStart->y);
	// 在左视图网格线中绘制托梁
	for (int i = 0; i < 6; i++)
	{
		AcGePoint2d ptBeamLeftBottom(ptCrossBase.x - (i * pitch) - beamWidth, ptLeftBottom.y);
		CDrawUtil::AddRectangle(ptBeamLeftBottom, beamWidth * 2, space * (number - 1) + 4, 0.1);
	}

}

void CTrapzoidTunnel::DrawLeftViewNet(CBolt bolt)
{
	double beamWidth = double(bolt.getBeamWidth()) / 100.0 - 0.1;
	double space = double(bolt.getSpace()) / 100.0;
	double pitch = double(bolt.getPitch()) / 100.0;

	AcGePoint2d ptCrossBase(ptTunnelStart->x - (bottomWidth * 1.5), ptTunnelStart->y);
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
			CDrawUtil::CreateDimAligned(ptStart, AcGePoint2d(ptStart.x, ptStart.y - space),
				AcGePoint2d(ptStart.x + 5, ptStart.y), space * 100, 0);
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
				AcGePoint2d(ptStart.x, ptStart.y - 5), pitch * 100, 0);
		}
	}

	// 在左视图中绘制锚杆托盘小矩形
	for (int i = 0; i < mLeftBoltArr->length(); i++)
	{
		// 绘制每一列的托盘
		for (int j = 0; j < 6; j++)
		{
			AcGePoint2d ptLeftBottom(ptCrossBase.x - beamWidth - (j*pitch), mLeftBoltArr->at(i).y - beamWidth);
			CDrawUtil::AddRectangle(ptLeftBottom, beamWidth * 2, beamWidth * 2, 0.05);
		}
	}
}
int CTrapzoidTunnel::GetMinPointId(AcGePoint2dArray * arr) {
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

int CTrapzoidTunnel::GetMaxPointId(AcGePoint2dArray * arr) {
	double max = arr->at(0).y;
	int maxId = 0; //找到最上面锚杆点的纵坐标
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

void CTrapzoidTunnel::DrawRightBolt(CBolt bolt)
{

	AcGePoint2d ptRightMid(ptTunnelStart->x + bottomWidth - (height / 2 / tan(CDrawUtil::angleToArc(rightAngle))),
		ptTunnelStart->y + (height / 2));

	int number = bolt.getNumber();
	double space = double(bolt.getSpace()) / 100.0;
	double length = double(bolt.getLength() / 100);
	double alength = double(bolt.getALength() / 100);
	double beamWidth = double(bolt.getBeamWidth()) / 100.0;
	if (number % 2 == 0)
	{
		// 偶数根锚杆,
		for (int i = 1; i <= (number / 2); i++)
		{
			AcGePoint2d ptUp(ptRightMid.x - (space  * (i - 0.5) / tan(CDrawUtil::angleToArc(rightAngle))), ptRightMid.y + (0.5 * i * space));
			AcGePoint2d ptBottom(ptRightMid.x + (space  * (i - 0.5) / tan(CDrawUtil::angleToArc(rightAngle))), ptRightMid.y - (0.5 * i * space));
			mRightBoltArr->append(ptUp);
			mRightBoltArr->append(ptBottom);
		}
	}
	else
	{

		mRightBoltArr->append(ptRightMid);
		for (int i = 1; i <= (number / 2); i++)
		{
			AcGePoint2d ptUp(ptRightMid.x - (i * space / (tan(CDrawUtil::angleToArc(rightAngle)))), ptRightMid.y + (i * space));
			AcGePoint2d ptBottom(ptRightMid.x + (i * space / (tan(CDrawUtil::angleToArc(rightAngle)))), ptRightMid.y - (i * space));
			mRightBoltArr->append(ptUp);
			mRightBoltArr->append(ptBottom);
		}
	}

	for (int i = 0; i < mRightBoltArr->length(); i++)
	{
		AcGePoint2d ptStart = mRightBoltArr->at(i);
		AcGePoint2d ptEnd(ptStart.x + (length * sin(mRightBoltAngle)), ptStart.y + (length * cos(mRightBoltAngle)));
		CDrawUtil::AddPolyLine(ptStart, ptEnd, 0.3); //绘制左锚杆
		AcGePoint2d ptAEnd(ptEnd.x - (alength* sin(mRightBoltAngle)), ptEnd.y - (alength * cos(mRightBoltAngle)));
		CDrawUtil::AddPolyLine(ptAEnd, ptEnd, 0.5); //绘制锚固头

		if (i == 0)
		{
			CDrawUtil::CreateDimAligned(ptStart, ptEnd, AcGePoint2d(ptStart.x, ptStart.y + 2), bolt.getLength());
			CDrawUtil::CreateDimAligned(ptEnd, ptAEnd, AcGePoint2d(ptEnd.x, ptEnd.y - 2), bolt.getALength());
		}

		AcGePoint2d ptTrayLeftBottom(ptStart.x - beamWidth - 0.5, ptStart.y - 0.5);
		CDrawUtil::AddRectangle(ptTrayLeftBottom, 0.5, 1, 0.1); // 绘制托盘
	}
}

void CTrapzoidTunnel::DrawRightTuoLiang(CBolt bolt)
{
	double beamWidth = double(bolt.getBeamWidth()) / 100.0;
	double space = double(bolt.getSpace()) / 100.0;
	double pitch = double(bolt.getPitch()) / 100.0;
	int number = bolt.getNumber();

	// 绘制右托梁
	int minId = GetMinPointId(mRightBoltArr); //找到最下面锚杆点的纵坐标
	int maxId = GetMaxPointId(mRightBoltArr);
	double min = mRightBoltArr->at(minId).y;
	double max = mRightBoltArr->at(maxId).y;

	AcGePoint2d ptLeftBottom(mRightBoltArr->at(minId).x - beamWidth, min - 2);
	AcGePoint2d ptRightBottom(mRightBoltArr->at(minId).x +(2 / tan(CDrawUtil::angleToArc(rightAngle))), ptLeftBottom.y);
	AcGePoint2d ptLeftTop(mRightBoltArr->at(maxId).x - beamWidth - (2 / tan(CDrawUtil::angleToArc(rightAngle))), max + 2);
	AcGePoint2d ptRightTop(mRightBoltArr->at(maxId).x - (2 / tan(CDrawUtil::angleToArc(rightAngle))), ptLeftTop.y);
	AcGePoint2dArray points(4);
	points.append(ptRightTop);
	points.append(ptLeftTop);
	points.append(ptLeftBottom);
	points.append(ptRightBottom);
	CDrawUtil::AddPolyLine(points, 0.1);

	AcGePoint2d ptCrossBase(ptTunnelStart->x + (bottomWidth *2.5), ptTunnelStart->y);
	// 在右视图网格线中绘制托梁
	for (int i = 0; i < 6; i++)
	{
		AcGePoint2d ptBeamLeftBottom(ptCrossBase.x + (i * pitch) - beamWidth, ptLeftBottom.y);
		CDrawUtil::AddRectangle(ptBeamLeftBottom, beamWidth * 2, space * (number - 1) + 4, 0.1);
	}
}

void CTrapzoidTunnel::DrawRightViewNet(CBolt bolt)
{
	AcGePoint2d ptCrossBase(ptTunnelStart->x + (bottomWidth *2.5), ptTunnelStart->y);
	double beamWidth = double(bolt.getBeamWidth()) / 100.0 - 0.1;
	double space = double(bolt.getSpace()) / 100.0;
	double pitch = double(bolt.getPitch()) / 100.0;

	// 绘制矩形巷道的两条宽对应的线
	for (int i = 0; i < 2; i++)
	{
		AcGePoint2d ptStart(ptCrossBase.x - 5, ptCrossBase.y + (i * height));
		AcGePoint2d ptEnd(ptStart.x + (6 * pitch) + 5, ptStart.y);
		CDrawUtil::AddPolyLine(ptStart, ptEnd, 0.05);
	}
	// 绘制与锚杆对应的横线，直接调用mRightBoltArr 的纵坐标即可
	for (int i = 0; i < mRightBoltArr->length(); i++)
	{
		AcGePoint2d ptStart(ptCrossBase.x - 5, mRightBoltArr->at(i).y);
		AcGePoint2d ptEnd(ptStart.x + (6 * pitch) + 5, ptStart.y);
		CDrawUtil::AddPolyLine(ptStart, ptEnd, 0.05);
	}
	// 绘制竖线，竖线长度为巷道宽度 + 10,间隔为排距
	for (int i = 0; i < 6; i++)
	{
		AcGePoint2d ptStart(ptCrossBase.x + (i * pitch), ptCrossBase.y - 5);
		AcGePoint2d ptEnd(ptStart.x, ptStart.y + height + 10);
		CDrawUtil::AddPolyLine(ptStart, ptEnd, 0.05);
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


void CTrapzoidTunnel::DrawCable(CCable cable)
{
	CRectangleTunnel * mRecTunnel = new CRectangleTunnel(bottomWidth * 100, height * 100);
	mRecTunnel->SetTopBoltAngle(90);
	mRecTunnel->DrawCable(cable);
}

void CTrapzoidTunnel::DrawBangBolt()
{
	DrawLeftBolt(*pLeftBolt);
	DrawLeftTuoLiang(*pLeftBolt);
	DrawLeftViewNet(*pLeftBolt);

	DrawRightBolt(*pLeftBolt);
	DrawRightTuoLiang(*pLeftBolt);
	DrawRightViewNet(*pLeftBolt);
}

void CTrapzoidTunnel::DrawThickness()
{
	double conThickness = pConcreteThickness / pScaleNumber,
		qiThickness = pQiThickness / pScaleNumber;

	double tan_leftAngle = tan(CDrawUtil::angleToArc(leftAngle)),
		tan_rightAngle = tan(CDrawUtil::angleToArc(rightAngle));
	double conBottomWidth = bottomWidth - (2 * conThickness) -
		((tan_leftAngle / conThickness)) - (tan_rightAngle / conThickness),
		qiBottomWidth = conBottomWidth - (2 * qiThickness) -
		(tan_leftAngle / qiThickness ) - (tan_rightAngle / qiThickness),
		conheight = height - (2 * conThickness),
		qiHeight = conheight - (2 * qiThickness);

	AcDbObjectIdArray tunnelArray = AcDbObjectIdArray();
	AcDbObjectIdArray conArray = AcDbObjectIdArray();
	AcDbObjectIdArray qiArray = AcDbObjectIdArray();
	AcGePoint2d ptLeftBottom(170, 60);
	AcDbObjectId tunnelId = CDrawUtil::AddTrapzoid(ptLeftBottom, bottomWidth, height, leftAngle, rightAngle, border);
	tunnelArray.append(tunnelId);

	AcGePoint2d ptConLeftBottom((tan_leftAngle /conThickness) + ptLeftBottom.x + conThickness,
		ptLeftBottom.y + conThickness);
	AcDbObjectId conId = CDrawUtil::AddTrapzoid(ptConLeftBottom, 
		conBottomWidth, conheight, leftAngle, rightAngle, border);
	conArray.append(conId);
	CDrawUtil::AddTwoBoundaryHatch(tunnelArray, conArray, _T("AR-CONC"), 0.015);

	AcGePoint2d ptQiLeftBottom((tan_leftAngle / qiThickness) + qiThickness + ptConLeftBottom.x, ptConLeftBottom.y + qiThickness);  
	AcDbObjectId QiID = CDrawUtil::AddTrapzoid(ptQiLeftBottom,
			qiBottomWidth, qiHeight, leftAngle, rightAngle, border);
	qiArray.append(QiID);
	CDrawUtil::AddTwoBoundaryHatch(conArray, qiArray, _T("EARTH"), 0.2);

	//绘制厚度批注
	if (conThickness != 0) {
		CDrawUtil::CreateDimAligned(ptLeftBottom, AcGePoint2d(ptConLeftBottom.x, ptLeftBottom.y), AcGePoint2d(ptLeftBottom.x, ptLeftBottom.y - 3), pConcreteThickness);
	}
	if (qiThickness != 0) {
		CDrawUtil::CreateDimAligned(AcGePoint2d(ptQiLeftBottom.x + qiBottomWidth, ptLeftBottom.y),
			AcGePoint2d(ptConLeftBottom.x + conBottomWidth, ptLeftBottom.y), AcGePoint2d(ptQiLeftBottom.x, ptLeftBottom.y - 3), pQiThickness);
	}

}

