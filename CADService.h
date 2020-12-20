#pragma once
#include "FileUtil.h"
#include "stdafx.h"

class CADService {

public:
	//��дacad.rx �ļ�
	static BOOL WriteAcadRx() {

		CString filename = CFileUtil::GetAppRegeditPath() + _T("acad.rx");

		CFile file;

		file.Open(filename, CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate, NULL);

		//�ӡ�size_t��ת������UINT�������ܶ�ʧ����
		file.Write("INGprjcadc.arx", strlen("INGprjcadc.arx"));

		file.Close();

		return true;
		
	};

	// ͨ���������̵ķ�ʽ���� acad.exe 
	static BOOL LaunchACad() {
		CString OutputPath;
		CString m_strCADPath = CFileUtil::GetAppRegeditPath(); //��ע����л�ȡ acad 2017��·��
		STARTUPINFO si; //һЩ�ر���������
		memset(&si, 0, sizeof(STARTUPINFO));
		si.cb = sizeof(STARTUPINFO);
		si.dwFlags = STARTF_USESHOWWINDOW;
		si.wShowWindow = SW_SHOWNORMAL;
		PROCESS_INFORMATION pi; //�ر��������ý���
		OutputPath = m_strCADPath + _T("acad.exe");
		BOOL bRet = CreateProcess(NULL, OutputPath.GetBuffer(OutputPath.GetLength()), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
		return bRet;
	};

};