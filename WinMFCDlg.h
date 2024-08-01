// WinMFCDlg.h : файл заголовка
//

#pragma once
#include "CustomDialog.h"

// диалоговое окно CWinMFCDlg
class CWinMFCDlg : public CDialogEx
{
private:
	CMFCButton m_ShowCustomDlgBtn;
	CustomDialog* m_ptrDialog;
	CString m_SomeData;
// Создание
public:
	CWinMFCDlg(CWnd* pParent = NULL);	// стандартный конструктор
	virtual ~CWinMFCDlg() 
	{
		delete m_ptrDialog;
	}

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
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedMainWndChangeData();
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
};
