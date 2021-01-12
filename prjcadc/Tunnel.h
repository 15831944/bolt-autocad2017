#pragma once
#include "Bolt.h"
#include "Cable.h"
#include "DrawUtil.h"
#include "TunnelProject.h"
class CTunnel
{
protected:
	int pZhihuWay = 0; // 巷道支护方式
	bool pHasRevertAngle = false; //角部锚杆偏转角度
	double pTopAngle = 90; // 与顶板的夹角
	double pLeftAngle = 90; // 与帮的上夹角
	double pRightAngle = 90; // 与帮的下夹角
	int pCalMethod = 0; //方法选择 1,2,3,4分别对应 理论计算、工程经验、松动范围、专家决策
	bool pHasTopBolt = true; // 要顶部锚杆
	bool pHasLeftBolt = false; // 要帮部锚杆
	bool pHasRightBolt = false; // 是否为全锚索
	bool pHasCable = false; // 要锚索
	int pTopNet = 0; // 顶部网
	int pBangNet = 0; // 帮部网 
	int pConcreteThickness = 0; //混凝土厚度
	int pQiThickness = 0; // 砌煊参数
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
	//绘制断面图形，三种巷道绘制断面方式各不相同
	virtual void DrawTunnel();
	//顶部锚杆托梁
	virtual void DrawTopTuoLiang(CBolt bolt);
	// 绘制顶部锚杆
	virtual void DrawTopBolt(CBolt bolt);
	//绘制顶视图的网格线
	virtual void DrawTopViewNet(CBolt bolt);
	virtual void DrawLeftBolt(CBolt bolt);
	virtual void DrawLeftTuoLiang(CBolt bolt);
	virtual void DrawLeftViewNet(CBolt bolt);
	virtual void DrawRightBolt(CBolt bolt);
	virtual void DrawRightTuoLiang(CBolt bolt);
	virtual void DrawRightViewNet(CBolt bolt);
	// 绘制锚索
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