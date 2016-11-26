#include <stdio.h>
int g;
int erk(int a, int b)
{
    int i;
    int x = g;
    int ret = 0;
    if(ret){
        if(ret){
            x = x-ret;
            printf("Value of x: %d\n", x);
        }
        else{
            x = x+ret;
            printf("Value of x: %d\n", x);
        }
    }else{
        x = x+ret;
        printf("Value of x: %d\n", x);
    }
    return ret;
}
int main(){
    erk(1, 2);
    return 0;
}
