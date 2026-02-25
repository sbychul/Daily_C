#include <stdio.h>

// 오늘의 문법 설명 : "거품이 위로 올라가듯"
// 정렬 알고리즘 중 가장 직관적이고 구현하기 쉬운 것이 바로 버블 정렬(Bubble Sort)입니다.

// 원리: 바로 옆에 있는 숫자(인접한 두 원소)를 비교해서, 앞의 숫자가 뒤의 숫자보다 크면 자리를 바꿉니다(Swap).
// 특징: 한 바퀴를 쫙 돌고 나면, 가장 큰 숫자가 배열의 맨 끝으로 밀려나서 자리를 잡습니다.
// 마치 무거운 거품이 위로 떠오르는 것과 같다고 해서 버블 정렬이라고 부릅니다.

int main() {
	int temp = 0; // 정렬에 사용할 임시 변수. 변수든 노드든 뭐든간에 임시를 잘 활용하는 게 최고
	int arr[5] = { 50, 20, 40, 10, 30 };

	printf("[정렬 전 배열]\n");
	for (int i = 0; i < 5; i++) {
		printf("%d ", arr[i]);
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4 - i; j++) {
			if (arr[j] > arr[j + 1]) {
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}

	printf("\n\n[버블 정렬 완료]\n");
	for (int i = 0; i < 5; i++) {
		printf("%d ", arr[i]);
	}
	return 0;
}