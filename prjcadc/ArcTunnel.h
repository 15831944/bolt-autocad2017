#pragma once
#include "Tunnel.h"
#include "RectangleTunnel.h"
class CArcTunnel :
	public CTunnel
{
public:
	CArcTunnel();
	CArcTunnel(double w, double wh, double ah, bool flag);
	CArcTunnel(double w, double wh, double ah, bool flag, int tba, int lba, int rba);
	~CArcTunnel();
	virtual void DrawTunnel();
	virtual void DrawTopBolt(CBolt bolt);
	virtual void DrawTopTuoLiang(CBolt bolt);
	virtual void DrawTopViewNet(CBolt bolt);
	// ��������Ļ��ưﲿê�� ���þ�������Ļ�����������ķ�������
	void DrawBangBolt();
	// ����ê��
	virtual void DrawCable();
	//���ƻ�����,����
	void DrawThickness();

	void SetWidth(double w) { width = w / pScaleNumber; };
	double GetWidth() const { return width * pScaleNumber; };
	void SetWallHeight(double w) { wallHeight = w / pScaleNumber; };
	double GetWallHeight() const { return wallHeight * pScaleNumber; }
	void SetArcHeight(double w) { arcHeight = w / pScaleNumber; };
	double GetArcHeight() const { return arcHeight; };
	void SetNormalToArc(bool flag) { isCableNormalToArc = flag; };
	bool GetNormalToArc() { return isCableNormalToArc; };
	void SetBangLeftAngle(double w) { mBangLeftAngle = w; };
	double GetBangLeftAngle() const { return mBangLeftAngle; };
	void SetBangRightAngle(double flag) { mBangRightAngle = flag; };
	double GetBangRightAngle() { return mBangRightAngle; };

private :
	AcGePoint2d * ptTunnelStart = new AcGePoint2d(170, 60);
	AcGePoint2d * ptCenter = new AcGePoint2d();
	AcGePoint2dArray * mTopBoltsArr = new AcGePoint2dArray();
	AcGePoint2dArray * mLeftBoltArr = new AcGePoint2dArray();
	AcGePoint2dArray * mRightBoltArr = new AcGePoint2dArray();
	AcGePoint2dArray * mCableArr = new AcGePoint2dArray();

	double border = 0.2;
	double width;
	double wallHeight;
	double arcHeight;
	double mBangLeftAngle;
	double mBangRightAngle;
	double radius;
	double startAngle;
	double endAngle;
	bool isCableNormalToArc; //�Ƿ�ֱ�ڹ���
};

