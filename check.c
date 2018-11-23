#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#define MAXERROR 5000
int getword(FILE *fp, char *w) {
	int c;
	while (!isalpha(c = fgetc(fp))) {
		if (c == EOF)	return c;
		else continue;
	}
	do {
		*w++ = tolower(c);
	} while (isalpha(c = fgetc(fp)));
	*w = '\0';
	return 1;
}
struct error{
    char word[50];
    int location[100];
};
struct error mistake[MAXERROR];
void append(struct error st){
	int i, j;
	for (i = 0; i < MAXERROR; i++) {
        if(strcmp(mistake[i].word,"")==0){
            strcpy(mistake[i].word,st.word);
            mistake[i].location[0]=st.location[0];
			break;
        }
		else if (strcmp(mistake[i].word, st.word) == 0) {
			for (j = 0; mistake[i].location[j] != 0; j++);
			mistake[i].location[j] = st.location[0];
			break;
		}
    }

}
void makelist(char dictionary[][50], int list[], int n) {
	int i;
	list[0] = 0;
	for (i = 0; i < n; i++)	list[dictionary[i][0] - 'a' + 1]++;
	for (i = 1; i < 27; i++)	list[i] += list[i - 1];

}
int find(char w[], char dictionary[][50], int low, int high) {
	int mid;
	if (low > high)	return 0;
	else {
		mid = (low + high) / 2;
		if ((low == high) && strcmp(w, dictionary[mid])!=0) return 0;
		else if (strcmp(w, dictionary[mid]) > 0) return find(w, dictionary, mid + 1, high);
		else if (strcmp(w, dictionary[mid]) < 0) return find(w, dictionary, low, mid - 1);
		else return 1;
	}
}
void sort(int order[]) {
	int i, j, temp;
	for (i = 0; i < MAXERROR; i++)	order[i] = i;
	for (i = 0; strcmp(mistake[i].word, "") != 0; i++) {
		for (j = i + 1; strcmp(mistake[j].word, "") != 0; j++) {
			if (strcmp(mistake[i].word, mistake[j].word) > 0) {
				temp = order[i];
				order[i] = order[j];
				order[j] = temp;
			}
		}
	}
}
int main() {
	int i = 0, j, n = 0, list[27] = { 0 }, order[MAXERROR];
	char buf[80], buf1[80];
	FILE *bfp, *in, *out;
	bfp = fopen("dictionary.txt", "r");
	in = fopen("article.txt", "r");
	out = fopen("misspelling.txt", "w");
	char dictionary[430000][50], word[50];
	while (getword(bfp, word) != EOF) strcpy(dictionary[n++], word);
	makelist(dictionary, list, n);
	struct error st;
	while (getword(in, word) != EOF) {
		if (find(word, dictionary, list[word[0] - 'a'], list[word[0] - 'a' + 1] - 1))	continue;
		else
		{
			strcpy(st.word, word);
			st.location[0] = ftell(in) - strlen(word) - 1;
			append(st);
		}
	}
	sort(order);
	for (i = 0; strcmp(mistake[order[i]].word, "") != 0; i++) {
		sprintf(buf, "%s ", mistake[order[i]].word);
		for (j = 0; mistake[order[i]].location[j] != 0; j++) {
			sprintf(buf1, "%d ", mistake[order[i]].location[j]);
			strcat(buf, buf1);
		}
		strcat(buf, "\n");
		fputs(buf, out);
	}
	fclose(bfp);
	fclose(in);
	fclose(out);
	return 0;
}
