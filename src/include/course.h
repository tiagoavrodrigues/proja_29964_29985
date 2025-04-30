#include "org.h"

#ifndef COURSE_H
#define COURSE_H

#define DESCRIPTION_MAX_CHAR 101
#define CODE_MAX_CHAR 9

typedef struct{
    unsigned short id;
    char description[DESCRIPTION_MAX_CHAR];
} AREA;

typedef struct{
    unsigned short count;
    AREA *items;
} AREALIST;

typedef struct{
    enum { CTeSP, Bachelor, Master, Doctorate } type;
    unsigned char code[CODE_MAX_CHAR];
    char description[DESCRIPTION_MAX_CHAR];
    AREA area;
    UNIT school;
    enum { Closed, Open } status;
} HCOURSE; //Higher Course

typedef struct hcourselist{
    unsigned short count;
    HCOURSE *items;
}HCOURSELIST;

typedef struct{
    unsigned char code[CODE_MAX_CHAR];
    char description[DESCRIPTION_MAX_CHAR];
    AREA area;
} COURSE;

AREALIST createAreaList();
AREA* getArea(AREA*, unsigned short id);
void listAreas(AREALIST*);
HCOURSELIST createHCourseList(AREA*, UNIT*);
void listHCourses(HCOURSELIST*);

#endif