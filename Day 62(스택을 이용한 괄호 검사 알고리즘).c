#include <stdio.h>
#define MAX_STACK_SIZE 50

// 오늘의 핵심 알고리즘 (LIFO 활용)
// 열린 괄호((, { ,[) 를 만나면 ? 👉 일단 스택에 push 합니다.
// 닫힌 괄호(), }, ]) 를 만나면 ? 👉 스택에서 하나를 pop 해서 방금 나온 닫힌 괄호와 짝이 맞는지 비교합니다.
// 만약 스택이 비어있는데 닫힌 괄호가 나왔거나, 짝이 안 맞으면 ? 👉 실패!
// 문장이 끝났는데 스택에 아직 괄호가 남아있다면 ? 👉 실패!

typedef char* element;

typedef struct {
	element data[50];
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
int check_matching(const char item[]) { // const == item을 건드리지 않고 검사만 하겠다는 뜻
	StackType matching_stack;
	init_stack(&matching_stack);

	int i = 0;
	while (item[i] != '\0') { // 문자열이 끝날 때까지 글자를 하나씩 빼 오기.
		char exp = item[i];
		switch (exp) {
			case '(':
			case '{':
			case '[':
				push(&matching_stack, exp); // 무조건 스택에 밀어 넣습니다.
				break;

			case ')': // 소괄호 검사, 이후 모두 같은 로직을 사용할 예정.
				if (stack_is_empty(&matching_stack)) { printf("괄호의 배치가 올바르지 않습니다.\n"); return 0; } // 스택이 비어 있을 경우. (닫힌 괄호 먼저 나옴)
				if (pop(&matching_stack) != '(') { printf("괄호의 짝이 맞지 않습니다."); return 0; } // 괄호의 짝이 맞지 않을 경우.
				break;
			
			case '}': // 중괄호 검사
				if (stack_is_empty(&matching_stack)) { printf("괄호의 배치가 올바르지 않습니다.\n"); return 0; }
				if (pop(&matching_stack) != '{') { printf("괄호의 짝이 맞지 않습니다."); return 0; }
				break;

			case ']': // 대괄호 검사
				if (stack_is_empty(&matching_stack)) { printf("괄호의 배치가 올바르지 않습니다.\n"); return 0; }
				if (pop(&matching_stack) != '[') { printf("괄호의 짝이 맞지 않습니다."); return 0; }
				break;

			// 괄호가 아닌 일반 숫자나 알파벳, 띄어쓰기를 만났을 때.
			default:
				break;
		} // switch문 종료
		i++;
	} // while문 종료

	if (!stack_is_empty(&matching_stack)) { printf("괄호의 짝이 맞지 않습니다."); return 0; } // 여는 괄호만 있을 경우.
	return 1; // 여기까지 왔으면 괄호의 짝이 맞음, 1 (true) 반환.
}

int main() {
	char line[50] = { 0 };
	printf("[스택 활용 괄호 검사기]\n검사할 수식을 입력하세요: ");
	fgets(line, sizeof(line), stdin);

	printf("\n판별 결과: ");
	if (check_matching(line)) { printf("모든 괄호의 짝이 맞습니다! (성공)\n"); }
	// 실패하면 함수 내의 메시지가 뜸!! 따로 적어줄 필요 X
	return 0;
}