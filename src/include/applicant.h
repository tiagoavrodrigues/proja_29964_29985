#include "user.h"
#include "course.h"

#ifndef APPLICANT_H
#define APPLICANT_H

#define YEAR_MIN 1900
#define YEAR_MAX 2010
#define NAME_MAX_CHAR 51

typedef struct date{
    unsigned short day;
    unsigned short month;
    unsigned short year;
} DATE;

typedef struct applicant{
    USER user;
    char name[NAME_MAX_CHAR];
    char surname[NAME_MAX_CHAR];
    unsigned nCC;
    unsigned nif;
    DATE dateofbirth;
    COURSE course;
    char school;
    float mean;
} APPLICANT;

typedef struct applicantlist{
    unsigned short count;
    APPLICANT *applicants;
} APPLICANTLIST;

int isValidDate(unsigned short day, unsigned short month, unsigned short year);

#endif