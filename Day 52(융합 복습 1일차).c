#include <stdio.h>

// 1. 오늘의 핵심 요소 (Spec)
// 구조체(struct) : 연관 있는 데이터(이름, 점수)를 하나로 묶기.
// 배열(Array) : 동일한 구조체 데이터를 여러 개 관리하기.
// 함수(Function) : 특정 기능을 독립된 블록으로 분리하여 가독성 높이기.

#define STUDENTS_COUNT 3

struct Student { // Student 구조체 정의
	char name[20];
	int score;
};

void printStudent(struct Student s) { // 학생 정보를 출력하는 함수
	printf("이름: %s / 점수: %d점\n", s.name, s.score);
}

int main() {
	struct Student myClass[STUDENTS_COUNT] = { 0 }; // 학생 3명의 이름과 점수를 입력받을 구조체 배열
	float scoreSum = 0; // 평균 점수를 계산할 때 사용할 변수.

	printf("[학생 정보 입력]\n");
	for (int i = 0; i < STUDENTS_COUNT; i++) { // 학생 3명의 이름과 점수를 입력받아 저장하기
		printf("%d번째 학생 이름: ", i + 1);
		scanf("%s", myClass[i].name); // 이름은 그 자체로 주소. &를 붙일 필요 없음.
		printf("%d번째 학생 점수: ", i + 1);
		scanf("%d", &myClass[i].score); // 정수 값은 &가 필요함.
		scoreSum += myClass[i].score; // 입력받는 즉시 합계에 더함.
	}

	printf("\n[성적표 출력]\n");
	for (int i = 0; i < STUDENTS_COUNT; i++) { // 함수를 호출하여 각 학생의 이름과 점수를 출력.
		printStudent(myClass[i]);
	}

	float scoreAvg = scoreSum / STUDENTS_COUNT; // 평균 계산, 애초에 합계가 float이기 때문에, 따로 캐스팅 필요 없음.
	printf("\n------------------\n전체 평균 점수: %.1f점\n", scoreAvg);
	if (scoreAvg >= 90) {
		printf("우수 학급입니다!\n");
	}
	return 0;
}