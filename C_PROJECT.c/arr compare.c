#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
//다른 행과 열을 입력하고 정답과 내 정답을 비교하도록 하는 코드
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
		printf("정답");
	}
	else {
		printf("오답");
	}


	return 0;
}
//크기가 10인 배열에서 0,2,4,6,8에는 행을, 1,3,5,7,9에는 열을 저장할 것