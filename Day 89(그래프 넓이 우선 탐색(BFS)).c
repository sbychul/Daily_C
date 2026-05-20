#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50
#define MAX_QUEUE_SIZE 100

// --- 그래프 관련 구조체 및 함수 (어제와 동일) ---
typedef struct GraphNode {
    int vertex;
    struct GraphNode* link;
} GraphNode;

typedef struct GraphType {
    int n;
    GraphNode* adj_list[MAX_VERTICES];
} GraphType;

int visited[MAX_VERTICES];

// --- 큐(Queue) 관련 구현 (BFS 전용 원형 큐) ---
typedef int element;
typedef struct {
    element queue[MAX_QUEUE_SIZE];
    int front, rear;
} QueueType;

void queue_init(QueueType* q) { q->front = q->rear = 0; }
int is_empty(QueueType* q) { return (q->front == q->rear); }
void enqueue(QueueType* q, element item) { q->rear = (q->rear + 1) % MAX_QUEUE_SIZE; q->queue[q->rear] = item; }
element dequeue(QueueType* q) { q->front = (q->front + 1) % MAX_QUEUE_SIZE; return q->queue[q->front]; }

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

// 🎯 너비 우선 탐색 (BFS) 함수
void bfs(GraphType* g, int v) {
    GraphNode* w;
    QueueType q;
    queue_init(&q); // 큐 초기화

    // 1. 시작 정점 v를 방문 처리하고, 큐에 삽입(enqueue)하세요.
    visited[v] = 1;
    enqueue(&q, v);

    // 2. 큐가 비어있지 않은 동안 반복합니다.
    while (!is_empty(&q)) {
        // 3. 큐에서 정점을 하나 꺼내어(dequeue) v에 저장하고 화면에 출력하세요.
        v = dequeue(&q);
        printf("%d -> ", v);


        // 4. 꺼낸 정점 v의 인접 리스트를 돌며 방문하지 않은 이웃을 찾습니다.
        for (w = g->adj_list[v]; w != NULL; w = w->link) {

            // 5. 인접 정점(w->vertex)이 아직 방문되지 않았다면?
            // 방문 표시를 '먼저' 하고 큐에 집어넣으세요! (DFS와 가장 큰 차이점)
            if (!visited[w->vertex]) {
                visited[w->vertex] = 1;
                enqueue(&q, w->vertex);
            }
        }
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
    bfs(&g, 0); // 0번 정점에서 탐색 시작
    printf("\n");

    return 0;
}