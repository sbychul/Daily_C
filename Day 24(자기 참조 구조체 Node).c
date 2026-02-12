#include <stdio.h>
#include <stdlib.h> // 동적 할당을 사용하기 위해 불러오는 헤더

struct Node {
	int data;           // 데이터를 담는 그릇
	struct Node* next;  // 다음 데이터(노드)의 주소를 담는 지팡이
};

int main() {
	struct Node* head = malloc(sizeof(struct Node)); // head의 메모리 동적 할당
	struct Node* node2 = malloc(sizeof(struct Node)); // node2의 메모리 동적 할당

	head->data = 10; // head의 data 값에 10을 지정
	// == (*head).data = 10;
	// 화살표(->)는 '주소를 찾아가서(dereference) 문을 연다'는 뜻
	node2->data = 20; // 위와 똑같은 방식

	head->next = node2; // head의 next(지팡이)가 가리키는 방향을 node2의 주소로 설정.
	// 물리적으로 떨어져 있는 두 메모리 공간이 논리적으로 연결됨.

	node2->next = NULL; // node2의 next에는 더 이상 연결할 곳이 없으므로, 여기가 마지막이라는 표지판의 용도로 NULL
	// 나중에 while문으로 탐색할 때 NULL을 만나면 그대로 멈춤 (반복문을 멈추는 용도로도 사용 가능)

	printf("[자료구조 노드 연결 테스트]\n첫 번째 노드 데이터: %d\n두 번째 노드 데이터: %d (head를 통해 접근)\n연결 성공!", head->data, head->next->data);
	// 두 번째 노드 데이터 출력 값을 node2->data가 아닌 head->next->data(head의 다음 칸으로 가서 data를 출력)로 표기했음에도 20이 출력 => 두 데이터가 성공적으로 연결되었음

	free(head); // 메모리 반납
	free(node2);

	return 0; // 프로그램 종료
}

// 오류 목록의 경고(C6011)에 대하여:
// 1. 경고의 원인 : malloc은 100% 성공하지 않는다
// 우리가 malloc에게 "메모리 좀 줘!"라고 요청하면, 대부분은 "옛다, 여기 있어" 하고 주소를 줍니다.하지만 만약 컴퓨터의 메모리가 꽉 찼다면?
// => malloc은 메모리를 구하지 못하고 * *NULL(빈 껍데기) * *을 반환합니다.

// 그런데 우리는 확인도 안 하고 바로 head->data = 10; 을 해버립니다.
// 문제 발생 : head가 NULL인데 화살표(->)로 안을 들여다보려고 하면, 프로그램은 그 즉시 강제 종료(Crash) 됩니다.


// 2. 비유 : 택배 상자와 언박싱
// malloc 호출 : 택배를 주문했습니다.
// 정상 상황 : 택배 상자(메모리)가 도착했습니다.→ 상자를 뜯습니다(->). (성공)
// 실패 상황 : 택배가 분실되어 안 왔습니다(NULL).→ 근데 허공에 대고 칼질을 하며 상자를 뜯으려고 합니다(->).→ 사고 발생!

// Visual Studio는 * *"택배가 진짜로 도착했는지 확인부터 하고 뜯어야지!" * *라고 경고하는 것입니다.


// 3. 해결 방법 (프로들의 습관)
// 원래는 malloc 직후에 항상 "제대로 할당받았는지" 검사하는 코드를 넣는 게 정석입니다.

// struct Node* head = malloc(sizeof(struct Node));
// [안전 장치] 혹시라도 메모리를 못 받았다면?
// if (head == NULL) {
//		printf("메모리가 부족해서 노드를 못 만들었어요 ㅠㅠ\n");
//  	return 1; // 프로그램 비정상 종료
// }
// 안전 장치를 통과했으니 마음 놓고 쓴다!
// head->data = 10;