#include "stdafx.h"
#include "WinMFC.h"
#include "CustomDialog.h"
#include "afxdialogex.h"
#include <fstream>
#include <ctime>

using namespace std;

IMPLEMENT_DYNAMIC(CustomDialog, CDialog)

CustomDialog::CustomDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CustomDialog::IDD, pParent), m_string(_T("DEFAULT"))
{

}

CustomDialog::~CustomDialog()
{
}

void CustomDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PUT_DATA, m_string);
}

void writeTextInFile(CustomDialog* dlg)
{
	time_t currentTime = time(0);
	tm* now = localtime(&currentTime);
	CString formattedLog;
	formattedLog.Format(L"%d-%d-%d %d:%d:%d      %s",
		now->tm_mday, 
		now->tm_mon + 1, 
		now->tm_year + 1900,
		now->tm_hour,
		now->tm_min,
		now->tm_sec,
		dlg->m_string);
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
END_MESSAGE_MAP()

void CustomDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	writeTextInFile(this);
	CDialog::OnOK();
}


void CustomDialog::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	writeTextInFile(this);
	CDialog::OnCancel();
}


void CustomDialog::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	UpdateData(TRUE);
	writeTextInFile(this);
	CDialog::OnClose();
}
