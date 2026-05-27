#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 5
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )

// 배열 출력 함수
void print_list(int list[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", list[i]);
    printf("\n");
}

// 1. 🎯 선택 정렬 (Selection Sort)
void selection_sort(int list[], int n) {
    int i, j, min, temp;
    for (i = 0; i < n - 1; i++) {
        min = i; // 최솟값의 인덱스 기록용

        // i 다음 칸부터 끝까지 돌며 가장 작은 값의 인덱스(min)를 찾기.
        for (j = i + 1; j < n; j++) { // j = i + 1, i 다음 칸부터
            if (list[min] > list[j]) { // 내부의 값을 비교, 현재 최솟값보다 j가 가리키는 게 더 작다면
                min = j; // 최솟값의 인덱스 = j
            }
        }

        // 찾은 최솟값과 i번째 자리를 교환
        if (i != min) {
            SWAP(list[i], list[min], temp);
        }
    }
}

// 2. 🎯 삽입 정렬 (Insertion Sort)
void insertion_sort(int list[], int n) {
    int i, j, key;
    // 두 번째 칸(인덱스 1)부터 시작
    for (i = 1; i < n; i++) {
        key = list[i]; // 현재 정렬할 타겟 값 저장

        // key보다 큰 값들을 뒤로 한 칸씩 밀어내기.
        // 힌트: j는 i-1부터 시작하여 역방향으로 진행하며, list[j]가 key보다 클 때만 돕니다.
        for (j = i - 1; j >= 0 && list[j] > key; j--) {
            list[j + 1] = list[j]; // 레코드를 오른쪽으로 이동
        }

        // 알맞은 위치에 key 삽입
        list[j + 1] = key;
    }
}

// 3. 🎯 버블 정렬 (Bubble Sort)
void bubble_sort(int list[], int n) {
    int i, j, temp;
    // 정렬 영역을 뒤에서부터 하나씩 줄여나갑니다.
    for (i = n - 1; i > 0; i--) {

        // 0번부터 i번까지 가면서 인접한 두 원소를 비교해 큰 원소를 뒤로
        for (j = 0; j < i; j++) {
            // 인접한 j 항목과 j+1 항목의 크기를 비교
            if (list[j] > list[j + 1]) { // j가 가리키는 값이 더 크면
                SWAP(list[j], list[j + 1], temp); // j와 j + 1의 값을 바꿔 오름차순 정렬
            }
        }
    }
}

int main() {
    int orig_list[SIZE] = { 7, 4, 9, 2, 5 };
    int list[SIZE];

    // 1. 선택 정렬 테스트
    for (int i = 0; i < SIZE; i++) list[i] = orig_list[i];
    printf("선택 정렬 전: "); print_list(list, SIZE);
    selection_sort(list, SIZE);
    printf("선택 정렬 후: "); print_list(list, SIZE);
    printf("------------------------\n");

    // 2. 삽입 정렬 테스트
    for (int i = 0; i < SIZE; i++) list[i] = orig_list[i];
    printf("삽입 정렬 전: "); print_list(list, SIZE);
    insertion_sort(list, SIZE);
    printf("삽입 정렬 후: "); print_list(list, SIZE);
    printf("------------------------\n");

    // 3. 버블 정렬 테스트
    for (int i = 0; i < SIZE; i++) list[i] = orig_list[i];
    printf("버블 정렬 전: "); print_list(list, SIZE);
    bubble_sort(list, SIZE);
    printf("버블 정렬 후: "); print_list(list, SIZE);

    return 0;
}