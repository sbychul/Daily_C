#include <stdio.h>
#include <stdlib.h>

#define MAX_LIST_SIZE 100 // 리스트의 최대크기 [cite: 47]

// 오늘의 핵심 문법 & 로직 (데이터 밀고 당기기)
// 배열의 중간에 데이터를 끼워 넣거나 빼려면 대공사가 필요합니다.

// 삽입(Insert) : 새로운 사람이 중간에 줄을 서려면, 그 자리부터 뒤에 있는 사람들이 전부 뒤로 한 칸씩 이동해서 빈자리를 만들어 주어야 합니다.
// (반복문을 뒤에서부터 앞으로 돌려야 데이터를 덮어쓰지 않습니다!)

// 삭제(Delete) : 중간에 있던 사람이 줄에서 빠져나가면, 빈 공간을 채우기 위해 뒤에 있는 사람들이 전부 앞으로 한 칸씩 당겨져 와야 합니다.
// (반복문을 앞에서부터 뒤로 돌립니다.)

typedef int element;

typedef struct {
	element array[MAX_LIST_SIZE]; // 배열 정의 
	int size; // 현재 리스트에 저장된 항목들의 개수 
} ArrayListType;

// 리스트 초기화 함수
void init(ArrayListType* L) {
	L->size = 0;
}

// 리스트가 가득 차 있으면 1, 아니면 0 반환
int is_full(ArrayListType* L) {
	return L->size == MAX_LIST_SIZE;
}

// 리스트가 비어 있으면 1, 아니면 0 반환
int is_empty(ArrayListType* L) {
	return L->size == 0;
}

// 리스트 출력
void print_list(ArrayListType* L) {
	for (int i = 0; i < L->size; i++)
		printf("%d->", L->array[i]);
		printf("NULL\n");
}

// 🚀 [미션 1] 지정된 위치(pos)에 데이터 삽입하기
void insert(ArrayListType* L, int pos, element item) {
	if (!is_full(L) && (pos >= 0) && (pos <= L->size)) {
		// TODO: 삽입할 자리(pos)를 만들기 위해 뒤에서부터 데이터를 한 칸씩 뒤로 미는 for문을 작성하세요.
		// 힌트: 시작 인덱스는 L->size - 1 이고, 목적지는 pos 입니다.
		for (int i = (L->size - 1); i >= pos; i--) {
			L->array[i + 1] = L->array[i];
		}
		L->array[pos] = item;
		L->size++; // 개수 1 증가
	}
}

// 🚀 [미션 2] 지정된 위치(pos)의 데이터 삭제하기
element delete(ArrayListType* L, int pos) {
	element item;
		if (pos < 0 || pos >= L->size) {
			printf("위치 오류\n"); return -1;
		}
	item = L->array[pos]; // 삭제할 데이터 백업

	// TODO: 삭제된 빈자리를 채우기 위해 뒤의 데이터를 앞으로 한 칸씩 당기는 for문을 작성하세요.
	// 힌트: 시작 인덱스는 pos 이고, 목적지는 L->size - 1 의 앞까지 입니다.
	for (int i = pos; i < (L->size - 1); i++) {
		L->array[i] = L->array[i + 1];
	}

	L->size--; // 개수 1 감소
	return item;
}

int main(void) {
	ArrayListType list;
	init(&list);

	insert(&list, 0, 10); print_list(&list); // 0번째에 10 추가
	insert(&list, 0, 20); print_list(&list); // 0번째에 20 추가
	insert(&list, 0, 30); print_list(&list); // 0번째에 30 추가
	insert(&list, 1, 99); print_list(&list); // 1번째(가운데)에 99 새치기!

	delete(&list, 0); print_list(&list);     // 맨 앞(0번째) 삭제
	return 0;
}