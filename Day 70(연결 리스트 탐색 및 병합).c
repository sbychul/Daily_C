#include <stdio.h>
#include <stdlib.h>

// 1. 특정 데이터 탐색하기(search_list)
// 리스트의 처음부터 끝까지 노드를 하나씩 방문하면서 원하는 값(x)이 있는지 확인합니다.
// 값을 찾으면 그 값이 들어있는 노드의 주소(포인터)를 반환하고, 끝까지 찾아도 없으면 NULL을 반환합니다.

// 2.두 리스트 하나로 합치기(concat_list)
// 2개의 리스트를 합하는 함수입니다.
// 첫 번째 리스트(head1)의 맨 마지막 노드를 찾아낸 뒤, 그 노드의 link에 두 번째 리스트(head2)의 시작 주소를 연결해주면 끝입니다.
// 단, 첫 번째 리스트가 아예 비어있을 경우(head1 == NULL) 바로 두 번째 리스트를 반환하는 예외 처리가 필수입니다.

typedef int element;

typedef struct ListNode {
    element data;
    struct ListNode* link;
} ListNode;

// (기존 함수들: insert_first, print_list 생략 - 유저님 코드 재활용!)
ListNode* insert_first(ListNode* head, element value) {
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    p->data = value;
    p->link = head;
    return p;
}

void print_list(ListNode* head) {
    for (ListNode* p = head; p != NULL; p = p->link)
        printf("%d->", p->data);
    printf("NULL \n");
}

// 🚀 [오늘의 미션 1] 리스트에서 특정한 값을 찾는 함수
ListNode* search_list(ListNode* head, element x) {
    // TODO: head부터 시작해서 link를 타고 이동하며 x값을 찾으세요!
    ListNode* temp = head;
    while (temp != NULL) { // 리스트의 끝까지 반복.
        if (temp->data == x) { return temp; } // 찾았다
        temp = temp->link;
    }
    // 여기까지 오면 없는 거, NULL을 반환.
    return NULL;
}
    

// 🚀 [오늘의 미션 2] 두 개의 리스트를 합하는 함수
ListNode* concat_list(ListNode* head1, ListNode* head2) {
    // TODO: 예외 처리 (head1이나 head2가 NULL일 때)를 먼저 작성하세요.

    // 내가 작성했던 코드:
    // if (head1 == NULL || head2 == NULL) { printf("두 리스트가 존재하지 않습니다."); return head2; }
    // 유저님의 의도는 "둘 중 하나라도 비어있으면 멈춰라!"였을 겁니다. 그런데 여기서 치명적인 버그가 하나 숨어있습니다.
    
    // [시나리오]
    // head1은 10 -> 20 -> 30 이고, head2는 NULL(빈 리스트)입니다.
    // if 문을 만납니다.head2가 NULL이니까 조건이 참(True)이 됩니다.
    // return head2; (즉, NULL)를 반환해 버립니다!
    // 합친 결과물로 당연히 10 -> 20 -> 30이 나와야 하는데, 멀쩡하던 head1마저 날려버리고 허공(NULL)을 반환해 버리는 대참사가 일어납니다.
    // 🛠️ 해결책(교수님의 정석 코드) 이럴 때는 뭉뚱그리지 말고 조건을 분리해 주어야 합니다.

    if (head1 == NULL) return head2; // 앞 기차가 없으면 뒷 기차가 대장!
    if (head2 == NULL) return head1; // 뒷 기차가 없으면 앞 기차가 대장!

    // TODO: head1의 맨 끝 노드를 찾아 head2를 연결하세요.
    ListNode* temp = head1; // 임시 노드 생성
    while (temp->link != NULL) { // head의 끝을 찾아 달리기, temp->link가 NULL이라면 끝이라는 뜻.
        temp = temp->link;
    }
    temp->link = head2; // 연결
    return head1; // 연결된 리스트 반환.
}

int main(void) {
    ListNode* head1 = NULL;
    ListNode* head2 = NULL;

    // 리스트 1 만들기: 10->20->30
    head1 = insert_first(head1, 30);
    head1 = insert_first(head1, 20);
    head1 = insert_first(head1, 10);

    // 리스트 2 만들기: 40->50
    head2 = insert_first(head2, 50);
    head2 = insert_first(head2, 40);

    printf("리스트 1: "); print_list(head1);
    printf("리스트 2: "); print_list(head2);

    // [미션 2 테스트] 두 리스트 합치기
    ListNode* total_list = concat_list(head1, head2);
    printf("합쳐진 리스트: "); print_list(total_list);

    // [미션 1 테스트] 데이터 탐색
    int target = 30;
    if (search_list(total_list, target) != NULL)
        printf("리스트에서 %d을(를) 찾았습니다.\n", target);
    else
        printf("리스트에서 %d을(를) 찾지 못했습니다.\n", target);

    return 0;
}