#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50

// --- 1. 그래프 관련 구조체 ---
typedef struct GraphNode {
    int vertex;
    struct GraphNode* link;
} GraphNode;

typedef struct GraphType {
    int n;
    GraphNode* adj_list[MAX_VERTICES];
} GraphType;

// --- 2. 스택(Stack) 관련 구조체 및 함수 ---
typedef struct {
    int data[MAX_VERTICES];
    int top;
} StackType;

void init(StackType* s) { s->top = -1; }
int is_empty(StackType* s) { return s->top == -1; }
void push(StackType* s, int item) { s->data[++(s->top)] = item; }
int pop(StackType* s) { return s->data[(s->top)--]; }

// --- 3. 그래프 관련 함수 ---
void graph_init(GraphType* g) {
    g->n = 0;
    for (int v = 0; v < MAX_VERTICES; v++) {
        g->adj_list[v] = NULL;
    }
}

void insert_vertex(GraphType* g, int v) {
    g->n++;
}

// 위상 정렬은 '방향 그래프'이므로 간선을 한쪽으로만 연결합니다. (u -> v)
void insert_edge(GraphType* g, int u, int v) {
    GraphNode* node = (GraphNode*)malloc(sizeof(GraphNode));
    node->vertex = v;
    node->link = g->adj_list[u];
    g->adj_list[u] = node;
}

// --- 🎯 4. 위상 정렬 함수 (빈칸 유지) ---
int topo_sort(GraphType* g) {
    int i;
    StackType s;
    GraphNode* node;

    // 1. 모든 정점의 진입 차수를 저장할 배열 동적 할당 및 0으로 초기화
    int* in_degree = (int*)malloc(g->n * sizeof(int));
    for (i = 0; i < g->n; i++) {
        in_degree[i] = 0;
    }

    // 2. 그래프를 순회하며 실제 진입 차수 계산하기
    for (i = 0; i < g->n; i++) {
        node = g->adj_list[i]; // 정점 i에서 나가는 간선들
        while (node != NULL) {

            // node가 가리키는 도착 정점의 진입 차수를 1 증가
            in_degree[node->vertex]++;
            node = node->link;
        }
    }

    // 3. 진입 차수가 0인 정점을 찾아 스택에 삽입
    init(&s);
    for (i = 0; i < g->n; i++) {
        if (in_degree[i] == 0) push(&s, i);
    }

    // 4. 위상 순서 생성 로직
    while (!is_empty(&s)) {
        int w = pop(&s);
        printf("정점 %d -> ", w); // 정점 출력 (수강 완료!)

        node = g->adj_list[w]; // 방금 수강 완료한 과목의 다음 과목들
        while (node != NULL) {
            int u = node->vertex;

            // 이웃 정점(u)의 진입 차수를 1 감소
            in_degree[u]--;

            // 감소시킨 후, 이웃 정점(u)의 진입 차수가 0이 되었다면 스택에 push.
            if (in_degree[u] == 0) { push(&s, u); }

            node = node->link;
        }
    }

    free(in_degree);
    printf("\n");
    return 1;
}

// --- 5. 메인 함수 ---
int main() {
    GraphType g;
    graph_init(&g);

    // 정점 6개 추가 (0번 ~ 5번)
    for (int i = 0; i < 6; i++) {
        insert_vertex(&g, i);
    }

    // 방향 간선 추가 (DAG: 사이클이 없는 방향 그래프)
    // 며칠 전 손으로 푸셨던 그래프(1~6)를 0번 인덱스(0~5)에 맞춰 변환했습니다.
    insert_edge(&g, 0, 2); // 0번 -> 2번
    insert_edge(&g, 1, 2); // 1번 -> 2번
    insert_edge(&g, 1, 3); // 1번 -> 3번
    insert_edge(&g, 2, 4); // 2번 -> 4번
    insert_edge(&g, 3, 5); // 3번 -> 5번
    insert_edge(&g, 4, 5); // 4번 -> 5번

    printf("위상 정렬 결과: ");
    topo_sort(&g);

    return 0;
}