// 오늘의 핵심 요소 (Spec)
// 자기 참조 구조체(Self - referential Structure) : 구조체 멤버로 자기 자신과 똑같은 타입의 포인터를 가집니다.다음 칸의 주소를 저장하는 '연결 고리' 역할을 합니다.
// 노드(Node) : 데이터(화물)와 다음 노드의 주소(연결 고리)를 합친 기차 칸 하나를 의미합니다.
// 헤드(Head) : 기차의 맨 앞부분을 가리키는 포인터입니다.리스트의 시작점을 잃어버리지 않게 해줍니다.

#include <stdio.h>

typedef struct Node {
	int data;
	struct Node* next;
};

int main() {
	
	return 0;
}