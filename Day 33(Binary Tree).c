#include <stdio.h>
#include <stdlib.h>

struct Node {
	int data;
	struct Node* left;
	struct Node* right;
};

int main() {
	struct Node* root = malloc(sizeof(struct Node));
	struct Node* left_side = malloc(sizeof(struct Node));
	struct Node* right_side = malloc(sizeof(struct Node));
	
	root->data = 10;
	root->left = left_side;		// 왼쪽 오른쪽 지정 (서로 손잡기)
	root->right = right_side;

	left_side->data = 20;
	right_side->data = 30;

	printf("[이진 트리 생성 완료]\n루트 노드: %d\n↙     ↘\n%d    %d\n", root->data, root->left->data, root->right->data);
	printf("\n왼쪽 자식 데이터: %d\n오른쪽 자식 데이터: %d\n", left_side->data, right_side->data);

	free(root);
	free(left_side);
	free(right_side);
	printf("\n트리 메모리를 해제하고 프로그램을 종료합니다.\n");
	return 0;
}

// [추천 습관]
// 노드를 만들 때는 무조건** "여기가 끝이다(NULL)" * *라고 명시해 주는 것이 안전합니다.
// left_side->data = 20;
// left_side->left = NULL;  // "내 밑으로 더 없음!"
// left_side->right = NULL;

// right_side->data = 30;
// right_side->left = NULL;
// right_side->right = NULL;