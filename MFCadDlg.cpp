
// MFCadDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCad.h"
#include "MFCadDlg.h"
#include "afxdialogex.h"
#include "FileUtil.h"
#include "ProjectBuilder.h"
#include <io.h>  
#include <fcntl.h>
#include "SkipDialog.h"
#include "ParametersDialog.h"
#include "DialogManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

CProjectDialog* pDlg = NULL;
const CString SUCCESS_CAPTION("成功");
const CString ERROR_CAPTION("错误");
const CString WARNING_CAPTION("警告");

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}



void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCadDlg 对话框



CMFCadDlg::CMFCadDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCAD_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON_FOLDER);
}

void CMFCadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCadDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(IDM_NEW_PROJECT, &CMFCadDlg::OnNewProject)
	ON_COMMAND(IDM_ABOUT_APPLICATION, &CMFCadDlg::OnAboutApplication)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_FILE, &CMFCadDlg::OnBnClickedButtonSaveFile)
	ON_COMMAND(IDM_OPEN_PROJECT, &CMFCadDlg::OnOpenProject)
	ON_COMMAND(IDM_SAVE_PROJECT, &CMFCadDlg::OnSaveProject)
	ON_BN_CLICKED(IDC_BUTTON_FIND_ACAD_PATH, &CMFCadDlg::OnBnClickedButtonFindAcadPath)
	ON_COMMAND(IDM_PROJECT_INFORMATION, &CMFCadDlg::OnProjectInformation)
	ON_COMMAND(ID_MENU_EXIT, &CMFCadDlg::OnMenuExit)
	ON_WM_CTLCOLOR()
	ON_WM_MOVE()
	ON_COMMAND(ID_SaveTo, &CMFCadDlg::OnSaveto)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMFCadDlg 消息处理程序

BOOL CMFCadDlg::OnInitDialog()
{


	//CSkipDialog *dlgSkip = new CSkipDialog();
	//dlgSkip->DoModal();


	CDialogEx::OnInitDialog();
	// 将“关于...”菜单项添加到系统菜单中。




	// 启动时令窗口最大化 
	this->ShowWindow(SW_MAXIMIZE);

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	CMenu menu;
	menu.LoadMenu(IDR_MAIN_MENU);
	SetMenu(&menu);

	std::cout << "set menu\n";
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCadDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCadDlg::OnPaint()
{
	CPaintDC   dc(this);
	CRect   rect;
	GetClientRect(&rect);    //获取对话框长宽      
	CDC   dcBmp;             //定义并创建一个内存设备环境
	dcBmp.CreateCompatibleDC(&dc);             //创建兼容性DC
	CBitmap   bmpBackground;
	bmpBackground.LoadBitmap(IDB_BITMAP_LIMPID_BG);    //载入资源中图片
	BITMAP   m_bitmap;                         //图片变量               
	bmpBackground.GetBitmap(&m_bitmap);       //将图片载入位图中
											  //将位图选入临时内存设备环境
	CBitmap  *pbmpOld = dcBmp.SelectObject(&bmpBackground);
	//调用函数显示图片StretchBlt显示形状可变
	dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcBmp, 0, 0, m_bitmap.bmWidth, m_bitmap.bmHeight, SRCCOPY);
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCadDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCadDlg::OnNewProject()
{
	//CArcProjectBuilder();
	std::cout << "is save to file? :" << CArcProjectBuilder::GetInstance()->GetSavedToFile() << std::endl;
	// TODO: 在此添加命令处理程序代码

	
	if (CArcProjectBuilder::GetInstance()->GetSavedToFile() == TRUE
		&& (!CArcProjectBuilder::GetInstance()->GetFileUrl().IsEmpty()))
	{ 
		// 打开的工程已经保存了
		CArcProjectBuilder::GetInstance()->SetFileUrl(_T(""));
		CArcProjectBuilder::GetInstance()->SetSavedToFile(FALSE);
		CArcProjectBuilder::GetInstance()->SetTunnelProject(new CTunnelProject());
		CArcProjectBuilder::GetInstance()->SetArcTunnel(new CArcTunnel());
		
		DialogManager::GetInstance().ShowProjectDialog();
		CArcProjectBuilder::GetInstance()->InitSaveToInstance();
	}
	else if (CArcProjectBuilder::GetInstance()->GetSavedToFile() == TRUE &&
		CArcProjectBuilder::GetInstance()->GetFileUrl().IsEmpty()) {
		// 当前窗口是新建窗口
		CArcProjectBuilder::GetInstance()->SetFileUrl(_T(""));
		CArcProjectBuilder::GetInstance()->SetSavedToFile(FALSE);
		CArcProjectBuilder::GetInstance()->SetTunnelProject(new CTunnelProject());
		CArcProjectBuilder::GetInstance()->SetArcTunnel(new CArcTunnel());

		DialogManager::GetInstance().ShowProjectDialog();
		CArcProjectBuilder::GetInstance()->InitSaveToInstance();

	}
	else if(CArcProjectBuilder::GetInstance()->GetSavedToFile() == FALSE)
	{

		DialogManager::GetInstance().ShowProjectDialog();
	}

}


void CMFCadDlg::OnAboutApplication()
{
	// TODO: 在此添加命令处理程序代码
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}


void CMFCadDlg::OnOK()
{
	CDialogEx::OnOK();
}



void CMFCadDlg::OnBnClickedButtonSaveFile()
{
	TCHAR szFilter[] = TEXT("参数文件(*.prj)|*.prj|所有文件(*.*)|*.*||");
	CFileDialog fileDlg(FALSE, TEXT("prj"), TEXT("my"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | MB_SYSTEMMODAL, szFilter, this);
	CString strFilePath;
	if (IDOK == fileDlg.DoModal())
	{
		strFilePath = fileDlg.GetPathName();
		SetDlgItemText(IDC_EDIT2, strFilePath);
	}
	CStdioFile myFile;
	CFileException fileException;

	if (myFile.Open(strFilePath, CFile::modeCreate | CFile::typeText | CFile::modeReadWrite | CFile::modeNoTruncate, &fileException))
	{
		myFile.SeekToBegin();
		CString str;

		myFile.ReadString(str);
		CString m_all = TEXT("hello world") + str;
		while (myFile.ReadString(str) != FALSE)
		{
			m_all += TEXT("\r\n") + str;
		}
		UpdateData(FALSE);
		//AfxMessageBox(m_all);
		myFile.Close();
		CArcProjectBuilder::GetInstance()->SetFileUrl(strFilePath);
	
		switch (CArcProjectBuilder::GetInstance()->ProjectSaver()) {
		case 0:
			MessageBox(_T("保存工程信息成功"), _T("成功"), MB_ICONHAND);
			CArcProjectBuilder::GetInstance()->SetSavedToFile(TRUE);
			break;
		case 5:
			MessageBox(_T("保存计算方法参数失败"), _T("失败"), MB_ICONERROR);
			break;
		case 4:
			MessageBox(_T("保存锚杆参数失败"), _T("失败"), MB_ICONERROR);
			break;
		case 3:
			MessageBox(_T("保存巷道参数失败"), _T("失败"), MB_ICONERROR);
			break;
		case 2:
			MessageBox(_T("保存flag参数失败"), _T("失败"), MB_ICONERROR);
			break;
		case 1:
			MessageBox(_T("保存工程信息失败"), _T("失败"), MB_ICONERROR);
			break;
		}
	}
	
}

void CMFCadDlg::ConcreteOpenProject() {

	TCHAR szFilter[] = TEXT("工程文件(*.prj)|*.prj|所有文件(*.*)|*.*||");
	CFileDialog fileDlg(TRUE, TEXT("prj"), NULL, 0, szFilter, this);
	CString strFilePath;
	if (IDOK == fileDlg.DoModal())
	{
		strFilePath = fileDlg.GetPathName();
	}
	if (!strFilePath.IsEmpty()) {

		CArcProjectBuilder::GetInstance()->SetFileUrl(strFilePath);

		CArcProjectBuilder::GetInstance()->BuildAll();

		//MessageBox(_T("文件打开成功！参数载入完毕"), 0, MB_SYSTEMMODAL);
		CArcProjectBuilder::GetInstance()->SetSavedToFile(FALSE);
		DialogManager::GetInstance().setHasCurrentFile(true);
		DialogManager::GetInstance().ShowProjectDialog();
	}
}

void CMFCadDlg::OnOpenProject()
{
	// TODO: 在此添加命令处理程序代码

	if (CArcProjectBuilder::GetInstance()->GetSavedToFile() == false) {
		if (IDYES == MessageBox(_T("当前工程尚未保存，是否直接打开？"), _T("打开"), MB_YESNO | MB_ICONQUESTION)) {
			ConcreteOpenProject();
		}
	}
	else {
		ConcreteOpenProject();
	}

}


void CMFCadDlg::OnSaveProject()
{
	// TODO: 在此添加命令处理程序代码
	if (CArcProjectBuilder::GetInstance()->GetFileUrl().IsEmpty()) {
		OnSaveto();
	}
	else {
		if ((CArcProjectBuilder::GetInstance()->SaveProjectToFile() == true)
			&& (CArcProjectBuilder::GetInstance()->SaveTunnelFlagToFile() == true)
			&& (CArcProjectBuilder::GetInstance()->SaveParametersToFile() == true)
			&& (CArcProjectBuilder::GetInstance()->SaveArcTunnelInfoToFile() == true)
			&& (CArcProjectBuilder::GetInstance()->SaveMethodToFile() == true)
			) {
			CArcProjectBuilder::GetInstance()->SetSavedToFile(TRUE);
			MessageBox(_T("保存工程信息成功"), _T("成功"), MB_OK);
		}
		else {
			CArcProjectBuilder::GetInstance()->SetSavedToFile(FALSE);
			MessageBox(_T("保存工程信息失败，参数可能不完善"), _T("失败"), MB_ICONERROR | MB_OK);
		}
	}
}


void CMFCadDlg::OnBnClickedButtonFindAcadPath()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(CFileUtil::GetAppRegeditPath());
}


void CMFCadDlg::OnProjectInformation()
{
	// TODO: 在此添加命令处理程序代码

	if (CArcProjectBuilder::GetInstance()->GetFileUrl().IsEmpty() &&
		(CArcProjectBuilder::GetInstance()->GetProjectSaveToInstance() == FALSE)
		) {
		MessageBox(_T("当前无工程打开"), _T("警告"), MB_ICONWARNING | MB_OK);
	}
	else {
		DialogManager::GetInstance().ShowProjectDialog();
	}
	
}


void CMFCadDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	// 新建文件
	
	if (CArcProjectBuilder::GetInstance()->GetSavedToFile() == FALSE) {
		if (CArcProjectBuilder::GetInstance()->GetFileUrl().IsEmpty()) {
			if (IDYES == MessageBox(_T("当前工程尚未保存，仍要退出吗？"), _T("退出"), MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2))
			{
				CDialogEx::OnCancel();
			}
		}
		else {
			// 打开文件后
			switch (MessageBox(_T("是否保存当前修改到文件？"), _T("退出"), MB_YESNOCANCEL | MB_ICONQUESTION ))
			{
			case IDYES:
				if ((CArcProjectBuilder::GetInstance()->SaveProjectToFile() == true)
					&& (CArcProjectBuilder::GetInstance()->SaveTunnelFlagToFile() == true)
					&& (CArcProjectBuilder::GetInstance()->SaveParametersToFile() == true)
					&& (CArcProjectBuilder::GetInstance()->SaveArcTunnelInfoToFile() == true)
					&& (CArcProjectBuilder::GetInstance()->SaveMethodToFile() == true)
					) {
					MessageBox(_T("保存工程信息成功"), _T("成功"), MB_OK);
					CDialogEx::OnCancel();
				}
				else {
					MessageBox(_T("保存工程信息失败"), _T("失败"), MB_ICONERROR | MB_OK);
				}
				break;
			case IDNO:
				CDialogEx::OnCancel();
				break;
			case IDCANCEL:
				break;
			default:
				break;
			}
		}
	}
	else
	{
		
		if (IDYES == MessageBox( _T("确定退出本软件吗？"), _T("退出") , MB_ICONQUESTION | MB_YESNO ))
		{
			CDialogEx::OnCancel();
		}
	}

}


void CMFCadDlg::OnMenuExit()
{
	// TODO: 在此添加命令处理程序代码
	OnCancel();
}



void CMFCadDlg::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);
	if (pDlg && ::IsWindow(pDlg->m_hWnd))
	{ CRect rect;        
	GetWindowRect(rect);        
	pDlg->SetWindowPos(NULL, rect.left, rect.top, 0,0, SWP_NOZORDER | SWP_NOSIZE);
	}
	
	// TODO: 在此处添加消息处理程序代码
}

// 另存为的点击事件
void CMFCadDlg::OnSaveto()
{
	// TODO: 在此添加命令处理程序代码
	OnBnClickedButtonSaveFile();
}


void CMFCadDlg::OnDestroy()
{

	CFileUtil::DeleteTheFile(CFileUtil::GetAppRegeditPath() + _T("acad.rx"));
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}