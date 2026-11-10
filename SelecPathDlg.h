#pragma once


// SelecPathDlg 대화 상자

class SelecPathDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SelecPathDlg)

public:
	SelecPathDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~SelecPathDlg();

	// 메인 다이얼로그에 전달
	CString m_selectedPath;

private:
	// 0: 기존경로 1: 선택 폴더 경로
	int m_pathType;

	// 라디오 버튼 멤버
	CButton m_radioDefault;
	CButton m_radioFolder;

	// 확인 버튼
	CButton m_Confirm;

	CString SelectSaveFolder();
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CVRT_DLG };
#endif

protected:
	// 폰트/ 브러시
	CFont m_Font;
	CBrush m_BgBrush;
	CStatic m_staticSel;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	afx_msg void OnBnClickedRadio(UINT id);
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButtonok();
};
