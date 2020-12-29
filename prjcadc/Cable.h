#pragma once
class CCable
{
	// 锚索
private:
	double diameter; //直径
	double length; //长度
	CString material; //材料
	double tailing; //尾部螺纹长
	int number; //数量
	double space; //间距
	double pitch; //排距
	double aLength; //锚固长

	double trayLength; //锚索托盘长度
	CString trayMaterial; //锚索托盘材料

	double shuDiameter; //树脂药卷直径
	double shuLength; //树脂药卷长度
	CString shuMaterial; //材料
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
	double getTrayLength() const { return trayLength; } //锚索托盘长度
	void setTrayMaterial(CString tm) { trayMaterial = tm; }
	CString getTrayMaterial() const { return trayMaterial; } //锚索托盘材料

	void setShuDiameter(double d) { shuDiameter = d; }
	double getShuDiameter() const { return shuDiameter; }
	void setShuLength(double l) { shuLength = l; }
	double getShuLength() const { return shuLength; }
	void setShuMaterial(CString m) { shuMaterial = m; }
	CString geShutMaterial() const { return shuMaterial; }


	CCable();
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
		CString sm);
	~CCable();
};

