#include <stdio.h>
#define ARR_SIZE 10

// 오늘의 문법 설명 : "분할 정복 (Divide and Conquer)"
// 퀵 정렬은 이름 그대로 '빠른' 정렬입니다.지금까지 배운 정렬들이 $O(N ^ 2)$의 시간이 걸렸다면,
// 퀵 정렬은 평균적으로 $O(N \log N)$이라는 압도적인 속도를 자랑합니다.

// 원리 :
// 1.  배열에서 기준점 하나를 잡습니다.이를 * *피벗(Pivot) * *이라고 부릅니다.
// 2.  피벗보다 작은 놈들은 왼쪽으로, 큰 놈들은 오른쪽으로 다 보냅니다. (이 과정을 파티셔닝이라고 합니다.)
// 3.  그러고 나면 피벗은 자기 자리를 딱 찾게 됩니다.
// 4.  이제 왼쪽 덩어리와 오른쪽 덩어리에 대해서 똑같은 짓을 반복합니다. (재귀 호출)

// 특징 : 어제 배운 '포인터'와 이전에 배웠던 '재귀 함수' 지식이 총동원되는 알고리즘입니다.

void quickSort(int arr[], int L, int R) {
    int pivot = arr[(L + R) / 2]; // 맨 처음과 맨 끝을 더한 뒤 나눔 = 가운데
    int left = L, right = R;
    int temp; // 신 강림

    while (left <= right) {
        while (arr[left] < pivot) left++;  // 피벗보다 큰 놈 찾을 때까지 전진
        while (arr[right] > pivot) right--; // 피벗보다 작은 놈 찾을 때까지 후진

        if (left <= right) { // 찾았으면 둘이 자리 바꿔! (우리의 신 temp 소환)
            temp = arr[left];
            arr[left] = arr[right];
            arr[right] = temp;
            left++; right--;
        }
    }
    // 나눠진 왼쪽과 오른쪽 덩어리를 다시 퀵 정렬 (재귀)
    if (L < right) quickSort(arr, L, right);
    if (left < R) quickSort(arr, left, R);
}

int main() {
	int arr[ARR_SIZE] = { 40, 10, 80, 90, 30, 50, 70, 20, 100, 60 };

    printf("정렬 전 배열]\n");
    for (int i = 0; i < ARR_SIZE; i++) {
        printf("%d ", arr[i]);
    }

    quickSort(arr, 0, ARR_SIZE - 1);

    printf("\n[퀵 정렬 후 배열]\n");
    for (int i = 0; i < ARR_SIZE; i++) {
        printf("%d ", arr[i]);
    }

	return 0;
}