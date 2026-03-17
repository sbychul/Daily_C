// 오늘의 핵심 요소 (Spec)
// 구조체 배열 : 여러 명의 데이터를 관리하기 위한 구조체 배열 활용.
// 파일 덤프(Dump) : 메모리에 있는 구조체 데이터를 그대로 텍스트 파일에 쓰고, 다시 불러오는 일련의 과정.
// 로직 분리 : 데이터를 저장하는 파트와 불러오는 파트를 논리적으로 구분하기.

#include <stdio.h>
#include <stdlib.h>
#define STUDENTS 2 // 상수 정의

typedef struct Score { // Score 구조체 정의
	char name[20];
	int kor;
	int eng;
} Score;

int main() {
	Score* scores = malloc(sizeof(Score) * STUDENTS); // 2명 분의 구조체 배열을 선언
	FILE* fp = fopen("day59scores.txt", "w"); // 쓰기 모드로 파일을 열기.
	if (fp == NULL) { printf("파일을 여는 과정에서 오류가 발생했습니다.\n"); return 1; } // 예외 처리

	printf("[성적 입력 및 파일 저장]\n");
	for (int i = 0; i < STUDENTS; i++) {
		printf("%d번째 학생 이름: ", i + 1);
		scanf("%s", scores[i].name); // 이름 입력
		printf("국어 점수: ");
		scanf("%d", &scores[i].kor); // 국어 입력
		printf("영어 점수: ");
		scanf("%d", &scores[i].eng); // 영어 입력

		fprintf(fp, "%s %d %d\n", scores[i].name, scores[i].kor, scores[i].eng); // 파일에 입력받은 정보 저장
	}
	printf("\n성적이 성공적으로 저장되었습니다.\n");

	fclose(fp); // 껐다 다시 키기
	fp = fopen("day59scores.txt", "r"); // 읽기
	if (fp == NULL) { printf("파일을 다시 여는 과정에서 오류가 발생했습니다.\n"); return 1; } // 예외 처리

	printf("\n[파일에서 데이터 불러오기]\n");
	Score temp;
	while (fscanf(fp, "%s %d %d", temp.name, &temp.kor, &temp.eng) != EOF) { // End Of File(끝까지) 불러와서 정보를 임시 구조체 변수에 담아 출력
		printf("- 이름: %s (국어: %d / 영어: %d)\n", temp.name, temp.kor, temp.eng);
	}

	free(scores);	// 동적 할당 해제
	fclose(fp);		// 파일 닫기
	return 0;		// 프로그램 종료
}