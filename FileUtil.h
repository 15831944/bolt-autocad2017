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
	static CString GetAppRegeditPath(); // ��ע����ȡ autocad 2017 ·��
};

