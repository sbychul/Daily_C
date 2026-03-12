#include <stdio.h>
#include <stdlib.h>

struct Student { // Student 구조체 정의
	char name[20];
	int id;
};

int main() {
	int students = 0;
	printf("등록할 학생 수는 몇 명인가요? : ");
	scanf("%d", &students);

	struct Student* myClass = (struct Student*)malloc(sizeof(struct Student) * students);
	if (myClass == NULL) { // 할당에 성공했는지 확인, 실패했다면 return 1을 뱉으며 종료.
		printf("학생을 입력할 공간 메모리 할당에 실패했습니다.");
		return 1;
	}

	for (int i = 0; i < students; i++) {
		printf("%d번째 학생 이름: ", i + 1);
		scanf("%s", myClass[i].name);
		printf("%d번째 학생 학번: ", i + 1);
		scanf("%d", &myClass[i].id);
	}

	printf("\n[등록된 수강생 명단]\n");

	for (int i = 0; i < students; i++) {
		printf("- 이름: %s (학번: %d)\n", myClass[i].name, myClass[i].id);
	}

	free(myClass); // 메모리 할당 해제
	myClass = NULL; // 확실하게 빈 껍데기로 만들어주기. Dangling Pointer 예방.
	return 0;
}

// 알고 있으면 좋은 점 (typedef의 마법): 매번 struct Student라고 길게 치기 귀찮으실 겁니다.
// 구조체를 정의할 때 typedef struct { char name[20]; int id; } Student; 라고 선언해 두면,
// 앞으로는 int나 float처럼 그냥 Student라는 단어 하나로 깔끔하게 사용할 수 있습니다!