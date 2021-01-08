#pragma once
#include "CTunnel.h"
#include "MFCUtil.h"
#include <vector>
#include "afxwin.h"


// CParametersDialog �Ի���

class CParametersDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CParametersDialog)

public:
	CParametersDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CParametersDialog();
	void UpdateUI();
	void SetThikcnessEdit();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PARAMETERS_DIALOG };
#endif
private:

	bool pmLeagal = false;

	CButton mCheckTopBolt;
	CButton mCheckLeftBolt;
	CButton mCheckRightBolt;
	CButton mCheckCable;

	/* ����ê�� */
	CEdit mEdtTopBoltDiameter;
	CEdit mEdtTopBoltLength;
	CEdit mEdtTopBoltMaterial;
	CEdit mEdtTopBoltTailing;
	CEdit mEdtTopBoltNumber;
	CEdit mEdtTopBoltSpace;
	CEdit mEdtTopBoltPitch;
	CEdit mEdtTopBoltALength;
	CEdit mEdtTopBoltBeamWidth;
	CEdit mEdtTopBoltBeamMaterial;
	CEdit mEdtTopBoltPortraitBeamMaterial;
	CEdit mEdtTopBoltPortraitBeamWidth;
	CEdit mEdtTopBoltTrayLength;
	CEdit mEdtTopBoltTrayMaterial;
	/*���ê��*/
	CEdit mEdtLeftBoltDiameter;
	CEdit mEdtLeftBoltLength;
	CEdit mEdtLeftBoltMaterial;
	CEdit mEdtLeftBoltTailing;
	CEdit mEdtLeftBoltNumber;
	CEdit mEdtLeftBoltSpace;
	CEdit mEdtLeftBoltPitch;
	CEdit mEdtLeftBoltALength;
	CEdit mEdtLeftBoltBeamWidth;
	CEdit mEdtLeftBoltBeamMaterial;
	CEdit mEdtLeftBoltPortraitBeamMaterial;
	CEdit mEdtLeftBoltPortraitBeamWidth;
	CEdit mEdtLeftBoltTrayLength;
	CEdit mEdtLeftBoltTrayMaterial;

	/*�Ұ�ê��*/
	CEdit mEdtRightBoltDiameter;
	CEdit mEdtRightBoltLength;
	CEdit mEdtRightBoltMaterial;
	CEdit mEdtRightBoltTailing;
	CEdit mEdtRightBoltNumber;
	CEdit mEdtRightBoltSpace;
	CEdit mEdtRightBoltPitch;
	CEdit mEdtRightBoltALength;
	CEdit mEdtRightBoltBeamWidth;
	CEdit mEdtRightBoltBeamMaterial;
	CEdit mEdtRightBoltPortraitBeamMaterial;
	CEdit mEdtRightBoltPortraitBeamWidth;
	CEdit mEdtRightBoltTrayLength;
	CEdit mEdtRightBoltTrayMaterial;

	/*ê��*/
	CEdit mEdtCableDiameter;
	CEdit mEdtCableLength;
	CEdit mEdtCableMaterial;
	CEdit mEdtCableTailing;
	CEdit mEdtCableNumber;
	CEdit mEdtCableSpace;
	CEdit mEdtCablePitch;
	CEdit mEdtCableALength;
	CEdit mEdtCableTrayLength;
	CEdit mEdtCableTrayMaterial;
	CEdit mEdtCableShuDiameter;
	CEdit mEdtCableShuLength;
	CEdit mEdtCableShuMaterial;

	std::vector<CEdit * > mVectorEdtTopBolt;
	std::vector<CEdit * > mVectorEdtLeftBolt;
	std::vector<CEdit *> mVectorEdtRightBolt;
	std::vector<CEdit *> mVectorCable;
	void InitEdtVector();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	virtual BOOL OnInitDialog();
	void OnBnClickedCheckLeftBolt();
	void OnBnClickedCheckRightBolt();
	void OnBnClickedCheckCable();
	CBolt * InitBoltInfo(int flag);
	CCable * InitCableInfo();
	void OnBnClickedCheckTopBolt();
	afx_msg void OnBnClickedOk();
	void SetMfcBoltCableFormIni();
	int CheckBoltOrCableLeagal();
	afx_msg void OnBnClickedButtonSavePm();
	virtual void OnOK();
	afx_msg void OnBnClickedButtonBackMethodChoose();
private:
	double mTopBoltLength;
	double mTopBoltNumber;
	double mTopBoltPitch;
	double mTopBoltALength;
public:
	afx_msg void OnMoving(UINT fwSide, LPRECT pRect);
private:
	CEdit mEdtConcreteThickness;
	CEdit mEdtQiThickness;
	double mTopBoltSpace;
	int mLeftBoltNumber;
	double mLeftBoltSpace;
	int mRightBoltNumber;
	double mRightBoltSpace;
	int mCableNumber;
	double mCableSpace;
};
