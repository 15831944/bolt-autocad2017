#pragma once
class CTunnelProject
{
private:
	// 绘图信息
	CString mPaperTitle;
	CString mPaperDescription;
	CString mScaleNumber;
	CString mPaperNumber;
	CString mPaperSize;

	// 设计信息
	CString mDesigner;
	CString mDate;
	CString mChecker;
	CString mCheckDate;
	CString mDesignApart;
	CString mDevelopApart;

	// 巷道类型设定为工程中的一个属性，便于在 ProjectBuilder 中通过 mTunnelProject 变量进行判断
	// 默认为拱形巷道，所以初始化为 2
	// 矩形巷道：1，拱形巷道：2，梯形巷道：3
	int mTunnelType = 0; 

public:
	CTunnelProject();
	CTunnelProject(CString title, CString Description, CString ScaleNumber, CString PaperNumber, CString PaperSize, CString Designer, CString Date, CString Checker, CString CheckDate, CString DesignApart, CString DevelopApart );
	~CTunnelProject();
	void SetPaperTitle(CString t) { mPaperTitle = t; };
	CString GetPaperTitle() const { return mPaperTitle; };
	void SetPaperDescription(CString t) { mPaperDescription = t; };
	CString GetPaperDescription() const { return mPaperDescription; };
	void SetPaperNumber(CString t) { mPaperNumber = t; };
	CString GetPaperNumber() const { return mPaperNumber; };
	void SetScaleNumber(CString t) { mScaleNumber = t; };
	CString GetScaleNumber() const { return mScaleNumber; };
	void SetPaperSize(CString t) { mPaperSize = t; };
	CString GetPaperSize() const { return mPaperSize; };

	void SetDesigner(CString t) { mDesigner = t; };
	CString GetDesigner() const { return mDesigner; };
	void SetDate(CString t) { mDate = t; };
	CString GetDate() const { return mDate; };
	void SetChecker(CString t) { mChecker = t; };
	CString GetChecker() const { return mChecker; };
	void SetCheckDate(CString t) { mCheckDate = t; };
	CString GetCheckDate() const { return mCheckDate; };
	void SetDesignApart(CString t) { mDesignApart = t; };
	CString GetDesignApart() const { return mDesignApart; };
	void SetDevelopApart(CString t) { mDevelopApart = t; };
	CString GetDevelopApart() const { return mDevelopApart; };

	void SetTunnelType(int type) { mTunnelType = type; };
	int GetTunnelType() const { return mTunnelType; };
};

