#include<stdio.h>
int NUM=0;
typedef struct node{
    int data;
    struct node *lchild,*rchild;
}BTNode,*BTREE;
BTREE insert(BTREE T,int i){
    if(T==NULL){
        T=(BTREE)malloc(sizeof(BTNode));
        T->data=i;
        T->lchild=T->rchild=NULL;
    }
    else if(i<T->data)  T->lchild=insert(T->lchild,i);
    else if(i>=T->data)  T->rchild=insert(T->rchild,i);
    return T;
}
void leaves(BTREE T){
    if(T!=NULL){
        NUM++;
        if((T->lchild==NULL)&&(T->rchild==NULL))    printf("%d %d\n",T->data,NUM);
        leaves(T->lchild);
        leaves(T->rchild);
        NUM--;
    }
}
int main(){
    int n,x,i;
    scanf("%d",&n);
    BTREE root=NULL;
    for(i=0;i<n;i++){
        scanf("%d",&x);
        root=insert(root,x);
    }
    leaves(root);
    return 0;
}
