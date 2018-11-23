/* 本次作业由本人独立实现完成，如有抄袭行为，愿承担由此带来的一切不良后果 */
#include<stdio.h>
#include<string.h>
int main(){
    int i,j,k;
    char key[50],string[26];
    scanf("%s",key);
    for(i=0;i<strlen(key)-1;i++){
        for(j=k=i;key[j]!='\0';j++)
            if(key[j+1]!=key[i])    key[++k]=key[j+1];
        key[k]='\0';
    }
    for(j=0,k=0;j<26;j++){
        string[j]='a'+j;
        for(k=0;k<strlen(key);k++)
            if(string[j]==key[k])   string[j]='\0';
    }
    for(i=25,j=0;i>strlen(key)-1;j++)
        if(string[j]!='\0')  key[i--]=string[j];
    key[26]='\0';
    printf("%s",key);
    FILE *in,*out;
    in = fopen("encrypt.txt","r");
    out = fopen("output.txt","w");
    char c;
    while((c=fgetc(in))!=EOF){
        i=c-'a';
        if(i>=0&&i<26)  fputc(key[i],out);
        else{
            fputc(c,out);
        }
    }
    return 0;
}
