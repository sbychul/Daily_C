#include <stdio.h>
#include <time.h>

// 1번 미션 핵심 힌트: "제곱을 제곱하면 횟수가 반으로 준다!
// 2^{10}을 구한다고 상상해 봅시다.
// 기존 방식 O(n): 2*2*2*2*2*2*2*2*2*2 (10번 곱함)
// O(log n) 방식: 2^{10}은 (2^5)^2 와 같습니다. (지수가 10에서 5로 반 토막 났습니다!)
// 2^5는 홀수니까, 2*(2^2)^2로 쪼갭니다. 2^2는 (2^1)^2와 같습니다.

double slow_power(double x, int n) { // 반복을 이용한 비효율적인 수업 예시
	double r = 1.0;
	for (int i = 0; i < n; i++) {
		r = r * x;
	}
	return r;
}

double fast_power(double x, int n) { // 효율적으로 바꿔보기.
	double result = 1.0;
	for (; n > 0; n /= 2) {
		if (n % 2 != 0) { // n이 홀수라면
			result *= x; // 결과값에 현재의 x를 곱해둔다.
		}
		x *= x; // 지수가 반으로 줄었으니, 밑은 제곱으로 덩치를 키운다.
	}
	return result;
}