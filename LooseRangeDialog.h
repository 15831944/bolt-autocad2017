#pragma once
#include "afxwin.h"
#include <vector>

// CLooseRangeDialog 对话框

class CLooseRangeDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CLooseRangeDialog)

public:
	CLooseRangeDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLooseRangeDialog();
	void UpdateUI();
	void SetThicknessEdit();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOOSE_RANGE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonTunnelDialog();
private:
	double mLooseRange;
	CEdit mEdtLooseRange;
	double mPushiNumber;
	CEdit mEdtPushiNumber;
	CEdit mEdtAvgGrivity;
	CEdit mEdtDepth;
	CEdit mEdtFriction;
	CEdit mMeiyanZhongdu;
	CEdit mEdtNianPower;
	CEdit mEdtShuLength;
	CEdit mEdtBoltDiameter;
	CEdit mEdtBoltDesignNumber;
	CEdit mEdtBoltAttach;
	CEdit mCalbeFreeLength;
	CEdit mEdtCableDiameter;
	CEdit mCableBreakPower;
	CEdit mEdtCableAttach;

	CEdit mEdtConThickness;
	CEdit mEdtQiThickness;
	double mConThickness;
	double mQiThickness;
	CButton mRadioMaoluo;
	CButton mRadioLooseRange;

	bool pmLeagal = false;
	std::vector<CEdit * > mVectorEdt;
	void InitEdtVector();
	void CheckThickness();
	void SetExpertValue();

	int GetMeasureWay();
	void SetMeasureButton(int type);
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadioMaoluoMeasure();
	afx_msg void OnBnClickedRadioLooseMeasure();
	afx_msg void OnMoving(UINT fwSide, LPRECT pRect);

};
