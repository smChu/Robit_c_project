#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
//�ٸ� ��� ���� �Է��ϰ� ����� �� ������ ���ϵ��� �ϴ� �ڵ�
int main(void) {
	int arr[10] = { 0 };
	for (int i = 1; i <= 5; i++) {
		arr[2 * (i - 1)] = i;
		arr[2 * i - 1] = i + 10;
	}
	for (int i = 0; i < 10; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	int arr1[10] = { 0, };
	for (int i = 0; i < 10; i++) {
		scanf("%d", &arr1[i]);
	}
	
	int cnt = 0;
	for (int i = 0; i < 10; i++) {
		if (arr[i] == arr1[i]) {
			cnt += 1;
		}
	}
	if (cnt == 10) {
		printf("����");
	}
	else {
		printf("����");
	}


	return 0;
}
//ũ�Ⱑ 10�� �迭���� 0,2,4,6,8���� ����, 1,3,5,7,9���� ���� ������ ��