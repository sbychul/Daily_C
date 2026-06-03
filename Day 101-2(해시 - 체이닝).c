#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 7

// 연결 리스트 노드 구조체 정의
typedef struct ListNode {
    int item;
    struct ListNode* link;
} ListNode;

// 해시 테이블 (각 칸이 연결 리스트의 첫 노드를 가리키는 포인터 배열)
ListNode* hash_table[TABLE_SIZE];

// 초기화: 모든 포인터를 NULL로 설정
void init_table(ListNode* ht[]) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht[i] = NULL;
    }
}

// 🎯 해시 함수
int hash_function(int key) {
    return key % TABLE_SIZE;
}

// 🎯 체이닝을 이용한 해시 삽입 함수
void hash_chain_add(int item, ListNode* ht[]) {
    int hash_value = hash_function(item);

    // 1. 새로운 노드 동적 할당 및 데이터 세팅
    ListNode* node_p = (ListNode*)malloc(sizeof(ListNode));
    node_p->item = item;

    // 2. 연결 리스트의 맨 앞에 새 노드 삽입하기
    // 새 노드가 맨 앞으로 들어오는 방식. 이전 노드를 새 노드가 가리키게끔 함.
    node_p->link = ht[hash_value];

    // 테이블의 시작 포인터(ht[hash_value])가 방금 만든 '새 노드(node_p)'를 가리키게 갱신
    ht[hash_value] = node_p;
}

// 해시 테이블 상태 출력 함수
void hash_chain_print(ListNode* ht[]) {
    ListNode* node;
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("[%d]->", i);
        for (node = ht[i]; node != NULL; node = node->link) {
            printf("%d->", node->item);
        }
        printf("NULL\n");
    }
}

int main() {
    int items[] = { 8, 1, 9, 6, 13 };
    int n = sizeof(items) / sizeof(items[0]);

    init_table(hash_table);

    printf("--- 체이닝 해시 테이블 삽입 ---\n");
    for (int i = 0; i < n; i++) {
        hash_chain_add(items[i], hash_table);
    }

    hash_chain_print(hash_table);

    return 0;
}