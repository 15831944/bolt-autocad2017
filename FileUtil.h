#pragma once
#include <Windows.h>
class CFileUtil
{
private:
	CString filename;

public:
	CFileUtil();
	~CFileUtil();
	static HANDLE AddFile(CString filename);
	static BOOL CreateFoler(CString dir);
	static BOOL WriteConfigInfo(CString filename, CString section, CString key, CString value);
	static BOOL DeleteTheFile(CString filename);
	static CString GetAppRegeditPath(); // 从注册表获取 autocad 2017 路径
};

