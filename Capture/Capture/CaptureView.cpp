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

// CaptureView.cpp : CCaptureView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "Capture.h"
#endif

#include "CaptureDoc.h"
#include "CaptureView.h"
#include "CanvasDlg.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCaptureView

IMPLEMENT_DYNCREATE(CCaptureView, CFormView)

BEGIN_MESSAGE_MAP(CCaptureView, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
//	ON_BN_CLICKED(IDC_BUTTON_CAPTURE, &CCaptureView::OnBnClickedButtonCapture)
ON_BN_CLICKED(IDC_BUTTON_CAPTURE, &CCaptureView::OnBnClickedButtonCapture)
ON_WM_PAINT()
END_MESSAGE_MAP()

// CCaptureView ����/�Ҹ�

CCaptureView::CCaptureView()
	: CFormView(IDD_CAPTURE_FORM)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CCaptureView::~CCaptureView()
{
}

void CCaptureView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CCaptureView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CFormView::PreCreateWindow(cs);
}

void CCaptureView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}

void CCaptureView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCaptureView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CCaptureView ����

#ifdef _DEBUG
void CCaptureView::AssertValid() const
{
	CFormView::AssertValid();
}

void CCaptureView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CCaptureDoc* CCaptureView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCaptureDoc)));
	return (CCaptureDoc*)m_pDocument;
}
#endif //_DEBUG


// CCaptureView �޽��� ó����



void CCaptureView::OnBnClickedButtonCapture()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (Image != NULL)
		Image.Destroy();


	CString imgName = _T("Desktop.jpg");
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	pFrame->SetLayeredWindowAttributes(0, 50, LWA_ALPHA);
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
	
	SIZE s;
	ZeroMemory(&s, sizeof(SIZE));
	s.cx = (LONG)::GetSystemMetrics(SM_CXFULLSCREEN);
	s.cy = (LONG)::GetSystemMetrics(SM_CYFULLSCREEN);
	
	Image.Save(imgName, Gdiplus::ImageFormatJPEG);
	if (cx > 520 && cy > 300) 
		pFrame->SetWindowPos(NULL, (s.cx / 2) - cx / 2, 0, cx + 50, cy + 200, SWP_NOREPOSITION);
	else if (cx < 520)
		pFrame->SetWindowPos(NULL, s.cx / 2 - 260, 0, 570, cy + 200, SWP_NOREPOSITION);
	else pFrame->SetWindowPos(NULL, s.cx / 2 - cx/2, 70, cx+50, cy+200, SWP_NOREPOSITION);
	
	
	/*
	WINDOWPLACEMENT wndpl;
	ZeroMemory(&wndpl, sizeof(wndpl));
	wndpl.length = sizeof(wndpl);
	wndpl.showCmd = SW_SHOWNORMAL;
	wndpl.rcNormalPosition = CRect(area.left, area.top, area.left, area.bottom);
	GetParentFrame()->SetWindowPlacement(&wndpl);
	*/

	Image.BitBlt(dc.m_hDC, 0, 0);
	


	// �� ������ ������ �ش�. 

	/*
	::ShellExecute(NULL,
	TEXT("open"), TEXT("Desktop.jpg"),
	NULL, NULL, SW_SHOW);
	*/

}


void CCaptureView::OnPaint()
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
}


void CCaptureView::SetTransparency(int percent)
{
	SLWA pSetLayeredWindowAttributes = NULL;  // �Լ������� ����, �ʱ�ȭ.
	HINSTANCE hmodUSER32 = LoadLibrary("USER32.DLL"); // �ν��Ͻ� ����.
	pSetLayeredWindowAttributes = (SLWA)GetProcAddress(hmodUSER32, "SetLayeredWindowAttributes");
	//�Լ������� ����.
	HWND hwnd = this->m_hWnd; //���̾�α��� �ڵ� ����.
	SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	pSetLayeredWindowAttributes(hwnd, 0, (255 * percent) / 100, LWA_ALPHA);
}
