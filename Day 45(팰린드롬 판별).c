#include <stdio.h>

// 오늘의 문법 설명 : "기러기, 토마토, 스위스, 인도인"
// 팰린드롬(Palindrome)이란 'level', 'radar', 'noon'처럼 앞에서부터 읽으나 뒤에서부터 읽으나 똑같은 단어나 문장을 말합니다.

// 원리 : 어제 배운 '문자열 뒤집기'와 아주 비슷합니다.
// start 포인터는 맨 앞을, end 포인터는 맨 끝 문자를 가리킵니다.
// 두 포인터가 가리키는 문자가 서로 같은지 비교합니다.
// 같다면 start는 뒤로 한 칸, end는 앞으로 한 칸 이동하며 계속 비교합니다.
// 만약 하나라도 다르면 ? "아, 이건 팰린드롬이 아니구나!" 하고 즉시 멈춥니다.
// 핵심 : 어제는 값을 '바꿨다면', 오늘은 값을 '비교만' 하면 됩니다.

int main() {
	char str[100] = { 0 };
	printf("문자열을 입력하세요: ");
	scanf("%s", str);

	char* start = str;
	char* end = str;

	while (*end != '\0') {
		end++;	// end를 마지막 문자 위치까지 보냄.
	}
	end--;		// 현재 \0 위치에 있는 상태. 한 칸 뒤로 보내기.

	int is_palindrome = 1; // 1: true, 0: false

	while (start < end) {
		if (*start != *end) {	// 주소가 가리키는 부분의 값이 다르네?
			is_palindrome = 0;	// 아니네?
			break;				// 나가.
		}
		start++;
		end--;
	}

	if (is_palindrome == 1) { // true
		printf("결과: 팰린드롬입니다!");
	}
	else { // false
		printf("결과: 팰린드롬이 아닙니다.");
	}

	return 0;
}