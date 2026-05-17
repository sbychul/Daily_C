#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50

// 인접 리스트의 노드 구조체
typedef struct GraphNode {
    int vertex;                 // 연결된 정점 번호
    struct GraphNode* link;     // 다음 노드를 가리키는 포인터
} GraphNode;

// 그래프 구조체
typedef struct GraphType {
    int n;                      // 정점의 개수
    GraphNode* adj_list[MAX_VERTICES]; // 각 정점의 연결 리스트 헤드 포인터 배열
} GraphType;

// 그래프 초기화
void graph_init(GraphType* g) {
    int v;
    g->n = 0;
    for (v = 0; v < MAX_VERTICES; v++) {
        g->adj_list[v] = NULL;
    }
}

// 정점 삽입
void insert_vertex(GraphType* g, int v) {
    if (((g->n) + 1) > MAX_VERTICES) {
        fprintf(stderr, "그래프: 정점의 개수 초과\n");
        return;
    }
    g->n++;
}

// 간선 삽입 연산 (정점 u에 정점 v를 연결)
void insert_edge(GraphType* g, int u, int v) {
    // 새로운 노드를 담을 포인터 변수 선언 및 동적 할당
    GraphNode* node = (GraphNode*)malloc(sizeof(GraphNode));

    // 에러 처리 (할당 실패 시)
    if (node == NULL) {
        fprintf(stderr, "메모리 할당 에러\n");
        return;
    }

    // 새로운 노드에 데이터 넣기
    node->vertex = v;

    // 리스트의 맨 앞에 새로운 노드 끼워 넣기 (핵심 로직!)
    node->link = g->adj_list[u]; // 새로 만든 노드가 이전 헤드를 가리키도록.
    g->adj_list[u] = node; // 리스트의 헤드가 node를 가리키도록.
}

// 인접 리스트 출력 함수
void print_adj_list(GraphType* g) {
    for (int i = 0; i < g->n; i++) {
        GraphNode* p = g->adj_list[i];
        printf("정점 %d의 인접 리스트 ", i);
        while (p != NULL) {
            printf("-> %d ", p->vertex);
            p = p->link;
        }
        printf("\n");
    }
}

int main() {
    GraphType* g = (GraphType*)malloc(sizeof(GraphType));
    graph_init(g);

    for (int i = 0; i < 4; i++) {
        insert_vertex(g, i);
    }

    // 무방향 그래프이므로 양쪽 정점에 모두 간선을 추가해줍니다.
    insert_edge(g, 0, 1); insert_edge(g, 1, 0); // 0-1 연결
    insert_edge(g, 0, 2); insert_edge(g, 2, 0); // 0-2 연결
    insert_edge(g, 0, 3); insert_edge(g, 3, 0); // 0-3 연결

    print_adj_list(g);
    free(g);
    return 0;
}