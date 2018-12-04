#pragma once

#define WS_EX_LAYERED  0x00080000  //Dialog Alpha define
#define LWA_ALPHA   0x00000002
// CanvasDlg ��ȭ �����Դϴ�.

class CanvasDlg : public CDialog
{
	DECLARE_DYNAMIC(CanvasDlg)

public:
	CanvasDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CanvasDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CANVAS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	LONG m_OrgX;
	LONG m_OrgY;
	LONG m_DstX;
	LONG m_DstY;
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	RECT GetClipRect();
	bool m_bLButtonDowned;
	HCURSOR m_cursor;
};
