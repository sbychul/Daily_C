#include <stdio.h>
#include "calculator.h"

int main() {
	int num1 = 0, num2 = 0;
	printf("[계산기 프로그램]\n두 정수 입력: ");
	scanf("%d %d", &num1, &num2);
	printf("결과: 더하기 = %d, 빼기 = %d", add(num1, num2), odd(num1, num2));
	return 0;
}