
// MFCad.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFCadApp: 
// �йش����ʵ�֣������ MFCad.cpp
//

class CMFCadApp : public CWinApp
{
public:
	CMFCadApp();

// ��д
public:

	virtual BOOL InitInstance();

// ʵ�� 

	DECLARE_MESSAGE_MAP()
};

extern CMFCadApp theApp;