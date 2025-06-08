#include "applicant.h"
#include "course.h"

#ifndef APPLICATION_H
#define APPLICATION_H

#define APPLICATION_FILENAME "data/applications.dat"

typedef struct application{
    APPLICANT info;
    struct application *next;
} ELEM;


short addApplication(ELEM **listHeader, APPLICANT newInfo);
void saveApplications(ELEM *listHeader);
void loadApplications(ELEM **listHeader);
short applicationExists(ELEM *listHeader, APPLICANT application);
void orderByMeanDesc(ELEM *listHeader);

#endif

