#include <stdio.h>

#define MAX_SIZE 10
int sorted[MAX_SIZE]; // 정렬된 결과를 담을 임시 배열 (전역 변수)

// 배열 출력 함수
void print_list(int list[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", list[i]);
    printf("\n");
}

// 🎯 두 개의 정렬된 부분 배열을 병합하는 함수
void merge(int list[], int left, int mid, int right) {
    int i = left;      // 왼쪽 부분 배열의 시작 인덱스
    int j = mid + 1;   // 오른쪽 부분 배열의 시작 인덱스
    int k = left;      // 정렬될 임시 배열(sorted)의 인덱스
    int l;

    // 1. 양쪽 부분 배열 중 작은 값을 임시 배열로 복사
    // i가 왼쪽 배열 끝 인덱스(mid)에 도달하기 전 && j가 오른쪽 배열 끝 인덱스(right)에 도달하기 전
    while (i <= mid && j <= right) {
        if (list[i] <= list[j]) {
            sorted[k++] = list[i++];
        }
        else {
            sorted[k++] = list[j++];
        }
    }

    // 2. 한쪽 배열이 먼저 비워졌을 경우, 남아있는 나머지 배열의 값들을 일괄 복사 (l은 단순 카운터 변수)
    // 왼쪽 배열(i)이 먼저 비워졌다면(i > mid), 오른쪽 배열(j)에 남은 값들을 sorted에 모두 복사
    if (i > mid) {
        for (l = j; l <= right; l++) {
            sorted[k++] = list[l];
        }
    }
    // 반대로 오른쪽 배열이 먼저 비워졌다면, 왼쪽 배열(i)에 남은 값들을 sorted에 모두 복사
    else {
        for (l = i; l <= mid; l++) {
            sorted[k++] = list[l];
        }
    }

    // 3. 정렬된 임시 배열(sorted)의 결과를 원본 배열(list)로 다시 복사
    for (l = left; l <= right; l++) {
        list[l] = sorted[l];
    }
}

// 병합 정렬 메인 함수 (재귀 호출)
void merge_sort(int list[], int left, int right) {
    int mid;
    if (left < right) {
        mid = (left + right) / 2;     // 배열을 절반으로 분할
        merge_sort(list, left, mid);  // 왼쪽 부분 정렬
        merge_sort(list, mid + 1, right); // 오른쪽 부분 정렬
        merge(list, left, mid, right);// 병합
    }
}

int main() {
    int list[MAX_SIZE] = { 27, 10, 12, 20, 25, 13, 15, 22 };
    int n = 8;

    printf("초기 배열: "); print_list(list, n);
    merge_sort(list, 0, n - 1);
    printf("최종 정렬: "); print_list(list, n);

    return 0;
}