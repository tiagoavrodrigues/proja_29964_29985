#include "applicant.h"
#include "course.h"

#ifndef APPLICATION_H
#define APPLICATION_H

#define APPLICATION_FILENAME "data/applications.dat"

typedef struct application{
    APPLICANT info;
    struct application *next;
} ELEM;

#endif

short addApplication(ELEM **listHeader, APPLICANT newInfo);
void saveApplication(ELEM *listHeader);
short applicationExists(ELEM *listHeader, APPLICANT application);