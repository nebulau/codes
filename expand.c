#include<stdio.h>
#include<string.h> 
char string[1100];
int main() {
	int i = 0, a, b, j, m;
	while (1) {
		string[i] = getchar();
		if (string[i] == '\n')	break;
		i++;
	}
	m = i;
	for (i = 0; i<m; i++) {
		if (string[i + 1] == '-') {
			a = string[i];
			b = string[i + 2];
			if (a<b) {
				for (j = a; j <= b; j++) {
					putchar(j);
				}
				i = i + 2;
			}
			else {
				i = i + 2;
			}
		}
		else {
			printf("%c", string[i]);
		}
	}
	return 0;
}