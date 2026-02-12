#include <stdio.h>

int main() {
	char buffer[200];

	FILE* fp = fopen("day18_diary.txt", "r");
	if (fp == NULL) { printf("파일을 찾을 수 없습니다."); return 1; }

	else {
		printf("=== 나의 일기장 ===\n");
		while (fgets(buffer, sizeof(buffer), fp) != NULL) { // 메모장이 끝날 때까지 buffer에 한 문장씩(\n을 만날 때까지) 읽어 넣어라 라는 뜻
			printf("%s", buffer); // fgets는 줄바꿈까지 읽기 때문에 \n을 넣으면 엔터가 두 번 돼서 출력됨.
		}
		fclose(fp);
		printf("\n===================\n파일을 모두 읽었습니다.");
		return 0;
	}
}