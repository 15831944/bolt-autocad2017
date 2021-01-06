#pragma once
#include <vector>


class CTheoreticalDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CTheoreticalDialog)

public:
	CTheoreticalDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTheoreticalDialog();
	void UpdateUI();
	void CheckThickness();
	afx_msg void OnBnClickedButtonAverage();
	afx_msg void OnBnClickedButtonBackMethodChooseDialog();
	afx_msg void OnBnClickedOk();
	afx_msg LRESULT OnMsgReceive(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnInitDialog();

	afx_msg void OnMoving(UINT fwSide, LPRECT pRect);
	afx_msg void OnBnClickedButtonTheorySavepm();


// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_THEORETICAL_CALCULATION_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	
private:

	// 参数是否合法
	bool pmLeagal = false;

	// 煤岩平均重度
	double mAvgGrivity;
	// 巷道埋深
	double mDepth;
	// 岩石坚固系数
	double mStoneStrongNumber = 1.7;
	// 树脂药卷长度
	double mShuLength;
	double mBoltDiameter;
	double mBoltDesignNumber;
	double mBoltAttach;
	double mBoltPitch;
	int mBoltNumber;
	double mBoltExperienceNumber=1.37 ;
	double mBoltCaiNumber = 1.5;
	double mCableDiameter;
	double mCableBreakPower;
	double mCableAttach;
	double mCablePitch;
	int mCableNumber;
	double mCableFreeLength;
	double mCableCaiNumber = 2.0;
	double mConcreteThickness;
	double mQiThickness;
	double mAttach;
	double mCompressive;
	// 内摩擦角
	double mInnerFirction;

};
