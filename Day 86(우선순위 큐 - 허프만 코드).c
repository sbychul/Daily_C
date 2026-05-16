#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200

// 허프만 트리 노드 구조체
typedef struct TreeNode {
    int weight;         // 빈도수
    char ch;            // 문자
    struct TreeNode* left, * right;
} TreeNode;

// 힙에 저장될 요소 (노드의 포인터를 담음)
typedef struct {
    TreeNode* ptree;
    int key;           // 힙 정렬 기준 (빈도수)
} element;

// 힙 구조체
typedef struct {
    element heap[MAX_ELEMENT];
    int heap_size;
} HeapType;

// 힙 초기화
void init(HeapType* h) {
    h->heap_size = 0;
}

// 최소 힙 삽입 함수
void insert_min_heap(HeapType* h, element item) {
    int i;
    i = ++(h->heap_size); 

    while (i != 1 && h->heap[i / 2].key > item.key) {
        h->heap[i] = h->heap[i / 2]; 
        i = i / 2;
    }

    h->heap[i] = item;
}

// 최소 힙 삭제 함수 (Downheap)
element delete_min_heap(HeapType* h) {
    int parent, child;
    element item, temp;

    item = h->heap[1];
    temp = h->heap[(h->heap_size)--];
    parent = 1;
    child = 2;
    while (child <= h->heap_size) {
        if (child < h->heap_size && h->heap[child].key > h->heap[child + 1].key) child++;
        if (temp.key <= h->heap[child].key) break;
        h->heap[parent] = h->heap[child];
        parent = child; 
        child = parent * 2; 
    }

    h->heap[parent] = temp;
    return item;
}

// 허프만 트리 생성 함수
void huffman_tree(int freq[], char ch_list[], int n) {
    int i;
    TreeNode* node, * x;
    HeapType heap;
    element e, e1, e2;

    init(&heap);

    // 1. 모든 문자를 각각 하나의 노드로 만들어 힙에 삽입
    for (i = 0; i < n; i++) {
        node = (TreeNode*)malloc(sizeof(TreeNode));
        node->ch = ch_list[i];
        node->weight = freq[i];
        node->left = node->right = NULL;
        e.ptree = node;
        e.key = node->weight;
        insert_min_heap(&heap, e);
    }

    // 2. n-1번 반복하여 노드들을 합침
    for (i = 1; i < n; i++) {
        // 힙에서 가장 빈도수가 낮은 노드 두 개(e1, e2)를 꺼내기
        e1 = delete_min_heap(&heap);
        e2 = delete_min_heap(&heap);

        // 새로운 부모 노드 생성, 빈도수를 합치기 위한 상자.
        x = (TreeNode*)malloc(sizeof(TreeNode));

        // 새로운 부모 노드 x의 왼쪽, 오른쪽 자식으로 e1, e2의 ptree 연결 (가장 작은 노드 두 개를 연결)
        x->left = e1.ptree;
        x->right = e2.ptree;

        // 부모 노드 x의 빈도수를 두 자식의 합으로 설정하고 다시 힙에 삽입
        x->weight = x->left->weight + x->right->weight;

        element new_e; // 힙에 넣을 값을 포장할 변수
        new_e.ptree = x; // ptree값은 형성된 트리
        new_e.key = x->weight; // key는 가중치
        insert_min_heap(&heap, new_e); // 다시 heap에 삽입.

        printf("%d + %d -> %d\n", e1.key, e2.key, x->weight);
    }
    // 최종적으로 힙에 남은 하나의 노드가 허프만 트리의 루트가 됨
}

int main(void) {
    char ch_list[] = { 's', 'i', 'n', 't', 'e' };
    int freq[] = { 4, 6, 8, 12, 15 };
    huffman_tree(freq, ch_list, 5);

    return 0;
}