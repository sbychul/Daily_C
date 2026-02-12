#include <stdio.h>
#include <stdlib.h>

struct Node {
	int data;
	struct Node* next;
};

int main() {
	int nodes_count = 0;
	while (1) {
		printf("정의할 노드의 갯수를 입력하세요: ");
		if (scanf("%d", &nodes_count) == 0) {
			printf("\n입력 형식이 올바르지 않습니다. 양의 정수를 입력하세요.\n");
			while (getchar() != '\n'); // 예외 처리 1, 문자 입력 방지
			continue;
		}
		if (nodes_count < 1) { // 예외 처리 2, 음의 정수를 입력할 경우
			printf("\n입력된 노드의 갯수가 잘못되었습니다. 양의 정수를 입력하세요.\n");
		}
		else { break; }
	}

    struct Node* head = NULL;    // 첫 번째 노드(머리)를 가리킬 포인터
    struct Node* current = NULL; // 마지막 노드(꼬리)를 따라다닐 포인터

    // 1. 노드 생성 및 연결 (반복문)
    for (int i = 1; i <= nodes_count; i++) {
        // [1단계] 새 집 짓기 (malloc)
        // 매번 반복할 때마다 새로운 메모리 번지(예: 100번지, 200번지...)가 생깁니다!
        struct Node* new_node = malloc(sizeof(struct Node));
        new_node->data = i;
        new_node->next = NULL; // 새 집 뒤에는 아직 아무것도 없음

        // [2단계] 집 연결하기
        if (head == NULL) {
            // 첫 번째 집이라면? 머리(head)가 이 집을 기억하게 함
            head = new_node;
        }
        else {
            // 이미 집이 있다면? 
            // 현재 마지막 집(current)의 뒷문(next)을 새 집(new_node)으로 연결!
            current->next = new_node;
        }

        // [3단계] 정비사 이동 (가장 중요!)
        // 방금 지은 집이 이제 '맨 마지막 집'이 되었으니, current를 그리로 옮김
        current = new_node;
    }

    // 2. 출력 (head부터 따라가며 출력)
    printf("\n[생성된 연결 리스트]\n");
    struct Node* temp = head; // 탐색용 임시 포인터
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next; // 다음 칸으로 이동
    }
    printf("NULL\n");

    // 3. 메모리 해제 (숙제: 이 부분은 일단 생략해도 좋습니다!)

    return 0;
}

// [상황 1: i = 1일 때]
// 1. malloc으로 100번지에 집을 짓습니다. (값: 1)
// [new_node] ----->[100번지(1)]

// 2. 연결합니다.
// [head] --------->[100번지(1)]
// [current] ------ > [100번지(1)]

// ----------------------------------

// [상황 2: i = 2일 때]
// 1. malloc으로 200번지에 '새로운' 집을 짓습니다. (값: 2)
// ★중요: new_node 변수는 이제 200번지를 가리킵니다!
// [new_node] ----->[200번지(2)]

// 2. 연결합니다(current->next = new_node)
// 아까 current는 100번지였죠 ?
// 100번지 집의 '다음' 칸에 200번지를 적습니다.
// [100번지(1)] ->[200번지(2)]

// 3. 정비사 이동(current = new_node)
// 이제 current도 200번지로 이동합니다.
// [current] ------ > [200번지(2)]

// malloc을 할 때마다 절대 사라지지 않는 새 집이 지어집니다.
// new_node는 그 집을 지을 때 잠깐 쓰 '공사 현장 소장님'일 뿐입니다.소장님이 다른 현장(200번지)으로 떠나도, 100번지 집은 안 무너집니다.
// 우리는 소장님이 떠나기 전에, 앞집(current)의 대문에다가 새 집 주소를 적어놨기 때문에 연결이 유지되는 것입니다.