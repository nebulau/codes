#include<stdio.h>
#include<string.h>
#define MAXNUM 512	 //�������վ��
#define MAXLEN 20		 //����վ������󳤶�
#define INFINITY  32767
struct  station { //��վ��Ϣ
	char  sname[MAXLEN];  	//��վ��
	int ischange; 		 //�Ƿ�Ϊ����վ��0-��1-����
};
struct weight {
	int wei; 		//����վ���Ȩ�أ������վ����ȱʡΪ1
	int lno;  		//�����������ڵ��ߺ�
};
struct station BGvertex[MAXNUM];  		//��������ͼ��������
struct weight BGweights[MAXNUM][MAXNUM]; 	//����ͼȨ������
int Vnum = 0; 	//ʵ�ʵ�����վ��
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
			v2 = addvertex(st); //����վ�ӵ�վ��Ϣ�����У��������±�
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
	int  wfound[MAXNUM] = { 0 }; //���ڱ�Ǵ�v0����Ӧ�����Ƿ��ҵ����·����0δ�ҵ���1�ҵ�
	int sweight[MAXNUM] = { 0 };
	for (i = 0; i<Vnum; i++) {
		sweight[i] = BGweights[v0][i].wei;  //��ʼ������Sweight
		spath[i] = v0;		  //��ʼ������spath
	}
	sweight[v0] = 0;
	wfound[v0] = 1;
	for (i = 0; i< Vnum - 1; i++) {  //����VNUM-1��
		minweight = INFINITY;
		for (j = 0; j < Vnum; j++)  	//�ҵ�δ��ǵ���СȨ��ֵ����
			if (!wfound[j] && (sweight[j] < minweight)) {
				v = j;
				minweight = sweight[v];
			}
		wfound[v] = 1;	//��Ǹö���Ϊ���ҵ����·��
		if (v == v1) return;	 //�ҵ�(v0,v1)���·��������
		for (j = 0; j < Vnum; j++) //�ҵ�δ��Ƕ�������Ȩֵ����v��Ȩֵ+(v,j)��Ȩֵ��������Ȩֵ
			if (!wfound[j] && (BGweights[v][j].lno > 0) && (minweight + BGweights[v][j].wei < sweight[j])) {
				sweight[j] = minweight + BGweights[v][j].wei;
				spath[j] = v;  //��¼ǰ������
			}
	}
}
void printPath(int v0, int v1, int spath[])
{

	char path[80] = { '0' }, buf[80];
	int board[80], bcount = 0, line = -1, sc = 0; //bcountΪ��v0��v1���·���ĳ���վ����scΪ����ĳһ��·��վ��
	int i;
	do { //��ó���վ���У�������Ϊ���ģ�����ʼվ�����
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
