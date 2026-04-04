#include <stdio.h>
#include <stdlib.h>

// 자료구조 3주 차 복습: "기차 칸 하나를 쏙 빼내기"
// 단순 연결 리스트에서 중간 노드를 삭제하려면, 반드시 그 앞 칸(pre)의 정보가 필요합니다.
// 10 -> 20 -> 30 기차에서 20을 빼려면 10의 링크를 30으로 바꿔줘야 하기 때문이죠.

// 1. 오늘의 핵심 전략 : "두 대의 포인터 기차놀이"
// 리스트를 훑을 때 포인터 두 개를 연달아 배치합니다.
// p : 현재 검사하고 있는 노드(Target인지 확인)
// pre : 바로 직전에 검사했던 노드(삭제 시 다리를 이어줄 노드)

typedef int element;
typedef struct ListNode {
    element data;
    struct ListNode* link;
} ListNode;

// 리스트 출력 함수
void print_list(ListNode* head) {
    for (ListNode* p = head; p != NULL; p = p->link)
        printf("%d->", p->data);
    printf("NULL \n");
}

// 맨 앞 삽입 함수
ListNode* insert_first(ListNode* head, element value) {
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    p->data = value;
    p->link = head;
    return p;
}

// 🚀 [오늘의 미션] 특정 값을 찾아 삭제하는 통합 함수
ListNode* search_and_delete(ListNode* head, element target) {
    ListNode* p = head;       // 현재 노드
    ListNode* pre = NULL;     // 이전 노드

    while (p != NULL) {
        if (p->data == target) { // 🎯 타겟을 찾았다!
            if (pre == NULL) {
                // 1. 찾은 노드가 맨 앞 노드일 때
                // pre == NULL이라는 것은 맨 앞이라는 뜻(head의 이전은 없기 때문)
                head = p->link; // head를 다음 칸으로 이동
                free(p); // p의 메모리를 해제

            }
            else {
                // 2. 찾은 노드가 중간 노드일 때
                // pre가 p의 다음을 가리키고 있어야 제대로 연결됨.
                pre->link = p->link; // 제대로 연결해 주기.
                free(p); // p의 메모리를 해제
            }
            return head; // 삭제 완료 후 탈출
        }

        // 🎯 타겟이 아니면 다음 칸으로 기차놀이 하듯 이동
        pre = p; // 다음 칸으로 갈 것이기 때문에 pre에 현재 p를 백업
        p = p->link; // 다음 칸으로.
    }

    printf("%d(을)를 찾지 못했습니다.\n", target);
    return head;
}

int main(void) {
    ListNode* head = NULL;

    // 10 -> 20 -> 30 -> 40 -> 50 만들기
    head = insert_first(head, 50);
    head = insert_first(head, 40);
    head = insert_first(head, 30);
    head = insert_first(head, 20);
    head = insert_first(head, 10);

    printf("초기 상태: "); print_list(head);

    // [테스트 1] 맨 앞(10) 삭제
    head = search_and_delete(head, 10);
    printf("10 삭제 후: "); print_list(head);

    // [테스트 2] 중간(30) 삭제
    head = search_and_delete(head, 30);
    printf("30 삭제 후: "); print_list(head);

    return 0;
}