#include <stdio.h>
#include <stdlib.h>

// 오늘의 미션: "동적 할당으로 무한 증식하는 리스트 만들기"
// 🛠️ 요구사항(Spec)
// 아래 제공된 뼈대 코드에서 빈칸(TODO)으로 남겨둔 insert_first 함수와 print_list 함수를 교수님의 교안에 맞게 완성해 주세요.
// print_list 함수는 교안 31페이지의 for문 방식을 사용해 주세요. (조건식과 증감식을 정확히 쓰는 게 핵심입니다!)

typedef int element;
typedef struct ListNode {
    element data;
    struct ListNode* link;
} ListNode;

// 🚀 [미션 1] 리스트의 맨 앞에 노드를 삽입하는 함수 구현
ListNode* insert_first(ListNode* head, int value) {
    // 1. 새로운 노드 p 동적 할당 (교안 27p)
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));

    // 2. 데이터 필드에 값(value) 저장
    /* TODO: p의 data에 value 넣기 */
    p->data = value;

    // 3. 새 노드의 링크가 기존의 head를 가리키게 함 (매우 중요!)
    /* TODO: p의 link에 head 연결 */
    p->link = head;

    // 4. head를 새로운 노드 p로 업데이트
    head = p;

    return head; // 변경된 헤드 포인터 반환
}

// 🚀 [미션 2] 리스트 순회 및 출력 함수 구현
void print_list(ListNode* head) {
    // 교안 31p: p가 NULL이 아닐 때까지 link를 타고 이동
    for (ListNode* p = head; p != NULL; p = p->link) { // 출발선(head)에 서서, 끝(NULL)을 만나기 전까지, 다음 쪽지의 주소(p->link)로 이동.
        printf("%d->", p->data);
    }
    printf("NULL \n");
}

int main(void) {
    ListNode* head = NULL; // 처음엔 비어있는 리스트

    head = insert_first(head, 10);
    print_list(head);

    head = insert_first(head, 20);
    print_list(head);

    head = insert_first(head, 30);
    print_list(head);

    return 0;
}