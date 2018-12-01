
// CaptureDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "atlimage.h"

// ���̾�α� ���� ������ ���� �ڵ�
#define WS_EX_LAYERED           0x00080000
#define LWA_COLORKEY            0x00000001
#define LWA_ALPHA               0x00000002
#define ULW_COLORKEY            0x00000001
#define ULW_ALPHA               0x00000002
#define ULW_OPAQUE              0x00000004 
typedef BOOL(WINAPI* SLWA)(HWND hWnd, COLORREF crKey, BYTE bAlpha, DWORD dwFlags);
// �������


// CCaptureDlg ��ȭ ����
class CCaptureDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CCaptureDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

private:
	CToolBar *m_toolbar;

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CAPTURE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedButtonCapture();

	
	
	CImage Image;
	RECT area;
//	void SetTransparency(int percent);
	BOOL m_bCaptureMode;
	void SetTransparency(int percent);
};
