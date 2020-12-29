#pragma once
class CBolt
{
	//ê�˶���
private:
	double diameter; //ֱ��
	double length; //����
	CString material; //����
	double tailing; //β�����Ƴ�
	int number; //����
	double space; //���
	double pitch; //�ž�
	double aLength; //ê�̳�
	double beamWidth; //ê����������
	CString beamMaterial; //ê����������

	double portBeamWidth; // ����ê����������
	CString portBeamMaterial;
	CString trayLength; //ê�����̳���
	CString trayMaterial; //ê�����̲���

public:
	CBolt();
	CBolt(double d, double l, CString m, double t, int n, double s,
		double p, double al, double bw, CString bm, CString tl, CString tm);
	~CBolt();
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

