#pragma once

// CAverageDialog �Ի���

class CAverageDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CAverageDialog)

public:
	CAverageDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAverageDialog();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AVERAGE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	double mTopCompressive;
	double mTunnelCompressive;
	double mBottomCompressive;
	double mTopAttach;
	double mTunnelAttach;
	double mBottomAttach;
	double mTopFriction;
	double mTunnelFriction;
	double mBottomFriction;
public:
	afx_msg void OnBnClickedOk();
};
