// 오늘의 핵심 요소 (Spec)
// FILE 포인터 : 파일을 다루기 위한 특별한 포인터 타입입니다. (FILE* fp;)
// fopen / fclose : 파일을 열고("w": 쓰기, "r" : 읽기) 반드시 닫아주어야 합니다. (메모리 해제만큼 중요!)
// fprintf / fgets : 파일에 내용을 쓰고, 파일로부터 내용을 한 줄씩 읽어옵니다.

#include <stdio.h>

int main() {
	FILE* fp = fopen("day58diary.txt", "w"); // 쓰기 모드로 파일을 열기

	// 파일이 존재하지 않거나 열리지 않을 때의 예외 처리
	if (fp == NULL) { printf("파일을 찾을 수 없습니다!"); return 1; }

	// 정상적으로 작동할 때
	printf("[C 간단 일기장]\n오늘의 소감을 한 줄로 남겨주세요: ");
	char str[100];
	fgets(str, sizeof(str), stdin); // 입력받아 str 변수에 저장.
	fprintf(fp, "%s", str); // 입력받은 내용을 파일에 작성
	printf("성공적으로 저장되었습니다.\n");

	fclose(fp); // 끄고
	fp = fopen("day58diary.txt", "r"); // 읽기 모드로 다시 열기

	// 파일이 존재하지 않거나 열리지 않을 때의 예외 처리 2
	if (fp == NULL) { printf("파일을 찾을 수 없습니다!"); return 1; }

	char buffer[100];
	printf("\n--- 파일을 다시 불러오는 중 ---\n불러온 내용: ");
	fgets(buffer, sizeof(buffer), fp);
	printf("%s", buffer); // fp(파일)에서 한 줄을 불러와 buffer에 저장 후 출력 (어차피 한 줄짜리임)

	fclose(fp); // 파일 닫아주기.
	return 0;
}