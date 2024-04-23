#pragma once


// диалоговое окно CustomDialog

class CustomDialog : public CDialog
{
	DECLARE_DYNAMIC(CustomDialog)

public:
	CustomDialog(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CustomDialog();

// Данные диалогового окна
	enum { IDD = IDD_CUSTOM_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
};
