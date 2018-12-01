
// CaptureDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "atlimage.h"

// 다이얼로그 투명도 조절을 위한 코드
#define WS_EX_LAYERED           0x00080000
#define LWA_COLORKEY            0x00000001
#define LWA_ALPHA               0x00000002
#define ULW_COLORKEY            0x00000001
#define ULW_ALPHA               0x00000002
#define ULW_OPAQUE              0x00000004 
typedef BOOL(WINAPI* SLWA)(HWND hWnd, COLORREF crKey, BYTE bAlpha, DWORD dwFlags);
// 여기까지


// CCaptureDlg 대화 상자
class CCaptureDlg : public CDialogEx
{
// 생성입니다.
public:
	CCaptureDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

private:
	CToolBar *m_toolbar;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CAPTURE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
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
