#pragma once
#include "afxwin.h"


// CSearchDlg 대화 상자입니다.

class CSearchDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSearchDlg)

public:
	CSearchDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSearchDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SEARCH };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CBitmapButton m_btNaver;
	CBitmapButton m_btGoogle;
	virtual BOOL OnInitDialog();
};
