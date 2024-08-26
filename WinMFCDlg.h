// WinMFCDlg.h : ���� ���������
//

#pragma once
#include "CustomDialog.h"

// ���������� ���� CWinMFCDlg
class CWinMFCDlg : public CDialogEx
{
private:
	CMFCButton m_ShowCustomDlgBtn;
	CustomDialog* m_ptrDialog;
	CString m_SomeData;
	HANDLE m_hThread;
// ��������
public:

	HANDLE m_ExitThread;
	CWinMFCDlg(CWnd* pParent = NULL);	// ����������� �����������
	virtual ~CWinMFCDlg() 
	{
		delete m_ptrDialog;
	}

// ������ ����������� ����
	enum { IDD = IDD_WINMFC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// ��������� DDX/DDV


// ����������
protected:
	HICON m_hIcon;

	// ��������� ������� ����� ���������
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
};
