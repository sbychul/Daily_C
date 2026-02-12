#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
    int score = 0;

    printf("점수를 입력하세요: ");
    scanf("%d", &score);

    if (score > 100 || score < 0) {
        printf("잘못된 점수 입력입니다.");
    }
    else {
        if (score >= 90)
        {
            printf("A학점입니다! (장학금 대상)");
        }
        else if (score >= 80) {
            printf("B학점입니다. (고생하셨습니다.)");
        }
        else if (score >= 70) {
            printf("C학점입니다. (재수강 고민 좀...)");
        }
        else {
            printf("F학점입니다. (교수님과 면담 필요)");
        }
    }

    return 0;
}
