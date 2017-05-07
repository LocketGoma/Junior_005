
// PL2Dlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "PL3.h"
#include "PL3Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPL3Dlg 대화 상자



CPL3Dlg::CPL3Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPL3Dlg::IDD, pParent)
	, expression_editbox(_T(""))
	, intermediate_code_editbox(_T(""))
	, result_editbox(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPL3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, expression_editbox);
	DDX_Text(pDX, IDC_EDIT2, intermediate_code_editbox);
	DDX_Text(pDX, IDC_EDIT3, result_editbox);
	DDX_Control(pDX, IDC_EDIT1, expression_editbox_control);
	DDX_Control(pDX, IDC_EDIT2, intermediate_code_editbox_control);
	DDX_Control(pDX, IDC_EDIT3, result_editbox_control);
}

BEGIN_MESSAGE_MAP(CPL3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CPL3Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CPL3Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CPL3Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CPL3Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CPL3Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CPL3Dlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CPL3Dlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CPL3Dlg::OnBnClickedButton8)
END_MESSAGE_MAP()


// CPL3Dlg 메시지 처리기

BOOL CPL3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CPL3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CPL3Dlg::OnPaint()
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
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CPL3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//화면 지우기
void CPL3Dlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	//현재 다이얼로그 edit box 상태 불러오기
	UpdateData(TRUE);
	// <수식입력> 초기화
	expression_editbox.Format(_T(""));
	//<표기법 변환/중간코드>
	intermediate_code_editbox.Format(_T(""));
	//<결과값 출력>
	result_editbox.Format(_T(""));
	//변경 내용 적용
	UpdateData(FALSE);

	//후위 표기 초기화
	if (topostfix != NULL){
		delete topostfix;
		topostfix = NULL;
	}
	//중간 코드 초기화
	if (tointermediate != NULL){
		delete tointermediate;
		tointermediate = NULL;
	}
	//불러온 중간 코드 초기화
	if (load_intermediate != NULL){
		delete load_intermediate;
		load_intermediate = NULL;
	}


}

//파일 불러오기
void CPL3Dlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.


	//불러올 경로 지정하기 위한 CFileDiaglog형 class 
	CFileDialog fDlg(true, _T("txt"), _T("infix.txt"), OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, _T("텍스트파일(*.txt)|*.txt|"));

	//파일 경로를 불러오는 다이얼로그 호출
	//정상적으로 파일 경로가 얻어 졌으면
	//파일 불러오기시작
	if (IDOK == fDlg.DoModal())
	{
		//파일 디스크립터
		CFile savefile;

		//경로명 저장될 변수
		CString Pathname = fDlg.GetPathName();

		//파일 내용 저장할 버퍼
		CStringA tmp;


		//읽어드린 버퍼의 index;
		int index = 0;

		//파일 열기
		if (!savefile.Open(Pathname, CFile::modeRead))
		{
			MessageBox(_T("파일을 열수 없습니다."), _T(""), MB_OK);
			return;
		}

		//CStringA를 char형 포인터 처럼 이용할때 필요한 char형 포인터
		char* wheretmp;

		//세이브 파일의 크기
		int lenfile = (int)savefile.GetLength();

		//CString class를 char배열 처럼 사용
		//세이브 파일 크기 만큼 버퍼 염
		wheretmp = tmp.GetBuffer(lenfile+1);

		//파일 전부를 버퍼에 씀
		savefile.Read(wheretmp, lenfile);

		
		//마지막에 NULL넣어줌
		wheretmp[lenfile] = NULL;		
		
		//파일 닫기
		savefile.Close();

		//남은 공간 해제
		tmp.ReleaseBuffer();
		
		//CStringA를 CString형으로
		CString tmp2(tmp);


		//현재 다이얼로그 edit box 상태 불러오기
		UpdateData(TRUE);
		//기존 입력된 문자가 있을시 이어 붙일지 아니면 지우고 새로 불러올지 정할수 있다.
		if ((expression_editbox.GetLength() != 0)){
			if (MessageBox(_T("입력된 문자열이 있습니다\n이어 붙이시겠습니까?"), _T(""), MB_YESNO | MB_ICONQUESTION) == IDNO){
				expression_editbox.Format(_T(""));				
			}
			//이어 붙일때 개행한번 해주고 이어 붙임
			else{
				expression_editbox.Append(_T("\r\n"));
			}
		}
		//읽어온 파일을 edit box에 기록한다.
		expression_editbox.Append(tmp2);

		//변경된 edit box에 적용
		UpdateData(FALSE);

		//스크롤 edit box 마지막으로 보내기
		expression_editbox_control.LineScroll(expression_editbox_control.GetLineCount());		
	}



}

//표기법 변환
void CPL3Dlg::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	//현재 다이얼로그 edit box 상태 불러오기
	UpdateData(TRUE);
	//<수식입력>에 입력된 것이 있나?
	if ((expression_editbox.GetLength() != 0)){
		//topostfix가 있다면 기존것 메모리 해제
		if (topostfix != NULL){
			delete topostfix;
			topostfix = NULL;
		}
		//중간 코드 초기화
		if (tointermediate != NULL){
			delete tointermediate;
			tointermediate = NULL;
		}
		//불러온 중간 코드 초기화
		if (load_intermediate != NULL){
			delete load_intermediate;
			load_intermediate = NULL;
		}

		//InfixToPostfix class생성
		topostfix = new InfixToPostfix(expression_editbox);
		//임시tmp에 <표기법변환/중간코드>에 띄어줄 메세지 받어옴
		CString tmp = topostfix->getMessage_Postfix();
		//기존것 내용지우고 받아온 메세지 집어넣음
		intermediate_code_editbox.Format(_T(""));
		intermediate_code_editbox.Append(tmp);
		//만약 입력에 성공한 식이 없다면
		if (topostfix->getPostfix().empty()){
			MessageBox(_T("입력된 식이 없거나, 올바른 식이 하나도 없습니다."), _T(""), MB_OK);
		}
		//결과 박스 초기화
		result_editbox.Format(_T(""));
		//변경된 내용 edit박스에 적용
		UpdateData(FALSE);

		//스크롤 edit box 마지막으로 보내기
		intermediate_code_editbox_control.LineScroll(expression_editbox_control.GetLineCount());

	}
	//<수식입력>에 입력된것 없을때
	else{
		MessageBox(_T("입력된 것이 없습니다"), _T(""), MB_OK);
	}
}

//중간코드 생성
void CPL3Dlg::OnBnClickedButton4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//후기식으로 변환되었나?
	if (topostfix != NULL){
		//아무것도 없는 상태에서 후기식 변환 눌렀을 때
		if (topostfix->getPostfix().empty()){
			MessageBox(_T("입력된 식(후위식)이 없습니다."), _T(""), MB_OK);
			return;
		}

		//기존 중간 코드 초기화
		if (tointermediate != NULL){
			delete tointermediate;
			tointermediate = NULL;
		}
		//불러온 중간 코드 초기화
		if (load_intermediate != NULL){
			delete load_intermediate;
			load_intermediate = NULL;
		}

		//PostfixToIntermediate class 생성
		tointermediate = new PostfixToIntermediate(topostfix->getPostfix());
		//기존것 내용지우고 받아온 메세지 집어넣음
		intermediate_code_editbox.Format(_T(""));

		// 올바른 후위식만 출력 (list에 저장된 후위식들 하나씩 꺼내서 templist에 넣음)
		std::list<CStringA> liststring;
		liststring = topostfix->getPostfix();

		CStringA templist;
		while (!liststring.empty())
		{
			templist.Append(liststring.front().GetString());
			templist.Append("\r\n");
			liststring.pop_front();
		}
		//templist를 intermediate_code_editbox에 넣기
		CString tmp(templist);
		intermediate_code_editbox.Append(tmp);
		intermediate_code_editbox.Append(_T("\r\n"));

		//중간코드
		CString tmp1(tointermediate->getIntermediate());
		intermediate_code_editbox.Append(tmp1);


		//결과 박스 초기화
		result_editbox.Format(_T(""));

		//변경된 내용 edit박스에 적용
		UpdateData(FALSE);

		//스크롤 edit box 마지막으로 보내기
		intermediate_code_editbox_control.LineScroll(intermediate_code_editbox_control.GetLineCount());

	}
	else{
		MessageBox(_T("입력된 식(후위식)이 없습니다."), _T(""), MB_OK);
		return;
	}

}

//중간코드 저장
void CPL3Dlg::OnBnClickedButton5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//중간코드로 변환된 것 있을 때
	if (tointermediate != NULL){
		//파일 경로 불러오기 위한 CFileDialog class 
		CFileDialog fDlg(false, _T("txt"), _T("inteCode.txt"), OFN_OVERWRITEPROMPT, _T("텍스트파일(*.txt)|*.txt|"));

		//다이얼로그 호출
		if (IDOK == fDlg.DoModal())
		{
			//경로명 저장
			CString Pathname = fDlg.GetPathName();
			//파일 디스크립터
			CFile savefile;

			//파일을 열기
			if (!savefile.Open(Pathname, CFile::modeWrite | CFile::modeCreate))
			{
				MessageBox(_T("파일을 열수 없습니다."), _T(""), MB_OK);
				return;
			}

			CStringA tmpS(tointermediate->getIntermediate());
			//파일에 쓰기
			savefile.Write(tmpS, tmpS.GetLength());

			//파일 닫기
			savefile.Close();

		}

	}
	else{
		MessageBox(_T("중간 코드가 생성 되지 않았습니다.\n(불러온 중간 코드는 저장하지 못합니다.)"), _T(""), MB_OK);
	}
}

//중간코드 불러오기
void CPL3Dlg::OnBnClickedButton6()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	//불러올 경로 지정하기 위한 CFileDiaglog형 class 
	CFileDialog fDlg(true, _T("txt"), _T("inteCode.txt"), OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, _T("텍스트파일(*.txt)|*.txt|"));

	//파일 경로를 불러오는 다이얼로그 호출
	//정상적으로 파일 경로가 얻어 졌으면
	//파일 불러오기시작
	if (IDOK == fDlg.DoModal())
	{
		//파일 디스크립터
		CFile savefile;

		//경로명 저장될 변수
		CString Pathname = fDlg.GetPathName();

		//파일 내용 저장할 버퍼
		CStringA tmp;


		//읽어드린 버퍼의 index;
		int index = 0;

		//파일 열기
		if (!savefile.Open(Pathname, CFile::modeRead))
		{
			MessageBox(_T("파일을 열수 없습니다."), _T(""), MB_OK);
			return;
		}

		//CStringA를 char형 포인터 처럼 이용할때 필요한 char형 포인터
		char* wheretmp;

		//세이브 파일의 크기
		int lenfile = (int)savefile.GetLength();

		//CString class를 char배열 처럼 사용
		//세이브 파일 크기 만큼 버퍼 염
		wheretmp = tmp.GetBuffer(lenfile + 1);

		//파일 전부를 버퍼에 씀
		savefile.Read(wheretmp, lenfile);		

		//마지막에 NULL넣어줌
		wheretmp[lenfile] = NULL;

		//파일 닫기
		savefile.Close();

		//남은 공간 해제
		tmp.ReleaseBuffer();

		//로드 된 것 있으면 초기화
		if (load_intermediate != NULL)
		{
			delete load_intermediate;
			load_intermediate = NULL;
		}
		//기존의 중간코드와 후위식 메모리 해제
		if (tointermediate != NULL){
			delete tointermediate;
			tointermediate = NULL;
		}		
		if (topostfix != NULL){
			delete topostfix;
			topostfix = NULL;
		}

		//세이브 파일 저장
		load_intermediate = new CStringA(tmp);

		//CStringA를 CString형으로 (화면에 뿌리기 위해)
		CString tmp2(tmp);
		//현재 다이얼로그 edit box 상태 불러오기
		UpdateData(TRUE);

		//읽어온 파일을 edit box에 기록한다.

		intermediate_code_editbox.Format(_T(""));
		intermediate_code_editbox.Append(tmp2);


		//기존 결과 초기화
		result_editbox.Format(_T(""));

		//변경된 edit box에 적용
		UpdateData(FALSE);

		//스크롤 edit box 마지막으로 보내기
		intermediate_code_editbox_control.LineScroll(intermediate_code_editbox_control.GetLineCount());
	}
}

//연산 수행
void CPL3Dlg::OnBnClickedButton7()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (tointermediate != NULL){


		//현재 다이얼로그 edit box 상태 불러오기
		UpdateData(TRUE);

		//result editbox 초기화
		result_editbox.Format(_T(""));
		//Interpreter class 생성
		Interpreter in(tointermediate->getIntermediate());
		//결과 받아오기
		CString temp(in.getResult());
		//출력
		result_editbox.Format(_T(""));
		result_editbox.Append(temp);

		//변경된 내용 edit박스에 적용
		UpdateData(FALSE);
		//스크롤 edit box 마지막으로 보내기
		result_editbox_control.LineScroll(result_editbox_control.GetLineCount());
		//스크롤 edit box 마지막으로 보내기 (??? 버그 같음 Intermediate 스코롤이 변경됨? )
		intermediate_code_editbox_control.LineScroll(intermediate_code_editbox_control.GetLineCount());

	}
	else if (load_intermediate != NULL){
		//현재 다이얼로그 edit box 상태 불러오기
		UpdateData(TRUE);

		//result editbox 초기화
		result_editbox.Format(_T(""));
		//Interpreter class 생성
		Interpreter in(*load_intermediate);
		//결과 받아오기
		CString temp(in.getResult());
		//출력
		result_editbox.Format(_T(""));
		result_editbox.Append(temp);

		//변경된 내용 edit박스에 적용
		UpdateData(FALSE);
		//스크롤 edit box 마지막으로 보내기
		result_editbox_control.LineScroll(result_editbox_control.GetLineCount());
		//스크롤 edit box 마지막으로 보내기 (??? 버그 같음 Intermediate 스코롤이 변경됨? )
		intermediate_code_editbox_control.LineScroll(intermediate_code_editbox_control.GetLineCount());

	}
	else{
		MessageBox(_T("입력된 중간코드가 없습니다."), _T(""), MB_OK);
		return;
	}

}

//끝내기
void CPL3Dlg::OnBnClickedButton8()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//종료 메세지 전달(Oncancel 호출)
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_APP_EXIT, NULL);
}


void CPL3Dlg::OnCancel()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (MessageBox(_T("종료하시겠습니까?"), _T(""), MB_YESNO | MB_ICONQUESTION) == IDYES){
		//후위 표기 초기화
		if (topostfix != NULL){
			delete topostfix;
			topostfix = NULL;
		}
		//중간 코드 초기화
		if (tointermediate != NULL){
			delete tointermediate;
			tointermediate = NULL;
		}
		//불러온 중간 코드 초기화
		if (load_intermediate != NULL){
			delete load_intermediate;
			load_intermediate = NULL;
		}
		CDialogEx::OnCancel();
	}
}
