// TunnelFeature.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCad.h"
#include "TunnelFeature.h"
#include "afxdialogex.h"


// CTunnelFeature �Ի���

IMPLEMENT_DYNAMIC(CTunnelFeature, CDialogEx)

CTunnelFeature::CTunnelFeature(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_TUNNEL_FEATURE, pParent)
{

}

CTunnelFeature::~CTunnelFeature()
{
}

void CTunnelFeature::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTunnelFeature, CDialogEx)
END_MESSAGE_MAP()


// CTunnelFeature ��Ϣ�������
