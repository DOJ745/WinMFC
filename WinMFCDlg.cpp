// WinMFCDlg.cpp : файл реализации
//
#include "stdafx.h"
#include "WinMFC.h"
#include "WinMFCDlg.h"
#include "afxdialogex.h"
#include "CustomDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWinMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MAIN_WND_TEXT, m_SomeData);
	DDX_Control(pDX, IDC_MAIN_WND_SHOW_CUSTOM_DIALOG, m_ShowCustomDlgBtn);
}

BEGIN_MESSAGE_MAP(CWinMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CWinMFCDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CWinMFCDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CWinMFCDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_MAIN_WND_CHANGE_DATA, &CWinMFCDlg::OnBnClickedMainWndChangeData)
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
	// TODO: Add your control notification handler code here
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
