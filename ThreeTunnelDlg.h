#pragma once
#include <vector>

// CThreeTunnelDlg 对话框

class CThreeTunnelDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CThreeTunnelDlg)

public:
	CThreeTunnelDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CThreeTunnelDlg();
	int GetZhihuWayBtn();
	void UpdateUI();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_THREE_TUNNEL_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	CButton mRecTunnelOption;
	CButton mArcTunnelOption;
	CButton mTrapTunnelOption;
	CEdit mEdtRecWidth;
	CEdit mEdtRecHeight;
	CEdit mEdtArcWidth;
	CEdit mEdtArcWallHeight;
	CEdit mEdtArcHeight;
	CButton mRadioNormalToArc;
	CButton mRadioNormalToGround;
	CEdit mEdtTrapTopWidth;
	CEdit mEdtTrapBottomWidth;
	CEdit mEdtTrapHeight;
	CEdit mEdtTrapLeftAngle;
	CEdit mEdtTrapRightAngle;
//	CEdit mEdtBoltTopAngle;
	CEdit mEdtBoltLeftAngle;
	CEdit mEdtBoltRightAngle;
	CButton mCheckBoltAngle;
	CStatic mTunnelChooseTitle;
	CButton mRadioDefaultWay;
	CButton mRadioBoltConcreteWay;
	CButton mRadioJetConcreteWay;
	CButton mRadioConcreteQiWay;

	double mLeftAngle;
	double mRightAngle;

	std::vector<CEdit*> mRectEdtArray;
	std::vector<CEdit*> mArcEdtArray;
	std::vector<CButton*> mArcButtonArray;
	std::vector<CEdit*> mTrapEdtArray;
	std::vector<CEdit*> mAngleEdtArray;

	void InitButtonEdtArray();
	void setOptionDisabled();

	void SetZhihuWay(int flag);

public:
	afx_msg void OnBnClickedCheckBoltAngle();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadioRectangle();
	afx_msg void OnBnClickedRadioArc();
	afx_msg void OnBnClickedRadioTrapzoid();
	afx_msg void OnBnClickedChooseCancel();
	afx_msg void OnBnClickedChooseOk();
	void SuccessToMethodChooseDlg();
	void TunnelSavepm();
	void OnBnClickedButtonProjectDialog();
};
