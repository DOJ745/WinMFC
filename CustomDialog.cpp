#include "stdafx.h"
#include "afxwin.h"
#include "WinMFC.h"
#include "CustomDialog.h"
#include "MyCMFCListCtrl.h"
#include "afxdialogex.h"
#include <ctime>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

IMPLEMENT_DYNAMIC(CustomDialog, CDialog)

CustomDialog::CustomDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CustomDialog::IDD, pParent), 
	m_listCtrl(MyCMFCListCtrl()),
	m_imageList(CImageList()),
	m_TextInfo(_T("DEFAULT")),
	m_testString("")
{
	m_imageList.Create(32, 32, ILC_COLOR, 0, 1);

	for (int i = 0; i < 20; i++)
	{
		CString strInd;
		strInd.Format(_T("========== ПЕРЕМЫЧКА %d =========="), i + 1);
		m_testString = strInd + "\nВЫСОТА 1 (мкм): 3000, ВЫСОТА 2 (мкм): 5000\n\n";
		m_testVectorStr.emplace_back(m_testString);
	}

	for each (string stitchLog in m_testVectorStr)
	{
		m_testString += stitchLog;
	}
}

CustomDialog::~CustomDialog(){}

BOOL CustomDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString testCStr = L"TEXT";

	m_imageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_CUSTOM));
	m_imageList.Add(AfxGetApp()->LoadIcon(IDI_ICON1));

	m_listCtrl.SetImageList(&m_imageList, LVSIL_SMALL);

	m_listCtrl.InsertColumn(0, L"Номер перемычки", 0, 200);
	m_listCtrl.InsertColumn(1, L"Высота 1 (мкм)", 1, 200);
	m_listCtrl.InsertColumn(2, L"Высота 2 (мкм)", 2, 200);

	for (int i = 0; i < 10; i++)
	{
		CString number, date;
		number.Format(_T("%d"), i);
		date.Format(_T("25-05-202%d"), i);

		int nIndex = m_listCtrl.InsertItem(i, date, 0);
		m_listCtrl.SetItemText(nIndex, 1, _T("14:54:01"));
		m_listCtrl.SetItemText(nIndex, 2, number);
	}
	m_listCtrl.SetItemText(4, 2, _T("100"));
	
	m_listCtrl.EnableMarkSortedColumn();
	m_listCtrl.SetBkColor(RGB(150, 30, 4));
	m_listCtrl.Sort(0, FALSE, FALSE);

	/*MessageBoxA(NULL,
		m_testString.c_str(),
		"CAPTION",
		MB_OKCANCEL | MB_ICONINFORMATION);*/

	return TRUE;
}

void CustomDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CUSTOM_DIALOG_LIST_CTRL, m_listCtrl);
	DDX_Text(pDX, IDC_CUSTOM_DIALOG_OUTPUT_INFO, m_TextInfo);
}

void formatData(int dataToFormat, CString& str)
{
	if (dataToFormat <= 9) str.Format(L"0%d", dataToFormat);
	else str.Format(L"%d", dataToFormat);
}

void writePreparedDataInFile(CString str)
{
	CStringA log(str);

	ofstream out("LOG-FILE.txt", ios::app);
	if (out.is_open())
	{
		out << log << endl;
	}
	out.close();
}

void writeTextInFile(CustomDialog* dlg)
{
	CString str;
	dlg->GetDlgItemTextW(IDC_PUT_DATA, str);

	time_t currentTime = time(0);
	tm* now = localtime(&currentTime);

	CString day;
	CString month;
	CString hours;
	CString minutes;
	CString seconds;

	formatData(now->tm_mday, day);
	formatData(now->tm_mon, month);
	formatData(now->tm_hour, hours);
	formatData(now->tm_min, minutes);
	formatData(now->tm_sec, seconds);

	if (now->tm_mon + 1 <= 9) month.Format(L"0%d", now->tm_mon + 1);
	else month.Format(L"%d", now->tm_mon + 1);

	CString formattedLog;
	formattedLog.Format(L"%s-%s-%d %s:%s:%s      %s",
		day, 
		month, 
		now->tm_year + 1900,
		hours,
		minutes,
		seconds,
		str);

	CStringA log(formattedLog);

	ofstream out("LOG-FILE.txt", ios::app);
	if (out.is_open())
	{
		out << log << endl;
	}
	out.close();
}

BEGIN_MESSAGE_MAP(CustomDialog, CDialog)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_WM_VSCROLL()
	ON_WM_SIZE()
	ON_WM_SIZING()
END_MESSAGE_MAP()

void CustomDialog::OnClose()
{
	CDialog::OnClose();
	// TODO: Add your message handler code here and/or call default
	//UpdateData(TRUE);
	//writeTextInFile(this);
}

void CustomDialog::OnDestroy()
{
	CDialog::OnDestroy();
	// TODO: Add your message handler code here
	//UpdateData(TRUE);
	//writeTextInFile(this);
}

void CustomDialog::OnSize(UINT nType, int cx, int cy)
{
	/*CDialog::OnSize(nType, cx, cy);
	
	CRect rect;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);
	int main_x_size = 800; // Your desired width
	int main_y_size = 600; // Your desired height
	::SetWindowPos(m_hWnd, HWND_DESKTOP, 0, 0, main_x_size, main_y_size, SWP_NOZORDER);


	if (m_listCtrl.GetSafeHwnd())
	{
		m_listCtrl.SetWindowPos(
			m_listCtrl.GetSafeOwner(),
			0,
			0,
			cx < 150 ? 150 : cx - 20,
			cy < 200 ? 200 : cy - 20,
			SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	}*/
}

void CustomDialog::AddData(CString str)
{
	//m_listBox.AddString(str);

	int nIndex = m_listCtrl.InsertItem(0, str.Mid(0, 11), 0);
	m_listCtrl.SetItemText(nIndex, 1, str.Mid(11, 8));
	m_listCtrl.SetItemText(nIndex, 2, str.Mid(25, str.GetLength()));
	UpdateWindow();

	writePreparedDataInFile(str);
}

void CustomDialog::OnSizing(UINT fwSide, LPRECT pRect)
{
	CDialog::OnSizing(fwSide, pRect);

	// TODO: Add your message handler code here
	CRect rect = pRect;
	
	m_TextInfo.Format(L"WIDTH: %d, HEIGHT %d",
		rect.Width(),
		rect.Height());

	UpdateData(FALSE);
}