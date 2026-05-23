#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 10
#define INF 1000000    /* 무한대 값 (연결이 없음을 의미) */

typedef struct GraphType {
    int n; /* 정점의 개수 */
    int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int distance[MAX_VERTICES]; /* 시작점으로부터의 최단경로 거리 */
int found[MAX_VERTICES];    /* 방문 확정 여부 */

// 아직 확정되지 않은 정점들 중 distance가 가장 작은 정점의 인덱스를 반환
int choose(int distance[], int n, int found[]) {
    int i, min, minpos;
    min = INT_MAX;
    minpos = -1;
    for (i = 0; i < n; i++) {
        if (distance[i] < min && !found[i]) {
            min = distance[i];
            minpos = i;
        }
    }
    return minpos;
}

// 🎯 다익스트라 최단 경로 함수
void shortest_path(GraphType* g, int start) {
    int i, u, v;

    // 1. 초기화 단계
    for (i = 0; i < g->n; i++) {
        distance[i] = g->weight[start][i];
        found[i] = FALSE;
    }
    found[start] = TRUE; // 시작 정점 방문 표시
    distance[start] = 0;

    // 2. 메인 루프: n-1개의 정점을 확정해 나갑니다.
    for (i = 0; i < g->n - 1; i++) {
        // choose 함수를 호출하여 현재 가장 가까운 정점을 찾아 u에 저장
        u = choose(distance, g->n, found);

        found[u] = TRUE; // 해당 정점 방문 표시

        // 3. 정점 u를 거쳐서 v로 가는 것이 더 빠른지 계산하여 distance 배열 갱신
        for (v = 0; v < g->n; v++) {
            if (!found[v] && g->weight[u][v] != INF) {
                // u를 거쳐서 v로 가는 비용이 기존 distance[v]보다 작다면 갱신
                if (distance[v] > g->weight[u][v] + distance[u]) {
                    distance[v] = distance[u] + g->weight[u][v];
                }
            }
        }
    }
}

int main() {
    GraphType g = { 5, {
        { 0,   7,   INF, INF, 3 },
        { 7,   0,   4,   1,   2 },
        { INF, 4,   0,   2,   INF },
        { INF, 1,   2,   0,   1 },
        { 3,   2,   INF, 1,   0 } }
    };

    shortest_path(&g, 0); // 0번 정점에서 출발

    printf("0번 정점으로부터의 최단 거리:\n");
    for (int i = 0; i < g.n; i++) {
        if (distance[i] == INF) printf("정점 %d: INF\n", i);
        else printf("정점 %d: %d\n", i, distance[i]);
    }
    return 0;
}