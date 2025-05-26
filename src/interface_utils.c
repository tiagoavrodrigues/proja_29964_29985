#include "include/interface_utils.h"
#ifndef _WIN32
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
#endif

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