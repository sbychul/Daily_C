#include <stdio.h>
#include <stdlib.h>

// 오늘의 핵심 구조 : 두 개의 포인터(교안 100p 부근)
// 연결 리스트 큐는 두 개의 특별한 포인터가 필요합니다.
// front : 줄의 맨 앞(삭제가 일어나는 곳)을 가리킵니다.
// rear : 줄의 맨 뒤(삽입이 일어나는 곳)를 가리킵니다.

// 2. 데이터 넣기 : enqueue
// 새로운 사람이 줄 뒤에 서는 과정입니다.
// 1. 새 노드를 만듭니다.
// 2. 큐가 비어있다면, front와 rear 모두 새 노드를 가리키게 합니다.
// 3. 큐에 사람이 있다면, 현재 rear의 뒤에 새 노드를 붙이고 rear를 새 노드로 옮깁니다.

typedef int element;
typedef struct QueueNode {
    element data;
    struct QueueNode* link;
} QueueNode;

typedef struct {
    QueueNode* front, * rear;
} LinkedQueueType;

// 초기화
void init(LinkedQueueType* q) {
    q->front = q->rear = NULL;
}

// 🚀 [오늘의 미션] 큐에 데이터를 넣는 함수
void enqueue(LinkedQueueType* q, element item) {
    QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
    temp->data = item;
    temp->link = NULL;

    if (q->front == NULL) { // 큐가 비어있다면
        q->front = temp; // 처음과 끝이 temp로 똑같음.
        q->rear = temp;
    }
    else { // 큐에 데이터가 있다면
        q->rear->link = temp; // 맨 뒤에 넣는 것. 이전 맨 뒤의 뒤는(말이 이상한데) temp로 지정.
        q->rear = temp; // 맨 뒤를 기리키는 포인터가 temp를 가리키도록 설정.
    }
}

void print_queue(LinkedQueueType* q) {
    for (QueueNode* p = q->front; p != NULL; p = p->link)
        printf("%d->", p->data);
    printf("NULL\n");
}

int main(void) {
    LinkedQueueType q;
    init(&q);

    enqueue(&q, 10); print_queue(&q);
    enqueue(&q, 20); print_queue(&q);
    enqueue(&q, 30); print_queue(&q);

    return 0;
}