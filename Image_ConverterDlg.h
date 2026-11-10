
// Image_ConverterDlg.h: 헤더 파일
//
#include "ConvertImageFile.h"
#include "SelecPathDlg.h"
#pragma once


// CImageConverterDlg 대화 상자
class CImageConverterDlg : public CDialogEx
{
// 생성입니다.
public:
	CImageConverterDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IMAGE_CONVERTER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 버튼
	CButton m_BtnOpenfolder;
	CButton m_BtnDelete;
	CButton m_BtnConvertAll;

	// 텍스트
	CStatic m_StExtension;

	// 리스트 컨트롤
	CListCtrl m_FileList;

	// 콤보 박스
	CComboBox m_CbExtension;

	// 폰트/ 브러시
	CFont m_Font;
	CBrush m_BgBrush;

	bool isDuplicatedFile(CString Filename);
	CString ExtractfileName(CString str);
	ConvertImageFile m_CvrtImg;
	SelecPathDlg m_PathDlg;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnopen();
	afx_msg void OnBnClickedBtndelete();
	afx_msg void OnBnClickedBtnconvertall();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
