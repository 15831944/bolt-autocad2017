#pragma once


// CThicknessDialog �Ի���

class CThicknessDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CThicknessDialog)

public:
	CThicknessDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CThicknessDialog();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_THICKNESS_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	double mConThickness;
	double mQiThickness;
	bool isPmLeagal = false;

	void SaveParams();
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonPredialog();
	virtual BOOL OnInitDialog();

};
