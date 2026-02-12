#include <stdio.h>

int main() {
    char writings[21] = {0};
    FILE* fp = fopen("note.txt", "w");
    if (fp == NULL) { printf("파일 열기 실패!"); return 1; }
    else {
        printf("파일에 저장할 내용을 입력하세요: ");
        scanf("%s", writings);
        fprintf(fp, writings); //이것도 잘 작동하지만, 만약 사용자가 입력한 문자열(writings) 안에 %d나 %s 같은 특수 기호가 포함되어 있다면
                                //컴퓨터가 오작동을 일으킬 수 있습니다.'(이것을 '포맷 스트링 버그'라고 합니다.)
                                //fprintf(fp, "%s", writings); 이렇게 하면 사용자가 %d를 입력해도 명령어가 아닌 그냥 글자로 인식해서 안전하게 저장됩니다.
        fclose(fp);
        printf("데이터가 note.txt에 성공적으로 저장되었습니다.");
    }
    return 0;
}
