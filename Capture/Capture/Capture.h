
// Capture.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CCaptureApp:
// �� Ŭ������ ������ ���ؼ��� Capture.cpp�� �����Ͻʽÿ�.
//

class CCaptureApp : public CWinApp
{
public:
	CCaptureApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CCaptureApp theApp;