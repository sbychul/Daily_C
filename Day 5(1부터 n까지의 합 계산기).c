#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
    int target = 0, sum = 0, i = 0;

    printf("어디까지 더할까요? (양의 정수를 입력하세요): ");
    scanf("%d", &target);

    if (target < 1) {
        printf("입력된 값이 올바르지 않습니다.");
    }
    else {
        for (; i <= target; i++) {
            sum += i;
        }

        printf("1부터 %d까지의 합은 %d입니다.", target, sum);
    }

    return 0;
}

// 한 가지 재미있는 디테일을 짚어드리자면 :
//
// int i = 0;
// ...
// for (; i <= target; i++)
//
// 현재 코드는 i가 0부터 시작합니다.그래서 컴퓨터는 0 + 1 + 2 + ... + target 순서로 계산을 수행합니다. 물론 0을 더해도 결과값(sum)은 변하지 않기 때문에 정답입니다!
//
// 다만, 조금 더 깐깐하게 최적화를 한다면 :
// "1부터 더하라"고 했으니 i를 1로 시작하게 하거나,
// for (i = 1; i <= target; i++) 처럼 반복문 안에서 초기화를 명시해주면,
// 컴퓨터가** "0을 더하는 쓸데없는 동작 하나" * *를 덜 할 수 있겠죠 ? (티끌 같은 최적화입니다 ㅎㅎ)