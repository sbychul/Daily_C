#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50

typedef struct GraphNode {
    int vertex;
    struct GraphNode* link;
} GraphNode;

typedef struct GraphType {
    int n;
    GraphNode* adj_list[MAX_VERTICES];
} GraphType;

int visited[MAX_VERTICES]; // 방문 여부를 기록할 전역 배열 (0: 미방문, 1: 방문)

// 그래프 초기화 및 간선 삽입 로직
void graph_init(GraphType* g) {
    g->n = 0;
    for (int v = 0; v < MAX_VERTICES; v++) g->adj_list[v] = NULL;
}

void insert_vertex(GraphType* g, int v) {
    g->n++;
}

void insert_edge(GraphType* g, int u, int v) {
    GraphNode* node = (GraphNode*)malloc(sizeof(GraphNode));
    node->vertex = v;
    node->link = g->adj_list[u];
    g->adj_list[u] = node;
}

// 🎯 깊이 우선 탐색 (DFS) 함수
void dfs(GraphType* g, int v) {
    GraphNode* w;

    // 현재 정점 v를 방문했으므로 visited 배열에 표시하고 정점 번호를 출력.
    visited[v] = 1; // 1이라고 함으로서 방문 체크
    printf("%d -> ", v); // 정점 번호의 출력


    // 현재 정점 v의 인접 리스트를 처음부터 끝까지 순회.
    // g->adj_list[v]가 리스트의 첫 번째 노드이고, 다음 노드는 w->link로 이동.
    for (w = g->adj_list[v]; w != NULL; w = w->link) {

        // 인접 정점(w->vertex)을 아직 방문하지 않았다면, 재귀적으로 dfs를 호출.
        if (!visited[w->vertex]) dfs(g, w->vertex);

    }
}

int main() {
    GraphType g;
    graph_init(&g);

    for (int i = 0; i < 5; i++) insert_vertex(&g, i);

    // 그래프 간선 연결 (무방향 그래프 구조를 위해 양방향으로 매핑)
    insert_edge(&g, 0, 2); insert_edge(&g, 2, 0);
    insert_edge(&g, 0, 1); insert_edge(&g, 1, 0);
    insert_edge(&g, 1, 4); insert_edge(&g, 4, 1);
    insert_edge(&g, 1, 3); insert_edge(&g, 3, 1);
    insert_edge(&g, 2, 4); insert_edge(&g, 4, 2);
    insert_edge(&g, 3, 4); insert_edge(&g, 4, 3);

    printf("깊이 우선 탐색(DFS) 방문 순서: ");
    dfs(&g, 0); // 0번 정점에서 탐색 시작
    printf("\n");

    return 0;
}