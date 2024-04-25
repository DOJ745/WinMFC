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
	: CDialog(CustomDialog::IDD, pParent)
	, m_editText(_T("empty"))
{

}

CustomDialog::~CustomDialog(){}

void CustomDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CUSTOM_DIALOG_EDIT, m_editText);
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
	ON_BN_CLICKED(IDOK, &CustomDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CustomDialog::OnBnClickedCancel)
	ON_WM_CLOSE()
	ON_EN_UPDATE(IDC_CUSTOM_DIALOG_EDIT, &CustomDialog::OnEnUpdateCustomDialogEdit)
	ON_EN_CHANGE(IDC_CUSTOM_DIALOG_EDIT, &CustomDialog::OnEnChangeCustomDialogEdit)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

void CustomDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	//writeTextInFile(this);
	CDialog::OnOK();
}


void CustomDialog::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	//writeTextInFile(this);
	CDialog::OnCancel();
}


void CustomDialog::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	UpdateData(TRUE);
	//writeTextInFile(this);
	CDialog::OnClose();
}

void CustomDialog::OnEnUpdateCustomDialogEdit()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.

	// TODO:  Add your control notification handler code here
}


void CustomDialog::OnEnChangeCustomDialogEdit()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CustomDialog::OnDestroy()
{
	// TODO: Add your message handler code here
	UpdateData(TRUE);
	writeTextInFile(this);
	CDialog::OnDestroy();
}


void CustomDialog::ChangeMember(CString str)
{
	UpdateData();
	for (int i = 0; i < 5; i++)
	{
		Sleep(500);
		m_editText += str;
		SetDlgItemTextW(IDC_CUSTOM_DIALOG_EDIT, m_editText);
	}
	UpdateData(FALSE);
}