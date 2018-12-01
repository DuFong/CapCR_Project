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

// CaptureView.h : CCaptureView Ŭ������ �������̽�
//

#pragma once

// ���̾�α� ���� ������ ���� �ڵ�
#define WS_EX_LAYERED           0x00080000
#define LWA_COLORKEY            0x00000001
#define LWA_ALPHA               0x00000002
#define ULW_COLORKEY            0x00000001
#define ULW_ALPHA               0x00000002
#define ULW_OPAQUE              0x00000004 
typedef BOOL(WINAPI* SLWA)(HWND hWnd, COLORREF crKey, BYTE bAlpha, DWORD dwFlags);
// �������


class CCaptureView : public CFormView
{
protected: // serialization������ ��������ϴ�.
	CCaptureView();
	DECLARE_DYNCREATE(CCaptureView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_CAPTURE_FORM };
#endif

// Ư���Դϴ�.
public:
	CCaptureDoc* GetDocument() const;


// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual void OnInitialUpdate(); // ���� �� ó�� ȣ��Ǿ����ϴ�.

// �����Դϴ�.
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

// ������ �޽��� �� �Լ�
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

#ifndef _DEBUG  // CaptureView.cpp�� ����� ����
inline CCaptureDoc* CCaptureView::GetDocument() const
   { return reinterpret_cast<CCaptureDoc*>(m_pDocument); }
#endif

