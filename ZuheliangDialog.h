#pragma once


// CZuheliangDialog �Ի���

class CZuheliangDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CZuheliangDialog)

public:
	CZuheliangDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CZuheliangDialog();

	void UpdateUI();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ZUHELIANG_METHOD_DIALOG };
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
	double mBoltALength;
	double mBoltDiameter;
	double mBoltOutLength;
	double mBoltSafeNumber;
	double mCeyaliNumber;
	double mCoalFriction;
	double mKangjian;
	double mKangla;
	double mKuadu;
	double mStableNumber;
	double mStoneHardNumber;
	double mTopGravity;
	double mTopSafeNumber;
	double mTopThickness;
	double mZhejianNumber;

	double mConcreteThickness;
	double mQiThickness;
	bool pmLeagal = false;

	void CheckThickness();
	void SetExpertValue();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonPredialog();
};
