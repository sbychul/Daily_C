#include <stdio.h>
#include <stdlib.h>

// 오늘의 문법 설명 : "왼쪽은 작게, 오른쪽은 크게"
// 이진 탐색 트리는 일반 이진 트리에 아주 강력한 '정렬 규칙'이 추가된 형태입니다.

// 규칙
// 1. 왼쪽 자식 노드는 부모 노드보다 작은 값이어야 합니다.
// 2. 오른쪽 자식 노드는 부모 노드보다 큰 값이어야 합니다.
// 장점 : 이 규칙 덕분에 원하는 숫자를 찾을 때마다 탐색 범위가 절반으로 줄어들어, 엄청난 속도로 데이터를 찾을 수 있습니다.

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

// 36일차 메인 메뉴:
struct Node* insert(struct Node* ptr, int data) { // insert라는 함수의 반환형이 struct Node* 임!! 구조체의 주소를 뱉어내는 함수.
	if (ptr == NULL) { // 빈자리를 찾았다면!
		struct Node* new_node = malloc(sizeof(struct Node));
		new_node->data = data;
		new_node->left = new_node->right = NULL; // 빈 자리의 주인의 양 손은 비워둠.
		return new_node;
	}

	if (data < ptr->data)		// 부모보다 작으면 왼쪽으로! 왼쪽은 작게..
		ptr->left = insert(ptr->left, data);
	else if (data > ptr->data)	// 부모보다 크면 오른쪽으로! 오른쪽은 크게!!
		ptr->right = insert(ptr->right, data);

	return ptr; // 완성된 트리의 주소를 반환
}

int main() {
	struct Node* root = NULL;	// 일단 값을 넣을 구조체들을 만들음.
	struct Node* left_side = NULL;
	struct Node* right_side = NULL;

	// insert 함수를 이용하여 값을 넣기.
	root = insert(root, 30);
	/* 1. 첫 번째 삽입 : root = insert(root, 30);
	이때 메인 함수의 root는 NULL입니다.
	insert 함수가 새 땅을 파서 30을 넣고, 그 주소(예: 100번지)를 반환합니다.
	메인 함수에서 root = 100번지; 로 반드시 받아줘야 비로소 트리의 뿌리가 생깁니다. (안 받으면 뿌리를 영영 잃어버립니다!) */

	insert(root, 20);
	insert(root, 40);
	/* 2. 두 번째 삽입 : insert(root, 20); (안 받고 그냥 던짐)
	이제 root는 100번지(데이터 30)입니다.insert(100번지, 20)이 호출되죠.
	함수 내부로 들어갑니다 : 20 < 30 이므로 다음 코드가 실행됩니다.

	ptr->left = insert(ptr->left, 20);

	바로 여기입니다! 함수 내부에서 자기들끼리 20짜리 새 노드를 만들고, 그 주소를 ptr->left(즉, root의 왼쪽 손)가 아주 찰떡같이 받아줍니다.
	연결이 끝난 후, 함수는 마지막에 return ptr; (원래의 100번지)을 뱉어냅니다.
	메인 함수에서는 이 반환값을 어떤 변수에도 담지 않고 허공에 날려버리지만, 이미 트리 내부의 left 연결은 완료되었기 때문에 아무 문제가 없는 것입니다. */

	printf("[이진 탐색 트리 데이터 삽입 완료]\n중위 순회 결과 (오름차순): ");
	inorder(root);	// 출력 함수 실행
	printf("끝\n"); // 출력 함수가 끝나버리면 화살표를 마지막으로 끝나버림. 깨끗하게 마무리해주기.

	printf("\n트리 메모리를 정리합니다.\n");
	deleteTree(root);	// 메모리 정리하는 함수 실행
	root = NULL;		// Dangling Pointer 방지

	printf("\n프로그램을 종료합니다.\n");
	return 0;
}

// 💡[알고 있으면 좋은 점] 그래도 다 받는 습관이 좋은 이유
// 지금 유저님의 코드는 완벽하게 동작하고 논리적으로도 전혀 하자가 없습니다.하지만 C언어를 다루는 많은 개발자들은 보통 아래처럼 코드를 작성합니다.

// root = insert(root, 30);
// root = insert(root, 20);
// root = insert(root, 40);

// 왜 굳이 계속 root = 으로 받을까요 ?

// 1. 일관성 : "이 함수는 결과를 뱉어내니까 받는다"는 규칙을 통일하기 위해서입니다.

// 2. 안전장치(더 심화된 트리 대비) : 나중에 자료구조를 더 깊이 배우시면, 트리가 스스로 한쪽으로 치우치지 않게 균형을 맞추는
// 'AVL 트리'나 '레드-블랙 트리'라는 것을 배우게 됩니다. 이때는 트리가 회전하면서 뿌리(root) 노드 자체가 30에서 20이나 40으로 바뀔 수도 있습니다.
// 뿌리가 바뀌었을 때 반환값을 root로 다시 받아주지 않으면 큰 버그가 생기기 때문에, 미리 안전하게 받는 습관을 들이는 것입니다.