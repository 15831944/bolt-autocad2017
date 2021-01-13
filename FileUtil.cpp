#include "stdafx.h"
#include "FileUtil.h"
#include <iostream>


CFileUtil::CFileUtil()
{
}


CFileUtil::~CFileUtil()
{
}

BOOL CFileUtil::AddFile(CString filename)
{
	HANDLE hFILE = NULL;
	// 判断是否有重名文件夹
	if (!PathFileExists(filename))
	{
		// 无对应文件夹则创建
		// 创建一个新文件
		hFILE = CreateFile(filename, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		std::cout << " create new file successfully\n";
		if (hFILE == INVALID_HANDLE_VALUE)
		{
			std::cout << "hFile ERROR" << std::endl;
			return FALSE;
		}
		CloseHandle(hFILE);
		return TRUE;
	}
	else {
		// 以写方式返回
		 hFILE = CreateFile(filename, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		 CloseHandle(hFILE);
		 return TRUE;
	}

}

BOOL CFileUtil::CreateFoler(CString dir)
{
	if (!PathIsDirectory(dir))
	{
		::CreateDirectory(dir, NULL);//创建目录,已有的话不影响
	}
	return true;
}


BOOL CFileUtil::DeleteTheFile(CString filename) {
	USES_CONVERSION;
	char * pFileName = T2A(filename);
	if (remove(pFileName) == 0) {
		std::cout << "delete file successfully" << std::endl;
		return TRUE;
	}
	else {
		return FALSE;
	}
}

CString GetAcad2017Path() {

	CString strAppName("SOFTWARE\\Autodesk\\AutoCAD\\R21.0\\ACAD-0001\\Install");
	std::cout << strAppName.GetString() << std::endl;
	HKEY hKey;
	CString strAppRegeditPath("");
	TCHAR szProductType[MAX_PATH];
	memset(szProductType, 0, sizeof(szProductType));

	DWORD dwBuflen = MAX_PATH;
	LONG lRet = 0;

	// 打开注册表，只有打开后才能进行其他操作
	lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, //要打开的根键
		LPCTSTR(strAppName), // 要打开的子键
		0, //这个一定为0
		KEY_WOW64_64KEY | KEY_QUERY_VALUE,//指定打开方式为读
		&hKey
	);

	std::cout << "lret: " << lRet << std::endl;
	if (lRet != ERROR_SUCCESS)
	{
		printf("open error!\n");
		return strAppRegeditPath;
	}
	else
	{
		// 下面开始查询
		lRet = RegQueryValueEx(hKey, //打开注册表时返回的句柄
			TEXT("INSTALLDIR"), //要查询的名称
			NULL, NULL,
			(LPBYTE)szProductType,
			&dwBuflen);
	}
	if (lRet != ERROR_SUCCESS)
	{
		printf("read error!\n");

		return strAppRegeditPath;
	}
	else
	{
		RegCloseKey(hKey);
		strAppRegeditPath = szProductType;
	}
	std::cout << strAppRegeditPath.GetString() << std::endl;
	return strAppRegeditPath;
}

CString CFileUtil::GetAppRegeditPath()
{
	return GetAcad2017Path();
}
