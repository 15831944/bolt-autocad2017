#include "stdafx.h"
#include "MFCUtil.h"
#include "CalMethod.h"
#pragma once
class CBolt
{
	//ê�˶���
private:
	double diameter = 18; //ֱ��
	double length = 2000; //����
	CString material = CString("��������"); //����
	double tailing = 120; //β�����Ƴ�
	int number = 3; //����
	double space = 1000; //���
	double pitch = 1000; //�ž�
	double aLength = 700; //ê�̳�
	double beamWidth = 50; //ê����������
	CString beamMaterial = CString("14��Բ�ֺ���"); //ê����������
	double portBeamWidth = 50; // ����ê����������
	CString portBeamMaterial = CString("14��Բ�ֺ���");
	CString trayLength = CString("150*150*10"); //ê�����̳���
	CString trayMaterial = CString("10�۸�"); //ê�����̲���

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
	// ˽�б�����Getter��Setter����ʹ����������ʵ��
	void setDiameter(double d) { diameter = d; }
	double getDiameter() const { return diameter; }
	void setLength(double l) { length = l; }
	double getLength() const { return length; }
	void setMaterial(CString m) { material = m; }
	CString getMaterial() const { return material; }
	void setTailing(double t) { tailing = t; }
	double getTailing() const { return tailing; } //β�����Ƴ�
	void setNumber(int n) { number = n; }
	int getNumber() const { return number; } //����
	void setSpace(double s) { space = s; }
	double getSpace() const { return space; } //���
	void setPitch(double p) { pitch = p; }
	double getPitch() const { return pitch; } //�ž�
	void setALength(double al) { aLength = al; }
	double getALength() const { return aLength; } //ê�̳�

	void setBeamWidth(double bw) { beamWidth = bw; }
	double getBeamWidth() const { return beamWidth; } //ê����������
	void setBeamMaterial(CString bm) { beamMaterial = bm; }
	CString getBeamMaterial() const { return beamMaterial; } //ê����������

	void setPortBeamWidth(double bw) { portBeamWidth = bw; }
	double getPortBeamWidth() const { return portBeamWidth; } //ê����������
	void setPortBeamMaterial(CString bm) { portBeamMaterial = bm; }
	CString getPortBeamMaterial() const { return portBeamMaterial; } //ê����������
	void setTrayLength(CString tl) { trayLength = tl; }
	CString getTrayLength() const { return trayLength; } //ê�����̳���
	void setTrayMaterial(CString tm) { trayMaterial = tm; }
	CString getTrayMaterial() const { return trayMaterial; } //ê�����̲���
};

class CCable
{
	// ê��
private:
	double diameter = 25; //ֱ��
	double length = 4500; //����
	CString material =  CString("�ֽ���"); //����
	double tailing = 120; //β�����Ƴ�
	int number = 2; //����
	double space = 1200; //���
	double pitch = 2400; //�ž�
	double aLength = 1400; //ê�̳�

	double trayLength = 500; //ê�����̳���
	CString trayMaterial = CString("12�۸�"); //ê�����̲���

	double shuDiameter = 28; //��֬ҩ��ֱ��
	double shuLength = 35; //��֬ҩ����
	CString shuMaterial = CString("Z2835"); //����
public:
	// ˽�б�����Getter��Setter����ʹ����������ʵ��
	void setDiameter(double d) { diameter = d; }
	double getDiameter() const { return diameter; }
	void setLength(double l) { length = l; }
	double getLength() const { return length; }
	void setMaterial(CString m) { material = m; }
	CString getMaterial() const { return material; }
	void setTailing(double t) { tailing = t; }
	double getTailing() const { return tailing; } //β�����Ƴ�
	void setNumber(int n) { number = n; }
	int getNumber() const { return number; } //����
	void setSpace(double s) { space = s; }
	double getSpace() const { return space; } //���
	void setPitch(double p) { pitch = p; }
	double getPitch() const { return pitch; } //�ž�
	void setALength(double al) { aLength = al; }
	double getALength() const { return aLength; } //ê�̳�

	void setTrayLength(double tl) { trayLength = tl; }
	double getTrayLength() const { return trayLength; } //ê����������

	void setTrayMaterial(CString tm) { trayMaterial = tm; }
	CString getTrayMaterial() const { return trayMaterial; } //ê�����̲���

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

 
// ����������е�����
class CTunnel {
protected:
	int pZhihuWay = 0; // ���֧����ʽ
	bool pHasRevertAngle = false; //�ǲ�ê��ƫת�Ƕ�
	double pTopAngle = 90 ; // �붥��ļн�
	double pLeftAngle = 90 ; // �����ϼн�
	double pRightAngle = 90; // �����¼н�
	int pCalMethod = 4; //����ѡ�� 1,2,3,4�ֱ��Ӧ ���ۼ��㡢���̾��顢�ɶ���Χ��ר�Ҿ���
	bool pHasTopBolt = true; // Ҫ����ê��
	bool pHasLeftBolt = false; // Ҫ�ﲿê��
	bool pHasRightBolt = false; // �Ƿ�Ϊȫê��
	bool pHasCable = false; // Ҫê��
	int pTopNet = 0; // ������
	int pBangNet = 0; // �ﲿ�� 
	CString pTopnetSize;
	CString pBangnetSize;
	int pConcreteThickness = 0; //���������
	int pQiThickness = 0; // ���Ӳ���
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
�ڼ���ʱ���ù�����������壬��¼��������Ĺ�ͬ����;
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
	double trapBottomWidth = 0; // �ù�������������¼���β�����
	int LeftAngle = 90; //���ε����Ҽн�
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

// �������
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

// �������
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