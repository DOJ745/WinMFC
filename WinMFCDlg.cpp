// WinMFCDlg.cpp : файл реализации
//
#include "stdafx.h"
#include "WinMFC.h"
#include "WinMFCDlg.h"
#include "afxdialogex.h"
#include "CustomDialog.h"

#include <string>
#include <Windows.h>
#include "Log.h"
#include "MathLibrary.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "IShowMessageBox.h"

// Custom window message
const int WM_THREADENDED = WM_USER + 1;


// Диалоговое окно CAboutDlg используется для описания сведений о приложении
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// диалоговое окно CWinMFCDlg
CWinMFCDlg::CWinMFCDlg(CWnd* pParent /*=NULL*/): 
	CDialogEx(CWinMFCDlg::IDD, pParent), 
	m_ptrDialog(NULL), 
	m_SomeData(_T("SOME DATA"))
	, m_ApplyNumber(FALSE)
	, m_InputNumber(10)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWinMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MAIN_WND_TEXT, m_SomeData);
	DDX_Control(pDX, IDC_MAIN_WND_SHOW_CUSTOM_DIALOG, m_ShowCustomDlgBtn);
	DDX_Check(pDX, IDC_CHECK_APPLY_NUMBER, m_ApplyNumber);
	DDX_Text(pDX, IDC_EDIT_INPUT_NUMBER, m_InputNumber);
	DDX_Control(pDX, IDC_SPIN_SET_NUMBER, m_SpinControl);
}

BEGIN_MESSAGE_MAP(CWinMFCDlg, CDialogEx)
	ON_MESSAGE(WM_THREADENDED, OnThreadEnded)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1,OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnBnClickedButton3)
	ON_BN_CLICKED(IDC_MAIN_WND_CHANGE_DATA, OnBnClickedMainWndChangeData)
	ON_WM_HOTKEY()
	ON_EN_UPDATE(IDC_EDIT_INPUT_NUMBER, OnEnUpdateEditInputNumber)
	ON_BN_CLICKED(IDC_CHECK_APPLY_NUMBER, OnBnClickedCheckApplyNumber)
//	ON_EN_CHANGE(IDC_EDIT_INPUT_NUMBER, &CWinMFCDlg::OnEnChangeEditInputNumber)
	ON_BN_CLICKED(IDC_MAIN_WND_OPEN_CALC, OnBnClickedMainWndOpenCalc)
	ON_BN_CLICKED(IDC_MAIN_WND_LAUNCH_ASYNC, OnBnClickedMainWndLaunchAsync)
	ON_BN_CLICKED(IDC_MAIN_WND_START_AFX, &CWinMFCDlg::OnBnClickedMainWndStartAfx)
	ON_BN_CLICKED(IDC_MAIN_WND_STOP_AFX, &CWinMFCDlg::OnBnClickedMainWndStopAfx)
	ON_BN_CLICKED(IDC_MAIN_WND_DO_INI, &CWinMFCDlg::OnBnClickedMainWndDoIni)
END_MESSAGE_MAP()

// обработчики сообщений CWinMFCDlg

BOOL CWinMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна. Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	m_ptrDialog = new CustomDialog();
	m_ptrDialog->Create(IDD_CUSTOM_DIALOG, GetSafeOwner());

	m_ShowCustomDlgBtn.EnableWindowsTheming(FALSE);
	m_ShowCustomDlgBtn.SetFaceColor(RGB(0, 255, 0));

	if (RegisterHotKey(
		this->m_hWnd,
		1,
		MOD_ALT | MOD_CONTROL | MOD_NOREPEAT,
		'B'))
	{
		MessageBoxA(
			NULL,
			"Hotkey 'CTRL+ALT+B' registered, using MOD_NOREPEAT flag",
			"HOTKEY REG COMBINATION",
			MB_OKCANCEL | MB_ICONASTERISK);
	}

	SetDlgItemInt(IDC_EDIT_INPUT_NUMBER, 10, FALSE);
	m_SpinControl.SetRange(-10, 10);

	GetDlgItem(IDC_EDIT_INPUT_NUMBER)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN_SET_NUMBER)->EnableWindow(FALSE);

	MessageDisplayer displayer;
	displayer.ShowMsgBox();

	Log::GetInstance().WriteMsg("TEST MSG");

	double tempNumber = std::stod("41.12345");
	double tempNumber2 = std::stod("42,12345");

	MessageBoxA(
		NULL, 
		std::to_string(static_cast<long double>(tempNumber)).c_str(),
		"STOD function with period",
		MB_OKCANCEL | MB_ICONINFORMATION);

	MessageBoxA(
		NULL,
		std::to_string(static_cast<long double>(tempNumber2)).c_str(),
		"STOD function with comma",
		MB_OKCANCEL | MB_ICONINFORMATION);

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CWinMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок. Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CWinMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CWinMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// UpdateData(FALSE) means variables->controls, 
// while UpdateData(TRUE) means controls->variables - includes "validation"

void formatData2(int dataToFormat, CString& str)
{
	if (dataToFormat <= 9) str.Format(L"0%d", dataToFormat);
	else str.Format(L"%d", dataToFormat);
}

CString formLog(CString logData)
{
	time_t currentTime = time(0);
	tm* now = localtime(&currentTime);

	CString day;
	CString month;
	CString hours;
	CString minutes;
	CString seconds;

	formatData2(now->tm_mday, day);
	formatData2(now->tm_mon, month);

	if (now->tm_mon + 1 <= 9) month.Format(L"0%d", now->tm_mon + 1);
	else month.Format(L"%d", now->tm_mon + 1);

	formatData2(now->tm_hour, hours);
	formatData2(now->tm_min, minutes);
	formatData2(now->tm_sec, seconds);

	CString formattedLog;
	formattedLog.Format(L"%s-%s-%d %s:%s:%s      %s",
		day,
		month,
		now->tm_year + 1900,
		hours,
		minutes,
		seconds,
		logData);

	return formattedLog;
}


void CWinMFCDlg::OnBnClickedButton1()
{
	// Modeless dialog
	CRect customDialogRect;
	m_ptrDialog->GetWindowRect(customDialogRect);

	m_ptrDialog->SetWindowPos(
		AfxGetMainWnd(), 
		1200, 
		100, 
		customDialogRect.Width(),
		customDialogRect.Height(),
		SWP_SHOWWINDOW
		);
}

void CWinMFCDlg::OnBnClickedButton2()
{
	CRect rect;
	GetWindowRect(&rect);

	CImage* img = new CImage();

	img->Create(rect.Width(), rect.Height(), 32);

	HDC device_context_handle = img->GetDC();
	HWND hwnd = this->GetSafeHwnd();

	// PW_CLIENTONLY
	bool isPrint = ::PrintWindow(hwnd, device_context_handle, 0);

	if (isPrint)
	{
		HRESULT res = img->Save(L"D:\\testImage.bmp", Gdiplus::ImageFormatBMP);
		img->ReleaseDC();

		MessageBoxA(
			NULL,
			"Screenshot has been saved to D:\\testImage.bmp",
			"SCREENSHOT",
			MB_OKCANCEL | MB_ICONWARNING);
	}

	delete img;
}


void CWinMFCDlg::OnBnClickedButton3()
{
	for (int i = 0; i < 5; i++)
	{
		m_ptrDialog->AddData(formLog(L"RANDOM DATA"));
		Sleep(250);
	}
}


void CWinMFCDlg::OnBnClickedMainWndChangeData()
{
	for (int i = 0; i < 10; i++)
	{
		m_SomeData.Format(L"RANDOM: %d", i);
		m_ptrDialog->AddData(formLog(m_SomeData));
		Sleep(1000 + i * 10);
		UpdateData(FALSE);
	}
}


void CWinMFCDlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	MessageBoxA(
		NULL,
		"Hotkey received!",
		"HOTKEY COMBINATION",
		MB_OKCANCEL | MB_ICONWARNING);

	if (m_ApplyNumber)
	{
		m_SomeData.Format(L"Add number: %d", m_InputNumber);
		UpdateData(FALSE);
	}
}


void CWinMFCDlg::OnEnUpdateEditInputNumber()
{
	m_InputNumber = GetDlgItemInt(IDC_EDIT_INPUT_NUMBER);

	UpdateData(FALSE);
}


void CWinMFCDlg::OnBnClickedCheckApplyNumber()
{
	m_ApplyNumber = !m_ApplyNumber;

	if (m_ApplyNumber)
	{
		GetDlgItem(IDC_EDIT_INPUT_NUMBER)->EnableWindow(TRUE);
		GetDlgItem(IDC_SPIN_SET_NUMBER)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_INPUT_NUMBER)->EnableWindow(FALSE);
		GetDlgItem(IDC_SPIN_SET_NUMBER)->EnableWindow(FALSE);
	}

	UpdateData(FALSE);
}

UINT ThreadFunc(LPVOID param)
{
	HWND mainWndHandle = (HWND)param;

	TRACE1("\n\t === ThreadFunc ID: %d === \t\n", GetCurrentThreadId());

	/*for (int i = 0; i < 5; i++)
	{
		std::string temp = "Test " + std::to_string(static_cast<long double>(i));
		
		SetDlgItemTextA(mainWndHandle, IDC_MAIN_WND_TEXT, temp.c_str());
		Sleep(1000);
	}*/

	// Exporting DLL (they should be the same bit depth - x86 or x64)

	fibonacci_init(1, 1);
	// Write out the sequence values until overflow.
	do 
	{
		std::string temp = "Fibonacci DLL --- " + 
			std::to_string(static_cast<long double>(fibonacci_index())) + ": "
			+ std::to_string(static_cast<long double>(fibonacci_current()));

		SetDlgItemTextA(mainWndHandle, IDC_MAIN_WND_TEXT, temp.c_str());
		Sleep(1000);
	} while (fibonacci_next());

	// Custom message send
	::PostMessage(mainWndHandle, WM_THREADENDED, (WPARAM)mainWndHandle, 0);

	return 0;
}

UINT AfxThreadFunc(LPVOID param)
{
	CWinMFCDlg* myDlg = (CWinMFCDlg*)param;

	for (int i = 0; i < 10; i++)
	{
		if (WaitForSingleObject(myDlg->m_ExitThread, 0) == WAIT_OBJECT_0)
		{
			break;
		}
			
		std::string temp = "AFX THREAD " + std::to_string(static_cast<long double>(i));

		SetDlgItemTextA(myDlg->GetSafeHwnd(), IDC_MAIN_WND_TEXT, temp.c_str());
		Sleep(1000);
	}

	return 0;
}

void CWinMFCDlg::OnBnClickedMainWndOpenCalc()
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	// Start the Calculator application
	if (!CreateProcess(
		TEXT("C:\\Windows\\System32\\calc.exe"),   // Path to the executable
		NULL,        // Command line
		NULL,        // Process handle not inheritable
		NULL,        // Thread handle not inheritable
		FALSE,       // Set handle inheritance to FALSE
		0,           // No creation flags
		NULL,        // Use parent's environment block
		NULL,        // Use parent's starting directory 
		&si,         // Pointer to STARTUPINFO structure
		&pi)         // Pointer to PROCESS_INFORMATION structure
		)
	{
		MessageBoxA
		(
			NULL,
			"Failed to start Calculator",
			"Error",
			MB_OK | MB_ICONERROR
		);

		return;
	}

	// Wait until Calculator exits
	DWORD result = WaitForSingleObject(pi.hProcess, 1000);

	if (result == WAIT_OBJECT_0)
	{
		MessageBoxA
		(
			NULL,
			"The calc has been opened successfully!",
			"Finish",
			MB_OK | MB_ICONINFORMATION
		);
	}

	if (result == WAIT_TIMEOUT)
	{
		MessageBoxA
		(
			NULL,
			"Tiemout!",
			"Error",
			MB_OK | MB_ICONERROR
		);
	}

	// Close process and thread handles
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

void CWinMFCDlg::OnBnClickedMainWndLaunchAsync()
{
	GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
	m_hThread = CreateThread(
		NULL,
		0,
		(LPTHREAD_START_ROUTINE)ThreadFunc,
		this->GetSafeHwnd(),
		0,
		NULL);
}

LONG CWinMFCDlg::OnThreadEnded(WPARAM wParam, LPARAM lParam)
{
	::MessageBox(
		(HWND)wParam,
		L"Thread Ended",
		L"Message from thread",
		MB_OK | MB_ICONINFORMATION);

	GetDlgItem(IDC_EDIT1)->EnableWindow(TRUE);
	CloseHandle(m_hThread);

	return 0;
}

void CWinMFCDlg::OnBnClickedMainWndStartAfx()
{
	GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
	m_ExitThread = ::CreateEvent(NULL, FALSE, FALSE, NULL);

	CWinThread* myAfxThread = AfxBeginThread(AfxThreadFunc, (LPVOID)this);
	HANDLE myAfxThreadHandle = myAfxThread->m_hThread;

	/*if (WaitForSingleObject(myAfxThreadHandle, INFINITE) == WAIT_OBJECT_0)
	{
		AfxMessageBox(L"FINISHED", MB_OK | MB_ICONINFORMATION);
		GetDlgItem(IDC_EDIT1)->EnableWindow(TRUE);
	}*/
}


void CWinMFCDlg::OnBnClickedMainWndStopAfx()
{
	// TODO: Add your control notification handler code here
	::SetEvent(m_ExitThread);
}


void CWinMFCDlg::OnBnClickedMainWndDoIni()
{
	const std::string filePath = ".\\test-config.ini";
	const std::string section = "SECTION";
	const std::string key = "KEY";
	const std::string value = "VALUE";
	
	std::string myStrData;
	
	WritePrivateProfileStringA(section.c_str(), key.c_str(), value.c_str(), filePath.c_str());
	GetPrivateProfileStringA(section.c_str(), key.c_str(), value.c_str(), myStrData._Myptr(), sizeof(myStrData) / sizeof(myStrData[0]), filePath.c_str());
	SetDlgItemTextA(GetSafeHwnd(), IDC_MAIN_WND_TEXT, myStrData.c_str());
}
