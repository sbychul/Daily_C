#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 오늘의 핵심 요소 (Spec)
// 포인터 멤버 구조체 : 구조체 안에 문자열 배열(char name[20]) 대신 문자열 포인터(char* title)를 두어, 제목 길이에 딱 맞는 메모리만 할당하기.
// 이중 메모리 할당 : 구조체 배열을 위한 malloc과, 각 구조체 내부의 문자열을 위한 malloc을 중첩해서 사용하기.
// 순차적 메모리 해제 : 할당한 순서의 역순으로 꼼꼼하게 free 호출하기.

typedef struct { char* title; int price; } Book; // Book 구조체 정의

int main() {
	int howManyBooks = 0;
	printf("등록할 도서는 몇 권인가요? : ");
	scanf("%d", &howManyBooks);

	Book* bookShelf = (Book*)malloc(sizeof(Book) * howManyBooks); // 책 수만큼 동적 할당
	for (int i = 0; i < howManyBooks; i++) {
		char temp[100] = { 0 }; // 책 제목을 입력받을 임시 배열
		printf("%d번째 도서 제목: ", i + 1);
		scanf("%s", temp);

		bookShelf[i].title = malloc(sizeof(strlen(temp) + 1)); // 문자열의 끝에 있는 \0의 크기까지 계산해서 동적 할당.
		// [리뷰어] 🚨 앗! 바로 여기에 아주 치명적이고 재미있는 함정이 숨어있습니다.
		// strlen(temp)는 이미 문자열의 '길이(숫자)'를 반환합니다. 만약 "Python"을 쳐서 길이가 6이 나왔다면, 6 + 1 = 7이 되죠.
		// 그런데 여기에 sizeof(7)을 씌워버리면? 컴퓨터는 7이라는 숫자의 형태인 '정수(int)'의 크기를 계산해서 '4(바이트)'를 반환합니다.
		// 즉, 글자가 아무리 길어도 이 코드는 무조건 '4바이트'만 할당해 버립니다! 
		// 올바른 코드는 sizeof(char) * (strlen(temp) + 1) 로 쓰시거나, char는 어차피 1바이트이므로 그냥 malloc(strlen(temp) + 1); 로 쓰셔야 합니다.

		strcpy(bookShelf[i].title, temp); // strcpy((복사받을 문자열), (복사할 문자열));
		printf("%d번째 도서 가격: ", i + 1);
		scanf("%d", &bookShelf[i].price);
	}

	printf("\n[도서 정보 목록]\n");
	for (int i = 0; i < howManyBooks; i++) {
		printf("- 제목: %s (가격: %d원)\n", bookShelf[i].title, bookShelf[i].price);
	}

	for (int i = 0; i < howManyBooks; i++) {
		free(bookShelf[i].title); // 먼저 title 부분의 할당을 해제하기.
	}
	free(bookShelf); // 이후 구조체 배열의 메모리 할당을 해제.

	return 0;
}