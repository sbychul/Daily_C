#include <stdio.h>
#include <stdlib.h>

// 오늘의 핵심 요소 (Spec)
// realloc(Re - allocation) : 이미 할당된 메모리의 크기가 부족할 때, 기존 데이터는 그대로 유지한 채로 더 큰 공간으로 이사시켜 주는 마법의 함수입니다.
// 동적 배열(Dynamic Array) : 데이터가 늘어날 때마다 실시간으로 크기가 커지는 배열 만들기.

typedef struct { char name[30]; } Item;

int main() {
	int capacity = 2; // capacity는 2에서 시작.
	int count = 0;
	Item* inventory = (Item*)malloc(sizeof(Item) * capacity); // 2칸짜리 인벤토리 형성
	Item* temp = NULL; // 임시 포인터 미리 형성.

	printf("[아이템 뽑기 시뮬레이터]\n");

	while (1) {
		int choice = 0; // 선택할 때 사용할 변수
		printf("아이템을 획득하시겠습니까? (1: 뽑기 / 0: 종료): ");
		scanf("%d", &choice);

		if (choice == 1) { // 뽑기를 진행할 때
			if (count == capacity) {
				capacity *= 2; // 방 크기 확장
				temp = (Item*)realloc(inventory, sizeof(Item) * capacity); // realloc이 실패했을 경우를 방지한 임시 포인터 활용
				if (temp != NULL) { inventory = temp; } // 메모리 할당에 성공한 경우, 임시 포인터의 주소를 그대로 복사해서 사용.
			}
			printf("획득한 아이템 이름: ");
			scanf("%s", inventory[count].name); // 아이템 입력받기
			count++; // 인벤토리 다음 칸으로 이동.
		}

		else if (choice == 0) { // 뽑기를 진행하지 않는다고 할 때
			printf("[내 인벤토리 목록]\n");
			for (int i = 0; i < count; i++) { // 목록을 하나씩 돌아가며 출력
				printf("%d. %s\n", i + 1, inventory[i].name);
			}

			printf("\n메모리를 정리하고 프로그램을 종료합니다.\n");
			break; // 반복문 탈출
		}
		
	}
	free(inventory); // 메모리 할당은 인벤토리만 해주면 충분 (어차피 temp와 같은 주소)
	inventory = NULL;
	temp = NULL; // Dangling Pointer 방지
	return 0;
}