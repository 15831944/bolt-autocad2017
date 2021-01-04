#pragma once
#include "Tunnel.h"
#include "RectangleTunnel.h"
class CTrapzoidTunnel :
	public CTunnel
{
private:
	double topWidth;
	double bottomWidth;
	double height;
	int leftAngle;
	int rightAngle;
	double mLeftBoltAngle = asin(0.5) * 3;
	double mRightBoltAngle = asin(0.5) * 3;
	double mTopBoltAngle = asin(0.5) * 3;
	double border = 0.2;

	// 这个是后面加的，因为帮部角度偏移的规定不一样了
	double mBangLeftAngle;
	double mBangRightAngle;

	AcGePoint2d * ptTunnelStart = new AcGePoint2d(170, 60);
	// 使用数组记录顶部锚杆在巷道边上的坐标
	AcGePoint2dArray * mTopBoltsArr = new AcGePoint2dArray();
	AcGePoint2dArray * mLeftBoltArr = new AcGePoint2dArray();
	AcGePoint2dArray * mRightBoltArr = new AcGePoint2dArray();
	AcGePoint2dArray * mCableArr = new AcGePoint2dArray();
	int GetMinPointId(AcGePoint2dArray * arr);
	int GetMaxPointId(AcGePoint2dArray * arr);
public:
	CTrapzoidTunnel();
	CTrapzoidTunnel(double bw, double h, int la, int ra);
	CTrapzoidTunnel(double bw, double h, int la, int ra, double tba, double lba, double rba);
	~CTrapzoidTunnel();

	double GetTopWidth() const { return topWidth*pScaleNumber; };
	double GetBottomWidth() const { return bottomWidth*pScaleNumber; };
	double GetHeight() const { return height*pScaleNumber; };
	int GetTrapLeftAngle() const { return leftAngle; };
	int GetTrapRightAngle() const{ return rightAngle; };
	void SetTopWidth(double v) { topWidth = v/ pScaleNumber; };
	void SetBottomWidth(double v) { bottomWidth = v/ pScaleNumber; };
	void SetHeight(double v) { height = v/ pScaleNumber; };
	void SetTrapLeftAngle(int v ){leftAngle = v; };
	void SetTrapRightAngle(int v) { rightAngle = v; };

	double GetLeftBoltAngle() const { return mLeftBoltAngle; };
	void SetLeftBoltAngle(double v) { mLeftBoltAngle = CDrawUtil::angleToArc(v); };
	double GetRightBoltAngle() const { return mRightBoltAngle; };
	void SetRightBoltAngle(double v) { mRightBoltAngle = CDrawUtil::angleToArc(v); };
	double GetTopBoltAngle() const { return mTopBoltAngle; };
	void SetTopBoltAngle(double v) { mTopBoltAngle = CDrawUtil::angleToArc(v); };

	void SetBangLeftAngle(double w) { mBangLeftAngle = w; };
	double GetBangLeftAngle() const { return mBangLeftAngle; };
	void SetBangRightAngle(double flag) { mBangRightAngle = flag; };
	double GetBangRightAngle() { return mBangRightAngle; };
	virtual void DrawTunnel();
	virtual void DrawTopBolt(CBolt bolt);
	virtual void DrawTopTuoLiang(CBolt bolt);
	//绘制顶视图的网格线
	virtual void DrawTopViewNet(CBolt bolt);
	// DrawLeftbolt，DrawLeftTuoliang， DrawLeftViewNet存在数据耦合，都要用到 LeftBoltArr 数组
	// 在DrawLeftBolt中对 leftBoltArr进行初始化
	virtual void DrawLeftBolt(CBolt bolt);
	virtual void DrawLeftTuoLiang(CBolt bolt);
	virtual void DrawLeftViewNet(CBolt bolt);
	
	virtual void DrawRightBolt(CBolt bolt);
	virtual void DrawRightTuoLiang(CBolt bolt);
	virtual void DrawRightViewNet(CBolt bolt);
	virtual void DrawCable(CCable cable);

	void DrawBangBolt();
	//绘制混凝土,砌煊
	void DrawThickness();
};
