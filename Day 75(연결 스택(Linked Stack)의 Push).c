#include <stdio.h>
#include <stdlib.h>

// 오늘의 핵심 원리 : "Push는 곧 insert_first 다!"
// 스택은 항상 '맨 위(Top)'에서만 삽입과 삭제가 일어납니다.
// 이걸 연결 리스트로 생각해보면, 항상 '맨 앞(Head)'에 노드를 추가하고, '맨 앞(Head)' 노드를 삭제하는 것과 완전히 똑같습니다!
// 즉, 연결 리스트의 insert_first와 delete_first 함수 이름만 push와 pop으로 바꾼 것이 바로 연결 스택입니다.

typedef int element;
// 스택 노드 구조체 (단순 연결 리스트 노드와 똑같이 생겼습니다!)
typedef struct StackNode {
    element data;
    struct StackNode* link;
} StackNode;

// 스택을 관리하는 구조체 (Top 포인터 하나만 가지고 있습니다)
typedef struct {
    StackNode* top;
} LinkedStackType;

// 스택 초기화 함수
void init(LinkedStackType* s) {
    s->top = NULL;
}

// 스택 출력 함수
void print_stack(LinkedStackType* s) {
    for (StackNode* p = s->top; p != NULL; p = p->link)
        printf("%d->", p->data);
    printf("NULL \n");
}

// 🚀 [오늘의 미션] 스택에 데이터를 삽입하는 함수 (insert_first와 동일!)
void push(LinkedStackType* s, element item) {
    // 1. 새로운 노드 동적 할당
    StackNode* temp = (StackNode*)malloc(sizeof(StackNode));

    // 2. 데이터 필드에 item 저장
    temp->data = item;

    // 3. 새 노드의 link가 현재의 맨 위(top)를 가리키게 함
    temp->link = s->top;

    // 4. 이제 스택의 맨 위(top)는 방금 만든 새 노드가 됨
    s->top = temp;
}

int main(void) {
    LinkedStackType s;
    init(&s); // 스택 초기화

    printf("데이터 1 팝업(Push):\n");
    push(&s, 1); print_stack(&s);

    printf("데이터 2 팝업(Push):\n");
    push(&s, 2); print_stack(&s);

    printf("데이터 3 팝업(Push):\n");
    push(&s, 3); print_stack(&s);

    return 0;
}