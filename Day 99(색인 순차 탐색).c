#include <stdio.h>

#define INDEX_SIZE 3
#define LIST_SIZE 9

// 색인 테이블을 위한 구조체 정의
typedef struct {
    int key;   // 해당 구역의 시작 값
    int index; // 해당 구역의 시작 인덱스
} I_table;

// 🎯 색인 순차 탐색 함수
int index_search(int list[], int n, I_table index_list[], int index_size, int key) {
    int i, low, high;

    // 1. 만약 찾으려는 key가 전체 범위를 벗어나면 즉시 예외 처리
    if (key < list[0] || key > list[n - 1]) return -1;

    // 2. 색인 테이블을 스캔하여 key가 포함된 구역(low ~ high)을 찾습니다.
    // i는 index_size보다 작고, i가 가리키는 곳의 key가 key보다 작거나 같을 동안 이동하면서 탐색.
    for (i = 0; i < index_size && index_list[i].key <= key; i++) {
        ; // 조건이 만족하는 동안 index_list의 다음 칸으로 이동
    }

    // 3. 찾아낸 색인 위치를 기반으로 원본 배열의 탐색 시작(low)과 끝(high) 경계선 설정
    // index_list[i-1]이 key가 속한 구역의 시작점이 됩니다.
    low = index_list[i - 1].index;

    // 다음 색인(i번째)이 존재하면 그 색인의 index 전까지가 경계선(따라서 그 색인의 인덱스가 high), 없으면 배열의 끝(n)
    if (i < index_size) {
        high = index_list[i].index;
    }
    else {
        high = n;
    }

    // 4. 설정된 구역(low부터 high 전까지) 안에서만 타겟을 순차 탐색
    for (i = low; i < high; i++) {
        if (list[i] == key) return i; // 탐색 성공 (인덱스 반환)
    }

    return -1; // 탐색 실패
}

int main() {
    // 원본 배열 (미리 정렬되어 있음)
    int list[LIST_SIZE] = { 3, 9, 15, 22, 31, 55, 67, 88, 99 };

    // 색인 테이블 (3칸 간격으로 이정표를 세움)
    // 0번 인덱스의 3, 3번 인덱스의 22, 6번 인덱스의 67
    I_table index_list[INDEX_SIZE] = { {3, 0}, {22, 3}, {67, 6} };

    int target = 55;
    printf("탐색할 키값: %d\n", target);

    int result = index_search(list, LIST_SIZE, index_list, INDEX_SIZE, target);

    if (result != -1) {
        printf("탐색 성공! 숫자 %d는 인덱스 %d에 있습니다.\n", target, result);
    }
    else {
        printf("탐색 실패!\n");
    }

    return 0;
}