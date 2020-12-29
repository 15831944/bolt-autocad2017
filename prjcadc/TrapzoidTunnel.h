#pragma once
#include "Tunnel.h"
#include "RectangleTunnel.h"
class CTrapzoidTunnel :
	public CTunnel
{
public:
	CTrapzoidTunnel();
	CTrapzoidTunnel(double bw, double h, int la, int ra);
	CTrapzoidTunnel(double bw, double h, int la, int ra, double tba, double lba, double rba);
	~CTrapzoidTunnel();
	virtual void DrawTunnel();
	virtual void DrawTopBolt(CBolt bolt);
	virtual void DrawTopTuoLiang(CBolt bolt);
	//���ƶ���ͼ��������
	virtual void DrawTopViewNet(CBolt bolt);
	// DrawLeftbolt��DrawLeftTuoliang�� DrawLeftViewNet����������ϣ���Ҫ�õ� LeftBoltArr ����
	// ��DrawLeftBolt�ж� leftBoltArr���г�ʼ��
	virtual void DrawLeftBolt(CBolt bolt);
	virtual void DrawLeftTuoLiang(CBolt bolt);
	virtual void DrawLeftViewNet(CBolt bolt);
	
	virtual void DrawRightBolt(CBolt bolt);
	virtual void DrawRightTuoLiang(CBolt bolt);
	virtual void DrawRightViewNet(CBolt bolt);
	virtual void DrawCable(CCable cable);

private:
	double topWidth;
	double bottomWidth;
	double height;
	int leftAngle;
	int rightAngle;
	double mLeftBoltAngle = 90;
	double mRightBoltAngle = 90;
	double mTopBoltAngle = 90;
	double border = 0.2;
	AcGePoint2d * ptTunnelStart = new AcGePoint2d(170, 60);
	// ʹ�������¼����ê����������ϵ�����
	AcGePoint2dArray * mTopBoltsArr = new AcGePoint2dArray();
	AcGePoint2dArray * mLeftBoltArr = new AcGePoint2dArray();
	AcGePoint2dArray * mRightBoltArr = new AcGePoint2dArray();
	AcGePoint2dArray * mCableArr = new AcGePoint2dArray();
int GetMinPointId(AcGePoint2dArray * arr);
int GetMaxPointId(AcGePoint2dArray * arr);
};
