#pragma once

#include "stdafx.h"
#include "SimpleIni.h"
class CConfigFileUtil
{
public:

	CConfigFileUtil()
	{
	}

	~CConfigFileUtil()
	{
	}

	static void CreateNewConfigIni(CString filename) {
		FILE * fp;
		CString dirPath("D:\\Program Files\\Autodesk\\AutoCAD 2017\\ini");
		// �ж��Ƿ��������ļ���
		if (!PathIsDirectory(dirPath))
		{ 
			// �޶�Ӧ�ļ����򴴽�
			CreateDirectory(dirPath, 0);
			printf("dir create successfully\n");
		}
		errno_t err;
		err = fopen_s(&fp, dirPath + "\\" + filename + ".ini", "wb+");
		if (err == 0) printf(" the file was opened!\n");

		else printf("the file was not opened!\n");
	};
};

