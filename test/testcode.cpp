#include <stdio.h>
int foo(int n=3){
    for(int i=0;i<n;i++)
        printf("This is foo! %d/%d\n",i,n);
    if(n==0)
        return 0;
    return 1+foo(n-1);
}

int main(){
    printf("This is main!\n");
    int r=foo();
    printf("Foo says %d\n",r);
    printf("Bye!\n");
    return 0;
}
