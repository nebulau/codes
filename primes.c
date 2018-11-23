/* 本次作业由本人独立实现完成，如有抄袭行为，愿承担由此带来的一切不良后果 */
#include<stdio.h>
int main()
{
	int n,i,j,flag=1;
	scanf("%d", &n);
	for (i = 2; i < n+1; i++) {
		for (j = 2; j < i; j++) {
			if (i%j == 0) {
				flag = 0;
				break;
			}
		}
		if ((flag == 1) && (n%i == 0)) {
			n = n / i;
			printf("%d ", i);
			i = 1;
		}
		flag = 1;
	}
	return 0;
}
