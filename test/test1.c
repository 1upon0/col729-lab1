#include <stdio.h>
int foo(int n){
    for(int i=0;i<n;i++){
        printf("This is foo! %d/%d\n",i,n);
    }
    if(n==0){
        return 0;
    }
    else{
        return 1+foo(n-1);
    }
}
void bar(int b,int g,int k){
    int a=1+b;
}
int main(){
    int a=1;
    int b=2;
    printf("This is main!\n");
    int s= a-b;
    bar(s,a,b);
    int r= foo(a+b*b);
    printf("Foo says %d\n",r);
    printf("Bye!\n");
    return 0;
}