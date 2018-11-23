#include<stdio.h>
int work(int a) {
	if (a == 1)	return 1;
	if (a == 2)	return 2;
	return work(a - 1) + work(a - 2);
}
int main() {
	int n;
	scanf("%d", &n);
	printf("%d", work(n));
	return 0;
}