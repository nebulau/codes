#include<stdio.h>
#include<stdlib.h>
int i, n, a[10], b[10];
void print() {
	for (i = 1; i <= n; i++)	printf("%d ", a[i]);
	printf("\n");
}
void work(int k) {
	if (k>n)	print();
	else {
		int i;
		for (i = 1; i <= n; i++) {
			if (!b[i]) {
				a[k] = i;
				b[i] = 1;
				work(k + 1);
				b[i] = 0;
				a[k] = 0;

			}
		}
	}
}
int main() {
	scanf("%d", &n);
	work(1);
	return 0;
}