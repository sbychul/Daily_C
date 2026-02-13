#include <stdio.h>
#include <stdlib.h>

struct Node {
	int data;
	struct Node* next;
};

int main() {
	struct Node* head = NULL;
	int coins_count = 0;

	printf("몇 개의 동전을 쌓으시겠습니까?: ");
	scanf("%d", &coins_count); // 쌓을 동전 갯수 입력

	for (int i = 0; i < coins_count; i++) { // 갯수만큼 반복
		struct Node* new_node = malloc(sizeof(struct Node));
		printf("%d번째 동전의 가치(원) 입력: ", i + 1);
		scanf("%d", &new_node->data);
		new_node->next = head; // 새 노드가 현재의 머리(맨 위)를 가리키게(현재의 머리보다 위(현재 머리를 밑으로)로 올라가게) 함. (LIFO(Last In First Out))
		head = new_node; // 새 노드가 새로운 머리(맨 위)가 됨 (원래 맨 위에 있던 것의 위에 지금 만든 새 노드를 쌓음)
	}

	// 직접 쓴 코드, 메모리 반납을 하지 않는 실수 발생. head가 이미 출력하면서 NULL이 되어버려 메모리 반납을 안 해버림..
	
	// printf("\n[현재 스택 상태 (위에서부터)]\n");
	// while (head != NULL) {
	//	 printf("%d원 -> ", head->data);
	//	 head = head->next; // 임시 포인터를 다음 칸으로
	// }
	// printf("NULL\n"); // 출력 종료

	// struct Node* temp = head;	// 메모리 해제를 위한 임시 포인터 구조체 형성
	// while (head != NULL) {
	//	 temp = head->next;	// 다음 칸을 적어두고
	//	 free(head);			// 현재 칸을 부수고
	//	 head = temp;		// 다음 칸으로 이동. (다음 칸을 적기 전에 부수면 Segfault 발생)
	// }

	// [출력 파트 수정본] / temp를 열심히 활용하도록 하자.
	printf("\n[현재 스택 상태 (위에서부터)]\n");

	struct Node* temp = head; // 1. 대리인 고용
	while (temp != NULL) {
		printf("%d원 -> ", temp->data);
		temp = temp->next;    // 2. 대리인 이동 (이거 없으면 무한루프!)
	}
	printf("NULL\n");

	// [메모리 해제 파트]
	// 이제 head가 살아있으니, 여기서부터는 정상 작동합니다!
	while (head != NULL) {
		struct Node* next_node = head->next;
		free(head);
		head = next_node;
	}

	printf("\n메모리를 해제하고 프로그램을 종료합니다.");
	return 0; // 프로그램 종료
}

// "새 노드가 기존 head를 손잡고, head 깃발을 새 노드에게 옮긴다"
// 💡 오늘 얻어가야 할 교훈
// head는 성역(聖域)입니다.
// 리스트의 시작점을 잃어버리면, 그 뒤에 줄줄이 달린 메모리들은 영영 찾을 수 없는 '국제 미아'가 됩니다. (Memory Leak)

// 출력할 때 : struct Node* temp = head; (복사해서 쓰기)
// 해제할 때 : head를 움직여도 됩니다. (어차피 다 부수고 끝낼 거니까요!)

