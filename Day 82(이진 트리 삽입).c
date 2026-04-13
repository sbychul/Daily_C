#include <stdio.h>
#include <stdlib.h>

// 오늘의 핵심 로직: 재귀적 연결
// 탐색과 다른 점은 재귀 호출의 반환값(Return Value)을 현재 노드의 자식 포인터에 대입해줘야 한다는 것입니다.
// node->left = insert_node(node->left, key); : "왼쪽으로 가서 삽입하고, 새로 만들어진(혹은 유지된) 노드 주소를 내 왼쪽 손(left)에 다시 연결해!"라는 뜻입니다.
// 오른쪽도 똑같은 방식!!

typedef struct TreeNode {
    int key;
    struct TreeNode* left, * right;
} TreeNode;

// 새 노드를 생성하는 보조 함수
TreeNode* new_node(int item) {
    TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

// 🚀 [오늘의 미션] 이진 탐색 트리 삽입 함수 구현
TreeNode* insert_node(TreeNode* node, int key) {
    // 1. 트리가 비어있거나 탐색 끝에 빈자리를 찾은 경우
    if (node == NULL) {
        return new_node(key); // 새 노드를 생성해서 위로 던져줌
    }

    // 2. 이미 같은 키가 있다면 삽입하지 않음 (BST 규칙)
    if (key == node->key) {
        return node;
    }

    // 3. 삽입할 값(key)이 현재 노드의 값보다 작다면?
    if (key < node->key) {
        // 왼쪽 자식에게 삽입을 지시하고, 바뀐(혹은 생성된) 주소를 내 왼쪽 손에 저장
        node->left = insert_node(node->left, key);
    }
    // TODO: 4. 삽입할 값(key)이 현재 노드의 값보다 크다면?
    else {
        // 오른쪽 자식에게 삽입을 지시하고, 바뀐 주소를 내 오른쪽 손에 저장
        node->right = insert_node(node->right, key);
    }

    // 최종적으로 연결이 완료된 현재 노드의 주소를 반환
    return node;
}

// 확인을 위한 중위 순회 (오름차순 출력)
void inorder(TreeNode* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("[%d] ", root->key);
        inorder(root->right);
    }
}

int main(void) {
    TreeNode* root = NULL;

    // 데이터 삽입
    root = insert_node(root, 35);
    root = insert_node(root, 18);
    root = insert_node(root, 7);
    root = insert_node(root, 26);
    root = insert_node(root, 48);
    root = insert_node(root, 60);

    printf("BST 중위 순회 결과 (오름차순): ");
    inorder(root);
    printf("\n");

    return 0;
}