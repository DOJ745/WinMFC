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
	m_string(_T("default")),
	m_ptrDialog(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWinMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DATA, m_string);
}

BEGIN_MESSAGE_MAP(CWinMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CWinMFCDlg::OnBnClickedButton1)
	ON_EN_UPDATE(IDC_EDIT_DATA, &CWinMFCDlg::OnEnUpdateEditData)
	ON_EN_CHANGE(IDC_EDIT_DATA, &CWinMFCDlg::OnEnChangeEditData)
	ON_BN_CLICKED(IDC_BUTTON2, &CWinMFCDlg::OnBnClickedButton2)
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
	m_ptrDialog->Create(IDD_CUSTOM_DIALOG, this);

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

void CWinMFCDlg::OnBnClickedButton1()
{
	// Modeless dialog
	m_ptrDialog->ShowWindow(SW_SHOW);
}

// UpdateData(FALSE) means variables->controls, 
// while UpdateData(TRUE) means controls->variables - includes "validation"

// About to display
void CWinMFCDlg::OnEnUpdateEditData()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.

	// TODO:  Add your control notification handler code here
	//UpdateData(TRUE);
	//m_ptrDialog->SetDlgItemTextW(IDC_PUT_DATA, m_string);
}

// Display is updated after text changed
void CWinMFCDlg::OnEnChangeEditData()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateData(TRUE);
	m_ptrDialog->SetDlgItemTextW(IDC_PUT_DATA, m_string);
}

void formatData2(int dataToFormat, CString& str)
{
	if (dataToFormat <= 9) str.Format(L"0%d", dataToFormat);
	else str.Format(L"%d", dataToFormat);
}

CString formLog()
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
	formattedLog.Format(L"\n%s-%s-%d %s:%s:%s\n",
		day,
		month,
		now->tm_year + 1900,
		hours,
		minutes,
		seconds);

	return formattedLog;
}

void CWinMFCDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	for (int i = 0; i < 10; i++)
	{
		Sleep(1000);
		m_string += formLog();
		m_ptrDialog->SetDlgItemTextW(IDC_PUT_DATA, m_string);
	}
	UpdateData(FALSE);
}
