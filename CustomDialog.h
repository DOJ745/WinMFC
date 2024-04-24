#pragma once

class CustomDialog : public CDialog
{
	DECLARE_DYNAMIC(CustomDialog)

public:
	CustomDialog(CWnd* pParent = NULL);
	virtual ~CustomDialog();

// Данные диалогового окна
	enum { IDD = IDD_CUSTOM_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnClose();
};
