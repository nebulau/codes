/* ������ҵ�ɱ��˶���ʵ����ɣ����г�Ϯ��Ϊ��Ը�е��ɴ˴�����һ�в������ */
#include<stdio.h>
#include<stdlib.h>
struct node {
	ElemType   data;
	struct node   *link;
};
typedef  struct node *Nodeptr;
typedef  struct node Node;
Nodeptr   list, p;
Nodeptr  createList(int n)
{
	Nodeptr p, r, head = NULL;
	Datatype a;              /* ����һ�������� */
	int i;
	for (i = 0; i<n; i++) {
		READ(a);                 /* ȡһ������Ԫ�� */
		r = (Nodeptr)malloc(sizeof(Node));
		r->data = a;
		r->link = NULL;
		if (head == NULL)
			head = p = r;
		else {
			p->link = r;          /* ���½������������β�� */
			p = p->link;
		}
	}
	p->link = head;
	return head;
}
void josephu(int n, int k, int m)
{
	Nodeptr list, p, r;
	int i;
	list = NULL;
	for (i = 0; i<n; i++) {
		r = (Nodeptr)malloc(sizeof(Node));
		r->data = i;
		if (list == NULL)
			list = p = r;
		else {
			p->link = r;
			p = p->link;
		}
	}

int main()
{

}
