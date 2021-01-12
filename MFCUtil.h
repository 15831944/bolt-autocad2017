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
	// 判断 CEdit 数组中是否有空数据
	static bool VectorHasEmpty(std::vector<CEdit *> vec);
	static int GetCheckedRadioButton(CButton IDC_FIRST, CButton IDC_LAST);
	static CTime * CStringToCTime(CString str);
	static double AngleToArc(double angle);
	// 获取 CEdit 中的值并转为 double 变量
	static double GetDoubleEdtValue(CEdit* mEdt);
};

