#pragma once
#include <vector>


// CBalanceMethodDialog �Ի���

class CBalanceMethodDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CBalanceMethodDialog)

public:
	CBalanceMethodDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBalanceMethodDialog();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonPredialog();
	afx_msg void OnBnClickedCancel();


// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BALANCE_METHOD_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()


private:
	double mGroundAvgGravity;
	double mMaiDepth;
	double mCoalHardNumber;
	double mCoalThickness;
	double mCaiEffectNumber;
	double mInnerFriction;
	double mCableSafeNumber;
	int mBoltNumber;
	double mBoltOutLength;
	double mBoltPower;
	double mBoltSafeNumber;
	double mBoltSpace;
	double mBoltYieldNumber;
	double mCableAlength;
	double mCableOutLength;
	double mCoalFriction;
	double mMinBreakPower;
	double mCableStoneHeight;
	double mStoneToughNumber;
	double mStableNumber;
	double mTopAvgGravity;
	double mConcreteThickness;
	double mQiThickness;
	bool pmLeagal = false;

};
