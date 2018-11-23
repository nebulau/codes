#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct node {
	char word[40];
	int count;
	struct node *link;
};
struct node *Wordlist = NULL;
int getWord(FILE *fp, char *w)
{
	int c;

	while (!isalpha(c = fgetc(fp)))
		if (c == EOF) return c;
		else continue;
		do {
			*w++ = tolower(c);
		} while (isalpha(c = fgetc(fp)));
		*w = '\0';
		return 1;
}
int insertWord(struct node  *p, char *w)
{
	struct node  *q;
	q = (struct node *)malloc(sizeof(struct node));
	if (q == NULL) return -1;
	strcpy(q->word, w);
	q->count = 1;
	q->link = NULL;
	if (Wordlist == NULL)
		Wordlist = q;
	else if (p == NULL) {
		q->link = Wordlist;
		Wordlist = q;
	}
	else {
		q->link = p->link;
		p->link = q;
	}
	return 0;
}
int searchWord(char *w)
{
	struct  node *p, *q = NULL;
	for (p = Wordlist; p != NULL; q = p, p = p->link) {
		if (strcmp(w, p->word) < 0)
			break;
		else if (strcmp(w, p->word) == 0) {
			p->count++;
			return 0;
		}
	}
	return insertWord(q, w);
}
int main()
{
	char word[40];
	FILE *bfp;
	bfp = fopen("article.txt", "r");
	struct node *p;
	while (getWord(bfp, word) != EOF)
		if (searchWord(word) == -1) return -1;
	for (p = Wordlist; p != NULL; p = p->link)
		printf("%s %d\n", p->word, p->count);
	return 0;
}
