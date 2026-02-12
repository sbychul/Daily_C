#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	int target = 0, input_num = 0, retry = 100, trials = 0, corrects = 0, fails = 0;
	double time_sum = 0, time_avg = 0;
	srand(time(NULL));
	printf("[수강 신청 연습]\n!누구보다 빠르게 4자리 숫자를 입력하기!\n준비되었다면 0을 입력해 주세요: ");
	scanf("%d", &retry);

	if (retry == 0) {
		while (1) {
			trials++;
			target = rand() % 9000 + 1000;
			printf("\n입력해야 할 번호: %d\n입력 칸: ", target);
			clock_t start, end;

			start = clock();
			scanf("%d", &input_num);
			while (getchar() != '\n');
			end = clock();
			double time = (double)(end - start) / CLOCKS_PER_SEC;
			time_sum += time;

			if (input_num == target) {
				printf("\n번호 일치! %.1f초가 소요되었습니다.\n", time);
				corrects++;
			}
			else {
				printf("\n번호 불일치.. %.1f초가 소요되었습니다.. 하지만 틀렸다면 시간이 의미가 없지..\n", time);
				fails++;
			}

			printf("\n다시 시도하시겠습니까? (Y: 0/N: 아무 숫자 입력): ");
			scanf("%d", &retry);

			if (retry != 0) {
				break;
			}
		}
		time_avg = time_sum / trials;
		printf("\n총 시도 횟수: %d회\n정답: %d회 / 오답: %d회\n평균 소요 시간: %.1f초\n\n고생했다. 파이팅.\n", trials, corrects, fails, time_avg);
		return 0;
	}
	else {
		printf("\n너는 아직 준비가 안 됐다.\n");
		return 1;
	}
}