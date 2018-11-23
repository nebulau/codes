#include<stdio.h>
#include<string.h>
#define MAXNUM 512	 //地铁最大站数
#define MAXLEN 20		 //地铁站名的最大长度
#define INFINITY  32767
struct  station { //车站信息
	char  sname[MAXLEN];  	//车站名
	int ischange; 		 //是否为换乘站，0-否，1-换乘
};
struct weight {
	int wei; 		//两个站间的权重，即相差站数，缺省为1
	int lno;  		//两个顶点所在的线号
};
struct station BGvertex[MAXNUM];  		//地铁网络图顶点数组
struct weight BGweights[MAXNUM][MAXNUM]; 	//网络图权重数组
int Vnum = 0; 	//实际地铁总站数
int addvertex(struct station st) {
	int i;
	for (i = 0; i < MAXNUM; i++) {
		if (strcmp(BGvertex[i].sname, "") == 0) {
			strcpy(BGvertex[i].sname, st.sname);
			BGvertex[i].ischange = st.ischange;
			break;
		}
		else if (strcmp(BGvertex[i].sname, st.sname) == 0) {
			break;
		}
	}
	return i;
}
void getvnum() {
	int i;
	for (i = 0; strcmp(BGvertex[i].sname, "") != 0; i++);
	Vnum = i;
}
void initMap()
{
	FILE *fp;
	int i, j, snum, lno, lnum, v1, v2, k;
	struct station st;
	for (i = 0; i < MAXNUM; i++) {
		for (j = 0; j < MAXNUM; j++) BGweights[i][j].wei = INFINITY;
	}
	fp = fopen("bgstations.txt", "r");
	fscanf(fp, "%d", &snum);
	for (i = 0; i<snum; i++) {
		fscanf(fp, "%d %d", &lno, &lnum);
		v1 = v2 = -1;
		for (j = 0; j<lnum; j++) {
			fscanf(fp, "%s %d", st.sname, &st.ischange);
			v2 = addvertex(st); //将该站加到站信息数组中，返回其下标
			if (v1 != -1) {
				BGweights[v1][v2].wei = BGweights[v2][v1].wei = 1;
				BGweights[v1][v2].lno = BGweights[v2][v1].lno = lno;
			}
			v1 = v2;
		}
	}
	getvnum();
	fclose(fp);
}
void Dijkstra(int v0, int v1, int spath[])
{
	int i, j, v, minweight;
	int  wfound[MAXNUM] = { 0 }; //用于标记从v0到相应顶点是否找到最短路径，0未找到，1找到
	int sweight[MAXNUM] = { 0 };
	for (i = 0; i<Vnum; i++) {
		sweight[i] = BGweights[v0][i].wei;  //初始化数组Sweight
		spath[i] = v0;		  //初始化数组spath
	}
	sweight[v0] = 0;
	wfound[v0] = 1;
	for (i = 0; i< Vnum - 1; i++) {  //迭代VNUM-1次
		minweight = INFINITY;
		for (j = 0; j < Vnum; j++)  	//找到未标记的最小权重值顶点
			if (!wfound[j] && (sweight[j] < minweight)) {
				v = j;
				minweight = sweight[v];
			}
		wfound[v] = 1;	//标记该顶点为已找到最短路径
		if (v == v1) return;	 //找到(v0,v1)最短路径，返回
		for (j = 0; j < Vnum; j++) //找到未标记顶点且其权值大于v的权值+(v,j)的权值，更新其权值
			if (!wfound[j] && (BGweights[v][j].lno > 0) && (minweight + BGweights[v][j].wei < sweight[j])) {
				sweight[j] = minweight + BGweights[v][j].wei;
				spath[j] = v;  //记录前驱顶点
			}
	}
}
void printPath(int v0, int v1, int spath[])
{

	char path[80] = { '0' }, buf[80];
	int board[80], bcount = 0, line = -1, sc = 0; //bcount为从v0到v1最短路径的乘坐站数，sc为乘坐某一线路的站数
	int i;
	do { //获得乘坐站序列，该序列为倒的，即起始站在最后
		board[bcount++] = v1;
	} while ((v1 = spath[v1]) != v0);
	board[bcount++] = v0;
	line = BGweights[board[bcount - 1]][board[bcount - 2]].lno;
	sprintf(buf, "%s-%d(", BGvertex[board[bcount - 1]].sname, line);
	strcpy(path, buf);
	sc = 1;
	for (i = bcount - 2; i>0; i--, sc++)
		if (BGweights[board[i]][board[i - 1]].lno != line) {
			line = BGweights[board[i]][board[i - 1]].lno;
			sprintf(buf, "%d)-%s-%d(", sc, BGvertex[board[i]].sname, line);
			strcat(path, buf);
			sc = 0;
		}
	sprintf(buf, "%d)-%s\n", sc, BGvertex[board[i]].sname);
	strcat(path, buf);
	puts(path);
}
int main() {
	char s1[MAXLEN], s2[MAXLEN];
	scanf("%s", s1);
	scanf("%s", s2);
	int spath[MAXNUM], i, v0, v1;
	initMap();
	for (i = 0; i < Vnum; i++) {
		if (strcmp(BGvertex[i].sname, s1) == 0){
                    v0 = i;
                    
		}
		if (strcmp(BGvertex[i].sname, s2) == 0){
                    v1 = i;
                    
		}
	}
	Dijkstra(v0, v1, spath);
	printPath(v0, v1, spath);
	return 0;
}
