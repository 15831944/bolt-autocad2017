#pragma once
#include "MFCUtil.h"
#include "stdafx.h"
#include <map>
#include <vector>
#include <iostream>
#include <array>
class CMethod
{
public:
	CMethod() {};
	~CMethod() {};
	void SetConcreteThickness(double t) { pConcreteThickness = t; };
	double GetConcreteThickness() const { return pConcreteThickness; };
	void SetQiThickness(double t) { pQiThickness = t; };
	double GetQiThickness() const { return pQiThickness; };
	void SetBoltDiameter(double t) { pBoltDiameter = t; };
	double GetBoltDiameter() const { return pBoltDiameter; };
	void SetBoltPitch(double t) { pBoltPitch = t; };
	double GetBoltPitch() const { return pBoltPitch; };
	void SetBoltAttach(double t) { pBoltAttach = t; };
	double GetBoltAttach() const { return pBoltAttach; };
	void SetBoltDesignNumber(double t) { pBoltDesignNumber = t; };
	double GetBoltDesignNumber() const { return pBoltDesignNumber; };
	void SetBoltNumber(int t) { pBoltNumber = t; };
	int GetBoltNumber() const { return pBoltNumber; };
	void SetCableNumber(int t) { pCableNumber = t; };
	int GetCableNumber() const { return pCableNumber; };
	void SetCableDiameter(double t) { pCableDiameter = t; };
	double GetCableDiameter() const { return pCableDiameter; };
	void SetCablePitch(double t) { pCablePitch = t; };
	double GetCablePitch() const { return pCablePitch; };
	void SetCableAttach(double t) { pCableAttach = t; };
	double GetCableAttach() const { return pCableAttach; };
	void SetCableBreakPower(double t) { pCableBreakPower = t; };
	double GetCableBreakPower() const { return pCableBreakPower; };
	void SetA(double a1) { a = a1 / 2; };
	void SetH(double h1) { h = h1; };

	// ��ȡ����ê�˵ĸ���
	virtual int GetTopBoltNumber() = 0;
	// ��ȡ����ê�˵ĳ���
	virtual double GetTopBoltLength() = 0;
	//virtual double GetTopBoltALength() = 0;
	//virtual double GetBangBoltLength() = 0;

protected:
	double pConcreteThickness = 0;
	double pQiThickness = 0;
	double pBoltDiameter; // ê�����ֱ��
	double pBoltPitch; //ê���ž� 
	double pBoltDesignNumber; //ê��ê�������ֵ
	int pBoltNumber ; // ê�˸���
	double pBoltAttach; //ê��ճ��ǿ��
	double pCableDiameter;
	int pCableNumber ; //ê������
	double pCablePitch; //ê���ž�
	double pCableBreakPower; //ê���ƶ���
	double pCableAttach; //ê��ճ��ǿ��
	double a ; // �����ȵ�һ��
	double h ; // ����߶�
};

class CTheoryCalMethod : public CMethod {
private:
	double mAvgGravity; // ú��ƽ���ض�
	double mCompressive; // ��ѹǿ��
	double mMaiDepth; //�������
	double mStoneNianPower; //Χ��ճ����
	double mInnerFriction; //ƽ����Ħ����
	double mShuLength; //��֬ҩ����
	double mStoneStrongNumber; // ��ʯ���ϵ��
	double mBoltExperienceNumber; //����ϵ��
	double mBoltCaiAffectNumber; //ê�˲ɶ�Ӱ��ϵ��
	double mCableCaiAffectNumber; // ê���ɶ�Ӱ��ϵ��
	double mCableFreeLength; //ê�����ɳ���
	 
	std::vector<double> mVecCompressive; //���壬������ڲ㣬�װ忹ѹǿ��
	std::vector<double> mVecAttach; //ճ����
	std::vector<double> mVecFriction; //��Ħ����

	double b;
	double G1;
public:
	CTheoryCalMethod() {};
	~CTheoryCalMethod() {};

	void SetAvgGravity(double t) { mAvgGravity = t; };
	double GetAvgGravity() const { return mAvgGravity; };
	void SetCompressive(double t) { mCompressive = t; };
	double GetCompressive() const { return mCompressive; };
	void SetMaiDepth(double t) { mMaiDepth = t; };
	double GetMaiDepth() const { return mMaiDepth; };
	void SetInnerFriction(double t) { mInnerFriction = t; };
	double GetInnerFriction() const { return mInnerFriction; };
	void SetShuLength(double t) { mShuLength = t; };
	double GetShuLength() const { return mShuLength; };
	void SetStoneStrongNumber(double t) { mStoneStrongNumber = t; };
	double GetStoneStrongNumber() const { return mStoneStrongNumber; };
	void SetBoltExperienceNumber(double t) { mBoltExperienceNumber = t; };
	double GetBoltExperienceNumber() const {
		return mBoltExperienceNumber;
	};
	void SetStoneNianPower(double t) { mStoneNianPower = t; };
	double GetStoneNianPower() const { return mStoneNianPower; };
	void SetBoltCaiAffectNumber(double t) { mBoltCaiAffectNumber = t; };
	double GetBoltCaiAffectNumber() const { return mBoltCaiAffectNumber; };
	void SetCableCaiAffectNumber(double t) { mCableCaiAffectNumber = t; };
	double GetCableCaiAffectNumber() const { return mCableCaiAffectNumber; };
	void SetCableFreeLength(double  t) { mCableFreeLength = t; };
	double GetCableFreeLength() const {
		return mCableFreeLength;
	};
	void SetVecCompressive(std::vector<double> vec) { 
		mVecCompressive = vec; 
		double sum = 0;
		for (auto i : vec) {
			sum += i;
		}

		std::cout << "sum: " << sum << std::endl;

		std::cout << "SetVecCompressive" << mCompressive << std::endl;

		mCompressive = (sum / 3.0);
		std::cout << "SetVecCompressive after divided: " << mCompressive << std::endl;

	};

	void SetVecNianPower(std::vector<double> vec) {
		mVecAttach = vec;
		double sum = 0;
		for (auto i : vec) {
			sum += i;
		}
		mStoneNianPower = sum / 3;
	};

	void SetVecFriction(std::vector<double> vec) {
		mVecFriction = vec;
		double sum = 0;
		for (auto i : vec) {
			sum += i;
		}
		mInnerFriction = sum / 3;
	};
	 
	/* Attention!!!!!!!! ���¼����е����м���ͷ��ض����� m Ϊ��λ�ģ��������� */

	// ʹ�����ۼ��㷨���㶥��ê�˵ĸ���
	int GetTopBoltNumber() {
		double b = (a + (h / 2) *  (1 / tan(MFCUtil::AngleToArc(45 + (mInnerFriction / 2)))))
			/ mStoneStrongNumber;
		double G1 = mBoltCaiAffectNumber * mAvgGravity * b * (pBoltPitch / 1000);
		int CalculateNumber = ceil(G1 / pBoltDesignNumber);
		std::cout << "cal bolt number : " << CalculateNumber << std::endl;
		if (CalculateNumber < pBoltNumber) {
			// �������ó���ê������С�������ê������
			return pBoltNumber;
		}
		else {
			// ������ó��� N > ����ê���������Լ���Ϊ׼������ȡ��
			return  CalculateNumber;
		}
	};
	// ͨ������õ�����ê�˵�ê�̳���
	double GetTopBoltALength() {
		double b = (a + (h / 2) *  (1 / tan(MFCUtil::AngleToArc(45 + (mInnerFriction / 2)))))
			/  mStoneStrongNumber;

		std::cout << "b: " << b << std::endl;
		// ð�买��ê�˳���ý�������
		double G1 = mBoltCaiAffectNumber * mAvgGravity  * b * (pBoltPitch / 1000);
		std::cout << "G1: " << G1 << std::endl;
		double length = (mBoltExperienceNumber * G1) /
			((2.83 * (mCompressive / 12) * (pBoltDiameter/ 1000) * 1000));
		std::cout << "A length: " << length << std::endl;
		return length;
	};
	double GetTopBoltLength() {
		//��ЧԲ�뾶
		std::cout << "a: " << a << std::endl;
		std::cout << "h: " << h << std::endl;

		double r0 = std::sqrt((a * a) + ((h / 2) * (h / 2)));
		std::cout << "r0: " << r0 << std::endl;

		std::cout << "P: " << mAvgGravity * mMaiDepth << std::endl;
		std::cout << "cot fai :" << 1 / tan(MFCUtil::AngleToArc(mInnerFriction)) << std::endl;
		std::cout << "sin fai :" << sin(MFCUtil::AngleToArc(mInnerFriction)) << std::endl;

		double cot_fai = 1 / tan(MFCUtil::AngleToArc(mInnerFriction));
		double sin_fai = sin(MFCUtil::AngleToArc(mInnerFriction));
		double tmp1 = ((mAvgGravity * mMaiDepth) + 
			(mStoneNianPower * cot_fai)) * (1 - sin_fai)
			/ (mStoneNianPower * cot_fai);
		std::cout << "������" << tmp1 << std::endl;
		double point_number = (1 - sin_fai) / (2 * sin_fai);
		
		std::cout << "ָ����" << point_number << std::endl;
		double tmp2 = pow(tmp1, point_number);
		std::cout << "pow: " << tmp2 << std::endl;
		double maxR0 = r0 * tmp2;
		std::cout << "R0: " << maxR0 << std::endl;

		double a2 = maxR0 - (h / 2);
		std::cout << "a2: " << a2 << std::endl;

		return a2 + GetTopBoltALength() + 0.1;
	};
	double GetBangBoltLength() {
		double r0 = std::sqrt((a * a) + ((h / 2) * (h / 2)));
		double cot_fai = 1 / tan(MFCUtil::AngleToArc(mInnerFriction));
		double sin_fai = sin(MFCUtil::AngleToArc(mInnerFriction));
		double tmp1 = ((mAvgGravity * mMaiDepth) +
			(mStoneNianPower * cot_fai)) * (1 - sin_fai)
			/ (mStoneNianPower * cot_fai);
		std::cout << "������" << tmp1 << std::endl;
		double point_number = (1 - sin_fai) / (2 * sin_fai);

		std::cout << "ָ����" << point_number << std::endl;
		double tmp2 = pow(tmp1, point_number);
		double maxR0 = r0 * tmp2;
		double a1 = maxR0 - a;
		return a1 + GetTopBoltALength() + 0.1;
	};
	
	double GetCableALength() {
		double G2 = mCableCaiAffectNumber * mAvgGravity *
			a * GetTopBoltLength() * (pCablePitch / 1000);

		std::cout << "G2: " << G2 << std::endl;
		double Lc = G2 / (2.83 * pCableNumber * (pCableDiameter / 1000) * (mCompressive / 12) * 1000);
		std::cout << "Lc: " << Lc << std::endl;
		return Lc;
	};
	double GetCableLength() {
		return 0.3 + (mCableFreeLength /1000) + GetCableALength();
	};
};

class CProExpMethod : public CMethod {
private:
	int mStoneType;
	double mBoltLength; // ê�˳���
	double mBoltSpace; //ê�˼��
	double mBoltShuLength; //ê����֬ҩ����
	double mCableLength; //ê������
	double mCableSpace; //ê�����
	double mCableShuLength; //ê����֬ҩ����
public:
	CProExpMethod() {};
	~CProExpMethod() {};
	void SetStoneType(int type) { mStoneType = type; };
	int GetStoneType() const { return mStoneType; };
	void SetBoltLength(double t) { mBoltLength = t; };
	double GetBoltLength() const { return mBoltLength; };
	void SetBoltSpace(double t) { mBoltSpace = t; };
	double GetBoltSpace() const { return mBoltSpace; };
	void SetBoltShuLength(double t) { mBoltShuLength = t; };
	double GetBoltShuLength() const { return mBoltShuLength; };
	void SetCableLength(double t) { mCableLength = t; };
	double GetCableLength() const { return mCableLength; };
	void SetCableSpace(double t) { mCableSpace = t; };
	double GetCableSpace() const { return mCableSpace; };
	void SetCableShuLength(double t) { mCableShuLength = t; };
	double GetCableShuLength() const { return mCableShuLength; };

	// ��ȡ����ê�˵ĸ���
	int GetTopBoltNumber() {
		return pBoltNumber;
	};
	// ��ȡ����ê�˵ĳ���
	double GetTopBoltLength() {
		return mBoltLength;
	};

};

class CLooseRangeMethod : public CMethod {
private:
	int mMeasureWay;
	double mLooseRange;
	double mStoneStrongNumber; //��ʯ���ϵ��
public:
	CLooseRangeMethod() {};
	~CLooseRangeMethod() {};
	void SetMeasureWay(int way) { mMeasureWay = way; };
	int GetMeasureWay() const { return mMeasureWay; };
	void SetLooseRange(double t) { mLooseRange = t; };
	double GetLooseRange() const { return mLooseRange; };
	void SetStoneStrongNumber(double t) { mStoneStrongNumber = t; };
	double GetStoneStrongNumber() const { return mStoneStrongNumber; };

	// ��ȡ����ê�˵ĸ���
	int GetTopBoltNumber() {
		return pBoltNumber;
	};
	// ��ȡ����ê�˵ĳ���
	double GetTopBoltLength() {
		return mLooseRange + 0.4;
	};

};

class CBalanceMethod : public CMethod {
private:
	
	double mAvgGravity; //�ײ�ƽ�������ܶ�
	double mMaiDepth; 
	double mCoalHardNumber_Fy;// ú��Ӳ��ϵ��
	double mCoalThickness;// ú����
	double mCaiEffectNumber;
	double mInnerFriction;
	double mStableNumber; // ��ê�Ҳ��ȶ���ϵ��
	double mStoneHardNumber;//ê���Ҳ�Ӳ��
	double mCoalAngle; //ú�����
	double mBoltOutLength; //ê����¶����
	double mBoltSpace;
	double mBoltYieldNumber; // ê������ǿ��
	double mBoltStablePower; // ê����
	double mBoltSafeNumber;
	double mTopAvgGravity;
	int mBoltNumber; // ê������
	double mCableOutLength;
	double mCableStoneHeight;
	double mCableALength;
	double mMinBreakLoader; //����ƻ�����
	double mCableSafeNumber;

	double GetBangBreakDepth() {
		double Kcx = 2.5;
		double div_top = Kcx * mAvgGravity * mMaiDepth * mCaiEffectNumber;
		double div_bottom = pow(10, 4) * mCoalHardNumber_Fy;
		double sub1 = div_top / div_bottom - 1;
		double tan_fai = tan(MFCUtil::AngleToArc((90 - mInnerFriction) * 0.5));
		std::cout << "BangBreakDepth C: " << sub1 * mCoalThickness * tan_fai << std::endl;
		return sub1 * mCoalThickness * tan_fai;
	};

	double GetTopBreakDepth() {
		double C = GetBangBreakDepth();
		double div_top = (a + C) * cos(MFCUtil::AngleToArc(mCoalAngle));
		double div_bottom = mStableNumber * mStoneHardNumber;
		std::cout << "TopBreakDepth b: " << div_top / div_bottom << std::endl;
		return div_top / div_bottom;
	};
public:
	void SetAvgGravity(double t) { mAvgGravity = t ; };
	double GetAvgGravity() const { return mAvgGravity; };
	void SetMaiDepth(double t) { mMaiDepth = t; };
	double GetMaiDepth() const { return mMaiDepth; };
	void SetCoalHardNumber_Fy(double t) { mCoalHardNumber_Fy = t; };
	double GetCoalHardNumber_Fy() const { return mCoalHardNumber_Fy; };
	void SetCoalThickness(double t) { mCoalThickness = t; };
	double GetCoalThickness() const { return mCoalThickness; };
	void SetCaiEffectNumber(double t) { mCaiEffectNumber = t; };
	double GetCaiEffectNumber() const { return mCaiEffectNumber; };
	void SetInnerFriction(double t) { mInnerFriction = t; };
	double GetInnerFriction() const { return mInnerFriction; };
	void SetStableNumber(double t) { mStableNumber = t; };
	double GetStableNumber() const { return mStableNumber; };
	void SetStoneHardNumber(double t) { mStoneHardNumber = t; };
	double GetStoneHardNumber() const { return mStoneHardNumber; };
	void SetCoalAngle(double t) { mCoalAngle = t; };
	double GetCoalAngle() const { return mCoalAngle; };
	void SetBoltOutLength(double t) { mBoltOutLength = t; };
	double GetBoltOutLength() const { return mBoltOutLength; };
	void SetBoltSpace(double t) { mBoltSpace = t; };
	double GetBoltSpace() const { return mBoltSpace; };
	void SetBoltYieldNumber(double t) { mBoltYieldNumber = t; };
	double GetBoltYieldNumber() const { return mBoltYieldNumber; };
	void SetBoltStablePower(double t) { mBoltStablePower = t; };
	double GetBoltStablePower() const { return mBoltStablePower; };
	void SetBoltSafeNumber(double t) { mBoltSafeNumber = t; };
	double GetBoltSafeNumber() const { return mBoltSafeNumber; };
	void SetTopAvgGravity(double t) { mTopAvgGravity = t; };
	double GetTopAvgGravity() const { return mTopAvgGravity; };
	void SetBoltNumber(int t) { mBoltNumber = t; };
	int GetBoltNumber() const { return mBoltNumber; };
	void SetCableOutLength(double t) { mCableOutLength = t; };
	double GetCableOutLength() const { return mCableOutLength; };
	void SetCableStoneHeight(double t) { mCableStoneHeight = t; };
	double GetCableStoneHeight() const { return mCableStoneHeight; };
	void SetCableALength(double t) { mCableALength = t; };
	double GetCableALength() const { return mCableALength; };
	void SetMinBreakLoader(double t) { mMinBreakLoader = t; };
	double GetMinBreakLoader() const { return mMinBreakLoader; };
	void SetCableSafeNumber(double t) { mCableSafeNumber = t; };
	double GetCableSafeNumber() const { return mCableSafeNumber; };

	// ��ȡ����ê�˵ĸ���
	int GetTopBoltNumber() {
		return mBoltNumber;
	};

	// ��ȡ����ê�˵ĳ���
	double GetTopBoltLength() {
		return GetTopBreakDepth() + mBoltOutLength;
	};

	double GetBangBoltLength() {
		return GetBangBreakDepth() + mBoltOutLength;
	};

	double GetBoltPitch() {
		double b = GetTopBreakDepth();
		double div_top = mBoltStablePower * mBoltNumber;
		double div_bottom = 2 * mBoltSafeNumber * mTopAvgGravity * a * b;
		std::cout << "balance method pitch: " << div_top / div_bottom << std::endl;
		return div_top / div_bottom;
	};

	double GetBoltDiameter() {
		double pi = asin(0.5) * 6;
		double d = sqrt((4 * mBoltStablePower * 1000) / (pi * mBoltYieldNumber));
		std::cout << "balance diameter: " << d << std::endl;
		return d;
	};

	// ���ؽ���� m Ϊ��λ
	double GetCableLength() {
		return mCableOutLength + mCableALength + mCableStoneHeight;
	};

	double GetCableSpaceAndPitch() {
		double width = a * 2;
		double S = (mMinBreakLoader * 3) / (4 * pow(width, 2) * mAvgGravity * mCableSafeNumber);
		return S;
	};
};

class CMethodFactory {
public:
	CMethodFactory() {  };
	~CMethodFactory() {};
	virtual CMethod* createMethod() = 0 ;

};

class CTheroyMethodFactory : public CMethodFactory {
public:
	CTheroyMethodFactory() {};
	~CTheroyMethodFactory() {};
	CMethod* createMethod() {
		return new CTheoryCalMethod();
	};
};

class CProExpMethodFactory :public CMethodFactory {
public:
	CProExpMethodFactory() {};
	~CProExpMethodFactory() {};
	CMethod* createMethod() {
		return new CProExpMethod();
	};
};

class CLooseRangeMethodFactory :public CMethodFactory {
public:
	CLooseRangeMethodFactory() {};
	~CLooseRangeMethodFactory() {};
	CMethod* createMethod() {
		return new CLooseRangeMethod();
	};
};

class CBalanceMethodFactory : public CMethodFactory {
public:
	CBalanceMethodFactory() {};
	~CBalanceMethodFactory() {};
	CMethod* createMethod() {
		return new CBalanceMethod();
	};
};