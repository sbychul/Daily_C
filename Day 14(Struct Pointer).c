#include <stdio.h>

struct Character {
    char name[20];
    int level;
    float hp;
};

void level_up(struct Character* c) {
    printf("레벨업을 수행합니다...\n");
    c->level++;
    c->hp += 100;
}

int main() {
    struct Character player = {0};
    struct Character* ptr = &player;
    printf("[초기 상태 입력]\n이름: ");
    scanf("%s", player.name); // 문자열: 배열이기 때문에 주소를 찾아가라는 &가 필요하지 않음
    printf("레벨: ");
    scanf("%d", &player.level); // 일반 정수 변수, 실수 변수이기 때문에 &가 필요
    printf("체력: ");
    scanf("%f", &player.hp);

    level_up(&player); // 초반에 미리 ptr 포인터를 만들어 두었기 때문에 level_up(ptr); 라고 작성해도 됨
    printf("[레벨업 후 정보]\n이름: %s\n레벨: %d\n체력: %.2f", player.name, player.level, player.hp);
    
    return 0;
}