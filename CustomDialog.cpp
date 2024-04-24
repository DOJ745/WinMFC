#include "stdafx.h"
#include "WinMFC.h"
#include "CustomDialog.h"
#include "afxdialogex.h"
#include <fstream>

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
	CStringA str(LPCTSTR(dlg->m_string));
	ofstream out("LOG-FILE.txt", ios::app);
	if (out.is_open())
	{
		out << str << endl;
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
