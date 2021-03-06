
// PostfixToIntermediate.cpp : cpp 파일
// 후위표기식을 중간 코드로 변환하는 class
// ㄴ 응 후위아냐 중위야
// 생성자 인자로 받는 list<CStringA>에는 형식에 맞게 후위표기식이 들어가 있다.
// 에러 체크는 모두 InfixToPostfix(중위표기식->후위표기식) 에서 한다.


#include "PostfixToIntermediate.h"
#include "stdafx.h"

//생성자
PostfixToIntermediate::PostfixToIntermediate(std::list<CStringA> Postfix_tmp){		//lv2. input이 잘못되네?
	Postfix = Postfix_tmp;
	//연산자 초기화
	oper[0] = "IF";
	oper[1] = "MINUS";
	oper[2] = "MOD";			//lv2
	oper[3] = "FACT";			//lv2

	//중간코드 만들기
	make_Intermediate();
}

//중간 코드 만드는 함수
void PostfixToIntermediate::make_Intermediate(){
	//리스트가 빌때 까지 앞에서 하나 씩 꺼낸다.
	//(CStringA하나당 후위표기식 라인 하나)
	while (!Postfix.empty())
	{
		//앞부분 line에 복사
		CStringA line = Postfix.front().GetString();  //--- 제대로 안 들어감.
		//list item하나 꺼내기
		Postfix.pop_front();
		//라인 길이						// 문제 찾음. ) 에서 자동으로 끊김.
		linelen = line.GetLength();		// lv2. 문제 : ((3 MINUS 2) MINUS 1) = 12
		//CStrinA char*로 사용하기 위해	//	(1 MINUS (3 MINUS 2)) = 21, <- 이게 맞음.
		linepointer = line.GetBuffer();
		int i = 0;
		//프로그램 시작 부분
		Intermediate.Append("begin\r\n");

		//괄호 인지 확인
		if (linepointer[i] == '('){
			Is_open_parentheses(i);
		}
		//변수 인지 확인
		else if (isalpha(linepointer[i]) || linepointer[i] == '-'){
			Is_val(i);
		}
		//상수 인지 확인
		else if (isdigit(linepointer[i])){
			Is_con(i);
		}
		//프로그램 끝 부분
		Intermediate.Append("end\r\n");
	}
}

//읽은 마지막 index 리턴
//열린 괄호인가?
int PostfixToIntermediate::Is_open_parentheses(int index){//-------------------------또?
	index++;
	bool is_fact = false;
	//* 현 문제, 전방 괄호 2개일때 에러.
	//term1 확인

	//괄호 인지 확인
	if (linepointer[index] == '('){
		index = Is_open_parentheses(index);
	}
	//lv2 팩토리얼인지 확인
	else if (isalpha(linepointer[index+1])) {		//lv2. 버그같은데 +1 하고 있음. 이거 없에기.
		if (Is_fact(index+1)) {
			is_fact = true;
		}
		else
			index = Is_val(index);
	}
	//변수 인지 확인
	else if (isalpha(linepointer[index]) || linepointer[index] == '-'){
		index = Is_val(index);
	}
	//상수 인지 확인
	else if (isdigit(linepointer[index])){
		index = Is_con(index);
	}
	index += 2;
	if (is_fact) {	//lv2 팩토리얼 재점검 
		index--;
		is_fact = false;
	}

	//function 확인
	index = Is_op(index);
//	index++;
	//term2 확인

	//괄호 인지 확인
	if (linepointer[index] == '('){
		index = Is_open_parentheses(index);
	}
	//변수 인지 확인
	else if (isalpha(linepointer[index]) || linepointer[index] == '-'){
		index = Is_val(index);
	}
	//상수 인지 확인
	else if (isdigit(linepointer[index])){
		index = Is_con(index);
	}
//	index ++;




	return index + 1;


}

//index에 문자 들어와야함
//읽은 마지막 index 리턴
//변수인가?
int PostfixToIntermediate::Is_val(int index){
	int i;
	//push
	Intermediate.Append("push ");
	//변수 마지막 index 찾기
	for (i = index; i < linelen; i++){
		if (linepointer[i] == ' '|| linepointer[i] == ')'){
			break;
		}
		else{
			Intermediate.AppendChar(linepointer[i]);
		}
	}
	Intermediate.Append("\r\n");
	return i - 1;
}

//index에 숫자 들어와야함
//읽은 마지막 index 리턴
//상수인가?
int PostfixToIntermediate::Is_con(int index){
	int i;
	//push
	Intermediate.Append("push ");
	//상수 마지막 index 찾기
	for (i = index; i < linelen; i++){
		if (linepointer[i] == ' ' || linepointer[i] == ')'){
			break;
		}
		else{
			Intermediate.AppendChar(linepointer[i]);
		}
	}
	Intermediate.Append("\r\n");
	return i - 1;
}

//index에 문자 들어와야함
//읽은 마지막 index 리턴
//연산자 인가?
int PostfixToIntermediate::Is_op(int index){
	int i, j;
	bool correct;
	for (i = 0; i < (sizeof(oper) / 4); i++){
		//연산자의 길이
		int OP_len = strlen(oper[i]);

		//현재 index 와 연산자 길이의 합이 전체 라인 길이보다 작아야된다.
		//안그러면 실제 짧은 연산자인데 긴 연산자 찾다가 메모리 덤프 날수 있음
		if (index + OP_len < linelen){	// lv2. linelen = '각 변수' 개수. 글자수아님. 요게 틀리네.
			correct = true;
			for (j = 0; j < OP_len; j++){
				if (linepointer[index + j] != oper[i][j]){
					correct = false;
					break;
				}
			}
			//해당연산자 일경우
			if (correct){
				Intermediate.Append(oper[i]);
				break;
			}
		}
	}
	Intermediate.Append("\r\n");
	return index + j + 1 ;		// 런타임 에러 체크 (-1 제거)
}
//lv2 팩토리얼 체킹용
bool PostfixToIntermediate::Is_fact(int index) {
	int j=0;
	bool correct;
		int OP_len = strlen(oper[3]);

		//현재 index 와 연산자 길이의 합이 전체 라인 길이보다 작아야된다.
		//안그러면 실제 짧은 연산자인데 긴 연산자 찾다가 메모리 덤프 날수 있음
		if (index + OP_len < linelen) {
			correct = true;
			for (j = 0; j < OP_len; j++) {
				if (linepointer[index + j] != oper[3][j]) {
					correct = false;
					break;
				}
			}
		}
//	Intermediate.Append("\r\n");
	return correct;		// 런타임 에러 체크 (-1 삭제)
}


//올바른 식들 후위식으로 넘겨줌
CStringA PostfixToIntermediate::getIntermediate(){
	return Intermediate;
}