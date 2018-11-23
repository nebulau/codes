#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>
int num = 0;
int getword(FILE *fp, char *w) {
	int c;
	while (!isalpha(c = fgetc(fp))) {
		if (c == EOF)  return c;
		else continue;
	}
	do {
		*w++ = tolower(c);
	} while (isalpha(c = fgetc(fp)));
	*w = '\0';
	return 1;
}
void find1(char input[],char dictionary[3500][20]) {
	int i;
	for (i = 0; strcmp(dictionary[i], input) <= 0; i++);
	if (strcmp(dictionary[i - 1], input) == 0)	printf("1 %d", i);
	else printf("0 %d", i+1);
}
void find2(char input[], char dictionary[3500][20],int n) {
	int low = 0, high = n - 1, mid, flag = 1;
	while (low <= high) {
		mid = (low + high) / 2;
		if ((low == high)&&strcmp(input, dictionary[mid])!=0) {
			flag = 0;
			break;
		}
		if (strcmp(input, dictionary[mid]) < 0) {
			num++;
			high = mid - 1;
		}
		if (strcmp(input, dictionary[mid]) > 0) {
			num++;
			low = mid + 1;
		}
		if (strcmp(input, dictionary[mid]) == 0) {
			num++;
			printf("1 %d", num);
			break;
		}
	}
	if(flag==0)	printf("0 %d", num+1);
}
void makelist(char dictionary[3500][20], int list[],int n) {
	int i;
	for (i = 0; i < n; i++) {
		list[dictionary[i][0] - 'a']++;
	}
	for (i = 1; i < 26; i++) {
		list[i] += list[i - 1];
	}
}
void find3(char input[], char dictionary[3500][20],int low,int high) {
	int mid;
	if (low > high)	printf("0 %d", num);
	else {
		mid = (low + high) / 2;
		num++;
		if ((low == high) && strcmp(input, dictionary[mid]) != 0)	printf("0 %d", num);
		else if (strcmp(input, dictionary[mid]) > 0) {
			return find3(input, dictionary, mid + 1, high);
		}
		else if (strcmp(input, dictionary[mid]) < 0) {
			return find3(input, dictionary, low, mid - 1);
		}
		else {
			printf("1 %d", num);
		}
	}
}
unsigned int hash(char *w) {
	unsigned int h = 0;
	char *p;
	for (p = w; *p != '\0'; p++)	h = 37 * h + *p;
	return h % 3001;
}
void find4(char dictionary[3500][20], int n, char input[]) {
	typedef struct HNode {
		char word[20];
		struct HNode *link;
	}HNode, *linklist;
	int i;
	linklist HT[3500] = { NULL }, p, q, r;
	for (i = 0; i < n; i++) {
		p = (linklist)malloc(sizeof(HNode));
		strcpy(p->word, dictionary[i]);
		if (HT[hash(dictionary[i])] == NULL||strcmp(dictionary[i], HT[hash(dictionary[i])]->word) < 0) {
			p->link = HT[hash(dictionary[i])];
			HT[hash(dictionary[i])] = p;
		}
		else
		{
			q = HT[hash(dictionary[i])];
			while (q != NULL&&strcmp(dictionary[i], q->word) > 0) {
				r = q;
				q = q->link;
			}
			p->link = q;
			r->link = p;
		}
	}//¹¹½¨hash±í
	if (HT[hash(input)] == NULL) printf("0 %d", num);
	else
	{
		for (p = HT[hash(input)], i = 0; p != NULL&&strcmp(input, p->word) > 0; p = p->link, i++);
		if(p==NULL)	printf("0 %d", i);
		else if(strcmp(input, p->word) == 0)	printf("1 %d", i+1);
		else printf("0 %d", i);
	}
}

int main() {
	char word[20], dictionary[3500][20], input[20];
	FILE *bfp;
	int n = 0, Q,list[26] = { 0 };
	bfp = fopen("dictionary3000.txt", "r");	
	while (getword(bfp, word) != EOF) 
		strcpy(dictionary[n++], word);
	scanf("%s %d", input, &Q);
	if (Q == 1)	find1(input, dictionary);
	if (Q == 2)	find2(input, dictionary,n);
	if (Q == 3) {
		makelist(dictionary, list, n);
		if(input[0]=='a')	find3(input, dictionary, 0, 247);
		else
		{
			find3(input, dictionary, list[input[0] - 'a' - 1], list[input[0] - 'a'] - 1);
		}
	}
	if (Q == 4)	find4(dictionary, n, input);
	fclose(bfp);
	return 0;
}
