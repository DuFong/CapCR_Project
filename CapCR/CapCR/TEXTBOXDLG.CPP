
#include "stdafx.h"
#include "CapCR.h"
#include "TextboxDlg.h"
#include "afxdialogex.h"
#include "MainFrm.h"


IMPLEMENT_DYNAMIC(CTextboxDlg, CDialogEx)

CTextboxDlg::CTextboxDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TEXTBOX, pParent)
	, m_strTextbox(_T(""))
{

}

CTextboxDlg::~CTextboxDlg()
{
}

void CTextboxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_TEXTBOX, m_editTextbox);
	DDX_Text(pDX, IDC_EDIT_TEXTBOX, m_strTextbox);
}


BEGIN_MESSAGE_MAP(CTextboxDlg, CDialogEx)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CTEXTBOX 메시지 처리기입니다.


BOOL CTextboxDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	RECT  rectParent;
	CRect rect;


	// 자동을 텍스트 박스 크기 조절.
	((CMainFrame*)AfxGetMainWnd())->GetWindowRect(&rectParent);
	CPoint parentSize;
	parentSize.x = rectParent.right - rectParent.left;
	parentSize.y = rectParent.bottom - rectParent.top;
	SetWindowPos(NULL, 0, 0, parentSize.x-17, 150, SWP_NOREPOSITION);
	GetClientRect(&rect); // 출력할 다이얼로그의 영역을 얻는다.
	CPoint pos;

	// 시작지점 지정
	pos.x = rectParent.left;
	pos.y = parentSize.y;

	// 표시위치 지정
	SetWindowPos(NULL, pos.x + 8, pos.y - 9, 0, 0, SWP_NOSIZE);

	// 폰트 설정
//	m_font.CreatePointFont(150, "굴림");
	m_font.CreateFontA(21, 9, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_CHARACTER_PRECIS, PROOF_QUALITY, DEFAULT_PITCH, _T("한컴 윤체 M"));
	m_editTextbox.SetFont(&m_font);


	CRect editRect;                                                // 에디트 박스 영역
	m_editTextbox.GetWindowRect(editRect);       // 에디트 박스의 스크린 영역을 구한다.

	ScreenToClient(editRect);     // 에디트박스의 스크린영역을 CDialog 객체의 클라이언트 영역 기준으로 변경

	CRect clientRect;
	GetClientRect(clientRect);    // CDialog 객체의 클라이언트 영역을 구한다.

	editRect.right = clientRect.right - 15;    // 클라이언트 영역의 오른쪽에 15픽셀의 공간을 둔다.
	editRect.bottom = clientRect.bottom - 15; // 클라이언트 영역의 하단에 15픽셀의 공간을 둔다.

	m_editTextbox.MoveWindow(editRect); // 에디트 박스의 수정된 위치를 적용한다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CTextboxDlg::OnSize(UINT nType, int cx, int cy)
{
	// 이거 제기능을 못함 ㅜㅠㅠ
	CDialogEx::OnSize(nType, cx, cy);

	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_TEXT);
	if (!pEdit) { return; }

	CRect rect1;
	pEdit->GetWindowRect(&rect1);
	ScreenToClient(&rect1);
	AfxMessageBox(rect1.Width());
	pEdit->MoveWindow(rect1.left, rect1.top, rect1.right - rect1.left, rect1.bottom - rect1.top, TRUE);
	return;

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}
