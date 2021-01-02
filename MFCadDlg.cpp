
// MFCadDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

CProjectDialog* pDlg = NULL;
const CString SUCCESS_CAPTION("�ɹ�");
const CString ERROR_CAPTION("����");
const CString WARNING_CAPTION("����");

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMFCadDlg �Ի���



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


// CMFCadDlg ��Ϣ�������

BOOL CMFCadDlg::OnInitDialog()
{


	//CSkipDialog *dlgSkip = new CSkipDialog();
	//dlgSkip->DoModal();


	CDialogEx::OnInitDialog();
	// ��������...���˵�����ӵ�ϵͳ�˵��С�




	// ����ʱ������ 
	this->ShowWindow(SW_MAXIMIZE);

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	CMenu menu;
	menu.LoadMenu(IDR_MAIN_MENU);
	SetMenu(&menu);

	std::cout << "set menu\n";
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCadDlg::OnPaint()
{
	CPaintDC   dc(this);
	CRect   rect;
	GetClientRect(&rect);    //��ȡ�Ի��򳤿�      
	CDC   dcBmp;             //���岢����һ���ڴ��豸����
	dcBmp.CreateCompatibleDC(&dc);             //����������DC
	CBitmap   bmpBackground;
	bmpBackground.LoadBitmap(IDB_BITMAP_LIMPID_BG);    //������Դ��ͼƬ
	BITMAP   m_bitmap;                         //ͼƬ����               
	bmpBackground.GetBitmap(&m_bitmap);       //��ͼƬ����λͼ��
											  //��λͼѡ����ʱ�ڴ��豸����
	CBitmap  *pbmpOld = dcBmp.SelectObject(&bmpBackground);
	//���ú�����ʾͼƬStretchBlt��ʾ��״�ɱ�
	dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcBmp, 0, 0, m_bitmap.bmWidth, m_bitmap.bmHeight, SRCCOPY);
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMFCadDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCadDlg::OnNewProject()
{
	//CArcProjectBuilder();
	std::cout << "is save to file? :" << CArcProjectBuilder::GetInstance()->GetSavedToFile() << std::endl;
	// TODO: �ڴ���������������

	
	if (CArcProjectBuilder::GetInstance()->GetSavedToFile() == TRUE
		&& (!CArcProjectBuilder::GetInstance()->GetFileUrl().IsEmpty()))
	{ 
		// �򿪵Ĺ����Ѿ�������
		CArcProjectBuilder::GetInstance()->SetFileUrl(_T(""));
		CArcProjectBuilder::GetInstance()->SetSavedToFile(FALSE);
		CArcProjectBuilder::GetInstance()->SetTunnelProject(new CTunnelProject());
		CArcProjectBuilder::GetInstance()->SetArcTunnel(new CArcTunnel());
		
		DialogManager::GetInstance().ShowProjectDialog();
		CArcProjectBuilder::GetInstance()->InitSaveToInstance();
	}
	else if (CArcProjectBuilder::GetInstance()->GetSavedToFile() == TRUE &&
		CArcProjectBuilder::GetInstance()->GetFileUrl().IsEmpty()) {
		// ��ǰ�������½�����
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
	// TODO: �ڴ���������������
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}


void CMFCadDlg::OnOK()
{
	CDialogEx::OnOK();
}



void CMFCadDlg::OnBnClickedButtonSaveFile()
{
	TCHAR szFilter[] = TEXT("�����ļ�(*.prj)|*.prj|�����ļ�(*.*)|*.*||");
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
			MessageBox(_T("���湤����Ϣ�ɹ�"), _T("�ɹ�"), MB_ICONHAND);
			CArcProjectBuilder::GetInstance()->SetSavedToFile(TRUE);
			break;
		case 5:
			MessageBox(_T("������㷽������ʧ��"), _T("ʧ��"), MB_ICONERROR);
			break;
		case 4:
			MessageBox(_T("����ê�˲���ʧ��"), _T("ʧ��"), MB_ICONERROR);
			break;
		case 3:
			MessageBox(_T("�����������ʧ��"), _T("ʧ��"), MB_ICONERROR);
			break;
		case 2:
			MessageBox(_T("����flag����ʧ��"), _T("ʧ��"), MB_ICONERROR);
			break;
		case 1:
			MessageBox(_T("���湤����Ϣʧ��"), _T("ʧ��"), MB_ICONERROR);
			break;
		}
	}
	
}

void CMFCadDlg::ConcreteOpenProject() {

	TCHAR szFilter[] = TEXT("�����ļ�(*.prj)|*.prj|�����ļ�(*.*)|*.*||");
	CFileDialog fileDlg(TRUE, TEXT("prj"), NULL, 0, szFilter, this);
	CString strFilePath;
	if (IDOK == fileDlg.DoModal())
	{
		strFilePath = fileDlg.GetPathName();
	}
	if (!strFilePath.IsEmpty()) {

		CArcProjectBuilder::GetInstance()->SetFileUrl(strFilePath);

		CArcProjectBuilder::GetInstance()->BuildAll();

		//MessageBox(_T("�ļ��򿪳ɹ��������������"), 0, MB_SYSTEMMODAL);
		CArcProjectBuilder::GetInstance()->SetSavedToFile(FALSE);
		DialogManager::GetInstance().setHasCurrentFile(true);
		DialogManager::GetInstance().ShowProjectDialog();
	}
}

void CMFCadDlg::OnOpenProject()
{
	// TODO: �ڴ���������������

	if (CArcProjectBuilder::GetInstance()->GetSavedToFile() == false) {
		if (IDYES == MessageBox(_T("��ǰ������δ���棬�Ƿ�ֱ�Ӵ򿪣�"), _T("��"), MB_YESNO | MB_ICONQUESTION)) {
			ConcreteOpenProject();
		}
	}
	else {
		ConcreteOpenProject();
	}

}


void CMFCadDlg::OnSaveProject()
{
	// TODO: �ڴ���������������
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
			MessageBox(_T("���湤����Ϣ�ɹ�"), _T("�ɹ�"), MB_OK);
		}
		else {
			CArcProjectBuilder::GetInstance()->SetSavedToFile(FALSE);
			MessageBox(_T("���湤����Ϣʧ�ܣ��������ܲ�����"), _T("ʧ��"), MB_ICONERROR | MB_OK);
		}
	}
}


void CMFCadDlg::OnBnClickedButtonFindAcadPath()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MessageBox(CFileUtil::GetAppRegeditPath());
}


void CMFCadDlg::OnProjectInformation()
{
	// TODO: �ڴ���������������

	if (CArcProjectBuilder::GetInstance()->GetFileUrl().IsEmpty() &&
		(CArcProjectBuilder::GetInstance()->GetProjectSaveToInstance() == FALSE)
		) {
		MessageBox(_T("��ǰ�޹��̴�"), _T("����"), MB_ICONWARNING | MB_OK);
	}
	else {
		DialogManager::GetInstance().ShowProjectDialog();
	}
	
}


void CMFCadDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���
	// �½��ļ�
	
	if (CArcProjectBuilder::GetInstance()->GetSavedToFile() == FALSE) {
		if (CArcProjectBuilder::GetInstance()->GetFileUrl().IsEmpty()) {
			if (IDYES == MessageBox(_T("��ǰ������δ���棬��Ҫ�˳���"), _T("�˳�"), MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2))
			{
				CDialogEx::OnCancel();
			}
		}
		else {
			// ���ļ���
			switch (MessageBox(_T("�Ƿ񱣴浱ǰ�޸ĵ��ļ���"), _T("�˳�"), MB_YESNOCANCEL | MB_ICONQUESTION ))
			{
			case IDYES:
				if ((CArcProjectBuilder::GetInstance()->SaveProjectToFile() == true)
					&& (CArcProjectBuilder::GetInstance()->SaveTunnelFlagToFile() == true)
					&& (CArcProjectBuilder::GetInstance()->SaveParametersToFile() == true)
					&& (CArcProjectBuilder::GetInstance()->SaveArcTunnelInfoToFile() == true)
					&& (CArcProjectBuilder::GetInstance()->SaveMethodToFile() == true)
					) {
					MessageBox(_T("���湤����Ϣ�ɹ�"), _T("�ɹ�"), MB_OK);
					CDialogEx::OnCancel();
				}
				else {
					MessageBox(_T("���湤����Ϣʧ��"), _T("ʧ��"), MB_ICONERROR | MB_OK);
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
		
		if (IDYES == MessageBox( _T("ȷ���˳��������"), _T("�˳�") , MB_ICONQUESTION | MB_YESNO ))
		{
			CDialogEx::OnCancel();
		}
	}

}


void CMFCadDlg::OnMenuExit()
{
	// TODO: �ڴ���������������
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
	
	// TODO: �ڴ˴������Ϣ����������
}

// ���Ϊ�ĵ���¼�
void CMFCadDlg::OnSaveto()
{
	// TODO: �ڴ���������������
	OnBnClickedButtonSaveFile();
}


void CMFCadDlg::OnDestroy()
{

	CFileUtil::DeleteTheFile(CFileUtil::GetAppRegeditPath() + _T("acad.rx"));
	CDialogEx::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
}