
// WinMFC.h : ������� ���� ��������� ��� ���������� PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"		// �������� �������


// CWinMFCApp:
// � ���������� ������� ������ ��. WinMFC.cpp
//

class CWinMFCApp : public CWinApp
{
public:
	CWinMFCApp();

// ���������������
public:
	virtual BOOL InitInstance();

// ����������

	DECLARE_MESSAGE_MAP()
};

extern CWinMFCApp theApp;