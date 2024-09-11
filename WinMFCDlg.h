// WinMFCDlg.h : файл заголовка
//

#pragma once
#include "CustomDialog.h"

// Custom edit field class
class CDoubleEdit : public CEdit
{
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
		if (pMsg->message == WM_CHAR)
		{
			TCHAR ch = (TCHAR)pMsg->wParam;

			if (!isdigit(ch) && ch != VK_BACK && ch != '.') //&& ch != '-')
			{
				return TRUE; // Ignore the character
			}
		}
		return CEdit::PreTranslateMessage(pMsg);
	}
};

// диалоговое окно CWinMFCDlg
class CWinMFCDlg : public CDialogEx
{
private:
	CMFCButton m_ShowCustomDlgBtn;
	CustomDialog* m_ptrDialog;
	CString m_SomeData;
	HANDLE m_hThread;
// Создание
public:

	HANDLE m_ExitThread;
	CDoubleEdit m_EditDouble;
	double m_DoubleNumber;

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

	afx_msg LONG OnThreadEnded(WPARAM wParam, LPARAM lParam);

	afx_msg void OnEnUpdateEditInputNumber();
	afx_msg void OnBnClickedCheckApplyNumber();
	afx_msg void OnBnClickedMainWndOpenCalc();
	afx_msg void OnBnClickedMainWndLaunchAsync();

private:
	BOOL m_ApplyNumber;
	int m_InputNumber;
	CSpinButtonCtrl m_SpinControl;

	
public:
	afx_msg void OnBnClickedMainWndStartAfx();
	afx_msg void OnBnClickedMainWndStopAfx();
	afx_msg void OnBnClickedMainWndDoIni();
	afx_msg void OnEnUpdateEditDouble();
};
