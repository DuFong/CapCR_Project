// SearchDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "CapCR.h"
#include "SearchDlg.h"
#include "afxdialogex.h"


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
