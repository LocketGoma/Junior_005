
// Interpreter.cpp : cpp ����
// class Interpreter ������
// �߰� �ڵ带 �޾� ����Ѵ�.


#include "Interpreter.h"
#include "stdafx.h"

//�߰��ڵ� ���ڷ� ����
Interpreter::Interpreter(CStringA intermediate_tmp){
	//������ �ʱ�ȭ
	oper[0] = "IF";
	oper[1] = "MINUS";
	intermediate.Append(intermediate_tmp);
	calc();

}

//��� ����
CStringA Interpreter::getResult(){
	return result;
}
//���
void Interpreter::calc()
{
	//��ü ����
	int len = intermediate.GetLength();
	int i;
	//�߰� �ڵ� ����
	char *intermediate_pointer = intermediate.GetBuffer();

	char *token;
	//�Ʒ� �� bool������ true�� �Ǹ� 
	//end ������ ���� ������ ��ū ��� �ǳ� �ٰ� �ȴ�.
	bool undefined=false;
	bool error_program=true;
	std::stack<int> cal_stack;
	std::stack<char*> func_stack;

	for (i = 0; i < len; i++){
		//���� ����
		CStringA line;
		//���� ���� ����
		char *line_pointer;
		//���� �б�
		while (intermediate_pointer[i] != '\n' && intermediate_pointer[i] != NULL){
			line.AppendChar(intermediate_pointer[i]);
			i++;
		}
		line.AppendChar('\n');
		line_pointer = line.GetBuffer();

		//strtok_s ���� �ӽ� ����
		char *temp_token;

		//���� ��ū ������ �б�
		token = strtok_s(line_pointer, "\r\n ", &temp_token);

		//�����
		if (token == NULL){
			continue;
		}

		//�����϶�, undefined false, stack �ʱ�ȭ
		if (!strcmp(token, "begin")){
			undefined = false;
			error_program = false;
			//end ���� begin�ٽ� ������
			if (!cal_stack.empty()){
				while (!cal_stack.empty()){
					cal_stack.pop();
				}
				result.Append("Error code\r\n");
			}
		}
		//Ǫ�� ����
		else if (!strcmp(token, "push")){
			//���� ���� ������ ����
			if (!undefined && !error_program){
				//push �� ��ū ����
				token = strtok_s(NULL, "\r\n ", &temp_token);
				//���
				if (isdigit(token[0]) || token[0] == '-'){
					cal_stack.push(atoi(token));
				}
				//����
				else{
					undefined = true;
				}
			}
		}
		//������									�׷��ϱ�... ������ ������ �±׸� �� (������ ������ ���ڸ� True / �ƴ� False), 3���� ������ ������ ���ѹ�����.
		else if(!strcmp(token,"IF")||!strcmp(token,"MINUS")) {	// ��, ��� ���͵� �����մϴ�
			if (!undefined && !error_program){		 //---- �������
				int cal1, cal2;
				//IF
				if (!strcmp(token, oper[0])){
					func_stack.push(oper[0]); // ������ ���� �����
					//stack�� �ּ� 2���̻��־���Ѵ�.
				}
				//MINUS
				else if (!strcmp(token, oper[1])) {		//-- ���⵵
					func_stack.push(oper[1]);
				}
				//���ǵ��� ���� ������
				else{
					error_program = true;
				}
			}
		}
		else if (!strcmp(token, "end")) {			// end ��� �����ϱ��.
			//���� ���� ��
			if (undefined) {
				result.Append("Undefined\r\n");
			}
			//�߸��� ���α׷�
			else if (error_program) {
				result.Append("Error code\r\n");
			}
			else if (cal_stack.size() > func_stack.size()+1 ) // ���� ������ �����ں��� 2���̻��� �� (������ �ִ� 1�� ���ƾ� ��)
			{
				result.Append("Input Error");
			}
			else // �������̽�
			{
				continue;
			}
		}
		else {
			result.Append("Undefined error\r\n");
		}
	}



	while (!func_stack.empty()) {
		if (!undefined && !error_program) {		 //---- �������
			int cal1, cal2;
			//IF
			char * index;
			index = func_stack.top();
			func_stack.pop();
			if (index==oper[0]) { // IF										  
				if (cal_stack.size() >= 2) { //stack�� �ּ� 2���̻��־���Ѵ�.
					cal2 = cal_stack.top();
					cal_stack.pop();
					cal1 = cal_stack.top();
					cal_stack.pop();
					if (cal1 > 0) {
						cal_stack.push(cal2);
					}
					else {
						cal_stack.push(0);
					}
				}
				//err��
				else {
					error_program = true;
				}
			}
			//MINUS
			else if (index==oper[1]) {		//-- ���⵵
				if (cal_stack.size() >= 2) {
					cal2 = cal_stack.top();
					cal_stack.pop();
					cal1 = cal_stack.top();
					cal_stack.pop();
					cal_stack.push(cal1 - cal2);
				}
				//err��
				else {
					error_program = true;
				}
			}

			//���ǵ��� ���� ������
			else {
				error_program = true;
			}
		}
	}

	if(!cal_stack.empty()){
		int temp = cal_stack.top();
		cal_stack.pop();
			if (cal_stack.empty()) {
				result.AppendFormat("%d\r\n", temp);
			}
			else {
				result.Append("Error code\r\n");
			}
		}



}