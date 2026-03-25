#include <stdio.h>
#define MAX_DEQUE_SIZE 20

// "앞뒤로 다 통하는 양방향 대기열, 덱(Deque)"
// 덱(Deque, Double - Ended Queue)은 큐(Queue)처럼 앞뒤로 길쭉한 대기열이지만,
// 앞과 뒤 양쪽 끝에서 삽입과 삭제가 모두 가능한 만능 자료구조입니다.
// 식당 대기열로 치면, 일반 손님은 맨 뒤에 줄을 서고 맨 앞사람이 입장(enqueue, dequeue)하지만,
// VIP 손님은 맨 앞으로 새치기해서 들어올 수 있고(add_front),
// 줄을 서던 맨 뒤 손님이 변심해서 빠져나갈 수도(delete_rear) 있는 구조입니다.

// 오늘의 핵심 공식(인덱스 역회전)
// 원형 큐에서 앞으로 한 칸 전진할 때(rear + 1) % MAX_SIZE를 썼던 것 기억하시죠 ?
// 덱에서는 반대로 뒤로 한 칸 후진(감소)해야 할 때가 있습니다.이때(front - 1) % MAX_SIZE를 하면 음수가 나올 수 있어 에러가 터집니다.
// 인덱스 감소 공식 : 음수 방지를 위해 한 바퀴(MAX_SIZE)를 더해줍니다.👉(index - 1 + MAX_SIZE) % MAX_SIZE

typedef int element;

typedef struct {
	element data[MAX_DEQUE_SIZE];
	int front, rear;
} DequeType;

// 대충 큐에서 다 뜯어오긴 했는데..
// 덱 초기화 함수
void init_deque(DequeType* q) {
	q->rear = q->front = 0;
}
// 덱 포화 상태 검출 함수
int deque_is_full(DequeType* q) {
	return ((q->rear + 1) % MAX_DEQUE_SIZE == q->front);
}
// 덱 공백 상태 검출 함수
int deque_is_empty(DequeType* q) {
	return (q->front == q->rear);
}
// 덱 맨 뒤에 넣기
void add_rear(DequeType* q, element item) {
	if (deque_is_full(q)) {
		printf("덱이 포화상태입니다.");
		return;
	}
	q->rear = (q->rear + 1) % MAX_DEQUE_SIZE;
	q->data[q->rear] = item; 
}
element delete_rear(DequeType* q) {
	if (deque_is_empty(q)) { printf("덱이 공백상태입니다."); return NULL; }
	int prev = q->rear;
	q->rear = (q->rear - 1 + MAX_DEQUE_SIZE) % MAX_DEQUE_SIZE;
	return q->data[prev];
}
// 덱 맨 앞에 넣기
void add_front(DequeType* q, element item) {
	if (deque_is_full(q)) { printf("덱이 포화상태입니다."); return; }
	q->data[q->front] = item;
	q->front = (q->front - 1 + MAX_DEQUE_SIZE) % MAX_DEQUE_SIZE;
}
// 덱 삭제 함수
element delete_front(DequeType* q) { 
	if (deque_is_empty(q)) { 
		printf("덱이 공백상태입니다.");
		return NULL;
	}
	q->front = (q->front + 1) % MAX_DEQUE_SIZE; 
	return q->data[q->front]; 
}

// 덱에서 뺄 때 MAX를 더하는 이유:
// 원형 큐에서 앞으로 전진할 때는(index + 1) % MAX를 썼었죠.
// 그럼 뒤로 갈 때는 단순히(index - 1) % MAX를 하면 될 것 같지만... C언어에서 음수를% 연산하면 그냥 음수가 나옵니다!
// 만약 현재 front가 0번 인덱스일 때 1을 빼면 - 1이 됩니다.C언어에서는 - 1 % 5 = -1이 되어버리고, 배열의 - 1번 인덱스에 접근하려다가 바로 어제 겪으신 Segfault(강제 종료) 철퇴를 맞게 됩니다.

// 해결책 : MAX를 한 번 더해주기!
// 배열의 끝과 처음이 이어져 있기 때문에, 음수가 나오는 걸 막으려고 배열의 전체 크기(MAX_DEQUE_SIZE)를 한 바퀴 쓱 더해주는 겁니다.

// 예를 들어 배열 크기(MAX_DEQUE_SIZE)가 5라고 해봅시다.

// 현재 front가 3일 때 뒤로 가기 :
// (3 - 1 + 5) % 5 = 7 % 5 = 2 👉 2번 인덱스로 정상 후진 완료!

// 🔥 현재 front가 0(맨 앞)일 때 뒤로 가기 :
// (0 - 1 + 5) % 5 = 4 % 5 = 4 👉 - 1이 아니라 배열의 맨 끝(4번 인덱스)으로 완벽하게 순간이동(Wrap - around) 완료!!

// 즉, MAX를 더해주는 건 수학적으로 결과값은 똑같이 유지하면서, 컴퓨터가 음수 때문에 터지는 걸 막아주는 '안전장치'인 셈입니다.

int main() {
	DequeType gogeup_restaurant;
	init_deque(&gogeup_restaurant);
	printf("[레스토랑 대기열 시뮬레이션]\n> 일반 손님 추가: 10\n> 일반 손님 추가: 20\n> VIP 손님 추가(맨 앞): 99\n");
	// 10번, 20번 일반 손님을 줄을 세움.
	add_rear(&gogeup_restaurant, 10); 
	add_rear(&gogeup_restaurant, 20);

	// vip의 레전드 새치기 발생
	add_front(&gogeup_restaurant, 99); 

	// 입장 시작
	printf("\n[!] 입장 완료: %d (맨 앞에서 제거)\n", delete_front(&gogeup_restaurant));
	// 런해버린 맨 뒤 손님
	printf("[!] 런: %d (맨 뒤에서 제거)\n", delete_rear(&gogeup_restaurant));
	// 어차피 남은 한 명은 뒤에서 빼나 앞에서 빼나..
	printf("\n남은 대기열 상태\n남은 손님 번호: %d", delete_rear(&gogeup_restaurant));
	return 0;
}