#include <stdio.h>

#define MAX_SIZE 10

// 🎯 보간 탐색 함수
int search_interpolation(int list[], int key, int n) {
    int low, high, j;
    low = 0;
    high = n - 1;

    // 💡 탐색 값(key)이 현재 범위의 최솟값과 최댓값 사이에 있을 때만 반복합니다.
    while (list[low] <= key && list[high] >= key) {

        // 타겟이 있을 법한 인덱스 j를 계산
        // 배열의 첫 값과 끝 값을 잇는 직선의 방정식을 활용
        j = low + ((key - list[low]) * (high - low)) / (list[high] - list[low]);

        if (key == list[j]) {
            return j; // 탐색 성공 (인덱스 반환)
        }
        else if (key > list[j]) {
            low = j + 1; // 찾고자 하는 값이 더 크면 오른쪽으로 구역 축소
        }
        else {
            high = j - 1; // 찾고자 하는 값이 더 작으면 왼쪽으로 구역 축소
        }
    }
    return -1; // 탐색 실패
}

int main() {
    // 데이터가 비교적 균등하게 정렬된 배열
    int list[MAX_SIZE] = { 3, 9, 15, 22, 31, 55, 67, 88, 91, 99 };

    int target = 67;
    printf("탐색할 키값: %d\n", target);

    int result = search_interpolation(list, target, MAX_SIZE);

    if (result != -1) {
        printf("탐색 성공! 숫자 %d는 인덱스 %d에 있습니다.\n", target, result);
    }
    else {
        printf("탐색 실패!\n");
    }

    return 0;
}