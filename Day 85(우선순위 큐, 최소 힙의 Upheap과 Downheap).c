#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENT 200

// 힙의 요소 구조체
typedef struct {
    int key;
} element;

// 힙 구조체
typedef struct {
    element heap[MAX_ELEMENT];
    int heap_size;
} HeapType;

// 힙 초기화
void init(HeapType* h) {
    h->heap_size = 0;
}

// 최소 힙 삽입 함수
void insert_min_heap(HeapType* h, element item) {
    int i;
    i = ++(h->heap_size); // 1. 힙 크기를 1 증가시키고, 인덱스 i를 맨 끝으로 설정

    // 2. 부모를 끌어내리며 내(item)가 들어갈 자리 찾기
    // 조건 1: i가 1이 아니다 (루트 노드가 아닐 때까지)
    // 조건 2: 부모 노드(i / 2)의 키값이 삽입하려는 item의 키값보다 크다
    while (i != 1 && h->heap[i/2].key > item.key) {

        // 부모 노드를 현재 위치(i)로 끌어내리기
        h->heap[i] = h->heap[i / 2]; // 어차피 첫 i번 칸엔 아무것도 없다. 임시 변수 자체가 필요 없는 상황.

        // i를 부모 노드의 인덱스로 이동하여 한 칸 위로 올라가기
        i = i / 2; // 부모 노드로 올라가면서 칸을 찾는 방식, 그러니까 이름이 Upheap.
    }

    // 3. 최종적으로 찾은 자리에 새로운 item 삽입
    h->heap[i] = item;
}

// 최소 힙 삭제 함수 (Downheap)
element delete_min_heap(HeapType* h) {
    int parent, child;
    element item, temp;

    // 1. 반환할 진짜 최솟값(루트 노드)을 미리 보관해 둠
    item = h->heap[1]; 

    // 2. 힙의 맨 마지막 방에 있던 데이터를 temp에 빼두고, 힙 크기를 1 줄임
    temp = h->heap[(h->heap_size)--];

    // 3. 루트 자리(1번)가 비었으므로, 여기서부터 아래로 내려갈 준비
    parent = 1;
    child = 2;  // 일단 왼쪽 자식(1 * 2)을 가리키게 둠

    // 자식 노드가 힙 크기 내에 존재하는 동안 반복
    while (child <= h->heap_size) {

        // 왼쪽 자식과 오른쪽 자식 중 '더 작은' 자식 찾기.
        // 오른쪽 자식이 존재하고(child < h->heap_size, child가 계속 왼쪽 자식을 지정할 것임(2i), 근데 사이즈가 더 크다는 건? 2i + 1도 존재한다는 뜻.)
        // 오른쪽 자식이 왼쪽 자식보다 작다면 child를 오른쪽 자식 인덱스로 변경(1 추가, ++)
        if (child < h->heap_size && h->heap[child].key > h->heap[child + 1].key) child++;

        // temp(원래 마지막 노드)의 키값이 찾은 child의 키값보다 작거나 같다면?
        // 부모가 자식보다 작으므로 힙의 조건을 만족, 더 진행할 필요 없음.
        if (temp.key <= h->heap[child].key) break;


        // 자식이 더 작다면, 자식을 위로 끌어올리고 나는 한 칸 더 아래로 내려갈 준비
        // 힌트: 부모 자리에 자식의 값을 복사하고, parent와 child 인덱스를 한 칸(한 레벨)씩 아래로 갱신
        h->heap[parent] = h->heap[child]; // 부모 자리에 자식 투입.
        parent = child; // 위로 가버린 자식이 있던 칸으로 인덱스를 이동
        child = parent * 2; // 2를 곱하면 밑 레벨로 간다. 배열로 구현한 트리의 힘.
    }

    // 4. 최종적으로 찾은 빈자리에 맨 마지막에 있던 노드(temp)를 안착시킴
    h->heap[parent] = temp;

    // 5. 처음에 보관해둔 최솟값 반환
    return item;
}

int main(void) {
    HeapType heap;
    init(&heap);

    // 데이터 삽입
    insert_min_heap(&heap, (element) { 50 });
    insert_min_heap(&heap, (element) { 40 });
    insert_min_heap(&heap, (element) { 30 });
    insert_min_heap(&heap, (element) { 20 });
    insert_min_heap(&heap, (element) { 10 });
    insert_min_heap(&heap, (element) { 80 });

    // 힙 내부 배열 출력 (1번 인덱스부터 출력)
    printf("최소 힙 배열 상태: ");
    for (int i = 1; i <= heap.heap_size; i++) {
        printf("%d ", heap.heap[i].key);
    }
    printf("\n");

    // 데이터 순서대로 뽑아보기. 힙 정렬이 된다.
    printf("힙에서 데이터 뽑기(오름차순 정렬): ");
    while (heap.heap_size > 0) {
        element e = delete_min_heap(&heap);
        printf("%d ", e.key);
    }
    printf("\n");

    return 0;
}