#include "user.h"
#include "course.h"

#ifndef APPLICANT_H
#define APPLICANT_H

#define YEAR_MIN 1900
#define YEAR_MAX 2010
#define NAME_MAX_CHAR 51
#define NCC_MAX_CHAR 10
#define NIF_MAX_CHAR 10
#define SCHOOL_MAX_CHAR 101

#define APPLICANT_FILENAME "data/applicant.dat"
#define APPLICANT_FILENAME_PRINT "output/applicant.txt"

typedef enum applicationstatus{ Pending, Enrolled, Accepted, Rejected } eApplicationStatus;

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
    COURSE course;
    char school[SCHOOL_MAX_CHAR];
    float mean;
    eApplicationStatus applicationStatus;
} APPLICANT;

typedef struct applicantlist{
    unsigned short count;
    APPLICANT *applicants;
} APPLICANTLIST;

unsigned short isValidDate(unsigned short day, unsigned short month, unsigned short year);
short addApplicant(APPLICANTLIST *applicantList, APPLICANT newApplicant);
short editApplicantInfo(APPLICANT *applicantInfo, APPLICANT newInfo);
void getApplicantInfo(APPLICANT *currentApplicant, APPLICANTLIST applicantList);

short saveApplicantData(APPLICANTLIST applicantList);
short loadApplicantData(APPLICANTLIST *applicantList);

short printApplicationInfo(APPLICANT applicant, HCOURSELIST hcourseList);
short displayApplicationInfo(APPLICANT applicant, HCOURSELIST hcourseList);

#endif