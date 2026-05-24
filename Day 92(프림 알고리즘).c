#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 10
#define INF 1000000

typedef struct GraphType {
    int n;
    int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int distance[MAX_VERTICES]; /* 트리 연합군에서 해당 정점까지 가기 위한 최소 간선 비용 */
int selected[MAX_VERTICES]; /* 트리 연합군에 포함되었는지 여부 (다익스트라의 found) */

// 아직 선택되지 않은 정점들 중 최소 간선 비용을 가진 정점 선택
int get_min_vertex(int n) {
    int v, minv = -1, min = INF;
    for (v = 0; v < n; v++) {
        if (!selected[v] && distance[v] < min) {
            min = distance[v];
            minv = v;
        }
    }
    return minv;
}

// 🎯 프림(Prim) 최소 신장 트리 함수
void prim(GraphType* g, int start) {
    int i, u, v;

    // 1. 초기화 단계
    for (u = 0; u < g->n; u++) {
        distance[u] = INF;
        selected[u] = FALSE;
    }
    distance[start] = 0; // 시작 정점의 진입 비용은 0

    // n개의 정점을 모두 트리 연합군에 포함
    for (i = 0; i < g->n; i++) {
        u = get_min_vertex(g->n);
        selected[u] = TRUE; // 정점 u를 트리 연합군에 포함

        if (distance[u] == INF) return; // 그래프가 끊겨있는 경우 종료
        printf("정점 %d 추가 (비용: %d)\n", u, distance[u]);

        // 정점 u가 들어옴으로써, 다른 정점 v로 가는 단일 간선 비용이 더 저렴해졌는지 갱신
        for (v = 0; v < g->n; v++) {
            if (g->weight[u][v] != INF && !selected[v]) {
                // 이미 알고 있던 v까지의 비용보다, 정점 u를 거쳐서 v로 가는 다리를 놓는 비용이 더 저렴한지 확인
                // 저렴하다면 새로 찾아낸 weight값으로 distance 배열을 갱신
                if (g->weight[u][v] <= distance[v]) {
                    distance[v] = g->weight[u][v];
                }
            }
        }
    }
}

int main() {
    GraphType g = { 7, {
        { 0,   29,  INF, INF, INF, 10,  INF },
        { 29,  0,   16,  INF, INF, INF, 15 },
        { INF, 16,  0,   12,  INF, INF, INF },
        { INF, INF, 12,  0,   22,  INF, 18 },
        { INF, INF, INF, 22,  0,   27,  25 },
        { 10,  INF, INF, INF, 27,  0,   INF },
        { INF, 15,  INF, 18,  25,  INF, 0 } }
    };

    printf("--- 프림 알고리즘 최소 신장 트리 빌드 시작 ---\n");
    prim(&g, 0); // 0번 정점에서 출발

    return 0;
}