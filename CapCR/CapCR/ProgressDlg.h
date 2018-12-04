#pragma once
#include "afxcmn.h"


// CProgressDlg 대화 상자입니다.

class CProgressDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CProgressDlg)

public:
	CProgressDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CProgressDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROGRESS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CProgressCtrl m_progressBar;
	virtual BOOL OnInitDialog();
};
