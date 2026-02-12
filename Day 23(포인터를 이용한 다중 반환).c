#include <stdio.h>
// 오늘의 문법 설명: "포인터를 이용한 다중 반환"
// C언어의 함수는 return을 한 번 하면 끝나버려서, 결과값을 딱 하나만 돌려줄 수 있습니다.그런데 만약 배열에서 최댓값과 최솟값을 동시에 구해서 가져오고 싶다면?
// return으로는 불가능합니다.
// 이때 * *"빈 그릇(변수)의 주소" * *를 함수에 보내고, 함수가 그 주소에 값을 채워 넣게 하면 됩니다.

#define NUMBERS_SIZE 7

void find_min_max(int arr[], int size, int* max, int* min) {
	*max = arr[0];
	*min = arr[0];
	
	for (int i = 1; i < size; i++) {
		if (*min > arr[i]) { 
			*min = arr[i];
		}

		if (*max < arr[i]) {
			*max = arr[i];
		}
	}
}

int main() {
	int numbers[NUMBERS_SIZE] = { 12, 5, 89, 2, 45, 99, 17 }, max_val = 0, min_val = 0;
	// 배열 안의 갯수가 모자라면 (위 배열은 7개뿐, 8번째 값을 찾으려고 하면) 자동으로 값을 0으로 채움

	printf("[배열 분석 결과]\n배열의 데이터: ");
	for (int i = 0; i < NUMBERS_SIZE; i++) {
		printf("%d ", numbers[i]);
	}

	find_min_max(numbers, NUMBERS_SIZE, &max_val, &min_val);
	printf("\n---------------------\n최댓값: %d\n최솟값: %d", max_val, min_val);
	return 0;
}