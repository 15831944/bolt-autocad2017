#pragma once
#include "Bolt.h"
#include "Cable.h"
#include "DrawUtil.h"
#include "TunnelProject.h"
class CTunnel
{
protected:
	int pZhihuWay = 0; // ���֧����ʽ
	bool pHasRevertAngle = false; //�ǲ�ê��ƫת�Ƕ�
	double pTopAngle = 90; // �붥��ļн�
	double pLeftAngle = 90; // �����ϼн�
	double pRightAngle = 90; // �����¼н�
	int pCalMethod = 0; //����ѡ�� 1,2,3,4�ֱ��Ӧ ���ۼ��㡢���̾��顢�ɶ���Χ��ר�Ҿ���
	bool pHasTopBolt = true; // Ҫ����ê��
	bool pHasLeftBolt = false; // Ҫ�ﲿê��
	bool pHasRightBolt = false; // �Ƿ�Ϊȫê��
	bool pHasCable = false; // Ҫê��
	int pTopNet = 0; // ������
	int pBangNet = 0; // �ﲿ�� 
	int pConcreteThickness = 0; //���������
	int pQiThickness = 0; // ���Ӳ���
	int  pScaleNumber = 100;

	CCable * pCable;
	CBolt * pTopBolt;
	CBolt * pLeftBolt;
	CBolt * pRightBolt;

public:
	CTunnel();
	~CTunnel();
	void DrawProject(CTunnelProject project);
	void DrawTableBoltPm();
	void DrawTopCastNet();
	void DrawBangCastNet();
	//���ƶ���ͼ�Σ�����������ƶ��淽ʽ������ͬ
	virtual void DrawTunnel();
	//����ê������
	virtual void DrawTopTuoLiang(CBolt bolt);
	// ���ƶ���ê��
	virtual void DrawTopBolt(CBolt bolt);
	//���ƶ���ͼ��������
	virtual void DrawTopViewNet(CBolt bolt);
	virtual void DrawLeftBolt(CBolt bolt);
	virtual void DrawLeftTuoLiang(CBolt bolt);
	virtual void DrawLeftViewNet(CBolt bolt);
	virtual void DrawRightBolt(CBolt bolt);
	virtual void DrawRightTuoLiang(CBolt bolt);
	virtual void DrawRightViewNet(CBolt bolt);
	// ����ê��
	virtual void DrawCable(CCable cable);

	void SetZhihuWay(int way) { pZhihuWay = way; };
	int GetZhihuWay() const { return pZhihuWay; };
	void SetHasRevertAngle(bool flag) { pHasRevertAngle = flag; };
	bool GetRevertAngle() const { return pHasRevertAngle; };
	void SetTopAngle(int angle) { pTopAngle = angle; };
	double GetTopAngle() const {
		return pTopAngle;
	};
	void SetLeftAngle(int angle) { pLeftAngle = angle; };
	double GetLeftAngle() const {
		return pLeftAngle;
	};
	void SetRightAngle(int angle) { pRightAngle = angle; };
	double GetRightAngle() const {
		return pRightAngle;
	};
	void SetCalMethod(int m) { pCalMethod = m; };
	int GetCalMethod() const { return pCalMethod; };
	void SetHasTopBolt(bool flag) { pHasTopBolt = flag; }
	bool GetHasTopBolt() const { return pHasTopBolt; };
	void SetHasLeftBolt(bool flag) { pHasLeftBolt = flag; }
	bool GetHasLeftBolt() const { return pHasLeftBolt; };
	void SetHasRightBolt(bool flag) { pHasRightBolt = flag; }
	bool GetHasRightBolt() const { return pHasRightBolt; };
	void SetHasCable(bool flag) { pHasCable = flag; }
	bool GetHasCable() const { return pHasCable; };
	void SetTopNet(int m) { pTopNet = m; };
	int GetTopNet() const { return pTopNet; };
	void SetBangNet(int m) { pBangNet = m; };
	int GetBangNet() const { return pBangNet; };
	void SetConcreteThickness(int m) { pConcreteThickness = m; };
	int GetConcreteThickness() const { return pConcreteThickness; };
	void SetQiThickness(int m) { pQiThickness = m; };
	int GetQiThickness() const { return pQiThickness; };
	void SetScaleNumber(int m) { pScaleNumber = m; };
	int GetScaleNumber() const { return pScaleNumber; };

	void SetTopBolt(CBolt * b) { pTopBolt = b; };
	CBolt * GetTopBolt() const { return pTopBolt; };
	void SetLeftBolt(CBolt * b) { pLeftBolt = b; };
	CBolt * GetLeftBolt() const { return pLeftBolt; };
	void SetRightBolt(CBolt * b) { pRightBolt = b; };
	CBolt * GetRightBolt() const { return pRightBolt; };
	void SetCable(CCable * c) { pCable = c; };
	CCable * GetCable() const { return pCable; };
};