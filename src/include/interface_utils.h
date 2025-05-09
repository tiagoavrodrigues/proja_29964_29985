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
unsigned char isInteger(char*buffer){
    long unsigned int i;
    unsigned char num=0,harmlessSymbols=0,harmfull=0;
    for(i=0;i<strlen(buffer);i++){
        if(buffer[i]=='0' || buffer[i]=='1' || buffer[i]=='2' || buffer[i]=='3' || buffer[i]=='4' || buffer[i]=='5' || buffer[i]=='6' || buffer[i]=='7' || buffer[i]=='8' ||buffer[i]=='9'){
            num=1;
        }else if(buffer[i]==' ' || buffer[i]=='\n'){
            if(num){
                return 0;
            }
            harmlessSymbols=1;
        }else{
            harmfull=1;
        }
    }
    return (!harmlessSymbols || num) && !harmfull;
}
unsigned char isReal(char*buffer){
    long unsigned int i;
    unsigned char num=0,harmlessSymbols=0,harmfull=0,dot=0;
    for(i=0;i<strlen(buffer);i++){
        if(buffer[i]=='0' || buffer[i]=='1' || buffer[i]=='2' || buffer[i]=='3' || buffer[i]=='4' || buffer[i]=='5' || buffer[i]=='6' || buffer[i]=='7' || buffer[i]=='8' ||buffer[i]=='9'){
            num=1;
        }else if(buffer[i]==' ' || buffer[i]=='\n'){
            if(num){
                return 0;
            }
            harmlessSymbols=1;
        }else if(buffer[i]=='.'){
            dot=1;
        }else{
            harmfull=1;
        }
    }
    return (!harmlessSymbols || num) && !harmfull;
}
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
unsigned char getInput(void*value,Type readAs,long unsigned int buf_size){
    double d;
    long int l;
    char buffer[buf_size];
    scanf("%[^\n]s",buffer);
    switch(readAs){
        case Real:
            if(isReal(buffer)){
                sscanf(buffer,"%lf",&d);
                value=malloc(sizeof(double));
                ((double*)value)[0]=d;
                return 1;
            }else{
                return 0;
            }
            break;
        case Integer:
            if(isInteger(buffer)){
                sscanf(buffer,"%ld",&l);
                value=malloc(sizeof(long int));
                ((long int*)value)[0]=l;
                return 1;
            }else{
                return 0;
            }
            break;
        case String:
            value=malloc(strlen(buffer)+1);
            strcpy(value,buffer);
            return 1;
            break;
        default:
        return 0;
            break;
    }
}

#endif