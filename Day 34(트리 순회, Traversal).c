#include <stdio.h>
#include <stdlib.h>

struct Node {
	int data;
	struct Node* left;
	struct Node* right;
};

void inorder(struct Node* ptr) {
	if (ptr != NULL) {				// 탈출 조건: 노드가 없으면 돌아가기
		inorder(ptr->left);			// 1. 왼쪽으로 끝까지 가기
		printf("%d ", ptr->data);	// 2. 현재 노드 데이터 출력
		inorder(ptr->right);		// 3. 오른쪽으로 가기
	}
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

	printf("[트리 중위 순회 결과]\n");
	inorder(root);

	free(root);
	free(left_side);
	free(right_side);

	printf("\n트리 메모리를 해제하고 프로그램을 종료합니다.\n");
	return 0;
}

// 🔍 트리의 마법 : 왜 20 -> 10 -> 30 일까 ?
// 유저님이 작성하신 코드가 컴퓨터 내부에서 어떻게 움직였는지 상상해 볼까요 ?

// inorder(10) 호출 -> "잠깐 출력 멈추고 왼쪽(left_side)으로 먼저 가!"
// inorder(20) 호출 -> "왼쪽 끝이네? 더 없으니 내 값 20 출력!"
// 다시 10으로 돌아옴 -> "이제 내 차례군. 10 출력!"
// 오른쪽(right_side)으로 이동->inorder(30) 호출 -> "30 출력!"