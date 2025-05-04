#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "include/utils.h"
#include "include/user.h"
#include "include/applicant.h"
#include "include/course.h"

#ifdef _WIN32

#include <windows.h>
#include <conio.h>
void enableANSI() { // ANSI CODES PARA TEXTO COLORIDO NA LINHA DE COMANDOS DO WINDOWS
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}

#else
#include <termios.h>
#endif

void clearScreen(){
    system(CLEAR);
}

void clearBuffer(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

void _pause(){
    printf("\nPrima Enter para continuar...");
    getchar();
}

void printFixedWidth(char string[], char fillerChar, unsigned short width){
    if(string == NULL || string[0] == '\0') return;

    if(width == 0) width = strlen(string) + 1;

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

void inputPasswordMask(char password[PASSWORD_MAX_CHAR]){
    int p = 0;
    char ch;
    do {
        ch = getch();
        
        // Handle backspace
        if(ch == 8 && p > 0){
            printf("\b \b");  // Move back, space, move back again
            p--;
        }
        // Handle normal character (not Enter or Backspace)
        else if(ch >= 32 && ch <= 126 &&  // Printable ASCII range
                ch != ' ' &&               // Explicitly exclude space
                p < PASSWORD_MAX_CHAR - 1){
            password[p] = ch;
            printf("*");
            p++;
        }
    } while (ch != 10);
    password[p] = '\0';
}

void initMemory(AREALIST *areaList, UNITLIST *unitList,HCOURSELIST *hcourseList, APPLICANTLIST *applicantList){
    *areaList = createAreaList();
    *unitList = createUnitList();
    if(loadHCourseData(hcourseList) < 0) *hcourseList = createHCourseList(areaList->items, unitList->items);
    if(loadApplicantData(applicantList) < 0) return;
    return;
}

void saveMemory(USERLIST userList, HCOURSELIST hcourseList, APPLICANTLIST applicantList){
    saveUserData(userList);
    saveHCourseData(hcourseList);
    saveApplicantData(applicantList);
}