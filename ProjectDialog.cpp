// ProjectDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCad.h"
#include "ProjectDialog.h"
#include "afxdialogex.h"
#include <iostream>
#include "DataChecker.h"
#include "DialogManager.h"

//һ��ʼ�����ѡ��Ի�������ֻ�й���һ�����
CTunnelChooseDialog * tDlg = NULL;
CTunnelProject  *project = new CTunnelProject();

// CProjectDialog �Ի���

IMPLEMENT_DYNAMIC(CProjectDialog, CDialogEx)

CProjectDialog::CProjectDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PROJECT_DIALOG, pParent)
	, mStrPaperTitle(_T(""))
	, mStrPaperDescription(_T(""))
	, mIntScaleNumber(0)
	, mStrPaperNumber(_T(""))
	, mStrPaperSize(_T(""))
	, mStrDesigner(_T(""))
	, mStrDate(_T(""))
	, mStrChecker(_T(""))
	, mStrCheckDate(_T(""))
	, mStrDesignApart(_T(""))
{

}

CProjectDialog::~CProjectDialog()
{
}

void CProjectDialog::UpdateUI()
{
	CTunnelProject * pInfo = CArcProjectBuilder::GetInstance()->GetTunnelProject();

	mEdtPaperTitle.SetWindowText(pInfo->GetPaperTitle());
	mEdtDevelopApart.SetWindowText(_T("�����Ƽ���ѧ"));
	mDtCheckDate.SetTime(MFCUtil::CStringToCTime(pInfo->GetCheckDate()));
	mEdtChecker.SetWindowText(pInfo->GetChecker());
	mDtDate.SetTime(MFCUtil::CStringToCTime(pInfo->GetDate()));
	mEdtDescription.SetWindowText(pInfo->GetPaperDescription());
	mEdtDesignApart.SetWindowText(pInfo->GetDesignApart());
	mEdtDesigner.SetWindowText(pInfo->GetDesigner());
	mEdtPaperNumber.SetWindowText(pInfo->GetPaperNumber());
	mEdtScaleOne.SetWindowText(_T("1"));
	mEdtScaleNumber.SetWindowText(pInfo->GetScaleNumber());
}

void CProjectDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_DEVELOPMENT_UNIT, mEdtDevelopApart);
	DDX_Control(pDX, IDC_EDIT_PROJECT_CHECKER, mEdtChecker);
	DDX_Control(pDX, IDC_EDIT_PROJECT_DESCRIPTION, mEdtDescription);
	DDX_Control(pDX, IDC_EDIT_PROJECT_DESIGN_UNIT, mEdtDesignApart);
	DDX_Control(pDX, IDC_EDIT_PROJECT_DESIGNER, mEdtDesigner);
	DDX_Control(pDX, IDC_EDIT_PROJECT_NAME, mEdtPaperTitle);
	DDX_Control(pDX, IDC_EDIT_PROJECT_NUMBER, mEdtPaperNumber);
	DDX_Control(pDX, IDC_EDIT_PROJECT_SCALE, mEdtScaleOne);
	DDX_Control(pDX, IDC_EDIT_SCALE_NUMBER, mEdtScaleNumber);
	DDX_Control(pDX, IDC_COMBO_PAPER_SIZE, mComboPaperSize);
	DDX_Text(pDX, IDC_EDIT_PROJECT_NAME, mStrPaperTitle);
	DDV_MaxChars(pDX, mStrPaperTitle, 20);
	DDX_Text(pDX, IDC_EDIT_PROJECT_DESCRIPTION, mStrPaperDescription);
	DDV_MaxChars(pDX, mStrPaperDescription, 50);
	DDX_Text(pDX, IDC_EDIT_SCALE_NUMBER, mIntScaleNumber);
	DDV_MinMaxInt(pDX, mIntScaleNumber, 1, 1000);
	DDX_Text(pDX, IDC_EDIT_PROJECT_NUMBER, mStrPaperNumber);
	DDV_MaxChars(pDX, mStrPaperNumber, 10);
	DDX_CBString(pDX, IDC_COMBO_PAPER_SIZE, mStrPaperSize);
	DDV_MaxChars(pDX, mStrPaperSize, 2);
	DDX_Text(pDX, IDC_EDIT_PROJECT_DESIGNER, mStrDesigner);
	DDV_MaxChars(pDX, mStrDesigner, 4);
	DDX_Control(pDX, IDC_PROJECT_DATE, mDtDate);
	DDX_Control(pDX, IDC_PROJECT_CHECK_DATE, mDtCheckDate);
	DDX_Text(pDX, IDC_EDIT_PROJECT_CHECKER, mStrChecker);
	//DDX_DateTimeCtrl(pDX, IDC_PROJECT_CHECK_DATE, mStrCheckDate);
	DDX_Text(pDX, IDC_EDIT_PROJECT_DESIGN_UNIT, mStrDesignApart);
	DDV_MaxChars(pDX, mStrDesignApart, 20);
}
BEGIN_MESSAGE_MAP(CProjectDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CProjectDialog::OnBnClickedOk)
	ON_WM_MOVE()
	ON_WM_MOVING()
	ON_BN_CLICKED(IDCANCEL, &CProjectDialog::OnBnClickedCancel)
END_MESSAGE_MAP()


void CProjectDialog::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (MFCUtil::VectorHasEmpty(mVectorProject) == true) {
		MessageBox(_T("���ܺ��п�ֵ"), _T("����"), MB_ICONWARNING | MB_OK);
	}
	else {
		// ���������ں��������
		CTime mDesignDate;
		CTime mCheckDate;

		mDtDate.GetTime(mDesignDate);
		mStrDate = mDesignDate.Format("%Y��%m��%d��");

		mDtCheckDate.GetTime(mCheckDate);
		mStrCheckDate = mCheckDate.Format("%Y��%m��%d��");

		if (mDesignDate > mCheckDate) {
			MessageBox(_T("���ʱ�䲻���������ʱ��!"),_T("����"), MB_ICONWARNING | MB_OK);
		}
		else {
			if (DataChecker::IsNegative(mIntScaleNumber) == true)
			{
				MessageBox(_T("��������Ϊ����!"), _T("����"), MB_ICONWARNING | MB_OK);
			}
			else
			{
				CDialogEx::OnOK();
				CTunnelProject * p = GetProjectInfoFromMFC();

				CArcProjectBuilder::GetInstance()->SetTunnelProject(p);
				CArcProjectBuilder::GetInstance()->SetProjectSaveToInstance(TRUE);

				DialogManager::GetInstance().ShowTunnelChooseDlg();
			}
		}
	}
	
}


BOOL CProjectDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	HICON hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_FOLDER));
	SetIcon(hIcon, FALSE);

	mComboPaperSize.AddString(_T("A1"));
	mComboPaperSize.AddString(_T("A2"));
	mComboPaperSize.AddString(_T("A3"));
	mComboPaperSize.AddString(_T("A4"));

	mComboPaperSize.SetCurSel(2);

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	CTunnelProject * pInfo = CArcProjectBuilder::GetInstance()->GetTunnelProject();

	mEdtPaperTitle.SetWindowText(pInfo->GetPaperTitle());
	mEdtDevelopApart.SetWindowText(_T("�����Ƽ���ѧ"));
	mEdtChecker.SetWindowText(pInfo->GetChecker());
	mEdtDescription.SetWindowText(pInfo->GetPaperDescription());
	mEdtDesignApart.SetWindowText(pInfo->GetDesignApart());
	mEdtDesigner.SetWindowText(pInfo->GetDesigner());
	mEdtPaperNumber.SetWindowText(pInfo->GetPaperNumber());
	mEdtScaleOne.SetWindowText(_T("1"));
	pInfo->SetScaleNumber(_T("100"));
	mEdtScaleNumber.SetWindowText(pInfo->GetScaleNumber());
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

CTunnelProject* CProjectDialog::GetProjectInfoFromMFC()
{
	CString strScaleNumber;
	CTime mDesignDate;
	CTime mCheckDate;

	mDtDate.GetTime(mDesignDate);
	mStrDate = mDesignDate.Format("%Y��%m��%d��");
	mEdtScaleNumber.GetWindowText(strScaleNumber);
	
	mDtCheckDate.GetTime(mCheckDate);
	mStrCheckDate = mCheckDate.Format("%Y��%m��%d��");

	project->SetPaperTitle(mStrPaperTitle);

		
	project->SetPaperDescription(mStrPaperDescription);
	project->SetScaleNumber(strScaleNumber);
	project->SetPaperNumber(mStrPaperNumber);
	project->SetPaperSize(mStrPaperSize);
	project->SetDesigner(mStrDesigner);
	project->SetDate(mStrDate);
	project->SetChecker(mStrChecker);
	project->SetCheckDate(mStrCheckDate);
	project->SetDesignApart(mStrDesignApart);
	project->SetDevelopApart( _T("�����Ƽ���ѧ"));

	return project;
}


void CProjectDialog::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

	if (CArcProjectBuilder::GetInstance()->GetProjectSaveToInstance() == FALSE)
	{
		if (IDYES == MessageBox(_T("��ǰҳ�������δ���棬��Ҫ�رյ�ǰҳ�棿"), _T("ȡ��"), MB_YESNO |  MB_ICONQUESTION))
		{
			CDialogEx::OnCancel();
		}
	}
	else {
		CDialogEx::OnCancel();
	}

}


void CProjectDialog::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);

	// TODO: �ڴ˴������Ϣ����������
}


void CProjectDialog::OnMoving(UINT fwSide, LPRECT lpRect)
{
	// �����ӶԻ������Ƴ����Ի�����
	CRect rectParent; 
	GetParent()->GetClientRect(&rectParent); 
	GetParent()->ClientToScreen(&rectParent); 
	CRect rectChild; GetWindowRect(&rectChild);
	lpRect->left = min(lpRect->left, rectParent.right - rectChild.Width());    
	lpRect->left = max(lpRect->left, rectParent.left);    
	lpRect->top = min(lpRect->top, rectParent.bottom - rectChild.Height());   
	lpRect->top = max(lpRect->top, rectParent.top);    
	lpRect->right = min(lpRect->right, rectParent.right);    
	lpRect->right = max(lpRect->right, rectParent.left + rectChild.Width());       
	lpRect->bottom = min(lpRect->bottom, rectParent.bottom);   
	lpRect->bottom = max(lpRect->bottom, rectParent.top + rectChild.Height());

	CDialogEx::OnMoving(fwSide,  lpRect);

	// TODO: �ڴ˴������Ϣ����������


}



void CProjectDialog::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnCancel();
	ShowWindow(SW_HIDE);
}
