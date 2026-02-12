#include <stdio.h>
#define PI 3.1415
#define MAX(a, b) (a > b ? a : b)
// 🛡️ 프로를 위한 디테일 : "괄호 방어막"
// 지금 작성하신 #define MAX(a, b) (a > b ? a : b)도 훌륭하지만, 현업에서는 혹시 모를 사고를 막기 위해 변수 하나하나에 괄호를 씌우는 것을 권장합니다.
// 왜냐하면 ? 만약 누군가 MAX(n1 + 1, n2) 처럼 수식을 넣었을 때 연산자 우선순위 때문에 꼬일 수도 있기 때문입니다.
// [추천 방식] 변수(a, b)마다 괄호를 씌워줍니다.
// #define MAX(a, b) ((a) > (b) ? (a) : (b))

int main() {
	int r = 0;
	printf("반지름 입력: ");
	scanf("%d", &r);

	printf("원의 넓이: %f\n", r * r * PI);

	int n1 = 0, n2 = 0;
	printf("\n두 정수 입력: ");
	scanf("%d %d", &n1, &n2);
	printf("더 큰 수: %d", MAX(n1, n2));
	return 0;
}