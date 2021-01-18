// ThicknessDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCad.h"
#include "ThicknessDialog.h"
#include "afxdialogex.h"
#include "ProjectBuilder.h"
#include "FileUtil.h"
#include "CADService.h"
#include "DialogManager.h"


// CThicknessDialog 对话框

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


// CThicknessDialog 消息处理程序

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

// 绘图按钮点击事件
void CThicknessDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	
	UpdateData(TRUE);
	if (mConThickness <= 0 || mQiThickness <= 0) {
		MessageBox(_T("参数必须大于0"), _T("警告"), MB_ICONWARNING);
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
			::CreateDirectory(dir, NULL);//创建目录,已有的话不影响
		}
		if (CFileUtil::AddFile(CFileUtil::GetAppRegeditPath() + _T("ini\\bridge.ini")) == TRUE) {
			if (CArcProjectBuilder::GetInstance()->SaveBridgeFile() == true) {
				//MessageBox(_T("桥接文件保存成功！"));
				CArcProjectBuilder::GetInstance()->SetFileUrl(_T(""));
				CArcProjectBuilder::GetInstance()->SetSavedToFile(FALSE);
			}
			else {
				MessageBox(_T("桥接文件保存失败！"), _T("错误"));
			}
			CADService::WriteAcadRx();
			CADService::LaunchACad();

			MessageBox(_T("绘制成功，AutoCad已启动！"), _T("绘图成功"));
		}
	}
}


void CThicknessDialog::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	SaveParams();
	ShowWindow(SW_HIDE);
}


void CThicknessDialog::OnBnClickedButtonPredialog()
{
	// TODO: 在此添加控件通知处理程序代码
	SaveParams();
	ShowWindow(SW_HIDE);
	DialogManager::GetInstance().ShowTunnelChooseDlg();
}


BOOL CThicknessDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect dlg;
	GetWindowRect(dlg);
	ScreenToClient(dlg);
	SetWindowPos(0, (GetSystemMetrics(SM_CXSCREEN) / 2) - (dlg.Width() / 2),
		(GetSystemMetrics(SM_CYSCREEN) / 2) - (dlg.Height() / 2), dlg.Width(), dlg.Height(),
		SW_SHOW);

	HICON hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_FOLDER));
	SetIcon(hIcon, FALSE);

	// 设置 ArcTunnel 的值
	mConThickness = CArcProjectBuilder::GetInstance()->GetArcTunnel()->GetConcreteThickness();
	mQiThickness = CArcProjectBuilder::GetInstance()->GetArcTunnel()->GetQiThickness();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
