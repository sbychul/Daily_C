#include <stdio.h>
#include <stdlib.h>

// 1. 오늘의 핵심 개념 : 왜 마지막 노드를 가리킬까 ? (교안 45p)
// 보통 head 포인터가 첫 번째 노드를 가리키게 하지만, 원형 리스트에서는 마지막 노드를 가리키게 하는 것이 훨씬 효율적입니다.
// 이유 : 마지막 노드를 알고 있으면 last->link를 통해 첫 번째 노드에도 바로 접근할 수 있기 때문입니다.
// 즉, 리스트의 '머리'와 '꼬리'에 모두 O(1)로 접근이 가능해집니다!

// 2. 원형 리스트의 맨 앞 삽입(insert_first)
// 새로운 노드 node를 생성합니다.
// 리스트가 비어있다면(last == NULL), node->link가 자기 자신을 가리키게 하고 last가 node가 되게 합니다.
// 리스트가 비어있지 않다면 :
// node->link가 첫 번째 노드(last->link)를 가리키게 합니다.
// last->link가 새로운 노드 node를 가리키게 합니다.

typedef int element;
typedef struct ListNode {
    element data;
    struct ListNode* link;
} ListNode;

// 🚀 [오늘의 미션 1] 원형 리스트의 맨 앞에 삽입
ListNode* insert_first(ListNode* last, element data) {
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    node->data = data;

    if (last == NULL) { // 처음일 때
        last = node;
        node->link = last; // 자기 자신을 가리킴
    }
    else {
        // TODO: 새 노드가 첫 번째 노드를 가리키게 하고, 
        // 마지막 노드가 새 노드를 가리키게 하세요.
        node->link = last->link; // 첫 번째 노드는 last의 다음.
        last->link = node; // 마지막 노드의 다음에 새 거를 넣음(맨 앞)
    }
    return last;
}

// 🚀 [오늘의 미션 2] 원형 리스트 출력 (do-while 문 권장)
void print_list(ListNode* last) {
    if (last == NULL) return;
    ListNode* p = last->link; // 첫 번째 노드부터 시작

    // TODO: do-while 문을 사용하여 p가 다시 첫 번째 노드로 돌아올 때까지 출력하세요.
    do { 
        printf("%d -> ", p->data);
        p = p->link;
    } while (p != last->link);
    printf("NULL\n");
}

int main(void) {
    ListNode* last = NULL;

    // 리스트에 10, 20, 30 추가 (항상 맨 앞에 추가)
    last = insert_first(last, 10);
    last = insert_first(last, 20);
    last = insert_first(last, 30);

    printf("원형 리스트 출력: ");
    print_list(last);

    return 0;
}