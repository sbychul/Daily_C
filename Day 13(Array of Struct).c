#include <stdio.h>
#define PARTY_MEMBERS 3

struct Character {
    char name[20];
    int level;
};

int main() {
    struct Character party[PARTY_MEMBERS] = {0};
    int loops = 0;
    printf("[파티원 정보 입력]\n");
    for (; loops < PARTY_MEMBERS; loops++) {    // 최신 C언어에서는 for 문 안에서 바로 선언하는 것을 선호, for (int loops = 0; ...)
        printf("%d번 캐릭터 이름: ", loops + 1);
        scanf("%s", party[loops].name);
        printf("%d번 캐릭터 레벨: ", loops + 1);
        scanf("%d", &party[loops].level);
    }
    printf("\n[파티 명단]\n");
    for (loops = 0; loops < PARTY_MEMBERS; loops++) {   // for문 내부에서 변수를 선언했을 때는 위에서 썼던 거여도 새로 선언해 줘야 함. 여기도 for int loops = 0; ...
        printf("%d. 이름: %s (Lv. %d)\n", loops + 1, party[loops].name, party[loops].level);
    }
    return 0;
}