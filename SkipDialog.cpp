// SkipDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include <iostream>
#include "MFCad.h"
#include "SkipDialog.h"
#include "afxdialogex.h"
#include "SimpleIni.h"
#include "MFCUtil.h"

// CSkipDialog �Ի���

IMPLEMENT_DYNAMIC(CSkipDialog, CDialog)

CSkipDialog::CSkipDialog(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_SKIP_DIALOG, pParent)
{

}

CSkipDialog::~CSkipDialog()
{
}

void CSkipDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

}


BEGIN_MESSAGE_MAP(CSkipDialog, CDialog)
	ON_WM_PAINT()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CSkipDialog ��Ϣ�������


// �Ի��򱳾�����Ϊ����ͼ
void CSkipDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()

	CRect   rect;
	GetClientRect(&rect);    //��ȡ�Ի��򳤿�      
	CDC   dcBmp;             //���岢����һ���ڴ��豸����
	dcBmp.CreateCompatibleDC(&dc);             //����������DC
	CBitmap   bmpBackground;
	bmpBackground.LoadBitmap(IDB_BITMAP_BG);    //������Դ��ͼƬ
	BITMAP   m_bitmap;                         //ͼƬ����               
	bmpBackground.GetBitmap(&m_bitmap);       //��ͼƬ����λͼ��
											  //��λͼѡ����ʱ�ڴ��豸����
	CBitmap  *pbmpOld = dcBmp.SelectObject(&bmpBackground);
	//���ú�����ʾͼƬStretchBlt��ʾ��״�ɱ�
	dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcBmp, 0, 0, m_bitmap.bmWidth, m_bitmap.bmHeight, SRCCOPY);
}


BOOL CSkipDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	const int CLOSE_SKIP = 1;

	SetTimer(CLOSE_SKIP, 3000, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CSkipDialog::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	std::cout << "on timer\n";
	//std::cout << "find window\n";
	switch (nIDEvent)
	{
	case 1:
		this->PostMessage(WM_CLOSE);
		KillTimer(1);
		break;
	default:
		break;
	}
	CDialog::OnTimer(nIDEvent);
}

