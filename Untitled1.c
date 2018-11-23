/* 本次作业由本人独立实现完成，如有抄袭行为，愿承担由此带来的一切不良后果 */
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
	Datatype a;              /* 创建一个空链表 */
	int i;
	for (i = 0; i<n; i++) {
		READ(a);                 /* 取一个数据元素 */
		r = (Nodeptr)malloc(sizeof(Node));
		r->data = a;
		r->link = NULL;
		if (head == NULL)
			head = p = r;
		else {
			p->link = r;          /* 将新结点链接在链表尾部 */
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
