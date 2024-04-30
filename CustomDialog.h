#pragma once
#include "afxwin.h"

class CustomDialog : public CDialog
{
	DECLARE_DYNAMIC(CustomDialog)

private:
	CStatic m_putData;
	CListBox m_listBox;

public:
	CustomDialog(CWnd* pParent = NULL);
	virtual ~CustomDialog();

// ������ ����������� ����
	enum { IDD = IDD_CUSTOM_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void AddData(CString str);
};
