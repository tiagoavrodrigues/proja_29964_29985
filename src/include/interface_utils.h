#ifndef _INTERFACE_UTILS_H
#define _INTERFACE_UTILS_H
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
int getch(void) {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
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
unsigned char menuSelect(char*options[],unsigned char res,char*up,char*down,long unsigned int size,char*selected,char*unSelected,char select,char*clear){
    long unsigned int i,j;
    for(i=0;i<size;i++){
        printf("\n%s%s",(i==res)?selected:unSelected,options[i]);
    }
    char ch=getch();
    if(ch==select){
        return res;
    }else{
        unsigned char isUp=2;
        for(j=0;j<strlen(up);j++){
            if(ch==up[j]){
                isUp=1;
                break;
            }
        }
        for(j=0;j<strlen(down);j++){
            if(ch==down[j]){
                isUp=0;
                break;
            }
        }
        if(isUp==1){
            system(clear);
            menuSelect(options,(res==0)?size-1:res-1,up,down,size,selected,unSelected,select,clear);
        }else if(isUp==0){
            system(clear);
            menuSelect(options,(res==size-1)?0:res+1,up,down,size,selected,unSelected,select,clear);
        }else{
            system(clear);
            menuSelect(options,res,up,down,size,selected,unSelected,select,clear); 
        }
    }
}
#endif