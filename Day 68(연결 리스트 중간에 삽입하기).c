#include <stdio.h>
#include <stdlib.h>

// 1. 오늘의 핵심 로직: insert(head, pre, value)
// 특정 노드(pre)의 뒤에 새로운 노드를 삽입하는 과정은 다음과 같습니다. (교안 28p 그림 참고)

// 1) 생성: 새로운 노드 p를 동적 할당하고 값을 채웁니다.
// 2) 다리 놓기(1) : 새 노드 p의 link가 pre가 가리키던 다음 노드를 가리키게 합니다. (p->link = pre->link;)
// 3) 다리 놓기(2) : 이제 pre의 link가 새로운 노드 p를 가리키게 합니다. (pre->link = p;)

// 2. 주의해야 할 점(시험 단골 함정!)
// 위의 2번과 3번 순서가 바뀌면 안 됩니다!만약 pre->link = p; 를 먼저 해버리면,
// 원래 pre 뒤에 있던 노드들의 주소를 잃어버리게 되어 리스트가 끊겨버립니다.

typedef int element;

typedef struct ListNode {
    element data;
    struct ListNode* link;
} ListNode;

// 리스트 출력 함수 (어제 완성한 코드)
void print_list(ListNode* head) {
    for (ListNode* p = head; p != NULL; p = p->link) {
        printf("%d->", p->data);
    }
    printf("NULL \n");
}

// 맨 앞에 삽입 (어제 완성한 코드)
ListNode* insert_first(ListNode* head, element value) {
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    p->data = value;
    p->link = head;
    head = p;
    return head;
}

// 🚀 [오늘의 미션] pre 노드 뒤에 새로운 노드를 삽입하는 함수
ListNode* insert(ListNode* head, ListNode* pre, element value) {
    // 1. 새로운 노드 p 동적 할당
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));

    // 2. p의 데이터 필드에 value 저장
    p->data = value;

    // 3. 새 노드 p의 link를 pre의 다음 노드와 연결
    p->link = pre->link;

    // 4. pre의 link가 새 노드 p를 가리키게 함
    pre->link = p;

    return head;
}

int main(void) {
    ListNode* head = NULL;

    // 10 -> 20 -> 30 순서로 리스트 만들기
    head = insert_first(head, 30);
    head = insert_first(head, 20);
    head = insert_first(head, 10);
    printf("기본 리스트: ");
    print_list(head);

    // 10(head) 뒤에 99를 삽입하여 10->99->20->30 만들기
    printf("10 뒤에 99 삽입: ");
    head = insert(head, head, 99); // head(10) 노드 뒤에 삽입
    print_list(head);

    return 0;
}