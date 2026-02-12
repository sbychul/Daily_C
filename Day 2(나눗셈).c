#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
	int apples, people, share, remainder;

	printf("전체 사과 개수: ");
	scanf("%d", &apples);

	printf("나눠줄 사람 수: ");
	scanf("%d", &people);

	share = apples / people;
	remainder = apples % people;

	printf("한 사람당 %d개의 사과를 가집니다.\n남는 사과는 %d개입니다.", share, remainder);

	return 0;
}

//🔍 잠깐! 여기서 "3.75개"를 구하고 싶다면? (심화)
//지금은 int(정수)라서 15 / 4 = 3이 나왔지만, 만약 정확하게 3.75라는 값을 얻고 싶다면 어떻게 해야 할까요 ?

//C언어에서는 * *"강제 형 변환(Type Casting)" * *이라는 기술을 씁니다.

//"야, 사과(apples) 너 잠깐만 실수(double)인 척해봐."

// 정수끼리 나누면 3이 나오지만...
//double real_share;

// (double)을 앞에 붙이면 아주 잠깐 실수로 변신합니다.
// 15.0 / 4 가 되어서 결과도 3.75가 됩니다.
//real_share = (double)apples / people;

//printf("정확히 나누면 %.2f개 입니다.", real_share);