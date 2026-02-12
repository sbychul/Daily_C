#include <stdio.h>

int add(int num1, int num2) {
    return num1 + num2;
}

int sub(int num1, int num2) {
    return num1 - num2;
}

int mul(int num1, int num2) {
    return num1 * num2;
}

float div(int num1, int num2) {
    return (float)num1 / num2;
}

int main() {
    int input_1 = 0, input_2 = 0;

    printf("두 정수를 입력하세요: ");
    scanf("%d %d", &input_1, &input_2);
    printf("[계산 결과]\n덧셈: %d\n뺄셈: %d\n곱셈: %d\n나눗셈: %.2f\n", add(input_1, input_2), sub(input_1, input_2), mul(input_1, input_2), div(input_1, input_2));
    return 0;
}

// 🔍 딱 하나, "악마의 디테일"을 챙긴다면 ? (Division by Zero)
// 지금 코드는 완벽하지만, 만약 사용자가 두 번째 숫자에 0을 넣으면 어떻게 될까요 ? 수학에서 0으로 나누기는 불가능하기 때문에,
// 컴퓨터는 inf(무한대)를 출력하거나 프로그램이 멈출 수도 있습니다.
//
// 나중에 여유가 되신다면 div 함수에 이런 안전장치를 추가해 보는 것도 좋습니다.
//
// float div(int num1, int num2) {
//     if (num2 == 0) {
//         return 0.0; // 0으로 나누면 그냥 0을 뱉거나, 에러 처리를 함
//     }
//     return (float)num1 / num2;
// }

// #include <stdio.h>
//
// // [예고편] "add라는 애는 정수 2개 받고 정수 뱉는 애야. 믿고 진행해."
// int add(int a, int b);  // <-- 이게 '함수 원형'입니다. (세미콜론 필수!) (Prototype)
// 
// int main() {
//     // 컴파일러: "아까 예고편에서 봤던 그 add구나! 오케이 통과!"
//     int result = add(10, 20);
//     return 0;
// }
//
// // [본편] 실제 기계 내용은 여기에
// int add(int a, int b) {
//     return a + b;
// }