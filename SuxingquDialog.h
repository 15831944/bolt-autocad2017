#pragma once
#include "afxwin.h"


// CSuxingquDialog �Ի���

class CSuxingquDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CSuxingquDialog)

public:
	CSuxingquDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSuxingquDialog();
	void UpdateUI();
	void SetThicknessEdit();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SUXINGQU_METHOD_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:

	double mInnerFriction;
	double mAvgGravity;
	double mMaiDepth;
	double mMeiyanZhongdu;
	double mNianPower;
	double mShuLength;
	double mBoltAttach;
	double mBoltDesignNumber;
	double mBoltDiameter;
	double mCableDiameter;
	double mCableFreeLength;
	double mCableAttach;
	double mCableBreakPower;

	double mConcreteThickness;
	double mQiThickness;
	bool pmLeagal = false;

	void CheckThickness();
	void SetExpertValue();
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonTunnelDialog();
	virtual BOOL OnInitDialog();
private:
	CButton CEdtConThickcness;
	CEdit CEdtQiThickcness;
};
