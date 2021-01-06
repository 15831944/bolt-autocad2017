#pragma once


// CTunnelFeature 对话框

class CTunnelFeature : public CDialogEx
{
	DECLARE_DYNAMIC(CTunnelFeature)

public:
	CTunnelFeature(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTunnelFeature();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TUNNELF_FEATURE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
