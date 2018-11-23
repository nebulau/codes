/* ������ҵ�ɱ��˶���ʵ����ɣ����г�Ϯ��Ϊ��Ը�е��ɴ˴�����һ�в������ */
#include<stdio.h>
#include<stdlib.h>
typedef struct node {
	int data;
	struct node   *link;
}LNode, *Linklist;
void JOSEPHU(int n, int m, int q)
{
	Linklist list, p, r;
	int i;
	list = NULL;
	for (i = 0; i<n; i++) {
		r = (Linklist)malloc(sizeof(LNode));
		r->data = i + 1;
		if (list == NULL)
			list = p = r;
		else {
			p->link = r;
			p = p->link;
		}
	}
	p->link = list;  
	r = p;
	for (p = list, i = 0; i<q - 1; i++, r = p, p = p->link)
		;
	while (p->link != p) {
		for (i = 0; i<m - 1; i++) {
			r = p;
			p = p->link;
		}
		r->link = p->link;
		free(p);
		p = r->link;
	}
	printf("%d", p->data);
}
int main()
{
	int n, m, q;
	scanf("%d %d %d", &n, &m, &q);
	JOSEPHU(20, 2, 1);
	return 0;
}
