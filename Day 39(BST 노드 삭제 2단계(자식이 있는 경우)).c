#include <stdio.h>
#include <stdlib.h>

// 오늘의 문법 설명: "후계자 찾기"
// 자식이 있는 노드를 지울 때는 단순히 지우는 게 아니라, 그 자리를 대신할** '후계자' * *를 세워야 트리의 규칙이 깨지지 않습니다.

// Case 2: 자식이 하나만 있는 경우
// 삭제될 노드의 부모에게 자신의 유일한 자식을 바로 연결해 줍니다. (할아버지가 손자의 손을 바로 잡는 셈입니다.)

// Case 3 : 자식이 둘 다 있는 경우(가장 중요!)
// 삭제될 노드보다 '살짝 더 큰 값'을 가진 노드를 찾아 그 자리에 앉힙니다.
// 그 값은 보통 '오른쪽 서브 트리에서 가장 작은 값'입니다. (오른쪽으로 한 번 간 뒤, 왼쪽 끝까지 내려가면 나옵니다.)

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

// 39일차 메인 메뉴: 자식 노드를 찾는 함수
struct Node* minValueNode(struct Node* node) {
	struct Node* current = node;
	// 왼쪽 끝까지 내려가서 가장 작은 값 찾기
	while (current && current->left != NULL)
		current = current->left;
	return current;
}

// 38일차 함수: 자식이 없는 노드(리프 노드(Leaf Node))를 삭제하는 함수 + 39일차 추가 내용
struct Node* deleteNode(struct Node* root, int key) {
	if (root == NULL) return root;

	// 1. 삭제할 노드 찾아 내려가기
	if (key < root->data)
		root->left = deleteNode(root->left, key); // 부모보다 작으니까 왼쪽으로 가서 시도.
	else if (key > root->data)
		root->right = deleteNode(root->right, key); // 부모보다 크니까 오른쪽으로 가서 시도.

	// 2. 삭제할 노드를 찾았을 때 (key == root->data)
	else {
		// Case 1: 자식이 없는 경우 (Leaf Node)
		if (root->left == NULL && root->right == NULL) { // 부모 노드는 이 조건에 걸려 삭제가 안 됨. return root을 뱉어내고 끝나버림.
			free(root);
			return NULL; // 부모에게 "나 이제 없으니 NULL로 채워라"고 알림
		}

		// (39일차 추가) 자식이 있는 경우 (Root Node)
		else {
			// Case 2: 자식이 하나인 경우: 자식을 부모에게 반환 후 root는 free
			// 1. 만약 왼쪽 자식이 없다면? (당연히 오른쪽 자식만 있다는 뜻!)
			if (root->left == NULL) {
				struct Node* temp = root->right; // 1) 손자의 주소를 temp에 안전하게 보관!
				free(root);                      // 2) 아빠(나)는 미련 없이 떠납니다.
				return temp;                     // 3) 할아버지에게 손자의 주소를 쥐어줍니다!
			}
			// 2. 만약 오른쪽 자식이 없다면? (당연히 왼쪽 자식만 있다는 뜻!)
			else if (root->right == NULL) {
				struct Node* temp = root->left;  // 1) 손자의 주소를 temp에 안전하게 보관!
				free(root);                      // 2) 아빠(나)는 떠납니다.
				return temp;                     // 3) 할아버지에게 손자의 주소를 쥐어줍니다!
			}

			// Case 3: 자식이 둘인 경우 (root->left != NULL && root->right != NULL)
			else {
				// 1. 오른쪽 서브트리에서 가장 작은 놈(후계자)을 찾는다.
				struct Node* temp = minValueNode(root->right);

				// 2. 후계자의 '데이터(값)'만 내 자리로 슬쩍 복사해 온다. (물리적 노드 교체 X)
				root->data = temp->data;

				// 3. 오른쪽 자식 트리에게 명령한다: 
				// "방금 내가 값을 뺏어온 그 녀석(temp->data), 네가 알아서 찾아서 지워줘!"
				root->right = deleteNode(root->right, temp->data);
			}
		}
	}
	return root;
}

int main() {
	struct Node* root = NULL;	
	struct Node* left_side = NULL;
	struct Node* right_side = NULL;

	root = insert(root, 30);
	root = insert(root, 20);
	root = insert(root, 40);

	printf("[삭제 전 중위 순회]\n");
	inorder(root); // 출력 함수
	printf("끝\n");

	root = deleteNode(root, 30); // 루트 노드 삭제.
	printf("\n루트(30) 노드를 삭제합니다.\n");

	printf("\n[삭제 후 중위 순회]\n");
	inorder(root); // 출력 함수
	printf("끝\n");

	printf("\n트리 메모리를 정리합니다.\n");
	deleteTree(root);	// 메모리 정리하는 함수 실행
	root = NULL;		// Dangling Pointer 방지

	printf("\n프로그램을 종료합니다.\n");
	return 0;
}

// 💡(보너스) 고수들의 시크릿 : "Case 1과 2는 사실 한 몸이다?"
// 유저님이 짜신 코드는 가독성이 미쳤습니다.Case 1, 2, 3이 명확히 나뉘어 있어서 나중에 누가 봐도 이해하기 쉽죠.
// 그런데 실무를 하다 보면 고수들이 이걸 더 짧게 줄여놓은 걸 보게 되실 텐데, 원리만 살짝 알려드릴게요.

// 유저님의 Case 2 코드를 잘 보세요.

// if (root->left == NULL) {
// 	 struct Node* temp = root->right;
//	 free(root);
//	 return temp;
// }

// 만약 자식이 아무도 없는 리프 노드(Case 1) 라면 어떨까요 ?
// 당연히 root->left == NULL 조건에 걸려서 들어갑니다.그리고 temp에는 root->right를 넣는데, 어차피 오른쪽 자식도 없으니 temp는 NULL이 됩니다.그걸 그대로 return 하죠 ?
// 즉, Case 2 로직이 알아서 Case 1(자식이 0개인 상황)까지 완벽하게 커버해 준다는 사실!
// 그래서 고수들은 굳이 Case 1을 따로 적지 않고 코드를 훅 줄여버리기도 합니다. (물론 지금 유저님처럼 명시적으로 나눠놓는 것이 학습과 유지보수에는 훨씬 좋습니다!)