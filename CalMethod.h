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

	// 获取顶部锚杆的根数
	virtual int GetTopBoltNumber() = 0;
	// 获取顶部锚杆的长度
	virtual double GetTopBoltLength() = 0;
	//virtual double GetTopBoltALength() = 0;
	//virtual double GetBangBoltLength() = 0;

protected:
	double pConcreteThickness = 0;
	double pQiThickness = 0;
	double pBoltDiameter; // 锚杆钻孔直径
	double pBoltPitch; //锚杆排距 
	double pBoltDesignNumber; //锚杆锚固力设计值
	int pBoltNumber ; // 锚杆根数
	double pBoltAttach; //锚杆粘结强度
	double pCableDiameter;
	int pCableNumber ; //锚索根数
	double pCablePitch; //锚索排距
	double pCableBreakPower; //锚索破断力
	double pCableAttach; //锚索粘结强度
	double a ; // 巷道宽度的一半
	double h ; // 巷道高度
};

class CTheoryCalMethod : public CMethod {
private:
	double mAvgGravity; // 煤岩平均重度
	double mCompressive; // 抗压强度
	double mMaiDepth; //巷道埋深
	double mStoneNianPower; //围岩粘聚力
	double mInnerFriction; //平均内摩擦角
	double mShuLength; //树脂药卷长度
	double mStoneStrongNumber; // 岩石坚固系数
	double mBoltExperienceNumber; //经验系数
	double mBoltCaiAffectNumber; //锚杆采动影响系数
	double mCableCaiAffectNumber; // 锚索采动影响系数
	double mCableFreeLength; //锚索自由长度
	 
	std::vector<double> mVecCompressive; //顶板，巷道所在层，底板抗压强度
	std::vector<double> mVecAttach; //粘聚力
	std::vector<double> mVecFriction; //内摩擦角

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
	 
	/* Attention!!!!!!!! 以下计算中的所有计算和返回都是以 m 为单位的！！！！！ */

	// 使用理论计算法计算顶部锚杆的根数
	int GetTopBoltNumber() {
		double b = (a + (h / 2) *  (1 / tan(MFCUtil::AngleToArc(45 + (mInnerFriction / 2)))))
			/ mStoneStrongNumber;
		double G1 = mBoltCaiAffectNumber * mAvgGravity * b * (pBoltPitch / 1000);
		int CalculateNumber = ceil(G1 / pBoltDesignNumber);
		std::cout << "cal bolt number : " << CalculateNumber << std::endl;
		if (CalculateNumber < pBoltNumber) {
			// 如果计算得出的锚杆数量小于输入的锚杆数量
			return pBoltNumber;
		}
		else {
			// 若计算得出的 N > 输入锚杆数，则以计算为准，向上取整
			return  CalculateNumber;
		}
	};
	// 通过计算得到顶部锚杆的锚固长度
	double GetTopBoltALength() {
		double b = (a + (h / 2) *  (1 / tan(MFCUtil::AngleToArc(45 + (mInnerFriction / 2)))))
			/  mStoneStrongNumber;

		std::cout << "b: " << b << std::endl;
		// 冒落拱内锚杆承受媒体的重量
		double G1 = mBoltCaiAffectNumber * mAvgGravity  * b * (pBoltPitch / 1000);
		std::cout << "G1: " << G1 << std::endl;
		double length = (mBoltExperienceNumber * G1) /
			((2.83 * (mCompressive / 12) * (pBoltDiameter/ 1000) * 1000));
		std::cout << "A length: " << length << std::endl;
		return length;
	};
	double GetTopBoltLength() {
		//等效圆半径
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
		std::cout << "底数：" << tmp1 << std::endl;
		double point_number = (1 - sin_fai) / (2 * sin_fai);
		
		std::cout << "指数：" << point_number << std::endl;
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
		std::cout << "底数：" << tmp1 << std::endl;
		double point_number = (1 - sin_fai) / (2 * sin_fai);

		std::cout << "指数：" << point_number << std::endl;
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
	double mBoltLength; // 锚杆长度
	double mBoltSpace; //锚杆间距
	double mBoltShuLength; //锚杆树脂药卷长度
	double mCableLength; //锚索长度
	double mCableSpace; //锚索间距
	double mCableShuLength; //锚索树脂药卷长度
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

	// 获取顶部锚杆的根数
	int GetTopBoltNumber() {
		return pBoltNumber;
	};
	// 获取顶部锚杆的长度
	double GetTopBoltLength() {
		return mBoltLength;
	};

};

class CLooseRangeMethod : public CMethod {
private:
	int mMeasureWay;
	double mLooseRange;
	double mStoneStrongNumber; //岩石坚固系数
public:
	CLooseRangeMethod() {};
	~CLooseRangeMethod() {};
	void SetMeasureWay(int way) { mMeasureWay = way; };
	int GetMeasureWay() const { return mMeasureWay; };
	void SetLooseRange(double t) { mLooseRange = t; };
	double GetLooseRange() const { return mLooseRange; };
	void SetStoneStrongNumber(double t) { mStoneStrongNumber = t; };
	double GetStoneStrongNumber() const { return mStoneStrongNumber; };

	// 获取顶部锚杆的根数
	int GetTopBoltNumber() {
		return pBoltNumber;
	};
	// 获取顶部锚杆的长度
	double GetTopBoltLength() {
		return mLooseRange + 0.4;
	};

};

class CBalanceMethod : public CMethod {
private:
	
	double mAvgGravity; //底层平均重力密度
	double mMaiDepth; 
	double mCoalHardNumber_Fy;// 煤层硬度系数
	double mCoalThickness;// 煤层厚度
	double mCaiEffectNumber;
	double mInnerFriction;
	double mStableNumber; // 待锚岩层稳定性系数
	double mStoneHardNumber;//锚固岩层硬度
	double mCoalAngle; //煤岩倾角
	double mBoltOutLength; //锚杆外露长度
	double mBoltSpace;
	double mBoltYieldNumber; // 锚杆屈服强度
	double mBoltStablePower; // 锚固力
	double mBoltSafeNumber;
	double mTopAvgGravity;
	int mBoltNumber; // 锚杆数量
	double mCableOutLength;
	double mCableStoneHeight;
	double mCableALength;
	double mMinBreakLoader; //最低破坏荷载
	double mCableSafeNumber;
public:

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