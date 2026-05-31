#include <stdio.h>

#define MAX_SIZE 10

// 1. 🎯 개선된 순차 탐색 (보초값 활용, 배열의 끝에 key값을 삽입)
// 보초값을 넣기 위해 배열의 끝(high + 1)에 여유 공간이 있어야 한다.
int seq_search2(int list[], int key, int low, int high) {
    int i;
    list[high + 1] = key; // 리스트 끝에 탐색 키 저장 (보초값)

    // list[i]가 찾고자 하는 key와 다를 동안만 i를 증가
    for (i = low; list[i] != key; i++) {
        ; // 아무것도 하지 않고 i만 증가
    }

    if (i == (high + 1)) return -1; // 끝까지 갔다면 탐색 실패
    else return i;                  // 아니라면 탐색 성공 (key가 있는 곳의 인덱스 반환)
}

// 2. 🎯 이진 탐색 (Binary Search)
// 전제 조건: 배열이 반드시 오름차순으로 정렬되어 있어야 함
int search_binary(int list[], int key, int low, int high) {
    int middle;

    while (low <= high) {
        middle = (low + high) / 2;

        if (key == list[middle]) {
            return middle; // 탐색 성공, 해당 인덱스 반환
        }
        else if (key > list[middle]) { // 찾으려는 값이 중앙 값보다 크다면 오른쪽에서 찾기
            low = middle + 1;
        }
        else {
            // 찾으려는 값이 작다면 왼쪽에서 찾기
            high = middle - 1;
        }
    }
    // low가 high와 같아지거나 역전한다면 탐색 실패
    return -1;
}

int main() {
    // 순차 탐색용 배열 (맨 끝 인덱스 7은 보초값을 위해 비워둠)
    int unsorted_list[8] = { 9, 5, 8, 3, 7, 2, 1, 0 }; // 0은 임시 빈칸

    // 이진 탐색용 배열 (미리 오름차순 정렬됨)
    int sorted_list[7] = { 1, 2, 3, 5, 7, 8, 9 };

    printf("--- 개선된 순차 탐색 ---\n");
    int idx1 = seq_search2(unsorted_list, 7, 0, 6);
    if (idx1 != -1) printf("숫자 7은 인덱스 %d에 있습니다.\n", idx1);
    else printf("탐색 실패\n");

    printf("\n--- 이진 탐색 ---\n");
    int idx2 = search_binary(sorted_list, 7, 0, 6);
    if (idx2 != -1) printf("숫자 7은 인덱스 %d에 있습니다.\n", idx2);
    else printf("탐색 실패\n");

    return 0;
}