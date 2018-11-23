#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct NODE *node;
struct NODE
{
	char hufcode[15];
	char c;
	int count;
	node left, right;
	node next;
}huf[128];
void statistic(FILE *in)
{
	char ch;
	while ((ch = getc(in)) != EOF)
	{
		huf[ch].count++;
		huf[ch].c = ch;
	}
	huf['\n'].count = 0;
	huf[0].count = 1;
}
node insert(node p, node head)
{
	if (head == NULL)
		return p;
	if (p->count < head->count)
	{
		p->next = head;
		return p;
	}
	node m = head, n = head->next;
	while (n != NULL&&n->count <= p->count)
	{
		m = n;
		n = n->next;
	}
	p->next = m->next;
	m->next = p;
	return head;
}
node buildHuf()
{
	int i = 1, con = 0;
	while (i < 128)
	{
		if (huf[i].count)
		{
			insert(&huf[i], &huf[0]);
			++con;
		}
		++i;
	}
	node t1, t2, root = &huf[0], temp;
	while (con >= 1)
	{
		t1 = root;
		t2 = root->next;
		root = t2->next;
		temp = (node)malloc(sizeof(struct NODE));
		memset(temp, 0, sizeof(struct NODE));
		temp->count = t1->count + t2->count;
		temp->left = t1;
		temp->right = t2;
		root = insert(temp, root);
		--con;
	}
	return root;
}


void code(node p, int level)
{
	if (p == NULL)
		return;
	if (p->left != NULL)
	{
		strcpy(p->left->hufcode, p->hufcode);
		p->left->hufcode[level] = '0';
	}
	if (p->right != NULL)
	{
		strcpy(p->right->hufcode, p->hufcode);
		p->right->hufcode[level] = '1';
	}
	code(p->left, level + 1);
	code(p->right, level + 1);
}
void compress(FILE *in, FILE *out)
{
	rewind(in);
	int ch, i = 0;
	unsigned char *pc, ec = 0, fc = 0;
	do
	{
		ch = getc(in);
		if (ch == '\n')
			continue;
		if (ch == EOF)
			ch = 0;
		for (pc = huf[ch].hufcode; *pc != '\0'; ++pc)
		{
			ec = (ec << 1) | (*pc - '0');
			fc = (fc << 1) | (*pc - '0');
			++i;
			if (i == 4)
			{
				if (fc != 0)
					printf("%x", fc);
				fc = 0;
			}
			if (i == 8)
			{
				fputc(ec, out);
				printf("%x", fc);
				i = 0, fc = 0;
			}
		}
	} while (ch != 0);
	if (i != 0)
	{
		if (!fc)
			printf("0");
		else
		{
			if (i < 4)
			{
				ec = ec << (8 - i);
				fc = fc << (4 - i);
				printf("%x0", fc);
				fputc(ec, out);
			}
			else
			{
				ec = ec << (8 - i);
				fc = fc << (8 - i);
				printf("%x", fc);
				fputc(ec, out);
			}
		}
		fputc(ec, out);
	}
}


int main() {
	FILE *in, *out;
	in = fopen("input.txt", "r");
	out = fopen("output.txt", "w");
	statistic(in);
	node root = buildHuf();
	code(root, 0);
	compress(in, out);
	fclose(in);
	fclose(out);
	return 0;
}
