#ifndef _INTERFACE_UTILS_H
#define _INTERFACE_UTILS_H
#include <stdio.h>
#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif
#include <stdlib.h>
#include <string.h>
#ifndef _WIN32
int getch(void);
#endif
/**
 * @brief uma espécie de menu dropdown
 * 
 * @param options  Opções oferecidas ao utilizador
 * @param res  Opção onde começa o seletor
 * @param up  Array com os caracteres válidos para mover o seletor para cima
 * @param down  Array com os caracteres válidos para mover o seletor para baixo
 * @param size  Número de opções disponíveis
 * @param selected  String que aparece para representar o seletor
 * @param unSelected String que aparece para representar os campos não selecionados
 * @param select  Carácter usado para selecionar uma opção 
 * @param clear  Comando usado para limpar o terminal, usado periodicamente cada vez que se muda de opção 
 * @return Índice da opção selecionada
 */
unsigned char menuSelect(char*options[],unsigned char res,char*up,char*down,long unsigned int size,char*selected,char*unSelected,char select,char*clear);


#endif