#include <stdio.h>
#include <stdlib.h>

// BST에서 노드를 삭제할 때는 자식 노드의 개수에 따라 대응 방식이 달라집니다.
// Case 1: 단말 노드(Leaf Node) 삭제
// 자식이 없으므로 그냥 노드를 메모리 해제(free)하고, 부모와의 연결을 NULL로 끊으면 끝입니다.
// Case 2 : 자식이 1개인 노드 삭제
// 자신을 지우고, 자신의 유일한 자식을 부모 노드에 직접 연결해 줍니다. (마치 할아버지가 손자의 손을 바로 잡는 것과 같습니다.)
// 
// Case 3 : 자식이 2개인 노드 삭제
// 후계자(Successor) 고르기
// BST의 규칙을 지키면서 빈자리를 채울 가장 적합한 후보는 딱 두 명입니다.
// 후보 1: 왼쪽 서브트리에서 가장 큰 값
// 후보 2 : 오른쪽 서브트리에서 가장 작은 값(교안에서 채택한 방식)

typedef struct TreeNode {
    int key;
    struct TreeNode* left, * right;
} TreeNode;

TreeNode* new_node(int key) {
    TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
    temp->key = key;
    temp->left = temp->right = NULL;
    return temp;
}

// 🚀 [84일차 미션 A] 가장 작은 값을 가진 노드를 찾는 함수
TreeNode* min_value_node(TreeNode* node) {
    TreeNode* current = node;
    // 맨 왼쪽 끝까지 내려가야 가장 작은 값이 나오기에, 왼쪽 끝날 때까지 쭉 이동.
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

// 🚀 [83일차 미션] 이진 탐색 트리 삭제 함수 구현 (Case 1 & 2)
TreeNode* delete_node(TreeNode* root, int key) {
    if (root == NULL) return root;

    // 1. 삭제할 노드를 찾아 내려가는 과정 (탐색)
    if (key < root->key)
        root->left = delete_node(root->left, key);
    else if (key > root->key)
        root->right = delete_node(root->right, key);

    // 2. 삭제할 노드를 찾은 경우 (key == root->key)
    else {
        // [Case 1 & 2] 자식이 없거나 하나만 있는 경우
        if (root->left == NULL) {
            TreeNode* temp = root->right; // 오른쪽 자식(있든 없든)을 백업
            free(root);                   // 현재 노드 삭제
            return temp;                  // 백업한 자식을 부모에게 전달
        }
        else if (root->right == NULL) {
            TreeNode* temp = root->left; // 오른쪽이 없으면 왼쪽에 똑같은 방식으로.
            free(root);
            return temp;
        }

        // [84일차 미션 B] [Case 3] 자식이 두 개인 경우
        // 1. 오른쪽 서브트리에서 가장 작은 노드(후계자)를 찾기. min_value_node 함수를 오른쪽 서브트리에 사용.
        TreeNode* temp = min_value_node(root->right);

        // 2. 후계자의 데이터를 현재 노드(root)에 복사.
        root->key = temp->key;

        // 3. 오른쪽 서브트리에서 후계자 노드를 삭제 (중복된 값이 있으면 안 되니까)
        // 그리고 그 결과를 root->right에 다시 연결.
        root->right = delete_node(root->right, temp->key);
    }
    return root;
}

void inorder(TreeNode* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("[%d] ", root->key);
        inorder(root->right);
    }
}

int main(void) {
    TreeNode* root = NULL;
    root = new_node(30);
    root->left = new_node(20);
    root->right = new_node(40);
    root->left->left = new_node(10); // 단말 노드

    printf("삭제 전: "); inorder(root); printf("\n");

    // 10 삭제 (Case 1: 단말 노드)
    root = delete_node(root, 10);
    // 20 삭제 (Case 2: 자식이 1개였던 노드)
    root = delete_node(root, 20);

    printf("삭제 후: "); inorder(root); printf("\n");

    return 0;
}