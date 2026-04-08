#include <stdio.h>
#include <stdlib.h>

// 교수님 교안(7.트리.pdf) 31~32페이지에 따르면, 순회는 "방문(V)을 언제 하느냐"에 따라 이름이 결정됩니다.
// 전위 순회(Preorder): 루트를 먼저(Pre) 방문: V > L > R
// 후위 순회(Postorder): 루트를 나중에(Post) 방문: L > R > V

typedef struct TreeNode {
    int data;
    struct TreeNode* left, * right;
} TreeNode;

// 전위 순회 (VLR) - 교안 31p
void preorder(TreeNode* root) {
    if (root != NULL) {
        // 1. 루트 방문 -> 2. 왼쪽 순회 -> 3. 오른쪽 순회
        printf("[%d] > ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

// 후위 순회 (LRV) - 교안 32p
void postorder(TreeNode* root) {
    if (root != NULL) {
        // 1. 왼쪽 순회 -> 2. 오른쪽 순회 -> 3. 루트 방문(printf)
        postorder(root->left);
        postorder(root->right);
        printf("[%d] > ", root->data);
    }
}

int main(void) {
    // 10(루트), 20(왼쪽), 30(오른쪽) 트리 세팅
    TreeNode* n1 = (TreeNode*)malloc(sizeof(TreeNode));
    TreeNode* n2 = (TreeNode*)malloc(sizeof(TreeNode));
    TreeNode* n3 = (TreeNode*)malloc(sizeof(TreeNode));
    n1->data = 10; n1->left = n2; n1->right = n3;
    n2->data = 20; n2->left = NULL; n2->right = NULL;
    n3->data = 30; n3->left = NULL; n3->right = NULL;

    printf("전위 순회 결과: "); preorder(n1); printf("\n");
    printf("후위 순회 결과: "); postorder(n1); printf("\n");

    free(n1); free(n2); free(n3);
    return 0;
}