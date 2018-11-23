#include<stdio.h>
#include<string.h>
int judge(int s1[], int s2[], int a,int b) {
	int i;
	if (a>b)   return 1;
	if (b>a)   return 0;
	if (a == b) {
		for (i = 0; i < a; i++) {
			if (s1[i]>s2[i]) {
				return 1;
				break;
			}
			if (s2[i]>s1[i]) {
				return 0;
				break;
			}
			if (i == a)   return 1;
		}
	}
}
int main() {
	int s1[83], s2[83], i = 0, j = 0, k, out[81], p, q;
	char c;
	while ((c = getchar()) != '\n')  s1[i++] = c - '0';
	while ((c = getchar()) != '\n')  s2[j++] = c - '0';
	k = judge(s1, s2,i,j);
	if (k) {
		for (p = i - 1,q = j - 1; q >= 0; p--,q--) {
			if (s1[p] >= s2[q])	out[p] = s1[p] - s2[q];
			else {
				out[p] = s1[p] - s2[q] + 10;
				s1[p - 1] = s1[p - 1] - 1;
			}
		}
		for (p = i - j; p > 0; p--)	out[p - 1] = s1[p - 1];
		for (p = i - 1; p > 0; p--) {
			if (out[p] < 0) {
				out[p] = out[p] + 10;
				out[p - 1] -= 1;
			}
		}
		for(p=0;p<i;p++)
			if (out[p] != 0) {
				for (q = p; q < i-1; q++)	printf("%d", out[q]);
				break;
			}
		printf("%d", out[i - 1]);
	}
	else {
		for (p = j - 1, q = i - 1; q >= 0; p--, q--) {
			if (s2[p] >= s1[q])	out[p] = s2[p] - s1[q];
			else {
				out[p] = s2[p] - s1[q] + 10;
				s2[p - 1] = s2[p - 1] - 1;
			}
		}
		for (p = j - i; p > 0; p--)	out[p - 1] = s2[p - 1];
		for (p = j - 1; p > 0; p--) {
			if (out[p] < 0) {
				out[p] = out[p] + 10;
				out[p - 1] -= 1;
			}
		}
		printf("-");
		for (p = 0; p<j; p++)
			if (out[p] != 0) {
				for (q = p; q < j; q++)	printf("%d", out[q]);
				break;
			}
	}
	return 0;
}