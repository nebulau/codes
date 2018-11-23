#include<stdio.h>
#define MAX 20
#define maxvalue 5000
int minspant_prim(int GE[MAX][MAX], int n, int edge[MAX][MAX], int out[MAX]) {
	int lowcost[MAX], teend[MAX], i, j, k, mincost, q = 0, totalcost = 0, temp;
	lowcost[0] = 0;
	teend[0] = 0;
	out[0] = 0;
	for (j = 1; j < n; j++) {
		teend[j] = 0;
		out[j] = 0;
		lowcost[j] = GE[0][j];
	}
	for (i = 1; i < n; i++) {
		mincost = maxvalue;
		for (j = 1; j < n; j++) {
			if (lowcost[j] > 0 && mincost > lowcost[j]){
				mincost = lowcost[j];
				k = j;
			}
		}
		out[q++] = edge[teend[k]][k];
		totalcost += GE[teend[k]][k];
		lowcost[k] = 0;
		for (j = 0; j < n; j++) {
			if(GE[k][j] < lowcost[j]) {
				lowcost[j] = GE[k][j];
				teend[j] = k;
			}
		}
	}
	for (i = 0; out[i] != 0; i++) {
		for (j = i + 1; out[j] != 0; j++) {
			if (out[j] < out[i]) {
				temp = out[j];
				out[j] = out[i];
				out[i] = temp;
			}
		}
	}
	return totalcost;
}
int main() {
	int n, e, id, vi, vj, weight;
	scanf("%d%d", &n, &e);
	int GE[MAX][MAX], edge[MAX][MAX], out[MAX];
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			GE[i][j] = maxvalue;
			edge[i][j] = 0;
		}
	}
	for (i = 0; i < e; i++) {
		scanf("%d%d%d%d", &id, &vi, &vj, &weight);
		GE[vi][vj] = weight;
		GE[vj][vi] = weight;
		edge[vi][vj] = id;
		edge[vj][vi] = id;
	}
	minspant_prim(GE, n, edge, out);
	printf("%d\n", minspant_prim(GE, n, edge, out));
	for (i = 0; out[i] != 0; i++)	printf("%d ", out[i]);
	return 0;
}