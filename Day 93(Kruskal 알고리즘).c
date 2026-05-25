#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100
#define MAX_EDGES 100

int parent[MAX_VERTICES]; // 각 정점의 루트를 저장하는 배열

// 1. Union-Find 초기화 (처음엔 모두 자기 자신이 루트)
void set_init(int n) {
    for (int i = 0; i < n; i++) parent[i] = -1;
}

// 2. 루트 찾기 (이 정점이 속한 그룹의 대장을 찾음)
int set_find(int curr) {
    if (parent[curr] == -1) return curr;
    while (parent[curr] != -1) curr = parent[curr];
    return curr;
}

// 3. 두 그룹 합치기 (a의 대장 밑으로 b의 대장을 편입)
void set_union(int a, int b) {
    int root1 = set_find(a);
    int root2 = set_find(b);
    if (root1 != root2) parent[root1] = root2;
}

// 간선 구조체
struct Edge {
    int start, end, weight;
};

// 그래프 구조체 (간선들의 목록만 가짐)
typedef struct GraphType {
    int v_count; // 정점 개수
    int e_count; // 간선 개수
    struct Edge edges[MAX_EDGES];
} GraphType;

// qsort를 위한 비교 함수 (가중치 오름차순)
int compare(const void* a, const void* b) {
    struct Edge* x = (struct Edge*)a;
    struct Edge* y = (struct Edge*)b;
    return (x->weight - y->weight);
}

// 🎯 크루스칼 최소 신장 트리 함수
void kruskal(GraphType* g) {
    int edge_accepted = 0; // 현재까지 선택된 간선의 수
    int uset, vset; // 정점 u와 v의 루트(대장) 번호
    struct Edge e;

    set_init(g->v_count); // Union-Find 초기화
    qsort(g->edges, g->e_count, sizeof(struct Edge), compare); // 간선 비용순 정렬

    printf("--- 크루스칼 알고리즘 쇼핑 시작 ---\n");

    int i = 0; // 정렬된 간선 배열의 인덱스
    // 트리 완성 조건: 간선의 수 == 정점의 수 - 1
    while (edge_accepted < (g->v_count - 1)) {
        e = g->edges[i]; // i번째로 싼 간선 꺼내기

        // 현재 간선의 시작점(e.start)과 끝점(e.end)이 속한 그룹의 대장(루트)을 각각 찾기
        uset = set_find(e.start);
        vset = set_find(e.end);

        // 두 그룹의 대장이 다르다면 (즉, 아직 연결 안 됨 = 사이클 안 생김)
        if (uset != vset) {
            printf("간선 (%d, %d) 선택 -> 비용: %d\n", e.start, e.end, e.weight);

            // 두 그룹을 하나로 합치기
            set_union(uset, vset);

            edge_accepted++; // 선택한 간선 개수 증가
        }
        i++; // 다음으로 싼 간선을 확인하기 위해 인덱스 증가
    }
}

int main() {
    // 정점 7개, 간선 9개짜리 그래프 (프림 때와 동일한 최소 신장 트리가 나옵니다)
    GraphType g = { 7, 9, {
        {0, 1, 29}, {1, 2, 16}, {2, 3, 12}, {3, 4, 22},
        {4, 5, 27}, {5, 0, 10}, {6, 1, 15}, {6, 3, 18}, {6, 4, 25}
    } };

    kruskal(&g);
    return 0;
}