#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 32
typedef struct node{
    char *word;
    int count;
    struct node *left,*right;
}BTNode,*BTREE;
int getword(FILE *fp,char *w){
    int c;
    while(!isalpha(c=fgetc(fp))){
        if(c==EOF)  return c;
        else continue;
    }
    do{
        *w++==tolower(c);
    }while(isalpha(c=fgetc(fp)));
    *w='\0';
    return 1;
}
BTREE treewords(BTREE T,char *w){
    if(T==NULL){
        T=(BTREE)malloc(sizeof(BTNode));
        strcpy(T->word,w);
        T->count=1;
        T->left=T->right=NULL;
    }
    else if(strcmp(T->word,w)>0)
        T->left=treewords(T->left,w);
    else if(strcmp(T->word,w)<0)
        T->right=treewords(T->right,w);
    else{
        T->count++;
    }
    return T;
}
void printtree(BTREE T){
    if(T!=NULL){
        printf("%s %d\n",T->word,T->count);
        printtree(T->left);
        printtree(T->right);
    }
}
int main(){
    char word[MAX];
    FILE *bfp;
    bfp=fopen("article.txt","r");
    BTREE root=NULL;
    while(getword(bfp,word)!=EOF)
        root=treewords(root,word);
    printtree(root);
    fclose(bfp);
    return 0;
}
