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