// SearchDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "CapCR.h"
#include "SearchDlg.h"
#include "afxdialogex.h"
#include "CapCRView.h"
#include "OCR.h"
#include "TextboxDlg.h"
#include "MainFrm.h"


// CSearchDlg ��ȭ �����Դϴ�.

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


// CSearchDlg �޽��� ó�����Դϴ�.


BOOL CSearchDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_btGoogle.LoadBitmaps(IDB_BITMAP_GOOGLE, IDB_BITMAP_GOOGLE, IDB_BITMAP_GOOGLE, NULL);
	m_btNaver.LoadBitmaps(IDB_BITMAP_NAVER, IDB_BITMAP_NAVER, IDB_BITMAP_NAVER,NULL);
	m_btGoogle.SizeToContent();
	m_btNaver.SizeToContent();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CSearchDlg::OnClickedButtonNaver()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CCapCRView* pView = (CCapCRView*)((CMainFrame*)AfxGetMainWnd())->GetActiveView();
	COCR *pOcr = pView->GetOcrObject();
	pOcr->textbox->UpdateData(TRUE);

	CString edit_text(pOcr->textbox->m_strTextbox.GetString());

	if (strcmp(edit_text, "") == 0)
	{
		AfxMessageBox(_T("�˻��� ������ �����ϴ�."));
	}
	else
	{
		CString naver_search("search.naver.com/search.naver?sm=top_hty&fbm=1&ie=utf8&query=");
		CString var(naver_search);

		// ���۹���URL�� ���� " " -> "%20" ���� ��ü�ϴ� ����
		TCHAR split_type[] = _T(" ");

		TCHAR *p_next_token = NULL;
		TCHAR *p_token = _tcstok_s((TCHAR *)(const TCHAR *)edit_text, split_type, &p_next_token);

		while (p_token != NULL) {
			var += p_token;
			p_token = _tcstok_s(NULL, split_type, &p_next_token);
			if (p_token != NULL)
				var += "+";
		}
		//�������

		ShellExecute(NULL, "open", "iexplore", var, NULL, SW_SHOW);
	}
}


void CSearchDlg::OnClickedButtonGoogle()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CCapCRView* pView = (CCapCRView*)((CMainFrame*)AfxGetMainWnd())->GetActiveView();
	COCR *pOcr = pView->GetOcrObject();
	pOcr->textbox->UpdateData(TRUE);

	CString edit_text(pOcr->textbox->m_strTextbox.GetString());

	if (strcmp(edit_text, "") == 0)
	{
		AfxMessageBox(_T("�˻��� ������ �����ϴ�."));
	}
	else
	{
		CString naver_search("www.google.co.kr/search?source=hp&ei=mHwHXLylI8an8AW1poegAQ&q=");
		CString var(naver_search);

		// ���۰˻�URL�� ���� " " -> "+" ���� ��ü�ϴ� ����
		TCHAR split_type[] = _T(" ");

		TCHAR *p_next_token = NULL;
		TCHAR *p_token = _tcstok_s((TCHAR *)(const TCHAR *)edit_text, split_type, &p_next_token);

		while (p_token != NULL) {
			var += p_token;
			p_token = _tcstok_s(NULL, split_type, &p_next_token);
			if (p_token != NULL)
				var += "+";
		}
		//�������

		ShellExecute(NULL, "open", "iexplore", var, NULL, SW_SHOW);
	}
}


BOOL CSearchDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CRect rect;
	GetClientRect(rect);
	pDC->FillSolidRect(rect, RGB(255, 255, 255));

	return TRUE;
}
