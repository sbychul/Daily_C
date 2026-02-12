#include <stdio.h>
#include <stdlib.h>

struct Node { // node 구조체 형성
	int score;
	struct Node* next;
};

int main() {
	struct Node* head = NULL; // 첫 번째 노드를 가리킬 포인터와 마지막을 가리킬 포인터 형성
	struct Node* current = NULL; // head와 current 구조체를 비워둔 상태로 시작
	int scores_count = 0;

	printf("입력할 점수 개수: ");
	scanf("%d", &scores_count);
	if (scores_count < 1) { // 예외 처리, 음수 개수를 입력받을 순 없으니까
		printf("입력할 점수의 개수가 잘못되었습니다.");
		return 1;
	}

	for (int i = 0; i < scores_count; i++) {
		struct Node* new_node = malloc(sizeof(struct Node)); // 점수를 입력받을 새 노드 형성
		printf("%d번째 점수 입력: ", i + 1);
		scanf("%d", &new_node->score);
		new_node->next = NULL; // new_node의 다음은 일단 없는 것으로; 마지막일 수 있음

		if (head == NULL) { // 만약 첫 번째일 경우, 처음 입력받는 경우 (head에 아무것도 없는 상태)
			head = new_node; // 방금 만든 첫 new_node를 head로 지정 (첫 번째 칸을 지정)
		}
		else { // 첫 번째가 아닐 경우
			current->next = new_node; // 마지막을 가리키는 포인터의 다음을 new_node로 지정
		}
		current = new_node; // 마지막을 가리키는 포인터를 new_node로 설정. new_node->next는 NULL이기 때문에 새로운 것이 형성되기 전까지는 마지막 칸으로서 활동.
	}

	struct Node* temp = head; // 출력하기 위해 사용할 임시 포인터 형성
	printf("\n[입력된 성적 리스트]\n");
	while (temp != NULL) { // 마지막 칸일 경우 temp == NULL이기 때문에, 그 전까지 계속 반복
		printf("%d점 -> ", temp->score);
		temp = temp->next; // 임시 포인터를 다음 칸으로 옮김
	}

	printf("NULL\n");
	return 0;
}

// 🏃 비유: "이어달리기 선수와 바통"
// 우리가 '인간 기차'를 만든다고 상상해 봅시다.

// head: 맨 앞에서 깃발을 들고 있는 '선두' (절대 움직이면 안 됨)
// new_node : 새로 들어오는 '신입 부원'
// current : 현재 줄의 맨 끝에 서 있는 '당번' (새로운 사람이 오면 손을 잡아줘야 함)

// 1. 상황 : 아무도 없을 때(head == NULL)
// if (head == NULL) {
//	 head = new_node;
// }
// current = new_node; // (if문 끝나고 실행)

// 현실: 운동장에 아무도 없습니다.

// 동작 :
// 첫 번째 신입(new_node)이 들어옵니다.
// 아무도 없으니 이 친구가 선두(head) 깃발을 듭니다. (head = new_node)
// 동시에, 이 친구는 줄의 맨 끝이기도 하죠? 그래서 당번 배지(current) 도 찹니다. (current = new_node)
//
// 결과 : 선두(head)이자 당번(current)인 첫 번째 사람이 서 있습니다.


// 2. 상황 : 두 번째 사람이 왔을 때(else)
// else {
//	 current->next = new_node;
// }
// current = new_node; // (if/else 끝나고 실행)
//
// 현실: 운동장에 첫 번째 사람(현재 current)이 서 있습니다.

// 동작 :
// 두 번째 신입(new_node)이 들어옵니다.
// else문 실행 : 현재 당번(current, 1번 사람)이 팔을 뻗어(next) 신입(new_node)의 손을 잡습니다. (연결 성사!)
// current->next = new_node;

// 중요한 순간: 이제 1번 사람은 더 이상 '맨 끝'이 아니죠 ?
// 1번 사람은 차고 있던 당번 배지(current)를 벗어서, 방금 들어온 신입(2번)에게 넘겨줍니다.
//	 current = new_node;

// 결과: 1번과 2번이 손을 잡았고, 배지(current)는 2번에게 갔습니다.


// 3. 상황 : 세 번째, 네 번째... (무한 반복)
// 이제부터는 계속 똑같습니다.
// 1. 새 신입이 온다.
// 2. 현재 배지를 단 사람(current)이 신입의 손을 잡는다(next).
// 3. 배지를 신입에게 넘겨준다(current = new_node).