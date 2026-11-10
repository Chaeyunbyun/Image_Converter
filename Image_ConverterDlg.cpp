
// Image_ConverterDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Image_Converter.h"
#include "Image_ConverterDlg.h"
#include "afxdialogex.h"
#include <vector>
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <string>


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CImageConverterDlg 대화 상자



CImageConverterDlg::CImageConverterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_IMAGE_CONVERTER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CImageConverterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTNOPEN, m_BtnOpenfolder);
	DDX_Control(pDX, IDC_BTNDELETE, m_BtnDelete);
	DDX_Control(pDX, IDC_BTNCONVERTALL, m_BtnConvertAll);
	DDX_Control(pDX, IDC_FILELIST, m_FileList);
	DDX_Control(pDX, IDC_CB_EXTENSION, m_CbExtension);
	DDX_Control(pDX, IDC_ST_EXTENSION, m_StExtension);

}

BEGIN_MESSAGE_MAP(CImageConverterDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTNOPEN, &CImageConverterDlg::OnBnClickedBtnopen)
	ON_BN_CLICKED(IDC_BTNDELETE, &CImageConverterDlg::OnBnClickedBtndelete)
	ON_BN_CLICKED(IDC_BTNCONVERTALL, &CImageConverterDlg::OnBnClickedBtnconvertall)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CImageConverterDlg 메시지 처리기

BOOL CImageConverterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// 다이얼로그 크기 설정
	MoveWindow(100, 100, 1000, 800);

	// 크기 조절 스타일 제거
	LONG_PTR style = GetWindowLongPtr(m_hWnd, GWL_STYLE);
	style &= ~WS_THICKFRAME;
	SetWindowLongPtr(m_hWnd, GWL_STYLE, style);

	// 프레임 갱신
	SetWindowPos(
		nullptr, 0, 0, 0, 0,
		SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED
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

	m_BgBrush.CreateSolidBrush(RGB(250, 250, 250));

	// 타이틀
	SetWindowTextW(L"멀티 이미지 컨버터");

	const int btnWidth = 200;
	const int btnHeight = 70;
	const int gap = 40;
	const int startX = 30;
	const int startY = 35;

	// 버튼
	m_BtnOpenfolder.MoveWindow(
		startX, startY, btnWidth, btnHeight);

	m_BtnDelete.MoveWindow(
		startX + (btnWidth + gap), startY, btnWidth, btnHeight);

	m_CbExtension.MoveWindow(
		startX + 3 * (btnWidth + gap)-15, startY, btnWidth, btnHeight);

	m_StExtension.MoveWindow(
		startX + 3 * (btnWidth + gap)-68, startY + 5, btnWidth, btnHeight);

	m_BtnConvertAll.MoveWindow(
		startX + 3 * (btnWidth + gap) -15, startY + 600, btnWidth, btnHeight);

	m_Font.CreatePointFont(90, _T("맑은 고딕"));
	m_CbExtension.SetFont(&m_Font);
	m_BtnOpenfolder.SetFont(&m_Font);
	m_BtnDelete.SetFont(&m_Font);
	m_BtnConvertAll.SetFont(&m_Font);
	m_StExtension.SetFont(&m_Font);

	m_BtnOpenfolder.SetWindowText(_T("파일 선택"));
	m_BtnDelete.SetWindowText(_T("삭제"));
	m_BtnConvertAll.SetWindowText(_T("이미지 변환"));
	m_StExtension.SetWindowText(_T("형식:"));

	// 리스트 컨트롤
	const int listWidth = 900;
	const int listHeight = 430;
	const int lstartX = 30;
	const int lstartY = 180;

	m_FileList.MoveWindow(lstartX, lstartY, listWidth, listHeight);

	m_FileList.SetExtendedStyle(
		LVS_EX_FULLROWSELECT |
		LVS_EX_GRIDLINES |
		LVS_EX_CHECKBOXES |
		LVS_EX_DOUBLEBUFFER
	);

	// 컬럼 추가
	m_FileList.InsertColumn(0, _T("  파일명"), LVCFMT_LEFT, 200);
	m_FileList.InsertColumn(1, _T("경로"), LVCFMT_LEFT, 700);

	//(0: jpg, 1 : jpeg, 2 : png, 3 : bmp, 4 : gif);
	std::vector<CString> vecExtension = {L"jpg", L"jpeg", L"png", L"bmp" , L"gif"};
	for (int i = 0; i < vecExtension.size(); i++)
	{
		m_CbExtension.AddString(vecExtension[i]);
	}
	m_CbExtension.SetCurSel(0);

	ConvertImageFile m_CvrtImg;
	SelecPathDlg m_PathDlg;

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CImageConverterDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CImageConverterDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		//dc.DrawIcon(x, y, m_hIcon);

	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CImageConverterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CImageConverterDlg::OnBnClickedBtnopen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	static TCHAR BASED_CODE szFilter[] =
		_T("이미지 파일 (*.BMP;*.GIF;*.JPG;*.JPEG;*.PNG)|")
		_T("*.BMP;*.GIF;*.JPG;*.JPEG;*.PNG;*.bmp;*.gif;*.jpg;*.jpeg;*.png|")
		_T("모든 파일 (*.*)|*.*||");

	CFileDialog dlg(TRUE, _T("*.jpg"), _T("image"), OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY, szFilter);
	// 다중 선택 시 리스트에 파일 목록 추가

	if (IDOK == dlg.DoModal())

	{
		for (POSITION pos = dlg.GetStartPosition(); pos != NULL;)
		{
			CString pathName = dlg.GetNextPathName(pos);

			int nPos = pathName.ReverseFind(_T('\\'));
			CString fileName = pathName.Mid(nPos + 1);

			if (!isDuplicatedFile(pathName))
			{
				int nIndex = m_FileList.InsertItem(m_FileList.GetItemCount(), fileName);
				m_FileList.SetItemText(nIndex, 1, pathName);
				m_FileList.SetCheck(nIndex, TRUE);
			}
		}
	}
}


void CImageConverterDlg::OnBnClickedBtndelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	for (int i = m_FileList.GetItemCount() - 1; i >= 0; i--)
	{
		if (m_FileList.GetCheck(i))
		{
			m_FileList.DeleteItem(i);
		}
	}
}


void CImageConverterDlg::OnBnClickedBtnconvertall()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 경로 선택 다이얼로그
	CString strPath;
	if (m_FileList.GetItemCount() == 0)
	{
		return;
	}
	if (m_PathDlg.DoModal() == IDOK)
	{
		strPath = m_PathDlg.m_selectedPath;
		bool blsuccess = true;
		for (int i = m_FileList.GetItemCount() - 1; i >= 0; i--)
		{
			if (m_FileList.GetCheck(i))
			{

				CString strFileName = m_FileList.GetItemText(i, 0);
				CString strFilePath = m_FileList.GetItemText(i, 1);

				Gdiplus::Image image(strFilePath);

				if (image.GetLastStatus() != Gdiplus::Ok)
				{
					AfxMessageBox(_T("이미지를 불러올 수 없습니다."));
					return;
				}

				CRect imageRect(
					0,
					0,
					image.GetWidth(),
					image.GetHeight()
				);

				int intComboidx = m_CbExtension.GetCurSel();
				CString strExtension;
				if (intComboidx == 0)
				{
					strExtension = ".jpg";
				}
				if (intComboidx == 1)
				{
					strExtension = ".jpeg";
				}
				if (intComboidx == 2)
				{
					strExtension = ".png";
				}
				if (intComboidx == 3)
				{
					strExtension = ".bmp";
				}
				if (intComboidx == 4)
				{
					strExtension = ".gif";
				}

				// 마지막 '\' 위치 찾기
				int nPos = strFilePath.ReverseFind(_T('\\'));

				// 디렉터리 경로 추출
				CString strDirectory = strFilePath.Left(nPos + 1);

				// 새 파일명 생성
				CString strTargetName = ExtractfileName(strFileName) + strExtension;
				CString strTargetPath;

				// 디폴트: 디렉터리 + 새 파일명
				if (strPath == "default")
				{
					strTargetPath = strDirectory + strTargetName;

				}
				// 폴더 선택한 경우
				else
				{
					strPath += "//";
					strTargetPath = strPath + strTargetName;
				}

				if (!m_CvrtImg.ConvertImagExtension(strFilePath, strTargetPath, imageRect, intComboidx))
				{
					blsuccess = false;
				}
			}
		}
		if (blsuccess)
		{
			OnBnClickedBtndelete();
			AfxMessageBox(_T("이미지 변환 성공!"), MB_OK | MB_ICONINFORMATION);
		}
		else
		{
			AfxMessageBox(_T("변환 실패"), MB_OK | MB_ICONERROR);
		}
	}
}

// 파일 중복 등록 방지
bool CImageConverterDlg::isDuplicatedFile(CString pathName)
{
	bool bDuplicate = false;
	for (int i = 0; i < m_FileList.GetItemCount(); i++)
	{
		CString existingPath = m_FileList.GetItemText(i, 1);
		if (existingPath.CompareNoCase(pathName) == 0)
		{
			bDuplicate = true;
			break;
		}
	}
	return bDuplicate;
}

CString CImageConverterDlg::ExtractfileName(CString str)
{
	CString res = L"";

	for (int i = 0; i < str.GetLength(); i++)
	{
		if (str[i] == '.')
		{
			break;
		}
		else
		{
			res += str[i];
		}
	}

	return res;
}

HBRUSH CImageConverterDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	switch (nCtlColor) {

	case CTLCOLOR_DLG:   
	{
		return (HBRUSH)m_BgBrush.GetSafeHandle();
	}
	case CTLCOLOR_BTN:   
	{
		//return CreateSolidBrush(RGB(100, 150, 170));
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
