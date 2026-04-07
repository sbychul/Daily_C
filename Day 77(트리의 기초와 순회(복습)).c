#include <stdio.h>
#include <stdlib.h>

// 노드의 구조 (교안 23p)
// 연결 리스트와 달리, 이진 트리의 노드는 왼쪽 자식(left)과 오른쪽 자식(right)을 가리키는 두 개의 포인터를 가집니다.

// 트리의 순회 (교안 27p ~ 32p)트리는 일렬로 서 있지 않기 때문에, 어떤 순서로 방문할지 규칙을 정해야 합니다.
// 교수님 교안에서는 다음 3가지를 강조하십니다.
// 전위 순회 (Preorder, VLR): 루트 > 왼쪽 > 오른쪽
// 중위 순회 (Inorder, LVR): 왼쪽 > 루트 > 오른쪽
// 후위 순회 (Postorder, LRV): 왼쪽 > 오른쪽 > 루트 

// 교안 23p: 링크 표현법 구조체 
typedef struct TreeNode {
    int data;
    struct TreeNode* left, * right;
} TreeNode;

// 🚀 [오늘의 미션] 교안 32p: 중위 순회(LVR) 알고리즘 구현
void inorder(TreeNode* root) {
    if (root != NULL) { // 노드가 비어있지 않다면
        // 1. 왼쪽 서브트리(root->left)를 순회하도록 자기 자신(inorder)을 호출
        inorder(root->left);

        // 2. 현재 노드(root)의 데이터를 출력
        printf("[%d] ", root->data);

        // 3. 오른쪽 서브트리(root->right)를 순회하도록 자기 자신(inorder)을 호출
        inorder(root->right);
    }
}

int main(void) {
    // 교안 24p: 3개의 노드 동적 할당
    TreeNode* n1 = (TreeNode*)malloc(sizeof(TreeNode));
    TreeNode* n2 = (TreeNode*)malloc(sizeof(TreeNode));
    TreeNode* n3 = (TreeNode*)malloc(sizeof(TreeNode));

    // 교안 25p: 데이터 삽입 및 링크 연결
    n1->data = 10;
    n1->left = n2;
    n1->right = n3;

    n2->data = 20;
    n2->left = NULL;
    n2->right = NULL;

    n3->data = 30;
    n3->left = NULL;
    n3->right = NULL;

    printf("중위 순회 결과: ");
    inorder(n1); // n1이 트리의 루트 노드 역할을 합니다.
    printf("\n");

    // 메모리 해제
    free(n1); free(n2); free(n3);

    return 0;
}