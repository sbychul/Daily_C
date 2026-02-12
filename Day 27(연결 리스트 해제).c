#include <stdio.h>
#include <stdlib.h>

// 26일차와 완벽하게 이어짐, 메모리 반납 이전 코드 해설은 26일차 파일 참조.
struct Node {
	int score;
	struct Node* next;
};

int main() {
	struct Node* head = NULL;
	struct Node* current = NULL;
	int scores_count = 0;

	printf("입력할 점수 개수: ");
	scanf("%d", &scores_count);
	if (scores_count < 1) {
		printf("입력할 점수의 개수가 잘못되었습니다.");
		return 1;
	}

	for (int i = 0; i < scores_count; i++) {
		struct Node* new_node = malloc(sizeof(struct Node));
		printf("%d번째 점수 입력: ", i + 1);
		scanf("%d", &new_node->score);
		new_node->next = NULL;

		if (head == NULL) {
			head = new_node;
		}
		else {
			current->next = new_node;
		}
		current = new_node;
	}

	struct Node* temp = head;
	printf("\n[입력된 성적 리스트]\n");
	while (temp != NULL) {
		printf("%d점 -> ", temp->score);
		temp = temp->next;
	}
	printf("NULL\n");

	// 연결된 노드의 메모리 반납, 출력하기 위해 사용했던 임시 구조체 temp를 재활용.
	printf("\n[메모리 해제 시작]\n");
	while (head != NULL) {
		temp = head->next; // 1. 다음 칸 주소를 미리 적어둔다.
		printf("%d점 노드 해제 완료.\n", head->score); // 2. 데이터 확인
		free(head);        // 3. 현재 칸을 부순다(해제).
		head = temp;       // 4. 적어둔 다음 칸으로 옮겨간다.
	}
	// temp에 다음 칸(head->next)을 적어둠.
	// head 칸을 제거, head를 다음 칸으로 옮김. (위와 똑같은 말인데 그냥 내가 나중에 보기 편하라고)

	printf("메모리 해제 완료, 프로그램을 정상적으로 종료합니다.");
	return 0;
}


// 💥 만약 메모리를 해제하는 순서를 틀렸다면 ? (공포의 시나리오)
// 만약 유저님이 temp = head->next; 를 free(head); 밑으로 내렸다면 어떻게 될까요?

// [잘못된 예시]
// free(head);        // 현재 노드를 지워버림 (메모리 반납)
// head = head->next; // ⚠️ 이미 반납해서 사라진 메모리(head) 안의 next를 찾으려고 함!

// 결과: Segmentation Fault(세그멘테이션 오류(허락받지 않은 메모리를 건드림))가 발생하며 프로그램이 즉시 강제 종료됩니다.
// 이유 : 이미 운영체제에 반납한 땅(head)에 다시 들어가서 "거기 적혀있던 다음 주소 내놔!"라고 떼를 쓰는 격이기 때문입니다.
// 운영체제는 이걸 "무단 침입"으로 간주하고 프로그램을 죽여버립니다.
// 👉 즉, 유저님의 프로그램이 "메모리 해제 완료" 메시지를 띄우고 정상 종료되었다는 것 자체가, 메모리 관리를 완벽하게 했다는 뜻입니다.

// Segfault(Segmentation Fault) = "무단 침입" (허락받지 않은 메모리를 건드림).
// 원인 = 주로 NULL을 찌르거나, free한 메모리를 또 건드리거나, 배열 밖으로 나갔을 때.
// 해결책 = 포인터가 NULL인지 확인하고(if (ptr != NULL)), 메모리 해제 순서를 잘 지키면 됩니다.