#include <stdio.h>
#include <stdlib.h>

// 오늘의 핵심 로직: "재귀적으로 합치기"
// 교수님의 교안(7.트리.pdf) 40페이지 부근의 내용을 응용한 문제입니다.
// 트리의 모든 노드를 방문하면서 특정 조건(자식이 없는 노드)을 만족하는 경우를 카운트해야 합니다.

// Case 1 : 노드가 NULL이면 ? 당연히 개수는 0입니다.
// Case 2 : left와 right가 모두 NULL이면 ? 이것이 바로 단말 노드이므로 1을 반환합니다.
// Case 3 : 그 외의 경우(자식이 있는 경우)는 ? (왼쪽 서브트리의 단말 노드 수) + (오른쪽 서브트리의 단말 노드 수)를 수행합니다.

typedef struct TreeNode {
    int data;
    struct TreeNode* left, * right;
} TreeNode;

// 🚀 [오늘의 미션] 단말 노드 개수 구하기
int get_leaf_count(TreeNode* node) {
    // 1. 노드가 비어있는 경우 (기본 종료 조건)
    if (node == NULL) {
        return 0;
    }

    // 2. 현재 노드가 단말 노드(왼쪽, 오른쪽 자식이 모두 NULL)인지 확인
    if (node->left == NULL && node->right == NULL) {
        return 1; // 단말 노드를 발견했으므로 1을 반환!
    }

    // 3. 단말 노드가 아니라면, 왼쪽과 오른쪽 서브트리로 이동.
    return get_leaf_count(node->left) + get_leaf_count(node->right); // 각 서브트리의 단말 노드 갯수를 반환.
}

int main(void) {
    // 트리 구조 생성
    //       10 (root)
    //     /    \
    //   20      30 (leaf)
    //  /  \
    // 40  50 (leaf)
    // (leaf)

    TreeNode* n5 = (TreeNode*)malloc(sizeof(TreeNode)); n5->data = 50; n5->left = NULL; n5->right = NULL;
    TreeNode* n4 = (TreeNode*)malloc(sizeof(TreeNode)); n4->data = 40; n4->left = NULL; n4->right = NULL;
    TreeNode* n3 = (TreeNode*)malloc(sizeof(TreeNode)); n3->data = 30; n3->left = NULL; n3->right = NULL;
    TreeNode* n2 = (TreeNode*)malloc(sizeof(TreeNode)); n2->data = 20; n2->left = n4; n2->right = n5;
    TreeNode* n1 = (TreeNode*)malloc(sizeof(TreeNode)); n1->data = 10; n1->left = n2; n1->right = n3;

    printf("단말 노드의 개수: %d\n", get_leaf_count(n1));

    free(n1); free(n2); free(n3); free(n4); free(n5);
    return 0;
}