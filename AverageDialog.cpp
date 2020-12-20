// AverageDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCad.h"
#include "AverageDialog.h"
#include "afxdialogex.h"
#include "ProjectBuilder.h"
#include <vector>
//#include "TheoreticalDialog.h"


// CAverageDialog �Ի���

IMPLEMENT_DYNAMIC(CAverageDialog, CDialogEx)

CAverageDialog::CAverageDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_AVERAGE_DIALOG, pParent)
	, mTopCompressive(0)
	, mTunnelCompressive(0)
	, mBottomCompressive(0)
	, mTopAttach(0)
	, mTunnelAttach(0)
	, mBottomAttach(0)
	, mTopFriction(0)
	, mTunnelFriction(0)
	, mBottomFriction(0)
{

}

CAverageDialog::~CAverageDialog()
{
}

void CAverageDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TOP_COMPRESSIVE, mTopCompressive);
	DDX_Text(pDX, IDC_EDIT_TUNNEL_COMPRESSIVE, mTunnelCompressive);
	DDX_Text(pDX, IDC_EDIT_BOTTOM_BAN_COMPRESSIVE, mBottomCompressive);
	DDX_Text(pDX, IDC_EDIT_TOP_ATTACH, mTopAttach);
	DDX_Text(pDX, IDC_EDIT_TUNNEL_ATTACH, mTunnelAttach);
	DDX_Text(pDX, IDC_EDIT_BOTTOM_ATTACH, mBottomAttach);
	DDX_Text(pDX, IDC_EDIT_TOP_FRICTION, mTopFriction);
	DDX_Text(pDX, IDC_EDIT_TUNNEL_FRICTION, mTunnelFriction);
	DDX_Text(pDX, IDC_EDIT_BOTTOM_FRICTION, mBottomFriction);
}


BEGIN_MESSAGE_MAP(CAverageDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAverageDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CAverageDialog ��Ϣ�������
static UINT WM_MSG_UPDATE_AVERAGE = RegisterWindowMessage(_T("update average"));

void CAverageDialog::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	std::vector<double> vecCompressive =
	{ mTopCompressive, mTunnelCompressive, mBottomCompressive };
	std::vector<double> vecAttach =
	{ mTopAttach, mTunnelAttach, mBottomAttach };
	std::vector<double> vecFriction =
	{ mTopFriction, mTunnelFriction, mBottomFriction };

	CArcProjectBuilder::GetInstance()->GetTheoryMethod()->SetVecCompressive(vecCompressive);
	CArcProjectBuilder::GetInstance()->GetTheoryMethod()->SetVecNianPower(vecAttach);
	CArcProjectBuilder::GetInstance()->GetTheoryMethod()->SetVecFriction(vecFriction);

	WPARAM a = (WPARAM)this;//�Ӵ���ı����ʵ��ָ��
	GetParent()->SendMessage(WM_MSG_UPDATE_AVERAGE, a);

	CDialogEx::OnOK();
}
