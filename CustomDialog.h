#pragma once


// ���������� ���� CustomDialog

class CustomDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CustomDialog)

public:
	CustomDialog(CWnd* pParent = NULL, int number = 1000);   // ����������� �����������
	virtual ~CustomDialog();
	int m_number;

// ������ ����������� ����
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()
};
