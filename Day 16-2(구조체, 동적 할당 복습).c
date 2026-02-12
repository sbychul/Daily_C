#include <stdio.h>  // 1. printf, scanf를 쓰기 위한 표준 입출력 도구함
#include <stdlib.h> // 2. malloc, free를 쓰기 위한 도구함 (이거 없으면 동적 할당 못함!)

struct Item {       // 3. '아이템'이라는 새로운 자료형(설계도) 정의
    char name[20];  //    - 이름은 최대 20글자(한글 10자)까지
    int count;      //    - 개수는 정수로
};
// 핵심: struct Item은 아직 메모리를 차지하지 않습니다.
// 그냥 "앞으로 struct Item이라고 하면 저렇게 생긴 애인 줄 알아라"라고 컴퓨터에게 알려주는 설계도일 뿐입니다.

// [함수 정의]
// 4. 아이템 목록(배열의 시작 주소)과 개수(size)를 받아서 검사하는 함수
void check_farming_needed(struct Item* list, int size) {
// struct Item* list: 이 함수는 배열 전체를 복사해서 받는 게 아니라, **배열이 시작되는 주소(번지수)**만 받습니다.
// 그래서 list[i]라고 쓰면 그 주소에서 i번째 방을 찾아갈 수 있는 것이죠.

    // 5. 0번부터 size 직전까지 반복
    for (int i = 0; i < size; i++) {

        // 6. i번째 아이템의 count가 5보다 작은지 검사
        // list[i]는 "기준 주소에서 i칸만큼 이동한 곳의 내용물"을 의미
        if (list[i].count < 5) {

            // 7. 조건 맞으면 경고 출력. list[i].name 등으로 내부 데이터 접근
            printf("[경고] %s의 파밍이 시급합니다! (현재 %d개)\n", list[i].name, list[i].count);
        }
    }
}

// [본격적인 실행]
int main() {
    int n = 0, x = 0;

    // 8. 사용자에게 몇 칸 필요한지 물어봄
    printf("몇 종류의 아이템을 가지고 있나요?: ");
    scanf("%d", &n); // n이라는 변수의 주소(&)에 입력값을 넣음


    // 가장 중요한 부분: 동적 할달
    struct Item* inventory = (struct Item*)malloc(sizeof(struct Item)* n);
    // sizeof(struct Item)* n: "아이템 구조체 하나 크기(약 24바이트) × n개" 만큼의 땅 크기를 계산합니다.
    // malloc(...) : 운영체제에게 그 크기만큼 땅을 빌려달라고 요청합니다. 성공하면 시작 주소를 줍니다.
    // (struct Item*) : malloc이 준 주소를 "이건 아이템 구조체가 사는 곳이야"라고 명찰을 달아줍니다.
    // inventory : 이 포인터 변수는 이제 힙 영역에 만들어진 거대한 배열의 * *열쇠(시작 주소) * *를 쥐고 있습니다.


    // 10. 입력받은 n만큼 반복 (세미콜론 실수 주의했던 구간!)
    for (x = 0; x < n; x++) {
    // 현상: for 문 뒤에 세미콜론(;)이 붙어버리면, 컴퓨터는 "아, 반복할 내용이 없구나. 그냥 x 숫자만 세고 끝낼게." 라고 생각합니다.

        printf("%d번째 아이템 이름: ", x + 1); 
        scanf("%s", inventory[x].name); // inventory[x].name은 그 자체로 '배열의 이름(주소)'이므로 &를 안 붙임!
        printf("%d번째 아이템 개수: ", x + 1); 
        scanf("%d", &inventory[x].count); // inventory[x].count는 그냥 '숫자 값'이므로, 그 위치를 알려주기 위해 &를 붙임!
    }

    printf("\n[파밍 필요 목록]\n");

    // 11. 함수 호출
    // inventory 변수 안에는 이미 '시작 주소'가 들어있으므로, 그냥 inventory를 넘김.
    // (아까 &inventory라고 해서 틀렸던 부분!)
    check_farming_needed(inventory, n);
    // inventory는 이미 malloc으로 주소를 받은 **포인터(주소)**입니다.
    // 그런데 앞에 &를 붙이면 **"포인터 변수 자체의 주소(이중 포인터)"**를 넘기게 됩니다.

    // 12. 메모리 반납 (필수!)
    // 빌린 땅을 다 썼으니 운영체제에 돌려줌. 안 하면 메모리 누수 발생.
    free(inventory);

    return 0; // 프로그램 종료
}
