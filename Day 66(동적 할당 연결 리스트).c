#include <stdio.h>
#include <stdlib.h>

// 오늘의 핵심 문법: 자기 참조 구조체
// 노드가 다음 노드를 가리키려면, 구조체 안에 자기 자신과 똑같은 타입의 포인터를 멤버로 가져야 합니다.

// 데이터 삽입의 혁신 (배열 vs 연결 리스트)
// 배열: 중간에 넣으려면 뒤에 있는 사람들을 다 뒤로 밀어야 함 (O(n))
// 연결 리스트: 삽입할 위치의 앞뒤 포인터(줄)만 새로 연결하면 끝! (O(1))

typedef int element;

typedef struct ListNode {
	element data;
	struct ListNode* link; // 다음 노드의 주소를 저장하는 '지도' 역할
} ListNode;

int main() {
	// 3개의 노드를 동적으로 할당.
	ListNode* p1 = malloc(sizeof(ListNode));
	ListNode* p2 = malloc(sizeof(ListNode));
	ListNode* p3 = malloc(sizeof(ListNode));
	// 정석은 (ListNode*)malloc... / 빈 포인터를 노드 포인터로 명확하게 변환하는 것.

	// 데이터 저장 및 연결
	p1->data = 10;
	p1->link = p2;

	p2->data = 20;
	p2->link = p3;

	p3->data = 30;
	p3->link = NULL; // 뒤에 없다는 뜻

	printf("[단순 연결 리스트 기차 출발]\n");
	ListNode* temp = p1; // 출력 시 사용할 임시 노드, 일단 맨 앞(head)을 가리킴
	while (temp != NULL) {
		printf("%d -> ", temp->data);
		temp = temp->link; // 다음 칸으로 이동.
	}
	printf("NULL\n");

	while (p1 != NULL) {
		temp = p1->link;	// 다음 칸을 일단 저장
		free(p1);			// 메모리 할당 해제
		p1 = temp;			// 다음 칸으로.
	}

	return 0;
}