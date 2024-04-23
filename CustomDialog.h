#pragma once


// диалоговое окно CustomDialog

class CustomDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CustomDialog)

public:
	CustomDialog(CWnd* pParent = NULL, int number = 1000);   // стандартный конструктор
	virtual ~CustomDialog();
	int m_number;

// Данные диалогового окна
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
};
