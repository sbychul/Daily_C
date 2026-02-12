#include <stdio.h>
#define ARR_SIZE 5

int get_array_sum(int* ptr, int size) {
    int sum = 0, i = 0;
    for (i = 0; i < size; i++) {
        sum += *(ptr + i);
    }
    return sum;
}

int main() {
    int arr[ARR_SIZE] = { 0 }, x = 0;
    for (x = 0; x < ARR_SIZE; x++) {
        printf("정수로 %d번째 배열 요소를 입력하세요: ", x + 1);
        scanf("%d", &arr[x]);
    }
    printf("입력받은 배열 요소: ");
    for (x = 0; x < ARR_SIZE; x++) {
        printf("%d ", arr[x]);
    }
    printf("\n배열 요소의 총합 : %d", get_array_sum(arr, ARR_SIZE));
    /*이 부분이 오늘 수업의 핵심이었습니다.
    함수는 int* ptr(포인터)를 달라고 했는데, 사용자 님은 arr(배열 이름)을 던져줬습니다.
    그런데도 에러 없이 잘 받아먹었죠 ?
    이것이 바로 * *"배열의 이름(arr)은 첫 번째 요소의 주소(&arr[0])와 같다" * *는 증거입니다.컴퓨터 입장에서는 arr나 ptr이나 둘 다 "주소값 하나"일 뿐이니까요.*/

    return 0;
}