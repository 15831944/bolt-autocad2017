#pragma once
#include "afxwin.h"
#include <vector>
#include "MFCUtil.h"
#include "MethodChooseDialog.h"


// CTunnelChooseDialog 对话框

class CTunnelChooseDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CTunnelChooseDialog)

public:
	CTunnelChooseDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTunnelChooseDialog();
	void OnBnClickedRadioRectangle();

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadioArc();
	afx_msg void OnBnClickedRadioTrapzoid();
	afx_msg void OnBnClickedCheckBoltAngle();
	afx_msg void OnBnClickedChooseOk();

	afx_msg void OnBnClickedButtonProjectDialog();
	virtual void OnCancel();
	afx_msg void OnBnClickedChooseCancel();
	afx_msg void OnMoving(UINT fwSide, LPRECT pRect);
	afx_msg void OnBnClickedButtonTunnelSavepm();


// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TUNNEL_CHOOSE_DIALOG };
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
	CEdit mEdtBoltTopAngle;
	CEdit mEdtBoltLeftAngle;
	CEdit mEdtBoltRightAngle;
	CButton mCheckBoltAngle;
	CStatic mTunnelChooseTitle;
	CButton mRadioDefaultWay;
	CButton mRadioBoltConcreteWay;
	CButton mRadioJetConcreteWay;
	CButton mRadioConcreteQiWay;

	std::vector<CEdit*> mRectEdtArray;
	std::vector<CEdit*> mArcEdtArray;
	std::vector<CButton*> mArcButtonArray;
	std::vector<CEdit*> mTrapEdtArray;
	std::vector<CEdit*> mAngleEdtArray;

	double mTopAngle;
	double mLeftAngle;
	double mRightAngle;

	void SetZhihuWay(int flag);
	int GetZhihuWayBtn();
	//void InitButtonEdtArray();
	void SuccessToMethodChooseDlg();

};
