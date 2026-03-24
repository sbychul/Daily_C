#include <stdio.h>
#define MAX_STACK_SIZE 50

// 오늘의 핵심 알고리즘
// 수식을 왼쪽부터 오른쪽으로 한 글자씩 읽습니다.
// 숫자를 만나면 ? 👉 스택에 무조건 push 합니다.
// 연산자(+, -, *, / )를 만나면 ? 👉 스택에서 숫자 2개를 pop 합니다.
// 주의 : 먼저 pop 된 숫자가 뒤로 가고, 나중에 pop 된 숫자가 앞으로 옵니다! (예 : pop 해서 3과 8이 나왔다면 8 - 3을 계산)
// 계산한 결과값을 다시 스택에 push 합니다.
// 수식이 끝나고 스택에 마지막으로 남은 숫자 딱 1개가 최종 정답입니다!

typedef int element; // 숫자를 넣을 것이기 때문

typedef struct {
	element data[30];
	int top;
} StackType;

// 함수 설명은 61일차 참조.
// 스택 초기화 함수
void init_stack(StackType* s) {
	s->top = -1;
}
// 스택 공백 상태 검출 함수
int stack_is_empty(StackType* s) {
	return (s->top == -1);
}
// 스택 포화 상태 검출 함수
int stack_is_full(StackType* s) {
	return (s->top == (MAX_STACK_SIZE - 1));
}
// 스택 삽입 함수
void push(StackType* s, element item)
{
	if (stack_is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->data[++(s->top)] = item;
}
// 스택 삭제 함수
element pop(StackType* s) {
	if (stack_is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		return NULL;
	}
	else return s->data[(s->top)--];
}

// 스택을 활용하여 괄호를 검사하는 함수
int eval(const char* exp) { // const == item을 건드리지 않고 검사만 하겠다는 뜻
	StackType cal_stack;
	init_stack(&cal_stack);

	// while문에 사용할 변수와 계산할 때 사용할 변수를 초기화
	int i = 0, num1 = 0, num2 = 0; 

	while (exp[i] != '\0') { // 문자열이 끝날 때까지 글자를 하나씩 빼 오기.
		char cal = exp[i];
		switch (cal) {
			// 따로따로 만드려다가 과정이 같은 코드를 여러 번 쓰게 될 것 같아서.
			// 다 쓰고 나니까 이게 더 더러운 것 같기도 하고..
			case '+':
			case '-':
			case '*':
			case '/':
				// 스택에서 숫자를 빼서 저장.
				num1 = pop(&cal_stack);
				num2 = pop(&cal_stack);
				if (cal == '+') {
					push(&cal_stack, num1 + num2); // 덧셈, 순서 상관 없이 더하기.
				}
				else if (cal == '-') {
					push(&cal_stack, num2 - num1); // 뺄셈, 뒤에 나온 수에서 먼저 나온 수를 빼야 함. 순서 바꿔주기.
				}
				else if (cal == '*') {
					push(&cal_stack, num1 * num2); // 곱셈, 순서 상관 없음. 근데 이렇게 쓰다 보니까 그냥 덧셈 곱셈도 순서 바꿔서 쓸 걸 그랬나 싶기도.
				}
				else { // 나눗셈
					if (num1 == 0) { printf("0으로는 나눌 수 없습니다.\n"); return 1; } // 먼저 나온 num1으로 나눌 예정인데, num1이 0이면 나눗셈 못 함!! 파업.
					push(&cal_stack, num2 / num1);
				}
				break;

			default: // 숫자일 경우.
				cal = cal - '0';		// 숫자 문자열에서 '0'을 빼주면 정수로 바뀜!! wow
				push(&cal_stack, cal);	// 해당 수를 집어넣음.
		}
		i++; // 다음 글자로.
	} // while문 종료
	return pop(&cal_stack); // 마지막에 남은 숫자가 결과.
}

int main() {
	char exp[30] = { 0 };
	printf("[스택 활용 후위 표기식 계산기]\n계산할 수식을 입력하세요(후위 표기법): ");
	scanf("%s", exp);
	printf("\n판별 결과: 수식 '%s'의 계산 결과는 %d 입니다!\n", exp, eval(exp));
	return 0;
}