// WinMFCDlg.h : ���� ���������
//

#pragma once
#include "CustomDialog.h"

// ���������� ���� CWinMFCDlg
class CWinMFCDlg : public CDialogEx
{
// ��������
public:
	CustomDialog* m_ptrDialog;
	CString m_string;
	CWinMFCDlg(CWnd* pParent = NULL);	// ����������� �����������

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
};
