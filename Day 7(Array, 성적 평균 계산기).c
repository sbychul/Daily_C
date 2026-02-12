#include <stdio.h>

int main() {
    int scores[5] = { 0 }, number = 0, total = 0;
    for (number = 0; number < 5; number++) {
        printf("%d번 과목 점수: ", number + 1);
        scanf("%d", &scores[number]);
        total += scores[number];
    }

    printf("[입력된 점수] ");
    for (number = 0; number < 5; number++) {
        printf("%d ", scores[number]);
    }

    printf("평균 점수: %.2f점", (float) total / 5);
    return 0;
}

// [Level Up] "매직 넘버(Magic Number)" 없애기
// 지금 코드도 훌륭하지만, 나중에 학생 수가 5명이 아니라 30명으로 늘어난다면 어떻게 될까요?
// 코드 곳곳에 적힌 숫자 5를 찾아서 30으로 전부 고쳐야 합니다. (실수하기 딱 좋죠!)
//
// 이럴 때 쓰는 것이 #define (상수 정의) 입니다.
//
// #include <stdio.h>
// #define STUDENT_SIZE 5  // "야, 이제부터 STUDENT_SIZE는 무조건 5야!" (맨 위에 선언)
//
// int main() {
//     int scores[STUDENT_SIZE]; // 여기도 5로 바뀜
//     // ...
//     for (number = 0; number < STUDENT_SIZE; number++) { // 여기도 자동으로 5
//         // ...
//     }
// }
//
// 이렇게 맨 윗줄(STUDENT_SIZE 5)만 30으로 고치면, 코드 전체가 자동으로 30명 버전으로 업데이트됩니다. 아주 편리하겠죠?