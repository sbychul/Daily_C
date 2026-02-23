#include <stdio.h>
#include <stdlib.h>

// 오늘의 문법 설명: "나무 가지치기"
// BST에서 노드를 삭제할 때는 삭제할 노드의 '자식 수'에 따라 전략이 달라집니다.
// Case 1: 자식이 없는 노드(Leaf Node) 삭제(오늘의 주제)
// 삭제가 가장 쉽습니다. 그냥 해당 노드의 메모리를 해제(free)하고, 부모 노드가 이 노드를 가리키던 손을 NULL로 바꿔주면 끝입니다.

struct Node {
	int data;
	struct Node* left;
	struct Node* right;
};

// 34일차 함수: 트리를 탐색하며 출력할 예정.
void inorder(struct Node* ptr) { 
	if (ptr != NULL) {	
		inorder(ptr->left);	
		printf("%d -> ", ptr->data);
		inorder(ptr->right);	
	}
}

// 35일차 함수: 구조체의 메모리 할당을 해제할 예정.
void deleteTree(struct Node* ptr) { 
	if (ptr == NULL) return;
	
	deleteTree(ptr->left); 
	deleteTree(ptr->right); 

	printf("%d번 노드 삭제 중...\n", ptr->data); 
	free(ptr);
}

// 36일차 함수: 최초에 부모 노드에게 값을 넣고, 부모보다 작으면 왼쪽으로, 크면 오른쪽으로 보내는 함수.
struct Node* insert(struct Node* ptr, int data) { 
	if (ptr == NULL) { 
		struct Node* new_node = malloc(sizeof(struct Node));
		new_node->data = data;
		new_node->left = new_node->right = NULL; 
		return new_node;
	}

	if (data < ptr->data)
		ptr->left = insert(ptr->left, data);
	else if (data > ptr->data)	
		ptr->right = insert(ptr->right, data);

	return ptr; 
}

// 37일차 함수: 노드에서 key값이 있는지 탐색하는 함수.
struct Node* search(struct Node* ptr, int key) {
	if (ptr == NULL || ptr->data == key) 
		return ptr;

	if (key < ptr->data) 
		return search(ptr->left, key);
	else  
		return search(ptr->right, key);
}

// 38일차 메인 메뉴: 자식이 없는 노드(리프 노드(Leaf Node)) 삭제
struct Node* deleteNode(struct Node* root, int key) {
	if (root == NULL) return root;

	// 1. 삭제할 노드 찾아 내려가기
	if (key < root->data)
		root->left = deleteNode(root->left, key); // 부모보다 작으니까 왼쪽으로 가서 시도.
	else if (key > root->data)
		root->right = deleteNode(root->right, key); // 부모보다 크니까 오른쪽으로 가서 시도.

	// 2. 삭제할 노드를 찾았을 때 (key == root->data)
	else {
		// 자식이 없는 경우 (Leaf Node)
		if (root->left == NULL && root->right == NULL) { // 자식이 둘일 때 하나만 지우면 이 조건에 걸려서 삭제가 안 됨.
			free(root);
			return NULL; // 부모에게 "나 이제 없으니 NULL로 채워라"고 알림
		}
		// 자식이 있는 경우, 자식이 둘인 경우(Case 2, 3)는 내일 다룹니다!
	}
	return root;
}

int main() {
	struct Node* root = NULL;	
	struct Node* left_side = NULL;
	struct Node* right_side = NULL;

	root = insert(root, 30);
	root = insert(root, 20);
	root = insert(root, 40); // 20, 30, 40이 들어있는 트리 형성.

	printf("[삭제 전 중위 순회]\n");
	inorder(root); // 출력 함수
	printf("끝\n");

	root = deleteNode(root, 20); // root 노드에서 20 값을 갖고 있는 노드를 삭제.
	printf("\n20번 노드를 삭제합니다.\n");

	printf("\n[삭제 후 중위 순회]\n");
	inorder(root); // 출력 함수
	printf("끝\n");

	printf("\n트리 메모리를 정리합니다.\n");
	deleteTree(root);	// 메모리 정리하는 함수 실행
	root = NULL;		// Dangling Pointer 방지

	printf("\n프로그램을 종료합니다.\n");
	return 0;
}