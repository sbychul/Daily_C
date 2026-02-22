#include <stdio.h>
#include <stdlib.h>

// 오늘의 문법 설명 : "비교하며 내려가기"
// 이진 탐색 트리의 진가는 '검색'에서 나타납니다.모든 노드가 "나보다 작으면 왼쪽, 크면 오른쪽"이라는 규칙을 지키고 있기 때문에,
// 우리는 매 순간 탐색 범위를 절반씩 날려버리며 빛의 속도로 값을 찾을 수 있습니다.

// 탐색 로직 :
// 찾으려는 값이 현재 노드보다 작으면 : 왼쪽 자식으로 이동.
// 찾으려는 값이 현재 노드보다 크면 : 오른쪽 자식으로 이동.
// 찾으려는 값과 현재 노드가 같으면 : "찾았다!" (노드 주소 반환)
// 끝까지 내려갔는데 NULL을 만나면 : "값이 없네?" (NULL 반환)

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
	if (ptr == NULL) { // 빈자리를 찾았다면!
		struct Node* new_node = malloc(sizeof(struct Node));
		new_node->data = data;
		new_node->left = new_node->right = NULL; 
		return new_node;
	}

	if (data < ptr->data)
		ptr->left = insert(ptr->left, data);
	else if (data > ptr->data)	
		ptr->right = insert(ptr->right, data);

	return ptr; // 완성된 트리의 주소를 반환
}

// 37일차 메인 메뉴: 탐색 함수
struct Node* search(struct Node* ptr, int key) {
	if (ptr == NULL || ptr->data == key) // 1. 없거나 찾았거나
		return ptr;

	if (key < ptr->data) // 2. 찾으려는 게 더 작으면 왼쪽으로
		return search(ptr->left, key);
	else                 // 3. 찾으려는 게 더 크면 오른쪽으로
		return search(ptr->right, key);
}

int main() {
	struct Node* root = NULL;	
	struct Node* left_side = NULL;
	struct Node* right_side = NULL;
	int finding = 0; // 찾을 때 쓸 변수

	root = insert(root, 30);
	root = insert(root, 20);
	root = insert(root, 40); // 20, 30, 40이 들어있는 트리 형성.

	printf("찾고 싶은 숫자를 입력하세요: ");
	scanf("%d", &finding);

	if (search(root, finding) == NULL) {
		printf("실패: %d은(는) 트리에 없습니다.\n", finding);
	}
	else {
		printf("성공: %d을(를) 찾았습니다!\n", finding);
	}

	printf("\n트리 메모리를 정리합니다.\n");
	deleteTree(root);	// 메모리 정리하는 함수 실행
	root = NULL;		// Dangling Pointer 방지

	printf("\n프로그램을 종료합니다.\n");
	return 0;
}