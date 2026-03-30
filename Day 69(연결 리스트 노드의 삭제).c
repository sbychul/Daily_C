#include <stdio.h>
#include <stdlib.h>

// 1. 맨 앞 노드 삭제(delete_first)
// 1) 삭제할 현재의 첫 번째 노드(head)를 removed라는 임시 포인터로 꽉 붙잡아 둡니다.
// 2) head 포인터를 다음 노드로 한 칸 넘깁니다. (head = head->link;)
// 3) 붙잡아 두었던 removed 노드를 free()로 메모리 해제합니다.

// 2. 중간 노드 삭제(delete)
// 특정 노드(pre) 뒤에 있는 노드를 삭제하는 과정입니다.
//
// 1) 삭제할 노드(pre->link)를 removed로 꽉 붙잡습니다.
// 2) pre의 링크가 삭제할 노드의 '다음' 노드를 가리키게 하여, 삭제할 노드를 건너뛰도록 다리를 놓습니다. (pre->link = removed->link;)
// 3) removed 노드를 free()로 날려줍니다.

typedef int element;
typedef struct ListNode {
    element data;
    struct ListNode* link;
} ListNode;

// 리스트 출력 함수 
void print_list(ListNode* head) {
    for (ListNode* p = head; p != NULL; p = p->link) {
        printf("%d->", p->data);
    }
    printf("NULL \n");
}

// 맨 앞에 삽입 
ListNode* insert_first(ListNode* head, element value) {
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    p->data = value;
    p->link = head;
    return p; // head = p 와 동일한 효과
}

// 🚀 [오늘의 미션 1] 맨 앞 노드 삭제하기
ListNode* delete_first(ListNode* head) {
    if (head == NULL) return NULL; // 빈 리스트면 그냥 종료

    // 1. 삭제할 노드를 임시 포인터(removed)로 붙잡기
    ListNode* removed = head;

    // 2. head를 다음 노드로 이동시키기
    head = head->link;

    // 3. 붙잡아둔 노드 메모리 해제
    free(removed);

    return head;
}

// 🚀 [오늘의 미션 2] pre 노드 '뒤'에 있는 노드 삭제하기
ListNode* delete(ListNode* head, ListNode* pre) {
    // 1. 삭제할 노드(pre의 다음 노드)를 임시 포인터로 붙잡기
    ListNode* removed = pre->link;

    // 2. pre가 삭제할 노드의 다음 노드를 가리키게 하여 건너뛰기
    pre->link = removed->link;

    // 3. 붙잡아둔 노드 메모리 해제
    free(removed);

    return head;
}
// pre가 맨 마지막이라 다음에 아무것도 없다면?
// pre->link가 들어간 removed(NULL)
// NULL->link...? 바로 Segmentation Fault 발생.

// 따라서 더 완벽한 코드를 작성하기 위해서는 if (pre == NULL || pre->link == NULL) return head;
// 와 같은 예외 처리를 진행해주면 매우 좋다.

int main(void) {
    ListNode* head = NULL;

    // 10 -> 20 -> 30 만들기
    head = insert_first(head, 30);
    head = insert_first(head, 20);
    head = insert_first(head, 10);
    printf("기본 리스트: ");
    print_list(head);

    // [미션 1] 맨 앞(10) 삭제하기
    head = delete_first(head);
    printf("맨 앞 삭제 후: ");
    print_list(head);

    // [미션 2] 20(head) 뒤에 있는 30 삭제하기
    head = delete(head, head);
    printf("20 뒤의 노드 삭제 후: ");
    print_list(head);

    return 0;
}