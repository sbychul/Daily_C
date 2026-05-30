#include <stdio.h>

#define SIZE 9
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )

void print_list(int list[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", list[i]);
    printf("\n");
}

// 🎯 피벗을 기준으로 배열을 두 그룹으로 나누는 분할 함수
int partition(int list[], int left, int right) {
    int pivot, temp;
    int low, high;

    low = left;
    high = right + 1;
    pivot = list[left]; // 💡 맨 앞 원소를 피벗으로 설정

    // low와 high가 교차할 때까지 무한 루프
    do {
        // 경계값(right)을 넘지 않으면서 list[low]가 pivot보다 작으면 low를 계속 증가.
        do {
            low++;
        } while (low < right && list[low] < pivot);

        // 경계값(left)보다 크면서 list[high]가 pivot보다 크면 high를 계속 감소시킵니다.
        do {
            high--;
        } while (high > left && list[high] > pivot);

        // low와 high가 교차하지 않았다면 찾은 두 원소의 자리를 맞바꿉니다.
        if (low < high) {
            SWAP(list[low], list[high], temp);
        }
    } while (low < high);

    // low와 high가 교차해서 루프를 빠져나왔다면, 
    // 피벗(list[left])과 high가 가리키는 값을 교환하여 피벗을 제자리에 꽂아 넣습니다.
    SWAP(list[left], list[high], temp);

    return high; // 피벗의 최종 위치(인덱스) 반환
}

// 🎯 퀵 정렬 메인 함수 (재귀 호출)
void quick_sort(int list[], int left, int right) {
    if (left < right) {
        int q = partition(list, left, right); // 피벗 정착 및 분할 위치 획득
        quick_sort(list, left, q - 1);       // 피벗 왼쪽 덩어리 퀵 정렬
        quick_sort(list, q + 1, right);      // 피벗 오른쪽 덩어리 퀵 정렬
    }
}

int main() {
    int list[SIZE] = { 5, 3, 8, 4, 9, 1, 6, 2, 7 };

    printf("초기 배열: "); print_list(list, SIZE);
    printf("-------------------------------------\n");

    quick_sort(list, 0, SIZE - 1);

    printf("-------------------------------------\n");
    printf("최종 정렬: "); print_list(list, SIZE);

    return 0;
}