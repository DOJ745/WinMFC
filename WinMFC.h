#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"

void DDX_TextNotEmpty (CDataExchange* pDX, int nIDC, CString& value);
class CWinMFCApp : public CWinApp
{
public:
	CWinMFCApp();

public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

extern CWinMFCApp theApp;