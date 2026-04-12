#include <stdio.h>
#include <stdlib.h>

// 교수님께서 주신 자율 숙제.
// 원형 연결 리스트를 이용한 덱의 delete_first, delete_last 구현하기.

typedef int element;
typedef struct DequeNode {
    element data;
    struct DequeNode* link;
} DequeNode;

typedef struct {
    DequeNode* tail; // 원형 연결 리스트의 '마지막 노드'를 가리키는 포인터
} LinkedDequeType;

// 초기화
void init(LinkedDequeType* q) {
    q->tail = NULL;
}

// 공백 상태 검사
int is_empty(LinkedDequeType* q) {
    return (q->tail == NULL);
}

// -------------------------------------------------------------
// 🚀 [자율 숙제: 유저님이 직접 구현하실 부분]
// -------------------------------------------------------------

// 1. 덱의 맨 앞(front)에서 데이터를 삭제하고 반환하는 함수
element delete_first(LinkedDequeType* q) {
    if (is_empty(q)) {
        fprintf(stderr, "덱이 비어있습니다.\n");
        exit(1);
    }
    // 삭제할 값을 removed 변수에 저장.
    // 맨 앞을 의미하는 것은 tail->link.
    element removed = q->tail->link->data;

    // 삭제할 칸을 저장.
    DequeNode* removed_node = q->tail->link;

    // [핵심 예외 처리] 노드가 딱 1개 남았던 경우
    if (q->tail == q->tail->link) {
        q->tail = NULL; // 큐를 완전히 비움
    }
    else {
        q->tail->link = removed_node->link; // 기존 로직, 맨 앞 칸의 다음 칸으로.
    }

    free(removed_node); // 노드 삭제.
    return removed; // 값 반환.
}

// 2. 덱의 맨 뒤(rear)에서 데이터를 삭제하고 반환하는 함수
element delete_last(LinkedDequeType* q) {
    if (is_empty(q)) {
        fprintf(stderr, "덱이 비어있습니다.\n");
        exit(1);
    }
    // 삭제할 값을 removed 변수에 저장.
    element removed = q->tail->data;

    // 삭제할 칸을 저장.
    DequeNode* removed_node = q->tail;

    // [핵심 예외 처리] 노드가 딱 1개 남았던 경우
    if (q->tail == q->tail->link) {
        q->tail = NULL; // 큐를 완전히 비움
    }
    else {
        DequeNode* temp = q->tail->link; // 첫 칸부터 달린다.
        // 맨 뒤 노드의 변경, 임시 노드 d의 다음 칸이 tail이 아닐 때까지 (= 마지막 바로 전 칸까지 이동)
        for (; temp->link != q->tail; temp = temp->link); 

        // 마지막 바로 전 칸과 맨 앞 칸의 손 잡아주기.
        temp->link = q->tail->link;
        // 마지막 바로 전 칸을 tail로 임명.
        q->tail = temp;
    }

    free(removed_node); // 노드 삭제.
    return removed; // 값 반환.
}

// -------------------------------------------------------------
// (테스트를 위해 미리 구현해 둔 삽입 및 출력 함수)
// -------------------------------------------------------------

// 맨 앞에 삽입
void insert_first(LinkedDequeType* q, element data) {
    DequeNode* node = (DequeNode*)malloc(sizeof(DequeNode));
    node->data = data;
    if (is_empty(q)) {
        q->tail = node;
        node->link = node;
    }
    else {
        node->link = q->tail->link;
        q->tail->link = node;
    }
}

// 맨 뒤에 삽입
void insert_last(LinkedDequeType* q, element data) {
    DequeNode* node = (DequeNode*)malloc(sizeof(DequeNode));
    node->data = data;
    if (is_empty(q)) {
        q->tail = node;
        node->link = node;
    }
    else {
        node->link = q->tail->link;
        q->tail->link = node;
        q->tail = node; // tail을 방금 넣은 새 노드로 이동
    }
}

// 출력 함수
void print_deque(LinkedDequeType* q) {
    if (is_empty(q)) {
        printf("덱이 비어있습니다.\n");
        return;
    }
    DequeNode* p = q->tail->link; // 첫 번째 노드
    do {
        printf("%d->", p->data);
        p = p->link;
    } while (p != q->tail->link);
    printf("(tail)\n");
}

int main(void) {
    LinkedDequeType q;
    init(&q);

    // 초기 데이터 세팅 (10 -> 20 -> 30)
    insert_last(&q, 10);
    insert_last(&q, 20);
    insert_last(&q, 30);
    printf("초기 상태: "); print_deque(&q);

    // 삭제 테스트 (유저님이 함수를 완성하시면 주석을 풀고 실행해 보세요!)
    /*
    printf("\n[delete_first 실행]\n");
    element data1 = delete_first(&q);
    printf("삭제된 데이터: %d\n", data1);
    print_deque(&q);

    printf("\n[delete_last 실행]\n");
    element data2 = delete_last(&q);
    printf("삭제된 데이터: %d\n", data2);
    print_deque(&q);
    */

    return 0;
}