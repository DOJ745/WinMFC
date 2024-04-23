// WinMFCDlg.h : файл заголовка
//

#pragma once
#include "CustomDialog.h"

// диалоговое окно CWinMFCDlg
class CWinMFCDlg : public CDialogEx
{
// Создание
public:
	CustomDialog* m_ptrDialog;
	CString m_string;
	CWinMFCDlg(CWnd* pParent = NULL);	// стандартный конструктор

// Данные диалогового окна
	enum { IDD = IDD_WINMFC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
