
// CaptureDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "Capture.h"
#include "CaptureDlg.h"
#include "afxdialogex.h"
#include "CanvasDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.




class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCaptureDlg ��ȭ ����



CCaptureDlg::CCaptureDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CAPTURE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCaptureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	
}

BEGIN_MESSAGE_MAP(CCaptureDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CAPTURE, &CCaptureDlg::OnClickedButtonCapture)

END_MESSAGE_MAP()


// CCaptureDlg �޽��� ó����

BOOL CCaptureDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CCaptureDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CCaptureDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

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
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CCaptureDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCaptureDlg::OnClickedButtonCapture()
{
	if (Image != NULL)
		Image.Destroy();


	CString imgName = _T("Desktop.jpg");
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CanvasDlg canvas;
	canvas.DoModal();

	RECT area = canvas.GetClipRect();
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

	// Image.Save(imgName, Gdiplus::ImageFormatJPEG);

    
     //CStatic *staticSize = (CStatic*)GetDlgItem(AFX_IDC_PICTURE);
    // CRect rect2;

	// staticSize->GetClientRect(rect2);
	   //Image.Load(imgName);
	
	Image.BitBlt(dc.m_hDC, 0, 0);
	
	Image.Save(imgName, Gdiplus::ImageFormatJPEG);


	   // �� ������ ������ �ش�. 

	
	/*::ShellExecute(NULL,
		TEXT("open"), TEXT("Desktop.jpg"),
		NULL, NULL, SW_SHOW);
		*/
		

}


