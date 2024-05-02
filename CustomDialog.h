#pragma once
#include "afxwin.h"
#include "MyCMFCListCtrl.h"

class CustomDialog : public CDialog
{
	DECLARE_DYNAMIC(CustomDialog)

private:
	CStatic m_putData;
	CListBox m_listBox;
	MyCMFCListCtrl m_listCtrl;

public:
	CustomDialog(CWnd* pParent = NULL);
	virtual ~CustomDialog();

// Данные диалогового окна
	enum { IDD = IDD_CUSTOM_DIALOG };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void AddData(CString str);
};
