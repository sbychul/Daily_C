#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
    int total_seconds, remainings, hour, minute, second, count = 0;
    printf("변환할 전체 초(Seconds)를 입력하세요: ");
    scanf("%d", &total_seconds);

    hour = total_seconds / 3600;
    remainings = total_seconds % 3600;
    minute = remainings / 60;
    second = remainings % 60;

    printf("[계산 횟수: %d회]\n입력한 %d초는 [%d시간 %d분 %d초] 입니다.", ++count, total_seconds, hour, minute, second);

    return 0;
}

// C6001 코드에 관하여:

// 1. 경고의 의미 : "방 청소를 안 하셨는데요?"
// 파이썬에서 minute = 0이라고 쓰면, 컴퓨터가 깨끗한 빈방을 준비하고 0을 넣어줍니다. 하지만 C언어는 다릅니다.

// int minute; (선언) : "메모리에 'minute'이라는 방을 하나 잡아줘."

// 현실 : C언어는 방을 잡아주긴 하는데, 청소는 안 해줍니다.
// 그 방에는 이전에 썼던 프로그램이 남기고 간** 이상한 숫자(쓰레기값, Garbage Value)** 가 들어있습니다. (예 : -858993460...)

// 2. 왜 경고가 뜰까요 ? (범인은 scanf)
// 작성하신 코드를 보면 분명히 minute = remainings / 60; 으로 값을 넣었는데 왜 뭐라고 할까요 ?

// Visual Studio의 추리 과정은 이렇습니다 :

// 사용자가 scanf로 total_seconds에 숫자를 넣으려 한다.
// 만약 사용자가 숫자가 아니라 문자를 입력해서 scanf가 실패한다면 ? (아까 C6031 경고랑 연결됨)
// 그럼 total_seconds는 입력받은 게 없으니 쓰레기값 상태 그대로겠네 ?
// 그럼 remainings도 쓰레기값, 결국 minute도 쓰레기값으로 계산되겠네 ?

// "주인님! minute이 쓰레기값일 수도 있는 위험한 상태로 사용되고 있습니다!" (C6001)

// 즉, ** "최악의 경우(scanf 실패)를 가정했을 때, 변수가 똥통(?)에 빠질 수 있다" * *고 경고하는 겁니다.