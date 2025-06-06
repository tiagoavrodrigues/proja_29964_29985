#include "org.h"

#ifndef COURSE_H
#define COURSE_H

#define DESCRIPTION_MAX_CHAR 101
#define CODE_MAX_CHAR 9

#define AREA_ITEM_QUANTITY 22
#define HCOURSE_ITEM_QUANTITY 30

#define COURSE_FILENAME "data/hcourse.dat"

typedef enum estate{
    Open,
    Closed
} eState;

typedef struct area{
    unsigned short id;
    char description[DESCRIPTION_MAX_CHAR];
} AREA;

typedef struct arealist{
    unsigned short count;
    AREA *items;
} AREALIST;

typedef struct hcourse{
    enum { CTeSP, Bachelor, Master, Doctorate } type;
    unsigned char code[CODE_MAX_CHAR];
    char description[DESCRIPTION_MAX_CHAR];
    unsigned slots;
    AREA area;
    UNIT school;
    eState state;
}HCOURSE; //Higher Course

typedef struct hcourselist{
    unsigned short count;
    HCOURSE *items;
} HCOURSELIST;

typedef struct course{
    unsigned char code[CODE_MAX_CHAR];
    char description[DESCRIPTION_MAX_CHAR];
    AREA area;
} COURSE;

AREALIST createAreaList();
AREA getArea(AREA[], unsigned short id);
void listAreas(AREALIST);

HCOURSELIST createHCourseList(AREA*, UNIT*);

HCOURSE* getHCourse(HCOURSELIST hcourseList, unsigned char code[]);
short setHCourseState(HCOURSE *hcourse, eState newState);
short changeHCourseState(HCOURSE *course);

short addHCourse(HCOURSELIST*, HCOURSE newCourse);
short editHCourse(HCOURSE *hcourse, HCOURSE newCourseInfo);

unsigned short isValidHCourse(HCOURSELIST hcourseList, unsigned char code[]);

void listHCourses(HCOURSELIST);
void listHCoursesAsc(HCOURSELIST);
void listHCoursesByUnit(HCOURSELIST, unsigned short unitID);
void listOpenHCourses(HCOURSELIST hcourseList);

short loadHCourseData(HCOURSELIST *hcourseList);
short saveHCourseData(HCOURSELIST hcourseList);

#endif