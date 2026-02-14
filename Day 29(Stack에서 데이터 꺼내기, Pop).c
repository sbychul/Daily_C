#include <stdio.h>
#include <stdlib.h>

// Day 28의 코드를 그대로 재활용. 코드 설명이 나중에 보고 싶을 때는 28일차 참조.
struct Node {
	int data;
	struct Node* next;
};

int main() {
	struct Node* head = NULL;
	int coins_count = 0, stack_or_not = 0;

	printf("몇 개의 동전을 쌓으시겠습니까?: ");
	scanf("%d", &coins_count);

	for (int i = 0; i < coins_count; i++) {
		struct Node* new_node = malloc(sizeof(struct Node));
		printf("%d번째 동전의 가치(원) 입력: ", i + 1);
		scanf("%d", &new_node->data);
		new_node->next = head;
		head = new_node;
	}

	printf("\n(%d개의 동전 입력 완료)\n[현재 스택]: ", coins_count);

	struct Node* temp = head;
	while (temp != NULL) {
		printf("%d원 -> ", temp->data);
		temp = temp->next;
	}
	printf("NULL\n");

	// 동전 쌓기 종료. 이 주석 밑부터 29일차(POP) 시작.
	while (1) {
		printf("\n동전을 하나 꺼내시겠습니까? (1: 예 / 0: 아니오): ");
		if (scanf("%d", &stack_or_not) == 0) { // 숫자가 아닌 것을 입력했을 때
			// scanf는 입력에 성공한 변수의 개수를 반환함!
			printf("숫자가 아닙니다! 다시 입력해 주세요.\n");
			while (getchar() != '\n');
			continue;
		}
		if (stack_or_not != 1 && stack_or_not != 0) { // 0과 1이 아닌 것을 입력했을 때
			printf("입력된 값이 올바르지 않습니다. 다시 입력해 주세요.\n");
			continue;
		}
		if (stack_or_not == 1) { // 동전을 하나 뺄 때, 맨 위의 한 개만 메모리를 해제.
			if (head == NULL) {
				printf("빼낼 동전이 없습니다. 프로그램을 종료합니다.\n");
				break;
			}
			struct Node* next_node = head->next;	// 생명줄 확보
			printf("[POP] %d원이 나옵니다.\n", head->data);
			free(head);			// 펑
			head = next_node;	// 다음으로.
			temp = head;		// 출력용 임시 포인터

			printf("[현재 스택]: ");

			while (temp != NULL) { // 출력
				printf("%d원 -> ", temp->data);
				temp = temp->next;
			}
			printf("NULL\n");
		}

		else { // 동전을 빼지 않을 때 == 프로그램 종료 절차로 넘어감
			break;
		}
	}

	while (head != NULL) { // 남은 동전들의 메모리 해제 절차
		struct Node* next_node = head->next;
		free(head);
		head = next_node;
	}
	printf("잔여 메모리를 해제하고 프로그램을 종료합니다.");
	return 0; // 프로그램 종료
}
