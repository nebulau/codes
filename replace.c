#include <stdio.h>
#include <string.h>
int main(){
    char s1[10],s2[10],c,string[4500];
    int i=0,j,k,d;
    scanf("%s",s1);
    scanf("%s",s2);
    FILE *in,*out;
    in = fopen("filein.txt","r");
    out = fopen("fileout.txt","w");
    while((c=fgetc(in))!=EOF)   string[i++]=c;
    for(i=0;string[i]!='\0';i++){
        for(j=i,k=0;s1[k]!='\0'&&(string[j]==s1[k]||string[j]==s1[k]-32);j++,k++);
        if(s1[k]=='\0'){
            d=strlen(s2)-strlen(s1);
            if(d>=0)    for(j=strlen(string);j>=i+k;j--)string[j+d]=string[j];
            else{
                for(j=i+k;string[j]!='\0';j++)string[j+d]=string[j];
                string[j+d]='\0';
            }
            for(j=i,k=0;k<strlen(s2);j++,k++)   string[j]=s2[k];
            }
    }
    for(i=0;string[i]!='\0';i++)   fputc(string[i],out);
    fclose(in);
    fclose(out);
    return 0;
}
