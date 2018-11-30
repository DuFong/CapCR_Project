// CanvasDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Capture.h"
#include "CanvasDlg.h"
#include "afxdialogex.h"


// CanvasDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CanvasDlg, CDialog)

CanvasDlg::CanvasDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_CANVAS, pParent)
	, m_OrgX(0)
	, m_OrgY(0)
	, m_DstX(0)
	, m_DstY(0)
{

}

CanvasDlg::~CanvasDlg()
{
}

void CanvasDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CanvasDlg, CDialog)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_KILLFOCUS()
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CanvasDlg 메시지 처리기입니다.


BOOL CanvasDlg::OnInitDialog()
{
	

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	int nScreenWidth = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	int nScreenHeight = GetSystemMetrics(SM_CYVIRTUALSCREEN);
	MoveWindow(0,0, nScreenWidth, nScreenHeight);
	typedef BOOL(WINAPI *SLWA)(HWND, COLORREF, BYTE, DWORD);
	SLWA pSetLayeredWindowAttributes = NULL;
	HWND hwnd = this->m_hWnd;

	SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	SetLayeredWindowAttributes(0, 150, LWA_ALPHA);

	// 최상위 윈도우
	::SetWindowPos(GetSafeHwnd(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	CDialog::OnInitDialog();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CanvasDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_OrgX = m_DstX = point.x;
	m_OrgY = m_DstY = point.y;

	CDialog::OnLButtonDown(nFlags, point);
}


void CanvasDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_DstX = point.x;
	m_DstY = point.y;

	CDialog::OnLButtonUp(nFlags, point);
	::SendMessage(this->m_hWnd, WM_CLOSE, NULL, NULL);

}


void CanvasDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_DstX = point.x;
	m_DstY = point.y;
	Invalidate(TRUE);
	CDialog::OnMouseMove(nFlags, point);
}


void CanvasDlg::OnKillFocus(CWnd* pNewWnd)
{
	CDialog::OnKillFocus(pNewWnd);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	CDialog::OnKillFocus(pNewWnd);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 키를 입력하면 Canvas 를 숨김(취소)	
	::SendMessage(this->m_hWnd, WM_CLOSE, NULL, NULL);
}


void CanvasDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialog::OnPaint()을(를) 호출하지 마십시오
	
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	dc.SelectObject(&pen);

	LONG x1 = m_OrgX, x2 = m_DstX, y1 = m_OrgY, y2 = m_DstY;
	if (x1 > x2) { x1 = m_DstX; x2 = m_OrgX; }
	if (y1 > y2) { y1 = m_DstY; y2 = m_OrgY; }


	dc.Rectangle(x1, y1, x2, y2);

	CString pixelInfo;
	pixelInfo.Format(_T("%d x %d"), abs(x2 - x1), abs(y2 - y1));
	RECT textPosition = { x2 - 80, y2, x2, y2 + 15 };
	DrawText(dc, pixelInfo, -1, &textPosition, DT_VCENTER | DT_SINGLELINE);
	// 그리기 메시지에 대해서는 CDialog::OnPaint()을(를) 호출하지 마십시오.



	
}


HBRUSH CanvasDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	switch (nCtlColor) {
	case CTLCOLOR_DLG:
		hbr = (HBRUSH)GetStockObject(WHITE_BRUSH);
		break;
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.

}


RECT CanvasDlg::GetClipRect()
{
	RECT rect;
	if (m_OrgX == m_DstX || m_OrgY == m_DstY) {
		rect.bottom = rect.left = rect.right = rect.top = 0;
		return rect;
	}

	LONG x1 = m_OrgX, x2 = m_DstX, y1 = m_OrgY, y2 = m_DstY;
	if (x1 > x2) { x1 = m_DstX; x2 = m_OrgX; }
	if (y1 > y2) { y1 = m_DstY; y2 = m_OrgY; }

	rect.left = x1;
	rect.right = x2;
	rect.top = y1;
	rect.bottom = y2;

	return rect;
}
