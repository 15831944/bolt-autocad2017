#include "stdafx.h"
#include "MFCUtil.h"
#include "CalMethod.h"
#pragma once
class CBolt
{
	//锚杆对象
private:
	double diameter = 18; //直径
	double length = 2000; //长度
	CString material = CString("螺旋钢纹"); //材料
	double tailing = 120; //尾部螺纹长
	int number = 3; //数量
	double space = 1000; //间距
	double pitch = 1000; //排距
	double aLength = 700; //锚固长
	double beamWidth = 50; //锚杆托梁净宽
	CString beamMaterial = CString("14号圆钢焊接"); //锚杆托梁材料
	double portBeamWidth = 50; // 纵向锚杆托梁净宽
	CString portBeamMaterial = CString("14号圆钢焊接");
	CString trayLength = CString("150*150*10"); //锚杆托盘长度
	CString trayMaterial = CString("10槽钢"); //锚杆托盘材料

public:
	CBolt() {};
	CBolt(double d, double l, CString m, double t, int n, double s,
		double p, double al, double bw, CString bm, double pbw, CString pbm, CString tl, CString tm) {
		diameter = d;
		length = l;
		material = m;
		tailing = t;
		number = n;
		space = s;
		pitch = p;
		aLength = al;
		beamWidth = bw;
		beamMaterial = bm;
		portBeamWidth = pbw;
		portBeamMaterial = pbm;
		trayLength = tl;
		trayMaterial = tm;
	};
	~CBolt() {};
	// 私有变量的Getter和Setter方法使用内联函数实现
	void setDiameter(double d) { diameter = d; }
	double getDiameter() const { return diameter; }
	void setLength(double l) { length = l; }
	double getLength() const { return length; }
	void setMaterial(CString m) { material = m; }
	CString getMaterial() const { return material; }
	void setTailing(double t) { tailing = t; }
	double getTailing() const { return tailing; } //尾部螺纹长
	void setNumber(int n) { number = n; }
	int getNumber() const { return number; } //数量
	void setSpace(double s) { space = s; }
	double getSpace() const { return space; } //间距
	void setPitch(double p) { pitch = p; }
	double getPitch() const { return pitch; } //排距
	void setALength(double al) { aLength = al; }
	double getALength() const { return aLength; } //锚固长

	void setBeamWidth(double bw) { beamWidth = bw; }
	double getBeamWidth() const { return beamWidth; } //锚杆托梁净宽
	void setBeamMaterial(CString bm) { beamMaterial = bm; }
	CString getBeamMaterial() const { return beamMaterial; } //锚杆托梁材料

	void setPortBeamWidth(double bw) { portBeamWidth = bw; }
	double getPortBeamWidth() const { return portBeamWidth; } //锚杆托梁净宽
	void setPortBeamMaterial(CString bm) { portBeamMaterial = bm; }
	CString getPortBeamMaterial() const { return portBeamMaterial; } //锚杆托梁材料
	void setTrayLength(CString tl) { trayLength = tl; }
	CString getTrayLength() const { return trayLength; } //锚杆托盘长度
	void setTrayMaterial(CString tm) { trayMaterial = tm; }
	CString getTrayMaterial() const { return trayMaterial; } //锚杆托盘材料
};

class CCable
{
	// 锚索
private:
	double diameter = 25; //直径
	double length = 4500; //长度
	CString material =  CString("钢绞线"); //材料
	double tailing = 120; //尾部螺纹长
	int number = 2; //数量
	double space = 1200; //间距
	double pitch = 2400; //排距
	double aLength = 1400; //锚固长

	double trayLength = 500; //锚索托盘长度
	CString trayMaterial = CString("12槽钢"); //锚索托盘材料

	double shuDiameter = 28; //树脂药卷直径
	double shuLength = 35; //树脂药卷长度
	CString shuMaterial = CString("Z2835"); //材料
public:
	// 私有变量的Getter和Setter方法使用内联函数实现
	void setDiameter(double d) { diameter = d; }
	double getDiameter() const { return diameter; }
	void setLength(double l) { length = l; }
	double getLength() const { return length; }
	void setMaterial(CString m) { material = m; }
	CString getMaterial() const { return material; }
	void setTailing(double t) { tailing = t; }
	double getTailing() const { return tailing; } //尾部螺纹长
	void setNumber(int n) { number = n; }
	int getNumber() const { return number; } //数量
	void setSpace(double s) { space = s; }
	double getSpace() const { return space; } //间距
	void setPitch(double p) { pitch = p; }
	double getPitch() const { return pitch; } //排距
	void setALength(double al) { aLength = al; }
	double getALength() const { return aLength; } //锚固长

	void setTrayLength(double tl) { trayLength = tl; }
	double getTrayLength() const { return trayLength; } //锚索托梁长度

	void setTrayMaterial(CString tm) { trayMaterial = tm; }
	CString getTrayMaterial() const { return trayMaterial; } //锚索托盘材料

	void setShuDiameter(double d) { shuDiameter = d; }
	double getShuDiameter() const { return shuDiameter; }
	void setShuLength(double l) { shuLength = l; }
	double getShuLength() const { return shuLength; }
	void setShuMaterial(CString m) { shuMaterial = m; }
	CString getShuMaterial() const { return shuMaterial; }

	CCable() {
	};
	CCable(double d,
		double l,
		CString m,
		double t,
		int n,
		double s,
		double p,
		double al,
		double tl,
		CString tm,
		double sd,
		double sl,
		CString sm) {
		diameter = d;
		length = l;
		material = m;
		tailing = t;
		number = n;
		space = s;
		pitch = p;
		aLength = al;
		trayLength = tl;
		trayMaterial = tm;
		shuLength = sl;
		shuDiameter = sd;
		shuMaterial = sm;
	};
	~CCable() {};
};

 
// 所有巷道共有的属性
class CTunnel {
protected:
	int pZhihuWay = 0; // 巷道支护方式
	bool pHasRevertAngle = false; //角部锚杆偏转角度
	double pTopAngle = 90 ; // 与顶板的夹角
	double pLeftAngle = 90 ; // 与帮的上夹角
	double pRightAngle = 90; // 与帮的下夹角
	int pCalMethod = 4; //方法选择 1,2,3,4分别对应 理论计算、工程经验、松动范围、专家决策
	bool pHasTopBolt = true; // 要顶部锚杆
	bool pHasLeftBolt = false; // 要帮部锚杆
	bool pHasRightBolt = false; // 是否为全锚索
	bool pHasCable = false; // 要锚索
	int pTopNet = 0; // 顶部网
	int pBangNet = 0; // 帮部网 
	CString pTopnetSize;
	CString pBangnetSize;
	int pConcreteThickness = 0; //混凝土厚度
	int pQiThickness = 0; // 砌煊参数
	CCable * pCable;
	CBolt * pTopBolt;
	CBolt * pLeftBolt;
	CBolt * pRightBolt;

	//CTheoryCalMethod * pTheoryMethod;
	//CProExpMethod *pExperienceMethod;
	//CLooseRangeMethod * pLooseRangeMethod;

public:
	CTunnel() {
		pCable = new CCable();
		pTopBolt = new CBolt();
		pLeftBolt = new CBolt();
		pRightBolt = new CBolt();
		//pTheoryMethod = new CTheoryCalMethod();
		//pExperienceMethod = new CProExpMethod();
		//pLooseRangeMethod = new CLooseRangeMethod();
	}
	~CTunnel() {
		delete pCable;
		delete pTopBolt;
		delete pLeftBolt;
		delete pRightBolt;
//		delete pTheoryMethod;
		//delete pExperienceMethod;
		//delete pLooseRangeMethod;
	}

	void SetZhihuWay(int way) { pZhihuWay = way; };
	int GetZhihuWay() const { return pZhihuWay; };
	void SetHasRevertAngle(bool flag) { pHasRevertAngle = flag; };
	bool GetRevertAngle() const { return pHasRevertAngle; };
	void SetTopAngle(double angle) { pTopAngle = angle; };
	double GetTopAngle() const {
		return pTopAngle;
	};
	void SetLeftAngle(double angle) { pLeftAngle = angle; };
	double GetLeftAngle() const {
		return pLeftAngle;
	};
	void SetRightAngle(double angle) { pRightAngle = angle; };
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
	void SetTopnetSize(CString v) { pTopnetSize = v; };
	CString GetTopnetSize() const { return pTopnetSize; };
	void SetBangnetSize(CString v) { pBangnetSize = v; };
	CString GetBangnetSize() const { return pBangnetSize; };
	void SetConcreteThickness(int m) { pConcreteThickness = m; };
	int GetConcreteThickness() const { return pConcreteThickness; };
	void SetQiThickness(int m) { pQiThickness = m; };
	int GetQiThickness() const { return pQiThickness; };

	void SetTopBolt(CBolt * b) { pTopBolt = b; };
	CBolt * GetTopBolt() const { return pTopBolt; };
	void SetLeftBolt(CBolt * b) { pLeftBolt = b; };
	CBolt * GetLeftBolt() const { return pLeftBolt; };
	void SetRightBolt(CBolt * b) { pRightBolt = b; };
	CBolt * GetRightBolt() const { return pRightBolt; };
	void SetCable(CCable * c) { pCable = c; };
	CCable * GetCable() const { return pCable; };
};

/**
在计算时利用拱形巷道做载体，记录三种巷道的共同属性;
Arc.WallHeight = Rect.height;
Arc.width = rect.width;

Arc.wallheight = trap.height;
arc.width = trap.topWidth;

**/
class CArcTunnel : public CTunnel {
private:
	double width = 0;
	double wallHeight = 0;
	double arcHeight = 0;
	bool isNormalToArc = true;
	double trapBottomWidth = 0; // 用拱形巷道做载体记录梯形参数是
	int LeftAngle = 90; //梯形的左右夹角
	int RightAngle = 90;
public:
	CArcTunnel() {};
	CArcTunnel(double w, double wh, double ah, bool flag) {
		width = w;
		wallHeight = wh;
		arcHeight = ah;
		isNormalToArc = flag;
	};
	~CArcTunnel() {};
	void SetWidth(double w) { width = w; };
	double GetWidth() const { return width; };
	void SetWallHeight(double w) { wallHeight = w; };
	double GetWallHeight() const { return wallHeight; };
	void SetArcHeight(double w) { arcHeight = w; };
	double GetArcHeight() const { return arcHeight; };
	void SetNormalToArc(bool flag) { isNormalToArc = flag; };
	bool GetNormalToArc() { return isNormalToArc; };
	double GetHeight() const { return (arcHeight + wallHeight); };

	void SetTrapBottomWidth(double v) { trapBottomWidth = v; };
	double GetTrapBottomWidth() const { return trapBottomWidth; };
	void SetTrapLeftAngle(int v) { LeftAngle = v; };
	int GetTrapLeftAngle() const { return LeftAngle; };
	void SetTrapRightAngle(int v) { RightAngle = v; };
	int GetTrapRightAngle() const { return RightAngle; };
};

// 矩形巷道
class CRectTunnel : public CTunnel {
private:
	double width = 0;
	double height = 0;
public:
	CRectTunnel() {};
	CRectTunnel(double w,double h) {
		width = w;
		height = h;
	};
	~CRectTunnel() {};
	void SetWidth(double v) { width = v; };
	double GetWidth() const { return width; };
	void SetHeight(double h) { height = h; };
	double GetHeight() const { return height; };
};

// 梯形巷道
class CTrapTunnel : public CTunnel {
private:
	double topWidth;
	double bottomWidth;
	double height;
	int leftAngle;
	int rightAngle;
public:
	CTrapTunnel() {};
	~CTrapTunnel() {};
	CTrapTunnel(double bw, double h, int la, int ra) {
		bottomWidth = bw ;
		height = h ;
		leftAngle = la;
		rightAngle = ra;
		topWidth = bottomWidth - (height / tan(MFCUtil::AngleToArc(la))) - (height / tan(MFCUtil::AngleToArc(ra)));
	};
	void SetTopWidth(double v) { topWidth = v; };
	double GetTopWidth() const { return topWidth; };
	void SetBottomWidth(double v) { bottomWidth = v; };
	double GetTbottomWidth() const { return bottomWidth; };
	void SetHeight(double v) { height = v; };
	double GetHeight() const { return height; };
	void SetLeftAngle(int v) { leftAngle = v; };
	int GetLeftAngle() const { return leftAngle; };
	void SetRightAngle(int v) { rightAngle = v; };
	int GetRightAngle() const { return rightAngle; };
};