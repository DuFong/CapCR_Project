// 이 MFC 샘플 소스 코드는 MFC Microsoft Office Fluent 사용자 인터페이스("Fluent UI")를 
// 사용하는 방법을 보여 주며, MFC C++ 라이브러리 소프트웨어에 포함된 
// Microsoft Foundation Classes Reference 및 관련 전자 문서에 대해 
// 추가적으로 제공되는 내용입니다.  
// Fluent UI를 복사, 사용 또는 배포하는 데 대한 사용 약관은 별도로 제공됩니다.  
// Fluent UI 라이선싱 프로그램에 대한 자세한 내용은 
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// CaptureView.h : CCaptureView 클래스의 인터페이스
//

#pragma once

// 다이얼로그 투명도 조절을 위한 코드
#define WS_EX_LAYERED           0x00080000
#define LWA_COLORKEY            0x00000001
#define LWA_ALPHA               0x00000002
#define ULW_COLORKEY            0x00000001
#define ULW_ALPHA               0x00000002
#define ULW_OPAQUE              0x00000004 
typedef BOOL(WINAPI* SLWA)(HWND hWnd, COLORREF crKey, BYTE bAlpha, DWORD dwFlags);
// 여기까지


class CCaptureView : public CFormView
{
protected: // serialization에서만 만들어집니다.
	CCaptureView();
	DECLARE_DYNCREATE(CCaptureView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_CAPTURE_FORM };
#endif

// 특성입니다.
public:
	CCaptureDoc* GetDocument() const;


// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.

// 구현입니다.
public:
	CImage Image;
	HICON m_hIcon;
	RECT area;
	virtual ~CCaptureView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnBnClickedButtonCapture();
	afx_msg void OnBnClickedButtonCapture();
	afx_msg void OnPaint();
	void SetTransparency(int percent);
};

#ifndef _DEBUG  // CaptureView.cpp의 디버그 버전
inline CCaptureDoc* CCaptureView::GetDocument() const
   { return reinterpret_cast<CCaptureDoc*>(m_pDocument); }
#endif

