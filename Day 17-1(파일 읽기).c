#include <stdio.h>

int main() {
	char buffer[100];

	// [파일 열기]
	// note.txt 파일과 프로그램 사이에 '연결 통로(Stream)'를 만듭니다.
	// fp는 파일 내용 자체가 아니라, 그 통로를 제어하는 '리모컨(구조체의 주소)'입니다.
	// "r" : 읽기 전용(Read) 모드
	FILE* fp = fopen("note.txt", "r");

	if (fp == NULL) { printf("파일을 찾을 수 없습니다."); return 1; }
	else {
		// fp(리모컨)가 가리키는 파일 위치에서 단어를 읽어와(Scan), 
		// buffer(변수)라는 그릇에 담는다(Save).
		fscanf(fp, "%s", buffer); // 100글자가 넘으면 크기를 넘어버려서 프로그램이 뻗음
		// fscanf(fp, "%99s", buffer); 라고 제한을 걸어줄 수 있음 (마지막 1칸은 /0 자리라 99s)

		printf("파일에서 읽어온 내용: %s\n", buffer);
		fclose(fp);
		printf("파일을 성공적으로 읽고 닫았습니다.");
		return 0;
	}
}
