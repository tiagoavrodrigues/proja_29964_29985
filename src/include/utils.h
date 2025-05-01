#ifndef UTILS_H
#define UTILS_H

#ifdef _WIN32
void enableANSI(); // ANSI CODES PARA TEXTO COLORIDO NA LINHA DE COMANDOS DO WINDOWS
#endif
void clearScreen();
void clearBuffer();
void pause();
void printFixedWidth(char string[], char fillerChar, unsigned short width);

#endif