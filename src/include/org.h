/*
ORGANIZATION; ORGANIC UNIT; SCHOOL
*/

#ifndef ORG_H
#define ORG_H

#define ACRONYM_CHAR_SIZE 6
#define DESIGNATION_CHAR_SIZE 51

typedef struct{
    unsigned short id;
    char acronym[ACRONYM_CHAR_SIZE];
    char designation[DESIGNATION_CHAR_SIZE];
} UNIT;

typedef struct{
    unsigned short count;
    UNIT *items;
} UNITLIST;

UNITLIST createUnitList();
UNIT* getUnit(UNIT *units ,unsigned short id);
const char* getUnitAcronym(UNITLIST *, unsigned short id);
char getUnitDesignation(unsigned short id);
void listUnits(UNITLIST*);

#endif