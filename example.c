#include<stdio.h>
#define M 200
int is_empty(int top) {
	return top == -1;
}
int is_full(int top) {
	return top == M - 1;
}
int push(char stack[], int *t, char i) {
	if (is_full(*t))	return 0;
	else {
		stack[++(*t)] = i;
		return 1;
	}
}
int pop(char stack[], int *t, char *i) {
	if (is_empty(*t))	return 0;
	else {
		*i = stack[(*t)--];
		return 1;
	}
}
char gettop(char stack[], int top) {
	return stack[top];
}
int main() {
	char stack[400], list[1000], out[400];
	int top = -1, i = 0, j, k, p = 0, q = 1;
	FILE *fp;
	fp = fopen("example.c", "r");
	char c, m;
	//将文件用列表储存起来
	while ((c = fgetc(fp)) != EOF) {
		list[i++] = c;
	}
	list[i] = '\0';
	fclose(fp);
	//将引号内和注释清空
	for (j = 0; j < i; j++) {
		if (list[j] == '/') {
			if (list[j + 1] == '/') {
				for (k = j; list[k] != '\n'; k++) {
					list[k] = '*';
				}
				j = k;
			}
			if (list[j + 1] == '*') {
				for (k = j; ; k++) {
					if (list[k] != '\n')   list[k] = '*';
					if (list[k] == '*'&&list[k + 1] == '/')  break;
				}
				list[k + 1] = '*';
				j = k + 1;
			}
		}
		if (list[j] == '"') {
			list[j] = '*';
			for (k = j; list[k] != '"'; k++) {
				if (list[k] != '\n')   list[k] = '*';
			}
			list[k] = '*';
			j = k;
		}
	}
	int flag = 1;
	for (j = 0; list[j] != '\0'&&flag; j++) {
		if (list[j] == '\n')   ++q;
		switch (list[j]) {
		case '(':
			push(stack, &top, list[j]);
			out[p++] = list[j];
			break;
		case ')':
			if (!is_empty(top) && gettop(stack, top) == '(') {
				pop(stack, &top, &m);
				out[p++] = list[j];
				break;
			}
			else {
				flag = 0;
				printf("without maching '%c' at line %d", list[j], q);
				break;
			}
		case '{':
			push(stack, &top, list[j]);
			out[p++] = list[j];
			break;
		case '}':
			if (!is_empty(top) && gettop(stack, top) == '{') {
				pop(stack, &top, &m);
				out[p++] = list[j];
				break;
			}
			else {
				flag = 0;
				printf("without maching '%c' at line %d", list[j], q);
				break;
			}
		}
	}
	out[p] = '\0';
	if (flag == 1) {
		printf("%s", out);
	}
	return 0;
}