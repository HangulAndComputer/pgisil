#include <stdio.h>

void test(int *a) {
    *a = 20;
}
void main(){
    int a = 10;
    test(&a);
    printf("%d",a);
}