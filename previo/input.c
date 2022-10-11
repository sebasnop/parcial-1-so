#include <stdio.h>

int main(void) 
{
    char name[200];
    printf("Hello. What's your name?\n");
    fgets(name, sizeof(name), stdin);
    printf("Hi there, %s", name);
    return 0;
}