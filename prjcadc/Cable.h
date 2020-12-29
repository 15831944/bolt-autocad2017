#pragma once
class CCable
{
	// ê��
private:
	double diameter; //ֱ��
	double length; //����
	CString material; //����
	double tailing; //β�����Ƴ�
	int number; //����
	double space; //���
	double pitch; //�ž�
	double aLength; //ê�̳�

	double trayLength; //ê�����̳���
	CString trayMaterial; //ê�����̲���

	double shuDiameter; //��֬ҩ��ֱ��
	double shuLength; //��֬ҩ����
	CString shuMaterial; //����
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
	double getTrayLength() const { return trayLength; } //ê�����̳���
	void setTrayMaterial(CString tm) { trayMaterial = tm; }
	CString getTrayMaterial() const { return trayMaterial; } //ê�����̲���

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

