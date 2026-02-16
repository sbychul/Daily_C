#include <stdio.h>
#include <stdlib.h>

struct Node {
	int queue; // Gemini tip: 'queue'라는 이름은 자료구조 전체를 의미할 때가 많아요. 'id' 혹은 'number'라고 짓는 것이 명확합니다.
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
		return 1; // 예외 처리인데, 반복 넣기 싫어서 꺼버리기.
	}
	for (int i = 0; i < waiting_teams; i++) { // 대기 번호 입력 절차
		struct Node* new_node = malloc(sizeof(struct Node));
		new_node->next = NULL;	// 언제든지 마지막일 수 있기 때문에 새 노드의 다음은 NULL (어차피 밑에서 해결)
		printf("%d번째 대기 번호 입력: ", i + 1);

		scanf("%d", &new_node->queue);			// 1. queue 값 입력
		if (front == NULL || rear == NULL) {	// 2. 처음 넣는 값일 때. (처음이라면 front와 rear가 둘 다 비어있으니까)
			front = rear = new_node;			// 2-1. 처음 등록 => 첫 번째 사람(front)이자 마지막 사람(rear)이 이 사람(new_node)
		}
		else {									// 3. 처음 넣는 값이 아닐 때.
			rear->next = new_node;				// 3-1. 마지막 사람(rear)의 다음 사람(rear->next)이 지금 들어오는 사람(new_node)
			rear = new_node;					// 3-2. 마지막 사람 바톤 터치.
		}
	}
	struct Node* temp = front; // 출력을 위한 임시 포인터 생성
	printf("\n[현재 대기열 상태(입력 순서)]\n");
	while (temp != NULL) {
		printf("%d번 -> ", temp->queue);
		temp = temp->next;
	}
	printf("대기열 종료\n"); // 괜히 NULL이 아닌 다른 말이 쓰고 싶어서

	while (front != NULL) { // 메모리 할당 해제, front를 따라가다 보면 결국 전부 해제됨.
		temp = front->next;
		free(front);
		front = temp;
	}

	return 0;
}