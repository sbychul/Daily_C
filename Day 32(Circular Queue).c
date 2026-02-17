#include <stdio.h>
#include <stdlib.h>

struct Node {
	int number;
	struct Node* next;
};

int main() {
	struct Node* front = NULL;
	struct Node* rear = NULL;

	printf("대기 번호 3개를 입력하세요.\n");
	for (int i = 0; i < 3; i++) {
		struct Node* new_node = malloc(sizeof(struct Node));
		new_node->next = front; // 항상 새 노드가 마지막으로 가기 때문에, 마지막 노드가 다시 맨 앞을 가리켜야 원형 큐의 완성.
		printf("%d번째: ", i + 1);

		scanf("%d", &new_node->number);
		if (front == NULL || rear == NULL) { // 첫 번째일 경우. 맨 앞과 뒤가 둘 다 없음.
			front = rear = new_node;
		}
		else { // 아닐 경우 맨 뒤 자리를 새 노드에게 넘겨줌
			rear->next = new_node;
			rear = new_node;
		}
	}
	struct Node* temp = front;
	printf("\n[원형 큐 순환 출력 (2바퀴)]\n");
	for (int i = 0; i < 6; i++) { // 2바퀴를 보여주기 위하여 6회 반복.
		printf("%d번 -> ", temp->number);
		temp = temp->next;
	}
	printf("(순환 중)\n");

	rear->next = NULL; // 메모리 할당 해제 전 무한 루프 방지.
	while (front != NULL) { // 메모리 할당 해제, front를 따라가다 보면 결국 전부 해제됨.
		temp = front->next;
		free(front);
		front = temp;
	}

	return 0;
}

// 💡 한 단계 더 나아가는 팁 (One More Thing)
// 지금 코드는 2개 이상일 때부터 완벽한 원형이 됩니다.
// 만약 "데이터가 딱 1개일 때도" 스스로를 가리키는(101 -> 101) 완벽한 원형으로 만들고 싶다면, if문 안을 살짝만 만져주면 됩니다.

// if (front == NULL || rear == NULL) {
//	 front = rear = new_node;
//	 new_node->next = new_node; // 🔥 나 자신을 가리키게 함 (스스로 도는 원)
// }