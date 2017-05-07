
// PL2Dlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include <list>

// CPL2Dlg 대화 상자
class CPL3Dlg : public CDialogEx
{
// 생성입니다.
public:
	CPL3Dlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_PL3_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	//화면 지우기
	afx_msg void OnBnClickedButton1();
	//파일 불러오기
	afx_msg void OnBnClickedButton2();
	//표기법 변환
	afx_msg void OnBnClickedButton3();
	//중간코드 생성
	afx_msg void OnBnClickedButton4();
	//중간코드 저장
	afx_msg void OnBnClickedButton5();
	//중간코드 불러오기
	afx_msg void OnBnClickedButton6();
	//연산 수행
	afx_msg void OnBnClickedButton7();
	//끝내기
	afx_msg void OnBnClickedButton8();


	// <수식입력>
	CString expression_editbox;
	//<표기법 변환/중간코드>
	CString intermediate_code_editbox;
	//<결과값 출력>
	CString result_editbox;
	// <수식입력> 콘트롤
	CEdit expression_editbox_control;
	// <표기법 변환/중간코드> 콘트롤
	CEdit intermediate_code_editbox_control;
	// <결과값 출력> 콘트롤
	CEdit result_editbox_control;

	//InfixToPostfix Class -> 중위 표현식을 후위 표현식으로 바꿔주는 class
	//생성자 인자로 수식입력의 문자열을 넘긴다.
	//이곳에서 실질적인 에러 체크 담당.
	InfixToPostfix *topostfix=NULL;
	//PostfixToIntermediate class-> 후위 표현식을 중간 코드로 바꿔주는 class
	//생성자로 InfixToPostfix Class에서 만든 list<CStringA>(후위표기식 한줄씩 들어가 있다)를 받는다.
	PostfixToIntermediate *tointermediate = NULL;
	//load_intermediate class -> 파일로부터 직접 읽어온 중간 코드를 저장하는 CStringA
	CStringA *load_intermediate = NULL;

	//종료 누를시 호출됨
	virtual void OnCancel();
};
