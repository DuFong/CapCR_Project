// TEXTBOX.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CapCR.h"
#include "TextboxDlg.h"
#include "afxdialogex.h"


// CTEXTBOX 대화 상자입니다.

IMPLEMENT_DYNAMIC(CTextboxDlg, CDialogEx)

CTextboxDlg::CTextboxDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TEXTBOX, pParent)
	, m_strTextbox(_T(""))
{

}

CTextboxDlg::~CTextboxDlg()
{
}

void CTextboxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_TEXTBOX, m_editTextbox);
	DDX_Text(pDX, IDC_EDIT_TEXTBOX, m_strTextbox);
}


BEGIN_MESSAGE_MAP(CTextboxDlg, CDialogEx)
END_MESSAGE_MAP()


// CTEXTBOX 메시지 처리기입니다.
