#pragma once
#include <vector>
class MFCUtil
{
public:
	MFCUtil();
	~MFCUtil();
	static CFont* GetTitleFont();
	static CString dtostr(double d);
	static CString itostr(int i);
	static CString GetSavedDialogTitle(CString title);
	static CString GetNotSavedDialogTitle(CString title);
	// �ж� CEdit �������Ƿ��п�����
	static bool VectorHasEmpty(std::vector<CEdit *> vec);
	static int GetCheckedRadioButton(CButton IDC_FIRST, CButton IDC_LAST);
	static CTime * CStringToCTime(CString str);
	static double AngleToArc(double angle);
	// ��ȡ CEdit �е�ֵ��תΪ double ����
	static double GetDoubleEdtValue(CEdit* mEdt);
};

