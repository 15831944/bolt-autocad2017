#pragma once


// CTunnelFeature �Ի���

class CTunnelFeature : public CDialogEx
{
	DECLARE_DYNAMIC(CTunnelFeature)

public:
	CTunnelFeature(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTunnelFeature();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TUNNELF_FEATURE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
