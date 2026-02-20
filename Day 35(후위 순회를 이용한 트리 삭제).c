#include <stdio.h>
#include <stdlib.h>

struct Node {
	int data;
	struct Node* left;
	struct Node* right;
};

void deleteTree(struct Node* ptr) {
	if (ptr == NULL) return;

	deleteTree(ptr->left);   // 1. 왼쪽 자식부터 지우러 가기
	deleteTree(ptr->right);  // 2. 오른쪽 자식 지우러 가기

	printf("%d번 노드 삭제 중...\n", ptr->data); // 3. 자식들이 다 죽었으니 이제 내가 죽을 차례
	free(ptr);
}

int main() {
	struct Node* root = malloc(sizeof(struct Node));
	struct Node* left_side = malloc(sizeof(struct Node));
	struct Node* right_side = malloc(sizeof(struct Node));
	
	root->data = 10;
	root->left = left_side;		// 왼쪽 오른쪽 지정 (서로 손잡기)
	root->right = right_side;

	left_side->data = 20;
	left_side->left = NULL;		// 이 밑으로 더 없음을 표현
	left_side->right = NULL;

	right_side->data = 30;
	right_side->left = NULL;	// 똑같음
	right_side->right = NULL;

	printf("[트리 삭제 프로세스 시작]\n");
	
	deleteTree(root);
	root = NULL; // Dangling Pointer 방지
	printf("\n모든 트리 메모리가 안전하게 해제되었습니다.\n");
	return 0;
}

// 1. 오늘의 문법 설명: "자식부터 챙기는 후위 순회(Post-order)"
// 트리를 삭제할 때는 순서가 매우 중요합니다. 만약 루트(부모) 노드를 먼저 지워버리면,
// 자식 노드들의 주소를 잃어버려 메모리에서 영영 찾을 수 없게 됩니다(메모리 누수).
// 그래서 반드시 자식들을 먼저 지우고 나서 나(부모)를 지워야 합니다.이때 사용하는 방식이 바로 후위 순회입니다.
//
// 후위 순회 순서 : 왼쪽 자식 → 오른쪽 자식 → 나(부모)
// 활용 : 트리 전체 삭제, 디렉토리 용량 계산 등(하위 항목이 먼저 계산되어야 하는 경우).


// 👻 댕글링 포인터(Dangling Pointer)란 ?
// 'Dangling(댕글링)'은 영어로 '대롱대롱 매달려 있는', '허공을 떠도는'이라는 뜻입니다. 즉, '허공을 가리키는 미아 포인터'를 의미합니다.
// 상황을 한 번 상상해 볼까요 ?

// 건물 짓기(malloc) : 유저님이 주소 '100번지'에 10번 노드라는 건물을 지었습니다.그리고 root라는 수첩에 '100번지'라고 적어두었습니다.
// 건물 철거(free) : deleteTree(root) 함수를 실행해서 건물을 흔적도 없이 철거하고 땅을 운영체제에 반납했습니다.
// 문제 발생(Dangling 상태) : 건물은 사라졌는데, 유저님의 root 수첩에는 여전히 '100번지'라는 주소가 적혀있습니다!

// 이때 root 포인터가 바로 '댕글링 포인터'입니다.가리키는 곳에 가봤자 이제 내 건물이 없기 때문이죠.

// 💀 왜 위험한가요 ?
// 만약 유저님이 철거 사실을 깜빡 잊고, 나중에 코드 밑에서 실수로 printf("%d", root->data); 를 실행하면 어떻게 될까요 ?
// 운영체제는 "어? 너 이미 반납한 빈 땅(혹은 남이 새로 산 땅)에 왜 무단 침입해!" 하면서 곧바로 Segmentation Fault를 띄우고 프로그램을 강제 종료시켜버립니다.