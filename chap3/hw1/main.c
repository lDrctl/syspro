#include <stdio.h>
#include <string.h>
#include "copy.h"

#define MAXLINE 1000

int main() {
    char lines[5][MAXLINE];
    char temp[MAXLINE];
    int i = 0, j = 0;

    // 1. while문을 이용하여 5개의 문장 입력받기
    while (i < 5 && gets(lines[i]) != NULL) {
        i++;
    }

    // 2. 문자열 길이가 긴 순서대로 정렬 (내림차순 버블 정렬)
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4 - i; j++) {
            if (strlen(lines[j]) < strlen(lines[j+1])) {
                // copy(원본, 대상) 함수를 이용하여 두 문자열의 위치 교환
                copy(lines[j], temp);
                copy(lines[j+1], lines[j]);
                copy(temp, lines[j+1]);
            }
        }
    }

    // 3. 정렬된 결과 출력
    for (i = 0; i < 5; i++) {
        printf("%s\n", lines[i]);
    }

    return 0;
}
