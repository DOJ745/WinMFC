// CustomDialog.cpp: файл реализации
//

#include "stdafx.h"
#include "WinMFC.h"
#include "CustomDialog.h"
#include "afxdialogex.h"


// диалоговое окно CustomDialog

IMPLEMENT_DYNAMIC(CustomDialog, CDialog)

CustomDialog::CustomDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CustomDialog::IDD, pParent)
{

}

CustomDialog::~CustomDialog()
{
}

void CustomDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CustomDialog, CDialog)
END_MESSAGE_MAP()


// обработчики сообщений CustomDialog
