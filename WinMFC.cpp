#include "stdafx.h"
#include "WinMFC.h"
#include "WinMFCDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CWinMFCApp
BEGIN_MESSAGE_MAP(CWinMFCApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// Craetion of CWinMFCApp
CWinMFCApp::CWinMFCApp()
{
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
}


// Single object CWinMFCApp
CWinMFCApp theApp;

// Initialization of CWinMFCApp
BOOL CWinMFCApp::InitInstance()
{
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);

	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	CShellManager *pShellManager = new CShellManager;

	SetRegistryKey(_T("Test MFC APP"));

	CWinMFCDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{

	}
	else if (nResponse == IDCANCEL)
	{

	}

	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	return FALSE;
}