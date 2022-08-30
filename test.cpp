#include <stdio.h>
void change(int *a, int b){
    a=&b;
    (*a)+=1;
}
int main(){
    int *a;
    int b=3;
    change(a, b);
    printf("%d", *a);
}