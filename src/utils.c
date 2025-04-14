#include <stdlib.h>
#include <stdio.h>

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

void clearScreen(){
    system(CLEAR);
}

void clearBuffer(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

void pause(){
    printf("\nPrima Enter para continuar...");
    getchar();
}