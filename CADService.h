#pragma once
#include "FileUtil.h"
#include "stdafx.h"

class CADService {

public:
	//编写acad.rx 文件
	static BOOL WriteAcadRx() {

		CString filename = CFileUtil::GetAppRegeditPath() + _T("acad.rx");

		CFile file;

		file.Open(filename, CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate, NULL);

		//从“size_t”转换到“UINT”，可能丢失数据
		file.Write("INGprjcadc.arx", strlen("INGprjcadc.arx"));

		file.Close();

		return true;
		
	};

	// 通过创建进程的方式启动 acad.exe 
	static BOOL LaunchACad() {
		CString OutputPath;
		CString m_strCADPath = CFileUtil::GetAppRegeditPath(); //从注册表中获取 acad 2017的路径
		STARTUPINFO si; //一些必备参数设置
		memset(&si, 0, sizeof(STARTUPINFO));
		si.cb = sizeof(STARTUPINFO);
		si.dwFlags = STARTF_USESHOWWINDOW;
		si.wShowWindow = SW_SHOWNORMAL;
		PROCESS_INFORMATION pi; //必备参数设置结束
		OutputPath = m_strCADPath + _T("acad.exe");
		BOOL bRet = CreateProcess(NULL, OutputPath.GetBuffer(OutputPath.GetLength()), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
		return bRet;
	};

};