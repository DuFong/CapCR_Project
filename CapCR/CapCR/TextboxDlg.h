#pragma once
#include "afxwin.h"


// CTEXTBOX ��ȭ �����Դϴ�.

class CTextboxDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTextboxDlg)

public:
	CTextboxDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTextboxDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEXTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editTextbox;
	CString m_strTextbox;
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
