#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
    int system_password = 1234;
    int input_password = 0;

    printf("비밀번호를 입력하세요: ");
    scanf("%d", &input_password);
    if (input_password == system_password)
    {
        printf("[로그인 성공]");
    }

    else
    {
        printf("[로그인 실패: 비밀번호가 일치하지 않습니다.]");
    }

    return 0;
}

//군더더기 없이 아주 깔끔합니다. 특히 가장 중요한 2가지를 정확하게 지키셨습니다.
//
//== (비교 연산자) : = (대입)이라고 실수하기 쉬운 부분인데, == 를 정확히 사용하여 "같다"는 의미를 표현하셨습니다.
//{ } (중괄호) : C언어에서는 if문 내용이 한 줄일 때 중괄호를 생략할 수 있지만, 지금처럼 무조건 중괄호를 치는 습관이 훨씬 좋습니다. (나중에 코드를 수정할 때 에러를 막아줍니다.)