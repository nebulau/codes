#include<stdio.h>
#include<stdlib.h>
#define MAX 105
typedef struct edge {
	int adjvex;
	struct edge *next;
}ELink;
typedef struct ver {
	int vertex;
	ELink *link;
}VLink;
void adjust(VLink G[], int n, int e) {
	int k, vi, vj;
	ELink *p, *q, *r,*s, *t,*u;
	for (k = 0; k < n; k++) {
		G[k].link = NULL;
	}
	for (k = 0; k < e; k++) {
		scanf("%d%d", &vi, &vj);
		p = (ELink *)malloc(sizeof(ELink));
		p->adjvex = vj;
		p->next = NULL;
		if (G[vi].link == NULL || vj < G[vi].link->adjvex) {
			p->next = G[vi].link;
			G[vi].link = p;
		}
		else
		{
			q = G[vi].link;
			while (q != NULL&&vj >= q->adjvex) {
				r = q;
				q = q->next;
			}
			p->next = q;
			r->next = p;
		}
		s = (ELink *)malloc(sizeof(ELink));
        s->adjvex = vi;
		s->next = NULL;
		if (G[vj].link == NULL || vi < G[vj].link->adjvex) {
			s->next = G[vj].link;
			G[vj].link = s;
		}
		else
		{
			t = G[vj].link;
			while (t != NULL&&vi >= t->adjvex) {
				u = t;
				t = t->next;
			}
			s->next = t;
			u->next = s;
		}
	}
}
int visited[MAX] = { 0 };
void DFS(VLink G[], int v) {
	ELink *p;
	visited[v] = 1;
	printf("%d ", v);
	for (p = G[v].link; p != NULL; p = p->next) {
		if (!visited[p->adjvex])	DFS(G, p->adjvex);
	}
	
}
void travelDFS(VLink  G[], int n)
{
	int i;
	for (i = 0; i<n; i++) visited[i] = 0;
	for (i = 0; i<n; i++)
		if (!visited[i]) DFS(G, i);
}
void traveldfs(VLink  G[], int n,int x)
{
	int i;
	for (i = 0; i<n; i++) visited[i] = 0;
	visited[x] = 1;
	for (i = 0; i<n; i++)
		if (!visited[i]) DFS(G, i);
}
void BFS(VLink  G[], int v)
{
	ELink  *p;
	int front = -1, rear = -1, Q[MAX];
	visited[v] = 1; //标识某顶点被访问过
	printf("%d ", v);
	Q[++front] = v;    // 队列Q未做定义，此段为示意代码
	while (front != rear) {
		v = Q[++rear];  //取出队头元素
		p = G[v].link;  //获取该顶点第一个邻接顶点
		while (p != NULL) {  //访问该顶点下的每个邻接顶点
			if (!visited[p->adjvex]) {
				visited[p->adjvex] = 1;
				printf("%d ", p->adjvex);
				Q[++front] = p->adjvex;
			}
			p = p->next;
		}
	}
}

void  travelBFS(VLink  G[], int n)
{
	int i;
	for (i = 0; i<n; i++) visited[i] = 0;
	for (i = 0; i<n; i++)
		if (!visited[i]) BFS(G, i);
}
void  travelbfs(VLink  G[], int n,int x)
{
	int i;
	for (i = 0; i<n; i++) visited[i] = 0;
	visited[x] = 1;
	for (i = 0; i<n; i++)
		if (!visited[i]) BFS(G, i);
}


int main() {
	int n, e, x;
	scanf("%d%d", &n, &e);
	VLink G[MAX];
	adjust(G, n, e);
	scanf("%d", &x);
	travelDFS(G, n);
	printf("\n");
	travelBFS(G, n);
	printf("\n");
	traveldfs(G, n, x);
	printf("\n");
	travelbfs(G, n, x);
	return 0;
}
