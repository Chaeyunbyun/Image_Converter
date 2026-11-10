// SelecPathDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Image_Converter.h"
#include "SelecPathDlg.h"
#include "afxdialogex.h"


// SelecPathDlg 대화 상자

IMPLEMENT_DYNAMIC(SelecPathDlg, CDialogEx)

SelecPathDlg::SelecPathDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CVRT_DLG, pParent)
	, m_pathType(0)
{

}

SelecPathDlg::~SelecPathDlg()
{
}

void SelecPathDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_ST_SELECT, m_staticSel);
	DDX_Radio(pDX, IDC_RADIO_DEFAULT, m_pathType);
	DDX_Control(pDX, IDC_RADIO_DEFAULT, m_radioDefault);
	DDX_Control(pDX, IDC_RADIO_SLFOLDER, m_radioFolder);
	DDX_Control(pDX, IDC_BUTTON_ok, m_Confirm);

}


BEGIN_MESSAGE_MAP(SelecPathDlg, CDialogEx)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO_DEFAULT, IDC_RADIO_SLFOLDER, &SelecPathDlg::OnBnClickedRadio)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_ok, &SelecPathDlg::OnBnClickedButtonok)
END_MESSAGE_MAP()

// 저장 폴더 선택하기
CString SelecPathDlg::SelectSaveFolder()
{
	BROWSEINFO BrInfo;
	TCHAR szBuffer[512];

	::ZeroMemory(&BrInfo, sizeof(BROWSEINFO));
	::ZeroMemory(szBuffer, 512);

	BrInfo.hwndOwner = GetSafeHwnd();
	BrInfo.lpszTitle = _T("폴더 선택");
	BrInfo.ulFlags = BIF_NEWDIALOGSTYLE | BIF_EDITBOX | BIF_RETURNONLYFSDIRS;
	LPITEMIDLIST pItemIdList = ::SHBrowseForFolder(&BrInfo);
	::SHGetPathFromIDList(pItemIdList, szBuffer);

	// 경로를 가져와 사용할 경우, Edit Control 에 값 저장
	CString str;
	str.Format(_T("%s"), szBuffer);
	return str;
}

afx_msg void SelecPathDlg::OnBnClickedRadio(UINT id)
{
	switch (id)
	{
	case IDC_RADIO_DEFAULT:
		m_pathType = 0;
		// do something...
		break;
	case IDC_RADIO_SLFOLDER:
		m_pathType = 1;
		// do something...
		break;
	default:
		break;
	}
}

BOOL SelecPathDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
		// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.

	// 다이얼로그 크기 설정
	MoveWindow(100, 100, 500, 400);

	// 크기 조절 스타일 제거
	LONG_PTR style = GetWindowLongPtr(m_hWnd, GWL_STYLE);
	style &= ~WS_THICKFRAME;
	SetWindowLongPtr(m_hWnd, GWL_STYLE, style);

	CRect rect;
	GetParent()->GetWindowRect(&rect);

	// 부모 다이얼로그와 동일한 위치로 이동
	SetWindowPos(
		NULL,
		rect.left,
		rect.top,
		0,
		0,
		SWP_NOSIZE | SWP_NOZORDER
	);


	COLORREF titleColor = RGB(100, 140, 180);
	COLORREF textColor = RGB(245, 255, 255);

	DwmSetWindowAttribute(
		GetSafeHwnd(),
		DWMWA_CAPTION_COLOR,
		&titleColor,
		sizeof(titleColor)
	);

	DwmSetWindowAttribute(
		GetSafeHwnd(),
		DWMWA_TEXT_COLOR,
		&textColor,
		sizeof(textColor)
	);

	if (!m_Font.GetSafeHandle())
		m_Font.CreatePointFont(90, _T("맑은 고딕"));

	if (!m_BgBrush.GetSafeHandle())
		m_BgBrush.CreateSolidBrush(RGB(250, 250, 250));

	// 타이틀
	SetWindowTextW(L"변환 후 파일 경로 선택");

	m_staticSel.SetFont(&m_Font);
	m_radioDefault.SetFont(&m_Font);
	m_radioFolder.SetFont(&m_Font);
	m_Confirm.SetFont(&m_Font);

	m_staticSel.SetWindowTextW(L"경로 선택");
	m_radioDefault.SetWindowTextW(L"기존 경로");
	m_radioFolder.SetWindowTextW(L"폴더 선택");
	m_Confirm.SetWindowTextW(L"확인");

	const int btnWidth = 200;
	const int btnHeight = 70;
	const int gap = 40;
	const int startX = 30;
	const int startY = 35;

	// 텍스트
	m_staticSel.MoveWindow(
		startX, startY, btnWidth, btnHeight);

	// 라디오
	m_radioDefault.MoveWindow(
		startX , startY + gap, btnWidth, btnHeight);
	m_radioFolder.MoveWindow(
		startX + gap *5, startY + gap, btnWidth, btnHeight);

	// 버튼
	m_Confirm.MoveWindow(
		startX + gap *5, startY + gap *5, btnWidth, btnHeight);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


HBRUSH SelecPathDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	switch (nCtlColor) {

	case CTLCOLOR_DLG:   /// 다이얼로그 배경색을 white로.
	{
		return (HBRUSH)m_BgBrush.GetSafeHandle();
	}
	case CTLCOLOR_BTN:    // 버튼의 배경색을 투명으로...
	{
		if (pWnd->GetDlgCtrlID() == IDC_RADIO_DEFAULT ||
			pWnd->GetDlgCtrlID() == IDC_RADIO_SLFOLDER)
		{
			pDC->SetTextColor(RGB(0, 0, 0));  // static text 글자색 변경
			pDC->SetBkMode(TRANSPARENT);   // static text 배경색 투명

		}
		break;
	}

	case CTLCOLOR_STATIC:

	{
		pDC->SetTextColor(RGB(0, 0, 0));  // static text 글자색 변경
		pDC->SetBkMode(TRANSPARENT);   // static text 배경색 투명
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}

	}
	return hbr;
}


void SelecPathDlg::OnBnClickedButtonok()
{
	//// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 기존 경로
	if (m_pathType == 0)
	{
		m_selectedPath = "default";
	}
	// 파일 선택하기
	else
	{
		m_selectedPath = SelectSaveFolder();
	}
	EndDialog(IDOK);
}
