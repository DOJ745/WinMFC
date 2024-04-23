// CustomDialog.cpp: файл реализации
//

#include "stdafx.h"
#include "WinMFC.h"
#include "CustomDialog.h"
#include "afxdialogex.h"


// диалоговое окно CustomDialog

IMPLEMENT_DYNAMIC(CustomDialog, CDialogEx)

CustomDialog::CustomDialog(CWnd* pParent /*=NULL*/, int number)
	: CDialogEx(CustomDialog::IDD, pParent)
{

}

CustomDialog::~CustomDialog()
{
}

void CustomDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}