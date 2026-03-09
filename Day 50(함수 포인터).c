#include <stdio.h>

// 오늘의 문법 설명: "함수도 결국 메모리에 있다"
// 지금까지 포인터(*)는 변수나 배열의 주소만 가리켰습니다.
// 하지만 생각해보면 우리가 작성한 main이나 printf 같은 함수(코드)들 역시 실행될 때 메모리 어딘가에 올라가 있어야 합니다.
// 그렇다면, 그 함수의 시작 주소를 포인터에 담아두고 원할 때마다 리모컨처럼 버튼을 눌러서 실행시킬 수도 있지 않을까요?
// 그것이 바로 함수 포인터입니다.

// 원리 : 함수의 이름 자체가 곧 그 함수의 시작 주소입니다. (배열의 이름이 배열의 시작 주소인 것과 똑같습니다!)
// 장점 : if - else나 switch 문을 수십 개씩 쓰지 않아도, 상황에 맞는 함수를 포인터 하나로 바꿔 끼우며 실행할 수 있습니다.
// (게임 엔진이나 운영체제에서 엄청나게 씁니다.)

// 포인터로 불러낼 일반 함수들. (add, sub, mul, div)
int add(int a, int b) {
	return a + b;
}
int sub(int a, int b) {
	return a - b;
}
int mul(int a, int b) {
	return a * b;
}
int div(int a, int b) {
	return a / b;
}

int main() {
	int (*functions[4])(int, int); // 함수들을 저장할 포인터의 배열 형성. 배열명에 괄호를 무조건 붙여주기. (*(배열명))
	functions[0] = add;
	functions[1] = sub;
	functions[2] = mul;
	functions[3] = div;

	int num1 = 0, num2 = 0;
	printf("1번째 숫자를 입력하세요: ");
	scanf("%d", &num1);
	printf("2번째 숫자를 입력하세요: ");
	scanf("%d", &num2);

	printf("\n덧셈, 뺄셈, 곱셈, 나눗셈 순서로 결과 출력\n");
	for (int i = 0; i < 4; i++) {
		printf("%d\n", functions[i](num1, num2));
	}

	return 0;
}