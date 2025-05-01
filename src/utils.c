#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "include/utils.h"

#ifdef _WIN32
#define CLEAR "cls"
#include <windows.h>

void enableANSI() { // ANSI CODES PARA TEXTO COLORIDO NA LINHA DE COMANDOS DO WINDOWS
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}

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

void printFixedWidth(char string[], char fillerChar, unsigned short width){
    if(string == NULL || string[0] == '\0') return;

    unsigned short strLength = 0;
    unsigned short specialCharCount = 0;
    for(strLength = 0; strLength < width && string[strLength] != '\0'; strLength++){
        if(string[strLength] < 0) specialCharCount++;
    }

    if(specialCharCount >= 2) specialCharCount /= 2; // dois caracteres especiais equivalem a um caracter de output

    unsigned short printedChars = 0;
    for(unsigned short i = 0; i < width && i <= strLength; i++){
        putchar(string[i]);
        printedChars++;
    }

    for(unsigned short i = strLength - specialCharCount; i <= width; i++){
        putchar(fillerChar);
    }
}

void printColored(char string[], eColor color, unsigned short width){
    if(string == NULL || string[0] == '\0') return;

    switch(color){
        case Red: printf(RED); break;
        case Green: printf(GREEN); break;
        case Blue: printf(BLUE); break;
        case Yellow: printf(YELLOW); break;
    }

    printFixedWidth(string, ' ', width);

    printf(RESET);

}
