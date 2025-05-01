#ifndef UTILS_H
#define UTILS_H

#ifdef _WIN32
void enableANSI(); // ANSI CODES PARA TEXTO COLORIDO NA LINHA DE COMANDOS DO WINDOWS
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
void pause();
void printFixedWidth(char string[], char fillerChar, unsigned short width);
void printColored(char string[], eColor color, unsigned short width);
#endif