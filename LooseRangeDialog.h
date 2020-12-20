#pragma once
#include "afxwin.h"


// CLooseRangeDialog �Ի���

class CLooseRangeDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CLooseRangeDialog)

public:
	CLooseRangeDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLooseRangeDialog();
	void UpdateUI();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOOSE_RANGE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonTunnelDialog();
private:
	double mLooseRange;
	CEdit mEdtLooseRange;
	CEdit mEdtStoneStrongNumber;
	CEdit mEdtAvgGrivity;
	CEdit mEdtCompressive;
	CEdit mEdtDepth;
	CEdit mEdtFriction;
	CEdit mEdtAttach;
	CEdit mEdtShuLength;
	CEdit mEdtBoltSpace;
	CEdit mEdtBoltPitch;
	CEdit mEdtBoltDiameter;
	CEdit mEdtBoltDesignNumber;
	CEdit mEdtBoltAttach;
	CEdit mCalbeFreeLength;
	CEdit mCableSpace;
	CEdit mEdtCablePitch;
	CEdit mEdtCableDiameter;
	CEdit mCableBreakPower;
	CEdit mEdtCableAttach;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadioMaoluoMeasure();
private:
	CButton mRadioLooseRange;
public:
	afx_msg void OnBnClickedRadioLooseMeasure();
	afx_msg void OnMoving(UINT fwSide, LPRECT pRect);
};
