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

		// ��ע���ֻ�д򿪺���ܽ�����������
		lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, //Ҫ�򿪵ĸ���
			LPCTSTR(strAppName), // Ҫ�򿪵��Ӽ�
			0, //���һ��Ϊ0
			KEY_WOW64_64KEY | KEY_QUERY_VALUE,//ָ���򿪷�ʽΪ��
			&hKey
		);

		if (lRet != ERROR_SUCCESS)
		{
			printf("open error!\n");
			return strAppRegeditPath;
		}
		else
		{
			// ���濪ʼ��ѯ
			lRet = RegQueryValueEx(hKey, //��ע���ʱ���صľ��
				TEXT("AcadLocation"), //Ҫ��ѯ������
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


