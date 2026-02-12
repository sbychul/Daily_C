#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    int count = 0, answer = rand() % 100 + 1, input_number = 0;

    while (1) {
        printf("[1~100] 숫자를 맞춰보세요!\n입력: ");
        scanf("%d", &input_number);

        if (input_number < 1 || input_number > 100) {
            printf("입력하신 '%d'은(는) 범위 내에 속한 수가 아닙니다.\n1부터 100 사이에 속하는 수를 입력해 주세요.\n", input_number);
        }

        else {
            count++;
            if (input_number == answer) {
                printf("정답입니다! (%d번 만에 맞히셨습니다.)", count);
                break;
            }
            else {
                if (input_number < answer) printf("Up!\n");
                else printf("Down!\n");
            }
        }
    }

    return 0;
}

// 🏆 베스트 코드 리뷰(Code Review)
//
// 완벽한 난수 초기화 위치(srand)
// while 반복문 안에 넣지 않고 main 함수 맨 위에 둠으로써, 매번 새로운 랜덤 게임이 되도록 정확하게 처리했습니다.
//
// 친절한 UX(User Experience)
// if (input_number < 1 || input_number > 100)
// 사용자가 실수를 범했을 때 프로그램이 뻗거나 이상하게 동작하는 대신, "범위 내의 수를 입력해 주세요"라고 친절하게 안내하고 다시 입력받는 흐름이 아주 매끄럽습니다.
//
// 깔끔한 break 활용
// while (1)로 무한 루프를 돌리다가, 정답을 맞혔을 때만 break로 탈출하는 구조가 아주 명확합니다.
