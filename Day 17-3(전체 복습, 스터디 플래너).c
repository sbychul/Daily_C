#include <stdio.h>
#include <stdlib.h>

struct Plan {
	char name[30];
	int hours;
};

int main() {
	int subs = 0;
	printf("[계획표 작성]");

	while (1) { // 과목 수 입력
		printf("\n내일 공부할 과목 수는?: ");

		if (scanf("%d", &subs) == 0) { // 문자열이 들어갔을 때 대비
			printf("숫자를 쓰세요.\n");
			while (getchar() != '\n');
			continue;
		}

		if (subs <= 0) { // 예외 처리
			printf("공부를 안 하겠다니... 기각.\n");
		}
		else if (subs >= 100) { // 99개까지는 뭐... 파이팅 하라는 느낌
			printf("공부가 장난이야? 기각.\n");
		}
		else { break; }
	}
	
	struct Plan* schedule = (struct Plan*)malloc(sizeof(struct Plan) * subs); // 동적 할당, 구조체의 크기만큼의 방을 넘김
	printf("\n[상세 계획 작성]\n");
	int i = 0; // 밑에서도 i를 활용하기 때문에 위에 선언

	for (i = 0; i < subs; i++) { // 과목명과 시간을 입력받을 반복문
		printf("%d번째 과목 이름: ", i + 1);
		scanf("%s", schedule[i].name); // 배열이기 때문에 & 필요 없음

		while (1) { // 시간 입력받는 반복문. 왜 반복인지는 밑에 참조
			printf("%d번째 과목 공부 시간: ", i + 1);
			if (scanf("%d", &schedule[i].hours) == 0) { // 숫자이기 때문에 & 필요
				printf("숫자를 쓰세요.\n");
				while (getchar() != '\n'); // 여기서도 숫자 안 쓸 수 있으니까
				continue;
			}
			
			if (schedule[i].hours <= 0 || schedule[i].hours >= 24) { // 예외 처리
				printf("공부가 장난이야? 다시.\n");
			}

			else { break; } // 제대로 썼으면 반복문 탈출. 과목명 및 시간 입력 완료
		}
	}

	FILE* fp = fopen("day17_plan.txt", "w"); // 파일 저장 빌드업
	if (fp == NULL) { printf("파일 열기 실패!"); return 1; } // 파일 못 열었을 때 대비

	fprintf(fp, "%d\n", subs); // 파일에 과목 갯수 입력
	for (i = 0; i < subs; i++) { // 과목명과 시간 입력
		fprintf(fp, "%s %d\n", schedule[i].name, schedule[i].hours);
	}

	free(schedule); // 파일에 입력하였으니 더 이상 필요 없음, 메모리 반납
	fclose(fp); // 파일을 잘 닫아줍시다. 고마워요 제미나이
	printf("\n... 파일 저장 완료! ...\n\n[저장된 파일 불러오기]\n== 내일의 계획 ==\n");

	struct Plan temp; // 임시 변수 사용
	FILE* fp2 = fopen("day17_plan.txt", "r"); // 읽기 모드로 변환, 못 열었을 때 대비는 생략(위에서 했으니까 비효율적)
	// 새로운 변수 fp를 창조해라!" (선언) → 한 구역({}) 안에서 한 번만 가능. fp라고 작성하면 이미 정의된 걸 또 하려 한다는 (재정의) C2374오류로 실행 안 됨.
	// 두 번째 혹은 그 이후 같은 변수로 열 때는 FILE* 을 안 붙이고 하면 된다. fp = fopen("day17_plan.txt", "r")
	fscanf(fp2, "%d", &subs);
	
	for (i = 0; i < subs; i++) { // 임시 변수 활용, 바로 입력받고 바로 출력.
		fscanf(fp2, "%s %d", temp.name, &temp.hours);
		printf("%d. %s (%d시간)\n", i + 1, temp.name, temp.hours);
	}
	printf("\n총 %d개의 계획을 확인했습니다.\n", subs);
	fclose(fp2); // 파일을 열심히 닫도록 합시다.
	return 0; // 프로그램 종료
}