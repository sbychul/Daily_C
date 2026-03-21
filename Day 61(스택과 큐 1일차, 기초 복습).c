#include <stdio.h>

// 오늘의 핵심 요소 (Spec)
// 원형 큐(Circular Queue) : 선형 큐의 단점을 보완하기 위해 % MAX_QUEUE_SIZE 연산을 사용하여 인덱스를 회전시킵니다.
// front와 rear가 같으면 비어있는 것이고, (rear + 1) % MAX_QUEUE_SIZE == front이면 가득 찬 것입니다.
// 스택(Stack) : top 변수 하나로 관리하며, 가장 마지막에 들어온 데이터가 가장 먼저 나가는 구조입니다.
// 구조체 분리 : StackType과 QueueType을 각각 정의하여 변수들이 서로 간섭하지 않도록 합니다.
#define MAX_STACK_SIZE 5
#define MAX_QUEUE_SIZE 5

typedef char* element;

typedef struct {
	element data[20];
	int top;
} StackType;

// 함수는 수업 자료 복붙, 주석은 이해한 대로 작성하였음.
// 스택 초기화 함수
void init_stack(StackType* s) {
	s->top = -1; // stack의 top 변수를 -1로 설정, 인덱스적 개념으로 봤을 때 비어 있음을 설명.
}
// 스택 공백 상태 검출 함수
int stack_is_empty(StackType* s) {
	return (s->top == -1); // top == -1 == 스택이 비어 있음. 1(true)를 반환, 아니면 0(false).
}
// 스택 포화 상태 검출 함수
int stack_is_full(StackType* s) {
	return (s->top == (MAX_STACK_SIZE - 1)); // MAX - 1번 인덱스 == top == 스택이 꽉 참, 1(true). 아니면 0(false).
}
// 스택 삽입 함수
void push(StackType* s, element item) // stack에 element item을 집어넣음.
{
	if (stack_is_full(s)) { // 꽉 차있으면 들어가면 안 됨. 예외 처리
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->data[++(s->top)] = item; // 아니라면 top에 +1을 해준 뒤, data에 item을 집어넣음.
}
// 스택 삭제 함수
element pop(StackType* s) { // stack에서 맨 위에 있는 것을 빼줌.
	if (stack_is_empty(s)) { // 아무것도 없는데 빼면 안 됨, 예외 처리.
		fprintf(stderr, "스택 공백 에러\n");
		return NULL;
	}
	else return s->data[(s->top)--]; // 아니라면 top에서 -1을 해준 뒤, data에 있는 것을 반환함. 
}

typedef struct {
	element data[20];
	int front, rear;
} QueueType;

// 큐 초기화 함수
void init_queue(QueueType* q) {
	q->rear = q->front = 0; // 초기 상태, rear와 front를 같은 0 값으로 설정. 비어 있음을 표기.
}
// 큐 포화 상태 검출 함수
int queue_is_full(QueueType* q) {
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front); // 맨 뒷칸 + 1(이면 MAX라는 거임(인덱스적 사고)!!!) % MAX == 0(front) 이면 1(true).
}
// 큐 공백 상태 검출 함수
int queue_is_empty(QueueType* q) {
	return (q->front == q->rear); // front와 rear가 같은 값 == 비어 있음, 1(true)를 반환, 아니면 0(false).
}
// 큐 삽입 함수
void enqueue(QueueType* q, element item) { // Queue에 item 집어넣기.
	if (queue_is_full(q)) { // 꽉 차있으면 들어가면 안 됨. 예외 처리
		printf("큐가 포화상태입니다.");
		return NULL;
	}
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE; // rear를 다음 칸으로.
	q->data[q->rear] = item; // 다음 칸에 data를 집어넣음.
}
// 큐 삭제 함수
element dequeue(QueueType* q) { // 수업 자료는 int 반환이었으나, 지금은 빼줘야 할 자료형이 element(char)이기 때문에 변경함.
	if (queue_is_empty(q)) { // 아무것도 없는데 빼면 안 됨, 예외 처리.
		printf("큐가 공백상태입니다.");
		return NULL;
	}
	q->front = (q->front + 1) % MAX_QUEUE_SIZE; // front를 0에서 다음 칸으로.
	return q->data[q->front]; // 다음 칸의 data를 꺼냄.
}

int main() {
	QueueType order;
	StackType dishes;
	init_queue(&order);
	init_stack(&dishes); // 큐와 스택 초기화
	
	printf("[레스토랑 주방 시뮬레이션]\n");
	// Circular Queue
	printf("> 주문 접수: Pasta\n");
	enqueue(&order, "Pasta");

	printf("> 주문 접수: Steak\n");
	enqueue(&order, "Steak");

	printf("> 주문 접수: Salad\n");
	enqueue(&order, "Salad");
	printf("[!] 요리 완성: %s (대기열에서 제거)\n", dequeue(&order)); // 맨 처음 들어간 주문 하나를 빼서 출력

	// Stack
	printf("\n> 빈 접시 추가: Dish 1\n");
	push(&dishes, "Dish 1");

	printf("> 빈 접시 추가: Dish 2\n");
	push(&dishes, "Dish 2");

	printf("> 빈 접시 추가: Dish 3\n");
	push(&dishes, "Dish 3");
	printf("[!] 설거지 완료: %s (대기열에서 제거)\n", pop(&dishes)); // 맨 위의 하나를 빼서 출력

	printf("\n--- 현재 주방 상태 ---\n");
	printf("남은 주문 대기열: ");
	while (!queue_is_empty(&order)) { // 큐가 다 빌 때까지 빼서 출력.
		printf("%s > ", dequeue(&order));
	}
	printf("없음\n"); // 깔끔하게 출력부를 마무리합시다.

	printf("남은 설거지 접시: ");
	while (!stack_is_empty(&dishes)) { // 스택이 다 빌 때까지 빼서 출력.
		printf("%s > ", pop(&dishes));
	}
	printf("없음 (위에서부터)\n"); // 마찬가지.

	return 0;
}