#include<stdio.h>
#include<stdlib.h>
#define M 100
int num = 0;
void swap(int *p, int *q) {
	int temp;
	temp = *p;
	*p = *q;
	*q = temp;
}
void select1(int K[], int n) {
	int i, j;
	for (i = 0; i < n - 1; i++) {
		for (j = i + 1; j < n; j++) {
			if (K[j] < K[i])	swap(&K[i], &K[j]);
		}
	}
	for (i = 0; i < n; i++)	printf("%d ", K[i]);
	printf("\n%d", n*(n - 1) / 2);
}
void select2(int K[], int n) {
	int i, j, flag = 1;
	i = n - 1;
	while (i > 0 && flag == 1) {
		flag = 0;
		for (j = 0; j < i; j++) {
			num++;
			if (K[j] > K[j + 1]) {
				swap(&K[j], &K[j+1]);
				flag = 1;
			}
		}
		i--;
	}
	for (i = 0; i < n; i++)	printf("%d ", K[i]);
	printf("\n%d", num);
}
void  adjust(int k[], int i, int n)
{
	int j, temp;
	for (temp = k[i]; 2 * i + 1 < n; i = j) {
		j = 2 * i + 1;
		num++;
		if (j != n - 1 && k[j + 1] > k[j])	++j;
		if (temp < k[j])	k[i] = k[j];
		else break;
	}
	k[i] = temp;
}
void select3(int k[], int n)
{
	int i;
	for (i = n / 2; i >= 0; --i)
		adjust(k, i, n);
	for (i = n-1; i >= 1; --i) {
		swap(&k[i], &k[0]);
		adjust(k, 0, i);
	}
	for (i = 0; i < n; i++)	printf("%d ", k[i]);
	printf("\n%d", num);
}
void merge(int x[], int tmp[], int left, int leftend, int rightend)
{
	int i = left, j = leftend + 1, q = left;
	while (i <= leftend && j <= rightend)
	{
		num++;
		if (x[i] <= x[j])
			tmp[q++] = x[i++];
		else
			tmp[q++] = x[j++];
	}
	while (i <= leftend)
		tmp[q++] = x[i++];
	while (j <= rightend)
		tmp[q++] = x[j++];
	for (i = left; i <= rightend; i++)
		x[i] = tmp[i];
}
void mSort(int k[], int tmp[], int left, int right)
{
	int center;
	if (left < right) {
		center = (left + right) / 2;
		mSort(k, tmp, left, center);
		mSort(k, tmp, center + 1, right);
		merge(k, tmp, left, center, right);
	}
}
void select4(int k[], int n)
{
	int *tmp, i;
	tmp = (int *)malloc(sizeof(int) * n);
	if (tmp != NULL) {
		mSort(k, tmp, 0, n - 1);
		free(tmp);
	}
	for (i = 0; i < n; i++)	printf("%d ", k[i]);
	printf("\n%d", num);
}
void quickSort(int k[], int left, int right)
{
	int i, last;
	if (left<right) {
		last = left;
		for (i = left + 1; i <= right; i++) {
			num++;
			if (k[i] < k[left])	swap(&k[++last], &k[i]);
		}
		swap(&k[left], &k[last]);
		quickSort(k, left, last - 1);
		quickSort(k, last + 1, right);
	}
}
void select5(int k[], int n) {
	int i;
	quickSort(k, 0, n-1);
	for (i = 0; i < n; i++)	printf("%d ", k[i]);
	printf("\n%d", num);
}

int main() {
	int numbers[M], n, Q, i;
	scanf("%d%d", &n, &Q);
	for (i = 0; i < n; i++)	scanf("%d", &numbers[i]);
	if (Q == 1)	select1(numbers, n);
	if (Q == 2)	select2(numbers, n);
	if (Q == 3)	select3(numbers, n);
	if (Q == 4)	select4(numbers, n);
	if (Q == 5)	select5(numbers, n);
	return 0;
}