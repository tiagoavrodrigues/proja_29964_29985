#include "user.h"
#include "course.h"

#ifndef APPLICANT_H
#define APPLICANT_H

#define YEAR_MIN 1900
#define YEAR_MAX 2010
#define NAME_MAX_CHAR 51
#define NCC_MAX_CHAR 9
#define NIF_MAX_CHAR 10
#define SCHOOL_MAX_CHAR 101

#define APPLICANT_FILENAME "src/data/applicant.dat"

typedef struct date{
    unsigned short day;
    unsigned short month;
    unsigned short year;
} DATE;

typedef struct applicant{
    USER user;
    char name[NAME_MAX_CHAR];
    char surname[NAME_MAX_CHAR];
    unsigned char nCC[NCC_MAX_CHAR];
    unsigned char nif[NIF_MAX_CHAR];
    DATE dateofbirth;
    char hcourseCode[CODE_MAX_CHAR];
    char school[SCHOOL_MAX_CHAR];
    float mean;
} APPLICANT;

typedef struct applicantlist{
    unsigned short count;
    APPLICANT *applicants;
} APPLICANTLIST;

unsigned short isValidDate(unsigned short day, unsigned short month, unsigned short year);
short addApplicant(APPLICANTLIST *applicantList, APPLICANT newApplicant);
short editApplicantInfo(APPLICANT *applicantInfo, APPLICANT newInfo);

short saveApplicantData(APPLICANTLIST applicantList);
short loadApplicantData(APPLICANTLIST *applicantList);

#endif