/* 本次作业由本人独立实现完成，如有抄袭行为，愿承担由此带来的一切不良后果 */
#include<stdio.h>
#include<string.h>
int main()
{	
	char s[200], op[50];
	gets(s);
	int i, j, out[80] = {0}, k, p;
	for (i = j = 0;s[i]!='\0'; i++) 
		if (s[i] != ' ')	s[j++] = s[i];
	s[j] = '\0';
	for (i =j=p= 0; s[i] != '\0'; i++) {			
		if (s[i] > 47 && s[i] < 58) {
			for (k = i; s[k] > 47 && s[k] < 58; k++) {
				out[p] = out[p] * 10 + s[k]-'0';
			}
			p++;
			i = k - 1;
		}
		else {
			op[j++] = s[i];
		}
	}
	op[j] = '\0';
	for (i = 0;op[i]!='\0'; i++) {
		if (op[i] == '*') {
			out[i] = out[i] * out[i + 1];
			for (k = i; k < 40; k++)out[k + 1] = out[k + 2];
			for (k = i; op[k] != '\0'; k++)op[k] = op[k + 1];
			i = -1;
		}
		else if (op[i] == '/') {
			out[i] = out[i] / out[i + 1];
			for (k = i; k < 40; k++)out[k + 1] = out[k + 2];
			for (k = i; op[k] != '\0'; k++)op[k] = op[k + 1];
			i = -1;
		}
	}
	for (i = 0; op[i] != '\0'; i++) {
		if (op[i] == '+') {
			out[i] = out[i] + out[i + 1];
			for (k = i; k < 40; k++)out[k + 1] = out[k + 2];
			for (k = i; op[k] != '\0'; k++)op[k] = op[k + 1];
			i = -1;
		}
		else if (op[i] == '-') {
			out[i] = out[i] - out[i + 1];
			for (k = i; k < 40; k++)out[k + 1] = out[k + 2];
			for (k = i; op[k] != '\0'; k++)op[k] = op[k + 1];
			i = -1;
		}
	}
	printf("%d", out[0]);
	return 0;
}
