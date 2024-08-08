#pragma once
#include "afxwin.h"
#include "MyCMFCListCtrl.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class CustomDialog : public CDialog
{
	DECLARE_DYNAMIC(CustomDialog)

private:
	MyCMFCListCtrl m_listCtrl;
	CImageList m_imageList;
	CString m_TextInfo;

	string m_testString;
	vector<string> m_testVectorStr;

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
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void AddData(CString str);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
};
