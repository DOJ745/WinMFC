#include "stdafx.h"
#include "WinMFC.h"
#include "CustomDialog.h"
#include "afxdialogex.h"
#include <fstream>
#include <ctime>
#include <iostream>

using namespace std;

IMPLEMENT_DYNAMIC(CustomDialog, CDialog)

CustomDialog::CustomDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CustomDialog::IDD, pParent), 
	m_putData(CStatic()),
	m_listBox(CListBox())
{
}

CustomDialog::~CustomDialog(){}

void CustomDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PUT_DATA, m_putData);
	DDX_Control(pDX, IDC_LIST1, m_listBox);
}

void formatData(int dataToFormat, CString& str)
{
	if (dataToFormat <= 9) str.Format(L"0%d", dataToFormat);
	else str.Format(L"%d", dataToFormat);
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
END_MESSAGE_MAP()

void CustomDialog::OnClose()
{
	CDialog::OnClose();
	// TODO: Add your message handler code here and/or call default
	UpdateData(TRUE);
	writeTextInFile(this);
}

void CustomDialog::OnDestroy()
{
	CDialog::OnDestroy();
	// TODO: Add your message handler code here
	UpdateData(TRUE);
	writeTextInFile(this);
}

void CustomDialog::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CustomDialog::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	//m_putData.SetWindowPos(
	m_listBox.SetWindowPos(
		nullptr, 
		0, 
		0,
		cx < 150 ? 150 : cx - 20,
		cy < 200 ? 200 : cy - 20,
		SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void CustomDialog::AddData(CString str)
{
	UpdateWindow();
	m_listBox.AddString(str);
}