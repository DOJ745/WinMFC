
// WinMFC.h : главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CWinMFCApp:
// О реализации данного класса см. WinMFC.cpp
//

class CWinMFCApp : public CWinApp
{
public:
	CWinMFCApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CWinMFCApp theApp;