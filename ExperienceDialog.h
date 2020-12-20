#pragma once
#include <vector>
// CExperienceDialog 对话框

class CExperienceDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CExperienceDialog)

public:
	CExperienceDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CExperienceDialog();
	void UpdateUI();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROGRAM_EXPERIENCE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonBackMethodChooseDialog();
	afx_msg void OnBnClickedOk();
private:

	bool pmLeagal = false;

	double mBoltLength;
	double mBoltSpace;
	double mBoltPitch;
	double mBoltDiameter;
	double mBoltDeisgnNumber;
	double mBoltAttach;
	double mBoltShuLegnth;
	double mCableLength;
	double mCableDiameter;
	double mCableSpace;
	double mCablePitch;
	int mCableNumber;
	double mCableAttach;
	double mCableShuLength;

	std::vector<double> mVecValue = {
		mBoltLength, mBoltShuLegnth, mBoltSpace, mBoltPitch,
		mBoltDiameter, mBoltDeisgnNumber, mBoltAttach, mCableLength,
		mCableDiameter, mCableSpace, mCablePitch, mCableAttach,
		mCableShuLength
	};


public:
	virtual BOOL OnInitDialog();
	afx_msg void OnMoving(UINT fwSide, LPRECT pRect);
private:
	int mConcreteThickness;
	int mQiThickness;
public:
	afx_msg void OnBnClickedButtonExpSavepm();
};