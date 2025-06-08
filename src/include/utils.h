#include "applicant.h"
#include "application.h"
#ifndef UTILS_H
#define UTILS_H

#if _WIN32
#define CLEAR "cls"
void enableANSI(); // ANSI CODES PARA TEXTO COLORIDO NA LINHA DE COMANDOS DO WINDOWS
#else
#define CLEAR "clear"
#endif

#define BLACK   "\033[1;30m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN    "\033[1;36m"
#define WHITE   "\033[1;37m"
#define RESET   "\033[0m"

#define ENTER_KEY 10

typedef enum eColor{
    Red,
    Green,
    Yellow,
    Blue
} eColor;

void clearScreen();
void clearBuffer();
void _pause();
void stringToUpper(char text[]);
void printFixedWidth(char string[], char fillerChar, unsigned short width);
void printColored(char string[], eColor color, unsigned short width);
void inputPasswordMask(char password[]);
void inputNumber(unsigned char input[], unsigned short maxChar);
void inputNumberMenu(unsigned char input[], unsigned short maxChar);
void inputDate(unsigned char input[], unsigned short maxChar);
void initMemory(AREALIST *areaList, UNITLIST *unitList, HCOURSELIST *hcourseList, APPLICANTLIST *applicantList);
void saveMemory(USERLIST userList, HCOURSELIST hcourseList, APPLICANTLIST applicantList, ELEM *listHeader);
#endif