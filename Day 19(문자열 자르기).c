#include <stdio.h>
#include <string.h>

int main() {
	char name[100];
	printf("이름을 입력하세요: ");
	fgets(name, sizeof(name), stdin);
	// C언어에서는 "키보드도 파일", 'stdin(Standard Input)'이라는 이름의 특수한 파일 취급
	// 열려있는 파일 = 키보드에서 읽어오라는 뜻
	
	int len = strlen(name);
	if (len > 0 && name[len - 1] == '\n') { // name[len - 1] == \n인 상태, 그대로 출력하면 줄바꿈이 됨
		name[len - 1] = '\0'; // 엔터 문자를 문자열 끝 문자로 교체, 출력 시 줄바꿈이 일어나지 않게 함
	}
	// if (len > 0 && ...) 가 필요한 이유: len이 0이면, len - 1은 -1.
	// name[-1]... ?! 배열의 - 1번지는 존재하지 않는 위험 구역.
	// 이 곳을 건드리면 프로그램이 "치명적인 오류"를 뿜으며 사망. (Segmentation Fault)

	printf("입력하신 이름: %s님, 반갑습니다!", name);
	return 0;
}