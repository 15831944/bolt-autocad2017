// ThicknessDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCad.h"
#include "ThicknessDialog.h"
#include "afxdialogex.h"
#include "ProjectBuilder.h"
#include "FileUtil.h"
#include "CADService.h"
#include "DialogManager.h"


// CThicknessDialog �Ի���

IMPLEMENT_DYNAMIC(CThicknessDialog, CDialogEx)

CThicknessDialog::CThicknessDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_THICKNESS_DIALOG, pParent)
	, mConThickness(0)
	, mQiThickness(0)
{

}

CThicknessDialog::~CThicknessDialog()
{
}

void CThicknessDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CONCRETE_THICKNESS, mConThickness);
	DDX_Text(pDX, IDC_EDIT_QI_THICKNESS, mQiThickness);
}


BEGIN_MESSAGE_MAP(CThicknessDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CThicknessDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CThicknessDialog::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_PREDIALOG, &CThicknessDialog::OnBnClickedButtonPredialog)
END_MESSAGE_MAP()


// CThicknessDialog ��Ϣ�������

void CThicknessDialog::SaveParams()
{
	CArcTunnel * pArc = CArcProjectBuilder::GetInstance()->GetArcTunnel();

	pArc->SetConcreteThickness(mConThickness);
	pArc->SetQiThickness(mQiThickness);
	pArc->SetHasTopBolt(false);
	pArc->SetHasLeftBolt(false);
	pArc->SetHasRightBolt(false);
	pArc->SetHasCable(false);
}

// ��ͼ��ť����¼�
void CThicknessDialog::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	UpdateData(TRUE);
	if (mConThickness <= 0 || mQiThickness <= 0) {
		MessageBox(_T("�����������0"), _T("����"), MB_ICONWARNING);
		isPmLeagal = false;
	}
	else {
		isPmLeagal = true;
	}
	
	if (isPmLeagal == true) {
		SaveParams();
		CArcProjectBuilder::GetInstance()->SetFileUrl(CFileUtil::GetAppRegeditPath() + _T("ini\\bridge.ini"));
		CString dir = CFileUtil::GetAppRegeditPath() + _T("ini");
		if (!PathIsDirectory(dir))
		{
			::CreateDirectory(dir, NULL);//����Ŀ¼,���еĻ���Ӱ��
		}
		if (CFileUtil::AddFile(CFileUtil::GetAppRegeditPath() + _T("ini\\bridge.ini")) == TRUE) {
			if (CArcProjectBuilder::GetInstance()->SaveBridgeFile() == true) {
				//MessageBox(_T("�Ž��ļ�����ɹ���"));
				CArcProjectBuilder::GetInstance()->SetFileUrl(_T(""));
				CArcProjectBuilder::GetInstance()->SetSavedToFile(FALSE);
			}
			else {
				MessageBox(_T("�Ž��ļ�����ʧ�ܣ�"), _T("����"));
			}
			CADService::WriteAcadRx();
			CADService::LaunchACad();

			MessageBox(_T("���Ƴɹ���AutoCad��������"), _T("��ͼ�ɹ�"));
		}
	}
}


void CThicknessDialog::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SaveParams();
	ShowWindow(SW_HIDE);
}


void CThicknessDialog::OnBnClickedButtonPredialog()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SaveParams();
	ShowWindow(SW_HIDE);
	DialogManager::GetInstance().ShowTunnelChooseDlg();
}


BOOL CThicknessDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect dlg;
	GetWindowRect(dlg);
	ScreenToClient(dlg);
	SetWindowPos(0, (GetSystemMetrics(SM_CXSCREEN) / 2) - (dlg.Width() / 2),
		(GetSystemMetrics(SM_CYSCREEN) / 2) - (dlg.Height() / 2), dlg.Width(), dlg.Height(),
		SW_SHOW);

	HICON hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_FOLDER));
	SetIcon(hIcon, FALSE);

	// ���� ArcTunnel ��ֵ
	mConThickness = CArcProjectBuilder::GetInstance()->GetArcTunnel()->GetConcreteThickness();
	mQiThickness = CArcProjectBuilder::GetInstance()->GetArcTunnel()->GetQiThickness();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
