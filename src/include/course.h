#include "org.h"

#ifndef COURSE_H
#define COURSE_H

#define DESCRIPTION_MAX_CHAR 101
#define CODE_MAX_CHAR 5

typedef struct{
    unsigned short id;
    char description[DESCRIPTION_MAX_CHAR];
} AREA;

typedef struct{
    unsigned char count;
    AREA *items;
} AREALIST;

typedef struct{
    //enum { CTeSP, Bachelor, Master, Doctorate } type;
    char code[CODE_MAX_CHAR];
    char description[DESCRIPTION_MAX_CHAR];
    AREA area;
    UNIT school;
    enum { Open, Closed } status;
} HCOURSE; //Higher Course

typedef struct{
    char code[CODE_MAX_CHAR];
    char description[DESCRIPTION_MAX_CHAR];
    AREA area;
} COURSE;

AREALIST createAreaList();
void listAreas();

#endif