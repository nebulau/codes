#include<stdio.h>
#include<stdlib.h>
typedef struct client {
	int no;
	int time;
	struct client *link;
}Lnode, *clientlink;
clientlink front = NULL, rear = NULL;
int windows = 3, timelist[500];
void enqueue(int no) {
	clientlink p = (clientlink)malloc(sizeof(Lnode));
	p->no = no;
	p->time = 0;
	p->link = NULL;
	if (front = NULL)	front = p;
	else {
		rear->link = p;
	}
	rear = p;
}
void dequeue() {
	if (front != NULL) {
		clientlink p = front;
		front = front->link;
		free(p);
	}
}
void start(int x, int *no) {
	int i;
	for (i = 0; i < x; i++) {
		enqueue(*no);
		(*no)++;
	}
	int tmplen;
	tmplen = (front != NULL) ? rear->no - front->no + 1 : 0;
	if (tmplen / windows >= 7) {
		if (tmplen / (windows + 1) < 7) {
			if (windows <= 4)	windows++;
		}
		else {
			windows = 5;
		}
	}
}
void finish() {
	int i;
	for (i = 0; i < windows; i++) {
		if (front != NULL) {
			timelist[front->no - 1] = front->time;
			dequeue();
		}
	}
	clientlink tmp = front;
	if (front != NULL) {
		while (1) {
			tmp->time++;
			if (tmp = rear)	break;
			else {
				tmp = tmp->link;
			}
		}
	}
	int tmplen;
	tmplen = (front != NULL) ? rear->no - front->no + 1 : 0;
	if (tmplen / windows < 7 && windows>3)	windows--;
}
int main() {
	int n, i, tmptotal = 0, no = 1;
	int fresher;
	scanf("%d", &n);
	while (1)
	{
		scanf("%d", &fresher);
		tmptotal += fresher;
		start(fresher, &no);
		finish();
		n--;
		if (n == 0)
		{
			while (front != NULL)
				finish();
			break;
		}
	}
	for (i = 0; i < tmptotal; i++) {
		printf("%d : %d\n", i + 1, timelist[i]);
	}
	return 0;
}