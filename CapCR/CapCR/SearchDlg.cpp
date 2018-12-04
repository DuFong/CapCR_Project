// SearchDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CapCR.h"
#include "SearchDlg.h"
#include "afxdialogex.h"


// CSearchDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSearchDlg, CDialogEx)

CSearchDlg::CSearchDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SEARCH, pParent)
{

}

CSearchDlg::~CSearchDlg()
{
}

void CSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_NAVER, m_btNaver);
	DDX_Control(pDX, IDC_BUTTON_GOOGLE, m_btGoogle);
}


BEGIN_MESSAGE_MAP(CSearchDlg, CDialogEx)
END_MESSAGE_MAP()


// CSearchDlg 메시지 처리기입니다.


BOOL CSearchDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_btGoogle.LoadBitmaps(IDB_BITMAP_GOOGLE, IDB_BITMAP_GOOGLE, IDB_BITMAP_GOOGLE, NULL);
	m_btNaver.LoadBitmaps(IDB_BITMAP_NAVER, IDB_BITMAP_NAVER, IDB_BITMAP_NAVER,NULL);
	m_btGoogle.SizeToContent();
	m_btNaver.SizeToContent();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
