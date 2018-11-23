#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DEFLINES  10
#define MAXLEN    81
struct Node {
	char *line;
	struct Node *next;
};
int main(int argc, char *argv[])
{
	char curline[MAXLEN], *filename;
	int n = DEFLINES, i;
	struct Node *first, *ptr;
	FILE *fp;
	if (argc == 3 && argv[1][0] == '-') {
		n = atoi(argv[1] + 1);
		filename = argv[2];
	}
	else if (argc == 2)
		filename = argv[1];
	else {
		printf("Usage: tail [-n] filename\n");
		return (1);
	}
	while (fgets(curline, MAXLEN, fp) != NULL) {
		if (ptr->line != NULL)                                                          // 如果已经存过行了，要释放掉，重新
			free(ptr->line);                                                              // 新行合适大小的内存   
		ptr->line = (char *)malloc(strlen(curline) + 1);
		strcpy(ptr->line, curline);
		ptr = ptr->next;
	}
	for (i = 0; i<n; i++) {
		if (ptr->line != NULL)
			printf("%s", ptr->line);
		ptr = ptr->next;
	}
	fclose(fp);
	return 0;
}
