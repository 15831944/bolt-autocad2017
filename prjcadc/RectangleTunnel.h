#pragma once
#include "Tunnel.h"
class CRectangleTunnel :
	public CTunnel
{
private:
	double width;
	double height;
	double mLeftBoltAngle = 90;
	double mRightBoltAngle = 90;
	double mTopBoltAngle = 90;
	double mBangTopAngle = 90;
	double mBangBottomAngle = 90;
	double border = 0.2;
	AcGePoint2d * ptTunnelStart = new AcGePoint2d(170, 60);
	// ʹ�������¼����ê����������ϵ�����
	AcGePoint2dArray * mTopBoltsArr = new AcGePoint2dArray(); 
	AcGePoint2dArray * mLeftBoltArr = new AcGePoint2dArray();
	AcGePoint2dArray * mRightBoltArr = new AcGePoint2dArray();
	AcGePoint2dArray * mCableArr = new AcGePoint2dArray();
public:
	CRectangleTunnel(double w, double h);
	CRectangleTunnel(double w, double h, double tba, double lba, double rba);
	CRectangleTunnel(double w, double h, CBolt topBolt);
	CRectangleTunnel(double w, double h, double bta, double bba);
	CRectangleTunnel();
	~CRectangleTunnel();
	double getWidth() const { return width; };
	virtual void DrawTunnel();
	virtual void DrawTopBolt(CBolt bolt);
	virtual void DrawTopTuoLiang(CBolt bolt);
	// ���Ƹ���ͼ��������
	virtual void DrawTopViewNet(CBolt bolt);
	virtual void DrawLeftBolt(CBolt bolt);
	void DrawTongLeftBolt(CBolt bolt);
	virtual void DrawLeftTuoLiang(CBolt bolt);
	virtual void DrawLeftViewNet(CBolt bolt);
	virtual void DrawRightBolt(CBolt bolt);
	void DrawTongRightBolt(CBolt bolt);
	virtual void DrawRightTuoLiang(CBolt bolt);
	virtual void DrawRightViewNet(CBolt bolt);
	virtual void DrawCable(CCable cable);
private:
	void InitTopBoltPointArr(CBolt bolt);
	int GetMinPointId(AcGePoint2dArray * arr);
	int GetMaxPointId(AcGePoint2dArray * arr);

};

