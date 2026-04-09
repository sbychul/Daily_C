#include <stdio.h>
#include <stdlib.h>

// 트리의 높이란 루트에서 가장 깊은 단말 노드까지의 길이를 말합니다.
// 단말 노드의 갯수를 세는 문제와 논리가 99 % 똑같습니다.
// 단지 '더하기(+)' 대신 '큰 값 고르기(MAX)'를 한다는 점만 다릅니다.

// 매크로 함수, 더 큰 값을 반환함.
#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct TreeNode {
    int data;
    struct TreeNode* left, * right;
} TreeNode;

// 🚀 [다음 미션] 트리의 높이 구하기
int get_height(TreeNode* node) {
    // 1. 노드가 비어있다면 높이는 0
    if (node == NULL) {
        return 0;
    }
    //  2. 왼쪽 서브트리의 높이를 재귀 호출을 이용하여 구함.
    int left_height = get_height(node->left);
    // 3. 같은 방식으로 오른쪽의 높이를 구함
    int right_height = get_height(node->right);

    // 4. 둘 중 더 큰 값에 1(자기 자신의 층수)을 더해서 반환
    return MAX(left_height, right_height) + 1; // MAX 매크로 함수를 이용하여 더 큰 값을 받아 1을 더해 반환.
}

int main(void) {
    // 3층짜리 트리 생성
    //       10 (3층)
    //     /    \
    //   20      30 (2층)
    //  /  
    // 40 (1층)

    TreeNode* n4 = (TreeNode*)malloc(sizeof(TreeNode)); n4->data = 40; n4->left = NULL; n4->right = NULL;
    TreeNode* n3 = (TreeNode*)malloc(sizeof(TreeNode)); n3->data = 30; n3->left = NULL; n3->right = NULL;
    TreeNode* n2 = (TreeNode*)malloc(sizeof(TreeNode)); n2->data = 20; n2->left = n4; n2->right = NULL;
    TreeNode* n1 = (TreeNode*)malloc(sizeof(TreeNode)); n1->data = 10; n1->left = n2; n1->right = n3;

    printf("트리의 높이: %d\n", get_height(n1)); // 기대 출력: 3

    free(n1); free(n2); free(n3); free(n4);
    return 0;
}