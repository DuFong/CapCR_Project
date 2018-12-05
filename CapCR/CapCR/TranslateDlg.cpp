// TranslateDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CapCR.h"
#include "TranslateDlg.h"
#include "afxdialogex.h"
#include "CapCRView.h"
#include "OCR.h"
#include "TextboxDlg.h"
#include "MainFrm.h"


// CTranslateDlg 대화 상자입니다.

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


// CTranslateDlg 메시지 처리기입니다.


void CTranslateDlg::OnClickedButtonOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CCapCRView* pView = (CCapCRView*)((CMainFrame*)AfxGetMainWnd())->GetActiveView();
	COCR *pOcr = pView->GetOcrObject();
	pOcr->textbox->UpdateData(TRUE);

	CString edit_text(pOcr->textbox->m_strTextbox.GetString());

	if (strcmp(edit_text, "") == 0)
	{
		AfxMessageBox(_T("번역할 내용이 없습니다."));
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
			AfxMessageBox(_T("번역할 언어를 선택하세요"));
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
			//여기까지

			ShellExecute(NULL, "open", "iexplore", var, NULL, SW_SHOW);
		}
	}
}
