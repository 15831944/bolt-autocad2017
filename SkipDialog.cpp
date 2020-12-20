// SkipDialog.cpp : 实现文件
//

#include "stdafx.h"
#include <iostream>
#include "MFCad.h"
#include "SkipDialog.h"
#include "afxdialogex.h"
#include "SimpleIni.h"
#include "MFCUtil.h"

// CSkipDialog 对话框

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


// CSkipDialog 消息处理程序


// 对话框背景设置为背景图
void CSkipDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialog::OnPaint()

	CRect   rect;
	GetClientRect(&rect);    //获取对话框长宽      
	CDC   dcBmp;             //定义并创建一个内存设备环境
	dcBmp.CreateCompatibleDC(&dc);             //创建兼容性DC
	CBitmap   bmpBackground;
	bmpBackground.LoadBitmap(IDB_BITMAP_BG);    //载入资源中图片
	BITMAP   m_bitmap;                         //图片变量               
	bmpBackground.GetBitmap(&m_bitmap);       //将图片载入位图中
											  //将位图选入临时内存设备环境
	CBitmap  *pbmpOld = dcBmp.SelectObject(&bmpBackground);
	//调用函数显示图片StretchBlt显示形状可变
	dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcBmp, 0, 0, m_bitmap.bmWidth, m_bitmap.bmHeight, SRCCOPY);
}


BOOL CSkipDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	const int CLOSE_SKIP = 1;

	SetTimer(CLOSE_SKIP, 3000, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CSkipDialog::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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

