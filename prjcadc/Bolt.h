#pragma once
class CBolt
{
	//锚杆对象
private:
	double diameter; //直径
	double length; //长度
	CString material; //材料
	double tailing; //尾部螺纹长
	int number; //数量
	double space; //间距
	double pitch; //排距
	double aLength; //锚固长
	double beamWidth; //锚杆托梁净宽
	CString beamMaterial; //锚杆托梁材料

	double portBeamWidth; // 纵向锚杆托梁净宽
	CString portBeamMaterial;
	CString trayLength; //锚杆托盘长度
	CString trayMaterial; //锚杆托盘材料

public:
	CBolt();
	CBolt(double d, double l, CString m, double t, int n, double s,
		double p, double al, double bw, CString bm, CString tl, CString tm);
	~CBolt();
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

