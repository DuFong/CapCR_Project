// SearchDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CapCR.h"
#include "SearchDlg.h"
#include "afxdialogex.h"
#include "CapCRView.h"
#include "OCR.h"
#include "TextboxDlg.h"
#include "MainFrm.h"


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
	ON_BN_CLICKED(IDC_BUTTON_NAVER, &CSearchDlg::OnClickedButtonNaver)
	ON_BN_CLICKED(IDC_BUTTON_GOOGLE, &CSearchDlg::OnClickedButtonGoogle)
	ON_WM_ERASEBKGND()
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


void CSearchDlg::OnClickedButtonNaver()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CCapCRView* pView = (CCapCRView*)((CMainFrame*)AfxGetMainWnd())->GetActiveView();
	COCR *pOcr = pView->GetOcrObject();
	pOcr->textbox->UpdateData(TRUE);

	CString edit_text(pOcr->textbox->m_strTextbox.GetString());

	if (strcmp(edit_text, "") == 0)
	{
		AfxMessageBox(_T("검색할 내용이 없습니다."));
	}
	else
	{
		CString naver_search("search.naver.com/search.naver?sm=top_hty&fbm=1&ie=utf8&query=");
		CString var(naver_search);

		// 구글번역URL을 위해 " " -> "%20" 으로 대체하는 과정
		TCHAR split_type[] = _T(" ");

		TCHAR *p_next_token = NULL;
		TCHAR *p_token = _tcstok_s((TCHAR *)(const TCHAR *)edit_text, split_type, &p_next_token);

		while (p_token != NULL) {
			var += p_token;
			p_token = _tcstok_s(NULL, split_type, &p_next_token);
			if (p_token != NULL)
				var += "+";
		}
		//여기까지

		ShellExecute(NULL, "open", "iexplore", var, NULL, SW_SHOW);
	}
}


void CSearchDlg::OnClickedButtonGoogle()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CCapCRView* pView = (CCapCRView*)((CMainFrame*)AfxGetMainWnd())->GetActiveView();
	COCR *pOcr = pView->GetOcrObject();
	pOcr->textbox->UpdateData(TRUE);

	CString edit_text(pOcr->textbox->m_strTextbox.GetString());

	if (strcmp(edit_text, "") == 0)
	{
		AfxMessageBox(_T("검색할 내용이 없습니다."));
	}
	else
	{
		CString naver_search("www.google.co.kr/search?source=hp&ei=mHwHXLylI8an8AW1poegAQ&q=");
		CString var(naver_search);

		// 구글검색URL을 위해 " " -> "+" 으로 대체하는 과정
		TCHAR split_type[] = _T(" ");

		TCHAR *p_next_token = NULL;
		TCHAR *p_token = _tcstok_s((TCHAR *)(const TCHAR *)edit_text, split_type, &p_next_token);

		while (p_token != NULL) {
			var += p_token;
			p_token = _tcstok_s(NULL, split_type, &p_next_token);
			if (p_token != NULL)
				var += "+";
		}
		//여기까지

		ShellExecute(NULL, "open", "iexplore", var, NULL, SW_SHOW);
	}
}


BOOL CSearchDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rect;
	GetClientRect(rect);
	pDC->FillSolidRect(rect, RGB(255, 255, 255));

	return TRUE;
}
