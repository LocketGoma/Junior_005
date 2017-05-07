
// PostfixToIntermediate.cpp : cpp ����
// ����ǥ����� �߰� �ڵ�� ��ȯ�ϴ� class
// �� �� �����Ƴ� ������
// ������ ���ڷ� �޴� list<CStringA>���� ���Ŀ� �°� ����ǥ����� �� �ִ�.
// ���� üũ�� ��� InfixToPostfix(����ǥ���->����ǥ���) ���� �Ѵ�.


#include "PostfixToIntermediate.h"
#include "stdafx.h"

//������
PostfixToIntermediate::PostfixToIntermediate(std::list<CStringA> Postfix_tmp){
	Postfix = Postfix_tmp;
	//������ �ʱ�ȭ
	oper[0] = "IF";
	oper[1] = "MINUS";
	oper[2] = "MOD";			//lv2
	oper[3] = "FACT";			//lv2

	//�߰��ڵ� �����
	make_Intermediate();
}

//�߰� �ڵ� ����� �Լ�
void PostfixToIntermediate::make_Intermediate(){
	//����Ʈ�� ���� ���� �տ��� �ϳ� �� ������.
	//(CStringA�ϳ��� ����ǥ��� ���� �ϳ�)
	while (!Postfix.empty())
	{
		//�պκ� line�� ����
		CStringA line = Postfix.front().GetString();  //--- ����� �� ������.
		//list item�ϳ� ������
		Postfix.pop_front();
		//���� ����
		linelen = line.GetLength();
		//CStrinA char*�� ����ϱ� ����
		linepointer = line.GetBuffer();
		int i = 0;
		//���α׷� ���� �κ�
		Intermediate.Append("begin\r\n");

		//��ȣ ���� Ȯ��
		if (linepointer[i] == '('){
			Is_open_parentheses(i);
		}
		//���� ���� Ȯ��
		else if (isalpha(linepointer[i]) || linepointer[i] == '-'){
			Is_val(i);
		}
		//��� ���� Ȯ��
		else if (isdigit(linepointer[i])){
			Is_con(i);
		}
		//���α׷� �� �κ�
		Intermediate.Append("end\r\n");
	}
}

//���� ������ index ����
//���� ��ȣ�ΰ�?
int PostfixToIntermediate::Is_open_parentheses(int index){//-------------------------��?
	index++;
	bool is_fact = false;

	//term1 Ȯ��

	//��ȣ ���� Ȯ��
	if (linepointer[index] == '('){
		index = Is_open_parentheses(index);
	}
	//lv2 ���丮������ Ȯ��
	else if (isalpha(linepointer[index+1])) {
		if (Is_fact(index+1)) {
			is_fact = true;
			index += Is_fact(index);
		}
		else
			index = Is_val(index);
	}
	//���� ���� Ȯ��
	else if (isalpha(linepointer[index]) || linepointer[index] == '-'){
		index = Is_val(index);
	}
	//��� ���� Ȯ��
	else if (isdigit(linepointer[index])){
		index = Is_con(index);
	}
	index += 2;
	if (is_fact) {	//lv2 ���丮�� ������
		index -= 2;
	}

	//function Ȯ��
	index = Is_op(index);
	index++;
	//term2 Ȯ��

	//��ȣ ���� Ȯ��
	if (linepointer[index] == '('){
		index = Is_open_parentheses(index);
	}
	//���� ���� Ȯ��
	else if (isalpha(linepointer[index]) || linepointer[index] == '-'){
		index = Is_val(index);
	}
	//��� ���� Ȯ��
	else if (isdigit(linepointer[index])){
		index = Is_con(index);
	}
	index ++;




	return index + 1;


}

//index�� ���� ���;���
//���� ������ index ����
//�����ΰ�?
int PostfixToIntermediate::Is_val(int index){
	int i;
	//push
	Intermediate.Append("push ");
	//���� ������ index ã��
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

//index�� ���� ���;���
//���� ������ index ����
//����ΰ�?
int PostfixToIntermediate::Is_con(int index){
	int i;
	//push
	Intermediate.Append("push ");
	//��� ������ index ã��
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

//index�� ���� ���;���
//���� ������ index ����
//������ �ΰ�?
int PostfixToIntermediate::Is_op(int index){
	int i, j;
	bool correct;
	for (i = 0; i < (sizeof(oper) / 4); i++){
		//�������� ����
		int OP_len = strlen(oper[i]);

		//���� index �� ������ ������ ���� ��ü ���� ���̺��� �۾ƾߵȴ�.
		//�ȱ׷��� ���� ª�� �������ε� �� ������ ã�ٰ� �޸� ���� ���� ����
		if (index + OP_len < linelen){
			correct = true;
			for (j = 0; j < OP_len; j++){
				if (linepointer[index + j] != oper[i][j]){
					correct = false;
					break;
				}
			}
			//�ش翬���� �ϰ��
			if (correct){
				Intermediate.Append(oper[i]);
				break;
			}
		}
	}
	Intermediate.Append("\r\n");
	return index + j;		// ��Ÿ�� ���� üũ (-1 ����)
}
//lv2 ���丮�� üŷ��
bool PostfixToIntermediate::Is_fact(int index) {
	int j=0;
	bool correct;
		int OP_len = strlen(oper[3]);

		//���� index �� ������ ������ ���� ��ü ���� ���̺��� �۾ƾߵȴ�.
		//�ȱ׷��� ���� ª�� �������ε� �� ������ ã�ٰ� �޸� ���� ���� ����
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
	return correct;		// ��Ÿ�� ���� üũ (-1 ����)
}


//�ùٸ� �ĵ� ���������� �Ѱ���
CStringA PostfixToIntermediate::getIntermediate(){
	return Intermediate;
}