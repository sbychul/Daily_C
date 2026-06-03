#include <stdio.h>
#include <stdlib.h>

#define KEY_SIZE 10
#define TABLE_SIZE 7 // 해시 테이블의 크기 (보통 소수를 사용)

// 해시 테이블의 각 칸(버킷) 구조체
typedef struct {
    int key;
} element;

element hash_table[TABLE_SIZE]; // 해시 테이블 배열

// 해시 테이블 초기화 (모든 칸을 빈 상태인 0으로 설정)
void init_table() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hash_table[i].key = 0;
    }
}

// 🎯 해시 함수: 나눗셈법
int hash_function(int key) {
    return key % TABLE_SIZE;
}

// 🎯 선형 조사법을 이용한 해시 삽입 함수
void hash_lp_add(element item) {
    int i, hash_value;
    hash_value = i = hash_function(item.key); // 시작 주소 계산

    // 해당 버킷이 비어있지 않고(hash_table[i].key != 0), 중복된 키가 아닐 동안 루프 돌기
    while (hash_table[i].key != 0) {
        if (hash_table[i].key == item.key) { // 키가 중복된다면 함수 끝내버림.
            printf("중복된 키 삽입 불가\n");
            return;
        }

        // 다음 버킷을 조사. 나머지 연산을 통하여 배열의 최대 크기를 넘지 않도록 함.
        i = (i + 1) % TABLE_SIZE;

        // 한 바퀴를 다 돌아서 다시 원래 시작 주소로 왔다면 테이블이 꽉 찬 것.
        if (i == hash_value) {
            printf("해시 테이블이 가득 찼습니다.\n");
            return;
        }
    }

    // 빈 버킷을 찾았으므로 데이터 삽입
    hash_table[i] = item;
}

// 해시 테이블 상태 출력 함수
void print_table() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("[%d]: %d\n", i, hash_table[i].key);
    }
}

int main() {
    element items[] = { {8}, {1}, {9}, {6}, {13} };
    int n = sizeof(items) / sizeof(items[0]);

    init_table();

    printf("--- 해시 테이블 삽입 시작 ---\n");
    for (int i = 0; i < n; i++) {
        printf("키 %d 삽입\n", items[i].key);
        hash_lp_add(items[i]);
    }

    printf("\n--- 최종 해시 테이블 상태 ---\n");
    print_table();

    return 0;
}