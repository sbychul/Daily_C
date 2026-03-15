// 오늘의 핵심 요소 (Spec)
// 자기 참조 구조체(Self - referential Structure) : 구조체 멤버로 자기 자신과 똑같은 타입의 포인터를 가집니다.다음 칸의 주소를 저장하는 '연결 고리' 역할을 합니다.
// 노드(Node) : 데이터(화물)와 다음 노드의 주소(연결 고리)를 합친 기차 칸 하나를 의미합니다.
// 헤드(Head) : 기차의 맨 앞부분을 가리키는 포인터입니다.리스트의 시작점을 잃어버리지 않게 해줍니다.

#include <stdio.h>
#include <stdlib.h>

typedef struct Node { // typedef struct (이름) { } (이름); 해야 완벽하게 동작함.
	int data;
	struct Node* next;
} Node;

int main() {
	Node* head = NULL;
	Node* current = NULL;
	int userInput = 0;
	int howManyNodes = 0;

	printf("[연결 리스트 숫자 기차 만들기]\n");
	while (1) {
		printf("숫자를 입력하세요 (-1 입력 시 종료): ");
		
		if (scanf("%d", &userInput) != 1) { // 입력이 잘못될 경우(정수가 아님)
			while (getchar() != '\n'); // 버퍼 치우기
			printf("제대로 된 수를 입력하십시오 휴먼.\n");
			continue; // 다시 반복문 처음으로
		}

		if (userInput == -1) { break; } // -1 입력받으면 그대로 끝

		// 이 밑으로는 예외 처리 안 걸렸을 때 (우리 식당 정상영업 합니다)
		Node* newNode = malloc(sizeof(Node));
		newNode->data = userInput; // 입력받은 숫자를 넣고
		newNode->next = NULL;

		if (head == NULL) { // 첫 번째 노드라면
			head = newNode; // 새 노드의 주소를 그대로 head에 넣음
		}
		else { // 첫 번째 노드가 아님 (head가 이미 먹혀 있음)
			current->next = newNode; // current가 마지막을 가리키고 있는데, 마지막의 다음이 방금 만든 노드가 됨.
		}

		current = newNode; // 왕위를 계승하는 중입니다
		howManyNodes++; // 노드 개수 세기
	}

	printf("[연결된 리스트 결과]\n");
	Node* temp = head; // 임시 포인터
	for (int i = 0; i < howManyNodes; i++) {
		printf("%d -> ", temp->data);
		temp = temp->next; // 다음 칸으로
	}
	printf("NULL\n모든 노드의 메모리를 해제하고 종료합니다.");

	for (int i = 0; i < howManyNodes; i++) { // 나 진짜 이거 예전 꺼 안 봤음 진짜로 맹세컨대 위에 내용은 좀 봤음 ㅎㅎ 근데 이건 진짜 안 봄
		temp = head->next; // 다음 위치를 기록
		free(head);
		head = temp; // 다음 박살낼 칸으로 이동.
	}

	return 0;
}