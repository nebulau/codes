/* 本次作业由本人独立实现完成，如有抄袭行为，愿承担由此带来的一切不良后果 */
#include<stdio.h>
#include<string.h>
int main() {
	int n, i, j;
	char telbook[50][10], namebook[50][10], temp[20];
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%s", &temp);
		strncpy(namebook[i], temp + 0, 10);
		scanf("%s", &temp);
		strncpy(telbook[i], temp + 0, 10);
	}
	for (i = 0; i < n; i++) {
		for (j = i; j < n; j++) {
			if (strcmp(namebook[i], namebook[j]) > 0) {
				strcpy(temp, namebook[i]);
				strcpy(namebook[i], namebook[j]);
				strcpy(namebook[j], temp);
				strcpy(temp, telbook[i]);
				strcpy(telbook[i], telbook[j]);
				strcpy(telbook[j], temp);
			}
		}
	}
	for (i = 0; i < n; i++) {
		printf("%12s", namebook[i]);
		printf("%12s", telbook[i]);
		printf("\n");
	}
	return 0;
}