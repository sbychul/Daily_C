#include <stdio.h>

#define SIZE 10

void print_list(int list[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", list[i]);
    printf("\n");
}

// 🎯 일정 간격(gap)만큼 떨어진 요소들을 삽입 정렬하는 함수
// 일반 삽입 정렬에서 '1' 대신 'gap'이 들어갔다고 생각하기.
void inc_insertion_sort(int list[], int first, int last, int gap) {
    int i, j, key;
    for (i = first + gap; i <= last; i = i + gap) {
        key = list[i];

        // j는 i - gap부터 시작
        // j가 첫 인덱스보다 크거나 같고, j가 가리키는 값이 key보다 큰 동안 j를 gap만큼 줄여가며 반복.
        for (j = i - gap; j >= first && list[j] > key; j -= gap) {
            list[j + gap] = list[j];
        }
        list[j + gap] = key;
    }
}

// 🎯 쉘 정렬 메인 함수
void shell_sort(int list[], int n) {
    int i, gap;

    // 초기 gap은 n/2로 시작하여, 0보다 큰 동안 절반(gap/2)씩 줄이기.
    for (gap = n / 2; gap > 0; gap = gap / 2) {

        if (gap % 2 == 0) gap++; // 짝수이면 1을 더해 홀수로 만듦 (성능 향상 팁)

        for (i = 0; i < gap; i++) {
            inc_insertion_sort(list, i, n - 1, gap); // 부분 리스트 정렬
        }
        printf("Gap이 %d일 때 정렬 결과: ", gap);
        print_list(list, n);
    }
}

int main() {
    int list[SIZE] = { 10, 8, 6, 20, 4, 3, 22, 1, 0, 15 };

    printf("초기 배열: ");
    print_list(list, SIZE);
    printf("------------------------\n");

    shell_sort(list, SIZE);

    printf("------------------------\n");
    printf("최종 정렬: ");
    print_list(list, SIZE);

    return 0;
}