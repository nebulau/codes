#include<stdio.h>
int primes[100000],j;
int is_prime(int a){
    int i;
    for(i=0;primes[i]*primes[i]<=a;i++)
        if(a%primes[i]==0)
            return 0;
    return 1;
}
int find(int n){
    int i;
    primes[0]=2,j=1;
    for(i=3;i<=n;i+=2)
        if(is_prime(i))
            primes[j++]=i;
}
int main(){
    int i,n;
    scanf("%d",&n);
    find(n);
    for(i=0;i<j;i++)    printf("%d\n",primes[i]);
    return 0;
}
