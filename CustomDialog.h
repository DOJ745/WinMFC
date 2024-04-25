#pragma once

class CustomDialog : public CDialog
{
	DECLARE_DYNAMIC(CustomDialog)

public:
	CString m_editText;
	CustomDialog(CWnd* pParent = NULL);
	virtual ~CustomDialog();

// ������ ����������� ����
	enum { IDD = IDD_CUSTOM_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnClose();
	afx_msg void OnEnUpdateCustomDialogEdit();
	afx_msg void OnEnChangeCustomDialogEdit();

	afx_msg void OnDestroy();
	void ChangeMember(CString str);
};
