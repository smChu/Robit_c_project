#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int main(void) {//�������� �ִ� 9���ڱ��� �Է� ����, ��¥ �Է�(11��)�Ҷ��� �� �� ����
	char arr[11] = {"A"};
	
	scanf("%[^\n]s", arr);

	printf("%s\n", arr);
	
}