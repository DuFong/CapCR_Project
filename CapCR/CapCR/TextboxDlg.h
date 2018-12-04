#pragma once
#include "afxwin.h"


// CTEXTBOX 대화 상자입니다.

class CTextboxDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTextboxDlg)

public:
	CTextboxDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTextboxDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEXTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editTextbox;
	CString m_strTextbox;
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
