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

// CapCRView.h : CCapCRView 클래스의 인터페이스
//

#pragma once
#include "atlimage.h"
#include "CapCRDoc.h"
#include "afxwin.h"
#include "OCR.h"


class CCapCRView : public CFormView
{
protected: // serialization에서만 만들어집니다.
	CCapCRView();
	DECLARE_DYNCREATE(CCapCRView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_CAPCR_FORM };
#endif

// 특성입니다.
public:
	CCapCRDoc* GetDocument() const;

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
	CImage openImage;
	CString sFilename;
	HICON m_hIcon;
	RECT area;
	virtual ~CCapCRView();
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
//	afx_msg void OnClickedButtonCapture();
	afx_msg void OnPaint();
	afx_msg void OnButtonCapture();
	afx_msg void OnButtonRunocr();
//	CString m_strTextbox;
//	CEdit m_editTextbox;
	afx_msg void OnButtonOpenimage();
	afx_msg void OnButtonSavetext();
	COCR* ocr;
	bool m_bOcrEmpty;
	afx_msg void OnCheckIgnoreFix();
	afx_msg void OnCheckIgnoreSpace();
	afx_msg void OnUpdateCheckIgnoreFix(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCheckIgnoreSpace(CCmdUI *pCmdUI);
	bool m_bIgnoreFix;
	bool m_bIgnoreSpace;
	afx_msg void OnButtonTranslate();
	afx_msg void OnButtonSearch();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
//	COCR GetOcrObject();
	COCR* GetOcrObject();
	afx_msg void OnUpdateButtonSavetext(CCmdUI *pCmdUI);
	afx_msg void OnUpdateButtonSearch(CCmdUI *pCmdUI);
	afx_msg void OnUpdateButtonTranslate(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // CapCRView.cpp의 디버그 버전
inline CCapCRDoc* CCapCRView::GetDocument() const
   { return reinterpret_cast<CCapCRDoc*>(m_pDocument); }
#endif

