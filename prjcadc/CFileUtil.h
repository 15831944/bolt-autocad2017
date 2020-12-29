#pragma once
#include "StdAfx.h"
class CFileUtil
{
public:
	CFileUtil() {};
	~CFileUtil() {} ;
	static CString GetAppRegeditPath() {

		CString strAppName("SOFTWARE\\Autodesk\\AutoCAD\\R21.0\\ACAD-0001:804");
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

		if (lRet != ERROR_SUCCESS)
		{
			printf("open error!\n");
			return strAppRegeditPath;
		}
		else
		{
			// 下面开始查询
			lRet = RegQueryValueEx(hKey, //打开注册表时返回的句柄
				TEXT("AcadLocation"), //要查询的名称
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
		return strAppRegeditPath;
	};
private:

};


