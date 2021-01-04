#pragma once
#include "Tunnel.h"
class CRectangleTunnel :
	public CTunnel
{
private:
	double width;
	double height;
	// 90 度的弧度制表示
	double mLeftBoltAngle = asin(0.5) * 3;
	double mRightBoltAngle = asin(0.5) * 3;
	double mTopBoltAngle = asin(0.5) * 3;
	// 绘制铜川矿务局的图时才会用到下面两个参数
	double mBangTopAngle = 90;
	double mBangBottomAngle = 90;

	double border = 0.2;
	AcGePoint2d * ptTunnelStart = new AcGePoint2d(170, 60);
	// 使用数组记录顶部锚杆在巷道边上的坐标
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
	double GetWidth() const { return width*pScaleNumber; };
	void SetWidth(double w) { width = w / pScaleNumber; };
	void SetHeight(double h) { height = h / pScaleNumber; };
	double GetHeight() const { return height*pScaleNumber; };

	double GetLeftBoltAngle() const { return mLeftBoltAngle; };
	void SetLeftBoltAngle(double v) { mLeftBoltAngle = CDrawUtil::angleToArc(v); };
	double GetRightBoltAngle() const { return mRightBoltAngle; };
	void SetRightBoltAngle(double v) { mRightBoltAngle = CDrawUtil::angleToArc(v); };
	double GetTopBoltAngle() const { return mTopBoltAngle; };
	void SetTopBoltAngle(double v) { mTopBoltAngle = CDrawUtil::angleToArc(v); };

	double GetBangTopAngle() const { return mBangTopAngle; };
	void SetBangTopAngle(double v) { mBangTopAngle = CDrawUtil::angleToArc(v); };
	double GetBangBottomAngle() const { return mBangBottomAngle; };
	void SetBangBottomAngle(double v) { mBangBottomAngle = CDrawUtil::angleToArc(v); };

	virtual void DrawTunnel();
	virtual void DrawTopBolt(CBolt bolt);
	virtual void DrawTopTuoLiang(CBolt bolt);
	// 绘制俯视图的网络线
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
	void DrawBangBolt();
	//绘制混凝土,砌煊
	void DrawThickness();
private:
	void InitTopBoltPointArr(CBolt bolt);
	int GetMinPointId(AcGePoint2dArray * arr);
	int GetMaxPointId(AcGePoint2dArray * arr);

};

