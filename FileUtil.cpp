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
	// �ж��Ƿ��������ļ���
	if (!PathFileExists(filename))
	{
		// �޶�Ӧ�ļ����򴴽�
		// ����һ�����ļ�
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
		// ��д��ʽ����
		 hFILE = CreateFile(filename, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		 CloseHandle(hFILE);
		 return TRUE;
	}

}

BOOL CFileUtil::CreateFoler(CString dir)
{
	if (!PathIsDirectory(dir))
	{
		::CreateDirectory(dir, NULL);//����Ŀ¼,���еĻ���Ӱ��
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

	// ��ע���ֻ�д򿪺���ܽ�����������
	lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, //Ҫ�򿪵ĸ���
		LPCTSTR(strAppName), // Ҫ�򿪵��Ӽ�
		0, //���һ��Ϊ0
		KEY_WOW64_64KEY | KEY_QUERY_VALUE,//ָ���򿪷�ʽΪ��
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
		// ���濪ʼ��ѯ
		lRet = RegQueryValueEx(hKey, //��ע���ʱ���صľ��
			TEXT("INSTALLDIR"), //Ҫ��ѯ������
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
