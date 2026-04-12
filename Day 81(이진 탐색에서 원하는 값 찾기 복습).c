#include <stdio.h>
#include <stdlib.h>

// 1. 오늘의 핵심 문법 : 재귀적 탐색(교안 80p)
// 원하는 숫자(key)를 찾기 위해 루트부터 비교를 시작합니다.
// 
// key == node->key : 보물 발견! 해당 노드를 반환합니다.
// key < node->key : 찾는 값이 더 작으니 왼쪽 서브트리로 가서 다시 찾으라고 시킵니다.
// key > node->key : 찾는 값이 더 크니 오른쪽 서브트리로 가서 다시 찾으라고 시킵니다.

typedef struct TreeNode {
    int key;
    struct TreeNode* left, * right;
} TreeNode;

// 🚀 [오늘의 미션] 이진 탐색 트리 탐색 함수 구현
TreeNode* search(TreeNode* node, int key) {
    // 1. 탐색 실패: 노드가 NULL이면 더 이상 갈 곳이 없으므로 NULL 반환
    if (node == NULL) return NULL;

    // 2. 탐색 성공: 현재 노드의 값이 찾는 값(key)과 같은 경우
    if (key == node->key) {
        return node;
    }

    // 3. 찾는 값(key)이 현재 노드의 값(node->key)보다 작다면?
    if (key < node->key) {
        // 작은 값은 왼쪽에 있음, 왼쪽으로 이동하여 찾기.
        return search(node->left, key);
    }
    // 4. 찾는 값(key)이 현재 노드의 값보다 크다면?
    else {
        // 큰 값은 오른쪽에 있음, 오른쪽으로 이동하여 찾기.
        return search(node->right, key);
    }
}

// 노드 생성을 위한 보조 함수
TreeNode* new_node(int item) {
    TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

int main(void) {
    // BST 구축 (교안 88p 예시 참고)
    //        30
    //       /  \
    //     20    40
    //    /        \
    //  10          50
    TreeNode* root = new_node(30);
    root->left = new_node(20);
    root->right = new_node(40);
    root->left->left = new_node(10);
    root->right->right = new_node(50);

    int target = 40;
    TreeNode* result = search(root, target);

    if (result != NULL)
        printf("이진 탐색 트리에서 %d을(를) 발견함!\n", result->key);
    else
        printf("이진 탐색 트리에서 %d을(를) 발견하지 못함.\n", target);

    return 0;
}