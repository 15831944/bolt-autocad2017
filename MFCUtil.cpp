#include "stdafx.h"
#include "MFCUtil.h"
#include <iostream>


MFCUtil::MFCUtil()
{
}


MFCUtil::~MFCUtil()
{
}

CFont * MFCUtil::GetTitleFont()
{

		CFont * font = new CFont;
		font->CreateFont(20, 0, 0, 0, FW_BOLD, TRUE, FALSE, 0,
			ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial"));
		return nullptr;

}

CString MFCUtil::dtostr(double d)
{
	CString str;
	str.Format(_T("%.2lf"),d);
	return str;
}

CString MFCUtil::itostr(int i)
{
	CString str;
	str.Format(_T("%d"), i);
	return str;
}

CString MFCUtil::GetSavedDialogTitle(CString title)
{
	title.Delete(title.GetLength() - 1, 1);
	return title;
}

CString MFCUtil::GetNotSavedDialogTitle(CString title)
{
	title.Append(_T("*"));
	return title;
}

bool MFCUtil::VectorHasEmpty(std::vector<CEdit*> vec)
{
	for(auto & it : vec){
		CString str("");
		it->GetWindowText(str);
		if (str.IsEmpty())
		{
			return true;
		}
	}
	return false;
}

int MFCUtil::GetCheckedRadioButton(CButton IDC_FIRST, CButton IDC_LAST)
{
	for (int i = IDC_FIRST.GetDlgCtrlID(); i < IDC_LAST.GetDlgCtrlID(); i++)
	{
		/*if ((CButton)(IDC_FIRST + i).GetCheck() == TRUE)
		{

		}*/
	}
	return 0;
}

CTime * MFCUtil::CStringToCTime(CString str)
{
	if (str.GetLength() == 0) {
		CTime * time = new CTime();
		return time;
	}
	COleVariant vtime(str);
	vtime.ChangeType(VT_DATE);
	COleDateTime oletime = vtime;
	SYSTEMTIME systime;
	VariantTimeToSystemTime(oletime, &systime);
	CTime * time = new CTime(systime);
	return time;
}

// 角度转弧度用于计算
double MFCUtil::AngleToArc(double angle)
{
	double pi = asin(0.5) * 6;
	return angle *pi / 180;
}