#include <stdio.h>
#include <stdlib.h>

// 1. 오늘의 핵심 문법: 노드 구조체 (교안 55p)
// 데이터 필드 하나에 포인터가 두 개 들어갑니다!
// 2. 헤드 노드(Head Node)의 도입 (교안 56p)
// 이중 연결 리스트에서는 데이터를 담지 않는 특별한 노드인 '헤드 노드'를 미리 하나 만들어두고 시작하는 경우가 많습니다.
// 이렇게 하면 리스트가 비어있을 때의 예외 처리가 훨씬 쉬워집니다. 마치 기차의 맨 앞 전용 기관차와 같죠!

typedef int element;

typedef struct DListNode {
    element data;
    struct DListNode* prev; // 앞 노드
    struct DListNode* next; // 뒤 노드
} DListNode;

// 이중 연결 리스트 초기화 (헤드 노드 생성)
void init(DListNode* phead) {
    phead->prev = phead;
    phead->next = phead;
}

// 🚀 [오늘의 미션] 노드 before의 오른쪽에 데이터 삽입
void dinsert(DListNode* before, element data) {
    DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));
    newnode->data = data;

    // 1. 새 노드의 prev 설정
    // before의 오른쪽(next)에 새 노드 == 새 노드의 왼쪽(prev)에 before
    newnode->prev = before;
    // 2. 새 노드의 next 설정
    // before와 before->next의 사이에 끼어들기 때문에 새 노드의 next는 before->next
    newnode->next = before->next;
    // 3. before 다음 노드의 prev를 새 노드로 설정 
    // before->next는 아직 왼손(prev)에 before를 잡고 있음. 새 노드의 손을 잡기.
    before->next->prev = newnode;
    // 4. before 노드의 next를 새 노드로 설정
    // before도 아직 오른손(next)에 이전 before->next를 잡고 있음. 마찬가지로 새 노드를 잡기.
    before->next = newnode;
}

// 리스트 출력 (앞방향 순회)
void print_dlist(DListNode* phead) {
    DListNode* p;
    for (p = phead->next; p != phead; p = p->next) {
        printf("<-| %d |-> ", p->data);
    }
    printf("\n");
}

int main(void) {
    DListNode* head = (DListNode*)malloc(sizeof(DListNode));
    init(head);

    printf("데이터 삽입 단계:\n");
    dinsert(head, 10); // 헤드 노드 뒤에 10 삽입
    print_dlist(head);
    dinsert(head, 20); // 헤드 노드 뒤에 20 삽입 (결과: 20 -> 10)
    print_dlist(head);
    dinsert(head->next, 30); // 20 노드 뒤에 30 삽입 (결과: 20 -> 30 -> 10)
    print_dlist(head);

    return 0;
}