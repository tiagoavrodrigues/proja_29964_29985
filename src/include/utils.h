#include "applicant.h"
#ifndef UTILS_H
#define UTILS_H

#if _WIN32
#define CLEAR "cls"
void enableANSI(); // ANSI CODES PARA TEXTO COLORIDO NA LINHA DE COMANDOS DO WINDOWS
#else
#define CLEAR "clear"
#endif

#define RED   "\033[1;31m\0"
#define GREEN "\033[1;32m\0"
#define BLUE  "\033[1;34m\0"
#define YELLOW "\033[1;33m\0"
#define RESET "\033[0m\0"

typedef enum eColor{
    Red,
    Green,
    Yellow,
    Blue
} eColor;

void clearScreen();
void clearBuffer();
void _pause();
void printFixedWidth(char string[], char fillerChar, unsigned short width);
void printColored(char string[], eColor color, unsigned short width);
void inputPasswordMask(char password[]);
void inputNumber(unsigned char input[], unsigned short maxChar);
void initMemory(AREALIST *areaList, UNITLIST *unitList, HCOURSELIST *hcourseList, APPLICANTLIST *applicantList);
void saveMemory(USERLIST userList, HCOURSELIST hcourseList, APPLICANTLIST applicantList);
#endif