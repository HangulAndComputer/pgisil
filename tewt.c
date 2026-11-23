#include <stdio.h>

typedef struct{
    char name[20];
    int age;
}Person;
void stat(const Person *p, int *a){
    *a = (p->age) + 1;
}

int main(){
    Person minsu = {"minsu", 20};
    minsu.name = "mins";
    Person yh = {"younghee",21};
    Person pop[2] = {minsu,yh}; 
    Person *ptr = pop;
    
    for (int i = 0; i < 2; i++) {
        printf("%s, %d", ptr->name, ptr->age);
        int ho = 0;
        stat(ptr,&ho);
        printf("%d", ho);

        ptr += 1;
    }
}
