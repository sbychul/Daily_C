#include <stdio.h>
#define MENUS 3 // 키오스크 메뉴를 수정할 때 편하게 할 수 있게끔 하고 싶었음.

void print_receipt(int total_price) {
	printf("\n=== 영수증 ===\n총 결제 금액: %d원\n이용해 주셔서 감사합니다!", total_price);
}

int main() {
	int choice = 0, sum = 0;
	int prices[MENUS] = { 2500, 4000, 3500 };
	char menu_names[MENUS][20] = { "아메리카노", "카페라떼", "아이스티" };

	printf("[메뉴]\n");
	for (int i = 0; i < MENUS; i++) {
		printf("%d. %s (%d원)\n", i + 1, menu_names[i], prices[i]);
	}

	while (1) {
		printf("\n메뉴를 선택하세요: ");
		// 문자를 입력받았을 때의 무한 루프 해결 방안, choice가 문자를 입력받으면 변수를 그대로 두는 성질에서 무한 루프 발생.
		// scanf의 반환값을 확인! (정수를 제대로 읽었으면 1, 못 읽었으면 0)
		if (scanf("%d", &choice) == 0) {
			printf("숫자가 아닙니다! 다시 입력해 주세요.\n");

			// ★ 핵심: 버퍼 안에 낀 'a'를 꺼내서 버린다!
			while (getchar() != '\n');
			//      ^^^^^^^^^    ^^^^
			//     1. 꺼낸다    2. 확인한다

			continue; // 아래 로직 실행하지 않고 다시 입력받으러 감
		}
		if (choice > MENUS || choice < 0) { // 예외 처리
			printf("올바른 메뉴 선택이 아닙니다.\n0부터 %d까지의 수를 입력해 주세요.\n", MENUS);
		}
		else {
			if (choice == 0) { // 0. 종료 선택 시
				printf("주문을 종료합니다.\n");
				break;
			}
			else { // 이외 전부
				sum += prices[choice - 1];
				printf("> %s 주문됨 (누적: %d원)\n", menu_names[choice - 1], sum);
			}
		}
	}

	print_receipt(sum);
	return 0;
}