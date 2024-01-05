#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int main(void) {//공백포함 최대 9글자까지 입력 가능, 날짜 입력(11개)할때도 쓸 수 있음
	char arr[11] = {"A"};
	
	scanf("%[^\n]s", arr);

	printf("%s\n", arr);
	
}