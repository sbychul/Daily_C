#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000 /* 연결이 없는 경우 무한대 */

typedef struct GraphType {
    int n; /* 정점의 개수 */
    int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int A[MAX_VERTICES][MAX_VERTICES]; /* 최단 거리 지도를 기록할 2차원 배열 */

// 출력 함수
void print_matrix(GraphType* g) {
    for (int i = 0; i < g->n; i++) {
        for (int j = 0; j < g->n; j++) {
            if (A[i][j] == INF) printf(" INF ");
            else printf("%4d ", A[i][j]);
        }
        printf("\n");
    }
    printf("------------------------\n");
}

// 🎯 플로이드 최단 경로 알고리즘 함수
void floyd(GraphType* g) {
    int i, j, k;

    // 1. 초기 상태 구축: 그래프의 기본 가중치로 지도(A)를 채웁니다.
    for (i = 0; i < g->n; i++) {
        for (j = 0; j < g->n; j++) {
            A[i][j] = g->weight[i][j];
        }
    }

    // 2. 3중 for문을 돌며 거쳐가는 정점(k)을 기준으로 지도를 갱신합니다.
    for (k = 0; k < g->n; k++) { // 거쳐가는 정점
        for (i = 0; i < g->n; i++) { // 시작 정점
            for (j = 0; j < g->n; j++) { // 목적지 정점

                // 그냥 가는 것보다 k를 거쳐 가는 것이 빠르다면 갱신
                if (A[i][j] > A[i][k] + A[k][j]) {
                    A[i][j] = A[i][k] + A[k][j];
                }

            }
        }
    }
}

int main() {
    // 정점 5개짜리 가중치 그래프
    GraphType g = { 5, {
        { 0,   7,   INF, INF, 3 },
        { 7,   0,   4,   1,   2 },
        { INF, 4,   0,   2,   INF },
        { INF, 1,   2,   0,   1 },
        { 3,   2,   INF, 1,   0 } }
    };

    floyd(&g);
    printf("--- 모든 정점 간의 최종 최단 경로 지도 ---\n");
    print_matrix(&g);

    return 0;
}