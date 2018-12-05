// TranslateDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "CapCR.h"
#include "TranslateDlg.h"
#include "afxdialogex.h"
#include "CapCRView.h"
#include "OCR.h"
#include "TextboxDlg.h"
#include "MainFrm.h"


// CTranslateDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CTranslateDlg, CDialogEx)

CTranslateDlg::CTranslateDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TRANSLATE, pParent)
{

}

CTranslateDlg::~CTranslateDlg()
{
}

void CTranslateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_LANG, m_cbLang);
}


BEGIN_MESSAGE_MAP(CTranslateDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_OK, &CTranslateDlg::OnClickedButtonOk)
//	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CTranslateDlg �޽��� ó�����Դϴ�.


void CTranslateDlg::OnClickedButtonOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CCapCRView* pView = (CCapCRView*)((CMainFrame*)AfxGetMainWnd())->GetActiveView();
	COCR *pOcr = pView->GetOcrObject();
	pOcr->textbox->UpdateData(TRUE);

	CString edit_text(pOcr->textbox->m_strTextbox.GetString());

	if (strcmp(edit_text, "") == 0)
	{
		AfxMessageBox(_T("������ ������ �����ϴ�."));
	}
	else 
	{
		
		int index = m_cbLang.GetCurSel();
		CString google_tran;
		CString var;
		switch (index)
		{
		case 0 :
			google_tran = "translate.google.co.kr/?hl=ko#view=home&op=translate&sl=en&tl=ko&text=";
			var = google_tran;
			break;
		case 1:
			google_tran = "translate.google.co.kr/?hl=ko#view=home&op=translate&sl=en&tl=ja&text=";
			var = google_tran;
			break;
		case 2:
			google_tran = "translate.google.co.kr/?hl=ko#view=home&op=translate&sl=en&tl=zh-TW&text=";
			var = google_tran;
			break;
		default:
			AfxMessageBox(_T("������ �� �����ϼ���"));
			break;
		}
		if (index + 1)
		{
			char* pEdit_text = (char*)((LPCSTR)(edit_text));

			for (int i = 0; i < strlen(pEdit_text); i++)
			{
				if (pEdit_text[i] == ' ')
					var += "%20";
				else if (pEdit_text[i] == '\n')
					var += "%0A";
				else
					var += pEdit_text[i];
			}
			//�������

			ShellExecute(NULL, "open", "iexplore", var, NULL, SW_SHOW);
		}
	}
}
