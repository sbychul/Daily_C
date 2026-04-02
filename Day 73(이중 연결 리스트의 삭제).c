#include <stdio.h>
#include <stdlib.h>

// 오늘의 핵심 로직: 건너뛰어 연결하기 (교안 62p)
// 특정 노드 removed를 리스트에서 빼내려면, 그 노드의 왼쪽 친구와 오른쪽 친구가 서로의 손을 직접 잡게 만들어야 합니다.
// 왼쪽 친구의 오른손 업데이트 : removed의 왼쪽 노드가 removed의 오른쪽 노드를 가리키게 합니다.
// 오른쪽 친구의 왼손 업데이트 : removed의 오른쪽 노드가 removed의 왼쪽 노드를 가리키게 합니다.
// 메모리 해제 : 고립된 removed 노드를 free()로 완전히 삭제합니다.

typedef int element;
typedef struct DListNode {
    element data;
    struct DListNode* prev;
    struct DListNode* next;
} DListNode;

// 초기화 및 삽입 함수 (이전 코드 활용)
void init(DListNode* phead) {
    phead->prev = phead;
    phead->next = phead;
}

void dinsert(DListNode* before, element data) {
    DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));
    newnode->data = data;
    newnode->prev = before;
    newnode->next = before->next;
    before->next->prev = newnode;
    before->next = newnode;
}

// 🚀 [오늘의 미션] 노드 removed를 삭제하는 함수
void ddelete(DListNode* head, DListNode* removed) {
    if (removed == head) return; // 헤드 노드는 삭제하지 않음

    // 1. removed의 왼쪽 노드가 removed의 오른쪽 노드를 가리키게 함
    // prev의 손을 잡게 해야 함!! prev = next로 해버리는 순간 난 모르겠다.
    removed->prev->next = removed->next;
    // 2. removed의 오른쪽 노드가 removed의 왼쪽 노드를 가리키게 함
    // 마찬가지.
    removed->next->prev = removed->prev;

    // 고립된 removed 노드의 메모리를 해제.
    free(removed);
}

// 알고 있으면 좋은 점 (헤드 노드의 진가):
// 유저님의 삭제 코드가 단 두 줄로 깔끔하게 끝날 수 있었던 숨은 공신은 바로 처음부터 만들어 두었던 '헤드 노드(Dummy Node)'입니다.
// 만약 이 빈 껍데기 노드가 없었다면,
// 삭제하려는 노드가 맨 앞일 때나 맨 뒤일 때를 전부 if문으로 나눠서 지저분하게 예외 처리(if (removed->prev != NULL) 등)를 해줘야 합니다.
// 교수님께서 교안에 굳이 헤드 노드를 넣으신 깊은 뜻을 이제 완벽히 이해하신 겁니다!

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

    // 10, 20, 30 삽입
    dinsert(head, 10);
    dinsert(head, 20);
    dinsert(head, 30);
    printf("삭제 전: "); print_dlist(head);

    // [미션 테스트] 중간 노드(20) 삭제하기
    // head -> 30 -> 20 -> 10 순서이므로, 20은 head->next->next 임
    ddelete(head, head->next->next);

    printf("20 삭제 후: "); print_dlist(head);

    return 0;
}