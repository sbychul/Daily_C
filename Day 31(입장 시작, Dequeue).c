#include <stdio.h>
#include <stdlib.h>

// Day 30의 코드를 그대로 재활용. 코드 설명이 나중에 보고 싶을 때는 30일차 참조.
struct Node {
	int queue;
	struct Node* next;
};

int main() {
	struct Node* front = NULL;
	struct Node* rear = NULL;
	int waiting_teams = 0;

	printf("대기 등록할 인원 수: ");
	scanf("%d", &waiting_teams);
	if (waiting_teams < 1) {
		printf("입력된 숫자가 올바르지 않습니다. (양의 정수를 입력하세요)");
		return 1;
	}
	for (int i = 0; i < waiting_teams; i++) {
		struct Node* new_node = malloc(sizeof(struct Node));
		new_node->next = NULL;
		printf("%d번째 대기 번호 입력: ", i + 1);

		scanf("%d", &new_node->queue);
		if (front == NULL || rear == NULL) {
			front = rear = new_node;
		}
		else {
			rear->next = new_node;
			rear = new_node;
		}
	}
	struct Node* temp = front;
	printf("\n[현재 대기열 상태(입력 순서)]\n");
	while (temp != NULL) {
		printf("%d번 -> ", temp->queue);
		temp = temp->next;
	}
	printf("대기열 종료\n");

	// 31일차 입장시키기(Dequeue) 시작.

	int dequeue_or_not = 0; // 입장시키는 데 활용할 변수 생성
	while (1) {
		printf("\n다음 손님을 입장시키겠습니까? (1: 예 / 0: 아니오): ");
		if (scanf("%d", &dequeue_or_not) == 0) { // 예외 처리 1: 숫자가 아닌 것을 입력했을 때 (29일차 코드 그대로 재활용)
			// scanf는 입력에 성공한 변수의 개수를 반환함!
			printf("숫자가 아닙니다! 다시 입력해 주세요.\n");
			while (getchar() != '\n');
			continue;
		}
		if (dequeue_or_not != 1 && dequeue_or_not != 0) { // 예외 처리 2: 0과 1이 아닌 것을 입력했을 때
			printf("입력된 값이 올바르지 않습니다. 다시 입력해 주세요.\n");
			continue;
		}
		if (dequeue_or_not == 1) { // 1 입력 시 맨 앞의 사람을 입장시킴(메모리 할당 해제)
			if (front == NULL) {
				printf("대기 중인 인원이 없습니다. 프로그램을 종료합니다.\n");
				break;
			}
			struct Node* next_node = front->next;	// 생명줄 확보
			printf("[입장] %d번 손님, 들어오세요!\n", front->queue);
			free(front);		// 입장하십니다.
			front = next_node;	// 다음 분~

			// 🔥 [추가해야 할 핵심 코드] 🔥
			// 만약 방금 나간 뒤에 줄이 텅 비어버렸다면?
			if (front == NULL) {
				rear = NULL; // rear도 "아무도 없음"으로 초기화해줘야 안전합니다! 양쪽 끝을 다 쓰기 때문에 꼭 챙겨야 합니다.
			}

			temp = front;		// 출력용 임시 포인터

			printf("[현재 대기열]: ");

			while (temp != NULL) { // 출력
				printf("%d원 -> ", temp->queue);
				temp = temp->next;
			}
			printf("대기열 종료\n");
		}

		else { break; } // 0 입력 시 그대로 반복문 종료.
	}

	while (front != NULL) { // 메모리 할당 해제, front를 따라가다 보면 결국 전부 해제됨.
		temp = front->next;
		free(front);
		front = temp;
	}

	return 0;
}