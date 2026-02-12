#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
	int money;
	int worked_time;
	int total;
	double tax;
	double salary;

	printf("시급을 입력하세요: ");
	scanf("%d", &money);

	printf("일한 시간을 입력하세요: ");
	scanf("%d", &worked_time);

	total = money * worked_time;
	tax = total * 0.033;
	salary = total - tax;

	printf("--- 급여 명세서 ---\n총 급여: %d 원\n세금(3.3%%): %.2f 원\n실수령액: %.2f 원\n", total, tax, salary);

	return 0;
}

//질문하신 **"% 기호가 출력이 안 되는 문제"**는 C언어 초심자들이 정말 많이 겪는 재미있는 특징 때문입니다.

//🔍 원인: %는 C언어에게 '특수 기호'입니다.
//printf 함수 안에서% 는** "자, 이제부터 변수값 넣을 거야! (%d, %f 처럼)" * *라고 컴퓨터에게 신호를 보내는 * *예약어(마법의 문자) * *입니다.

//그래서 컴퓨터는 세금(3.3 %)를 보고 이렇게 오해합니다.

//"어? %가 나왔네? 근데 뒤에 )가 있네? %d도 아니고 %f도 아니고 이게 무슨 명령이지? 에라 모르겠다, 무시하자."

//✅ 해결책 : % 를 두 번 쓰세요!(%%)
//컴퓨터에게 "이건 명령어가 아니라 그냥 문자 퍼센트(%)야!"라고 알려주려면 % %라고 두 번 연속으로 써주면 됩니다.