#include <stdio.h>
#include <stdlib.h>

#define SIZE 10
#define BUCKETS 10  // 0~9번 자릿수를 위한 10개의 버킷
#define DIGITS 2    // 최대 2자릿수(0~99) 정렬 기준

// --- 단순 큐(Queue) 구현부 ---
typedef struct {
    int data[SIZE];
    int front, rear;
} QueueType;

void init(QueueType* q) { q->front = q->rear = 0; }
int is_empty(QueueType* q) { return q->front == q->rear; }
void enqueue(QueueType* q, int item) { q->data[(q->rear++) % SIZE] = item; }
int dequeue(QueueType* q) { return q->data[(q->front++) % SIZE]; }
// -----------------------------

// 🎯 기수 정렬 메인 함수
void radix_sort(int list[], int n) {
    int i, b, d;
    int factor = 1; // 자릿수를 결정하는 인자 (1 -> 10 -> 100 ...)
    QueueType queues[BUCKETS];

    // 1. 10개의 버킷(큐) 초기화
    for (b = 0; b < BUCKETS; b++) init(&queues[b]);

    // 2. 자릿수(DIGITS)만큼 메인 루프 돌기
    for (d = 0; d < DIGITS; d++) {

        for (i = 0; i < n; i++) {
            int bucket_idx = (list[i] / factor) % 10; // 자릿수를 구하여
            enqueue(&queues[bucket_idx], list[i]); // 해당 자릿수에 해당하는 버킷에 요소를 삽입
        }

        i = 0; // list의 인덱스 초기화
        for (b = 0; b < BUCKETS; b++) { // 0부터 버킷의 최대 크기까지 순회
            while (!is_empty(&queues[b])) { // b가 가리키고 있는 버킷이 빌 때까지
                list[i++] = dequeue(&queues[b]); // enqueue하여 배열에 삽입 = 자릿수 정렬 완료
            }
        }

        factor *= 10; // 다음 자릿수(10의 자리)로 이동
    }
}

int main() {
    int list[SIZE] = { 85, 14, 92, 47, 12, 51, 63, 22, 7, 30 };

    printf("초기 배열: ");
    for (int i = 0; i < SIZE; i++) printf("%d ", list[i]);
    printf("\n-----------------------------------------\n");

    radix_sort(list, SIZE);

    printf("최종 정렬: ");
    for (int i = 0; i < SIZE; i++) printf("%d ", list[i]);
    printf("\n");

    return 0;
}