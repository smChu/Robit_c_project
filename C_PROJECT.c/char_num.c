#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int main(void) {
	int num[10] = { 0 };
	int cnt = 0;
		for (int i = 0; i < 10; i++) {
			cnt += scanf("%d", &num[i]);
		}


		for (int i = 0; i < 10; i++) {
			printf("%d", num[i]);
		}printf("\n\n");
		printf("%d", cnt);
}