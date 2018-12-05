// �� MFC ���� �ҽ� �ڵ�� MFC Microsoft Office Fluent ����� �������̽�("Fluent UI")�� 
// ����ϴ� ����� ���� �ָ�, MFC C++ ���̺귯�� ����Ʈ��� ���Ե� 
// Microsoft Foundation Classes Reference �� ���� ���� ������ ���� 
// �߰������� �����Ǵ� �����Դϴ�.  
// Fluent UI�� ����, ��� �Ǵ� �����ϴ� �� ���� ��� ����� ������ �����˴ϴ�.  
// Fluent UI ���̼��� ���α׷��� ���� �ڼ��� ������ 
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// CapCRView.cpp : CCapCRView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "CapCR.h"
#endif

#include "CapCRDoc.h"
#include "CapCRView.h"
#include "MainFrm.h"
#include "CanvasDlg.h"
#include "OCR.h"
#include "ProgressDlg.h"
#include "TranslateDlg.h"
#include "SearchDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCapCRView

IMPLEMENT_DYNCREATE(CCapCRView, CFormView)

BEGIN_MESSAGE_MAP(CCapCRView, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
//	ON_BN_CLICKED(IDC_BUTTON_CAPTURE, &CCapCRView::OnClickedButtonCapture)
	ON_WM_PAINT()
	ON_COMMAND(ID_BUTTON_CAPTURE, &CCapCRView::OnButtonCapture)
	ON_COMMAND(ID_BUTTON_RUNOCR, &CCapCRView::OnButtonRunocr)
	ON_COMMAND(ID_BUTTON_OPENIMAGE, &CCapCRView::OnButtonOpenimage)
	ON_COMMAND(ID_BUTTON_SAVETEXT, &CCapCRView::OnButtonSavetext)
	ON_COMMAND(ID_CHECK_IGNORE_FIX, &CCapCRView::OnCheckIgnoreFix)
	ON_COMMAND(ID_CHECK_IGNORE_SPACE, &CCapCRView::OnCheckIgnoreSpace)
	ON_UPDATE_COMMAND_UI(ID_CHECK_IGNORE_FIX, &CCapCRView::OnUpdateCheckIgnoreFix)
	ON_UPDATE_COMMAND_UI(ID_CHECK_IGNORE_SPACE, &CCapCRView::OnUpdateCheckIgnoreSpace)
	ON_COMMAND(ID_BUTTON_TRANSLATE, &CCapCRView::OnButtonTranslate)
	ON_COMMAND(ID_BUTTON_SEARCH, &CCapCRView::OnButtonSearch)
END_MESSAGE_MAP()

// CCapCRView ����/�Ҹ�

CCapCRView::CCapCRView()
	: CFormView(IDD_CAPCR_FORM)
	, ocr(NULL)
	, m_bOcrEmpty(true)
	, m_bIgnoreFix(false)
	, m_bIgnoreSpace(false)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CCapCRView::~CCapCRView()
{
}

void CCapCRView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT_INPUT_IMG, m_strInput);
	//  DDX_Text(pDX, IDC_EDIT_OUTPUT_TXT, m_strOutput);
	//  DDX_Text(pDX, IDC_EXPLAIN, m_message);
}

BOOL CCapCRView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.
	//CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	
	return CFormView::PreCreateWindow(cs);
}

void CCapCRView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->SetWindowPos(NULL, 0, 0, 560, 500, SWP_NOMOVE);
	pFrame->m_bCreated = true;
}

void CCapCRView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCapCRView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CCapCRView ����

#ifdef _DEBUG
void CCapCRView::AssertValid() const
{
	CFormView::AssertValid();
}

void CCapCRView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CCapCRDoc* CCapCRView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCapCRDoc)));
	return (CCapCRDoc*)m_pDocument;
}
#endif //_DEBUG


// CCapCRView �޽��� ó����



void CCapCRView::OnPaint()
{
	CPaintDC dc(this);
	
	if (IsIconic())
	{
		// �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
		if (Image.IsNull() == FALSE)			// â ��ȭ�� �׸� ������°� ����
			Image.BitBlt(dc.m_hDC, 0, 0);
	}
	else
	{
		if (Image.IsNull() == FALSE)		// â ��ȭ�� �׸� ������°� ����
			Image.BitBlt(dc.m_hDC, 0, 0);
		CFormView::OnPaint();
	}
	if (!openImage.IsNull())
	{
		openImage.BitBlt(dc.m_hDC, 0, 0);
		
	}
	
}


void CCapCRView::OnButtonCapture()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (Image != NULL)
		Image.Destroy();

	CString imgName = _T("Desktop.jpg");
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	// ���� â �����ϰ�
	::SetWindowLong(pFrame->GetSafeHwnd(), GWL_EXSTYLE, ::GetWindowLong(pFrame->GetSafeHwnd(), GWL_EXSTYLE) | WS_EX_LAYERED);
	pFrame->SetLayeredWindowAttributes(0, 0, LWA_ALPHA);


	// Canvas ���̾�α� ȣ��
	CanvasDlg canvas;
	canvas.DoModal();




	area = canvas.GetClipRect();
	int nClipWidth = area.right - area.left;
	int nClipHeight = area.bottom - area.top;

	CWnd* pWndDesktop = GetDesktopWindow();
	// ���� ȭ�� ������ DC 

	CWindowDC ScrDC(pWndDesktop);
	// �� ������ DC
	CClientDC dc(this);
	CRect Rect;
	GetClientRect(&Rect);
	CWnd::GetWindowRect(&Rect);


	int sx = area.left;
	int sy = area.top;
	int cx = nClipWidth;
	int cy = nClipHeight;

	SIZE s;
	ZeroMemory(&s, sizeof(SIZE));
	s.cx = (LONG)::GetSystemMetrics(SM_CXFULLSCREEN);
	s.cy = (LONG)::GetSystemMetrics(SM_CYFULLSCREEN);



	Image.Create(cx, cy, ScrDC.GetDeviceCaps(BITSPIXEL));

	// �̹��� DC�� ���� �۾� ������ ���� ��ǥ�� ����� �� ũ�⸸ŭ �����ϰ� �Ѵ�. 

	CDC* pDC = CDC::FromHandle(Image.GetDC());
	pDC->BitBlt(0, 0, cx, cy, &ScrDC, sx, sy, SRCCOPY);
	Image.ReleaseDC();

	// ����� �̹����� ���ϴ� ���ϸ�, ����Ÿ���� �����ؼ� �����Ѵ�. 

	//Image.Save(imgName, Gdiplus::ImageFormatJPEG);


	//CStatic *staticSize = (CStatic*)GetDlgItem(AFX_IDC_PICTURE);
	// CRect rect2;

	// staticSize->GetClientRect(rect2);
	//Image.Load(imgName);


	Image.Save(imgName, Gdiplus::ImageFormatJPEG);

	if (cx > 560 && cy > 300)
		pFrame->SetWindowPos(NULL, (s.cx / 2) - (cx + 50) / 2, 0, cx + 30, cy + 170, SWP_NOREPOSITION);
	else if (cx < 560 && cy < 300) {
		pFrame->SetWindowPos(NULL, s.cx / 2 - 285, 0, 560, 500, SWP_NOREPOSITION);
		Invalidate();
	}
	else if (cx < 560)
		pFrame->SetWindowPos(NULL, (s.cx / 2) - 285, 0, 560, cy + 170, SWP_NOREPOSITION);
	else
		pFrame->SetWindowPos(NULL, s.cx / 2 - ((cx + 50) / 2), 0, cx + 30, 500, SWP_NOREPOSITION);



	// â ����ȭ ����
	pFrame->SetLayeredWindowAttributes(0, 255, LWA_ALPHA);

	// �̹��� �信 ���̱�
	Image.BitBlt(dc.m_hDC, 0, 0);



	// �� ������ ������ �ش�. 

	/*
	::ShellExecute(NULL,
	TEXT("open"), TEXT("Desktop.jpg"),
	NULL, NULL, SW_SHOW);
	*/
}


void CCapCRView::OnButtonRunocr()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	if (Image == NULL)
	{
		AfxMessageBox(_T("��ȯ�� �̹����� �����ϴ�."));
		return;
	}

	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_WAIT));

	CProgressDlg *pDlg = new CProgressDlg;
	pDlg->Create(IDD_PROGRESS, this);
	pDlg->CenterWindow(this);
	pDlg->ShowWindow(SW_SHOW);
	
	if (m_bOcrEmpty == FALSE)
		ocr->DestroyTextDialog();
	ocr = new COCR();
	ocr->RunOCR(&Image, "ConvertedText.txt", pDlg);
	m_bOcrEmpty = FALSE;
	pDlg->ShowWindow(SW_HIDE);
	pDlg->DestroyWindow();
	UpdateData(FALSE);

	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
}


void CCapCRView::OnButtonOpenimage()
{
	char szFilter[] = " All Files(*.*)|*.*|";
	sFilename = "";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, (CString)szFilter, NULL);
	
	int cx, cy;
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	SIZE s;
	ZeroMemory(&s, sizeof(SIZE));
	s.cx = (LONG)::GetSystemMetrics(SM_CXFULLSCREEN);
	s.cy = (LONG)::GetSystemMetrics(SM_CYFULLSCREEN);


	if (IDOK == dlg.DoModal())
	{
		sFilename = dlg.GetPathName();
		if (!openImage.IsNull())
			openImage.Destroy();


		openImage.Load(sFilename);
		
		HRESULT hResult = Image.Load(sFilename);



		// ����ó��

		if (FAILED(hResult))
		{
			CString strtmp = _T("ERROR:Failed to load");
			strtmp += sFilename + _T("\n");
			TRACE(strtmp);
			return;
		}

	

		cx = openImage.GetWidth();
		cy = openImage.GetHeight();
		
		

		if (cx> 560 &&cy> 300)
			pFrame->SetWindowPos(NULL, (s.cx / 2) - (cx + 50) / 2, 0, cx + 50, cy + 200, SWP_NOREPOSITION);
		else if (cx < 560 && cy < 300) {
			pFrame->SetWindowPos(NULL, s.cx / 2 - 285, 0, 560, 500, SWP_NOREPOSITION);
			Invalidate();
		}
		else if (cx < 560)
			pFrame->SetWindowPos(NULL, (s.cx / 2) - 285, 0, 560, cy + 200, SWP_NOREPOSITION);
		else
			pFrame->SetWindowPos(NULL, s.cx / 2 - ((cx + 50) / 2), 0, cx + 50, 500, SWP_NOREPOSITION);

		

		Invalidate();
		UpdateWindow();
	}

}



void CCapCRView::OnButtonSavetext()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	printf("[OnBnClickedBtnSave] \n");
	CString m_strPath;
	CStdioFile file;
	// CFile file;
	CFileException ex;
	CFileDialog dlg(FALSE, _T("*.txt"), NULL, OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT, _T("TXT Files(*.txt)|*.txt|"), NULL);
	if (dlg.DoModal() == IDOK)
	{
		m_strPath = dlg.GetPathName();
		if (m_strPath.Right(4) != ".txt")
		{
			m_strPath += ".txt";
		}
		file.Open(m_strPath, CFile::modeCreate | CFile::modeReadWrite, &ex);
		// ����Ʈ �ڽ��� �ִ� ���� �����Ѵ�. 
		UpdateData(TRUE);
		//file.WriteString(m_strTextbox);
		// �����Ѵ�. 
		file.Close();
	}

}


void CCapCRView::OnCheckIgnoreFix()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if (!m_bIgnoreFix)
		m_bIgnoreFix = true;
	else
		m_bIgnoreFix = false;
}


void CCapCRView::OnCheckIgnoreSpace()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if (!m_bIgnoreSpace)
		m_bIgnoreSpace = true;
	else
		m_bIgnoreSpace = false;
}


void CCapCRView::OnUpdateCheckIgnoreFix(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	if (m_bIgnoreFix)
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}


void CCapCRView::OnUpdateCheckIgnoreSpace(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	if (m_bIgnoreSpace)
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}


void CCapCRView::OnButtonTranslate()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CTranslateDlg dlg;
	dlg.DoModal();
}


void CCapCRView::OnButtonSearch()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CSearchDlg dlg;
	dlg.DoModal();
}
