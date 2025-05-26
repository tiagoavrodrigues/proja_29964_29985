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
unsigned char isInteger(char*buffer);
unsigned char isReal(char*buffer);
typedef enum Type{Real,Integer,String}Type;
/**
 * @brief Obtém input e verifica o tipo
 * 
 * @param value variável onde se guarda o valor
 * @param readAs como se pretende interpretar o input
 * @param buf_size tamanho do input em caracteres
 * 
 * @return sucesso ou insucesso 
 */
unsigned char getInput(void*value,Type readAs,long unsigned int buf_size);
#endif