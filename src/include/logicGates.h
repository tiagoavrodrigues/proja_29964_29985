#ifndef _LOGICGATES_H
#define _LOGICGATES_H
unsigned char imply(unsigned char p,unsigned char q){
    return !p||q;
}
#endif