#include <stdio.h>
int main()
{
	char c;
	FILE *in, *out;
	in = fopen("input.txt","r");
	out = fopen("output.txt", "w");
	while ((c=fgetc(in)) != EOF)
		fputc(c, out);
	fclose(in);
	fclose(out);

	return 0;
}
