#pragma once


// ���������� ���� CustomDialog

class CustomDialog : public CDialog
{
	DECLARE_DYNAMIC(CustomDialog)

public:
	CString m_string;
	CustomDialog(CWnd* pParent = NULL);
	virtual ~CustomDialog();

// ������ ����������� ����
	enum { IDD = IDD_CUSTOM_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
};
