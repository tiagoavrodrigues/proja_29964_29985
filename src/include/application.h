#include "applicant.h"
#include "course.h"

#ifndef APPLICATION_H
#define APPLICATION_H


typedef struct application{
    APPLICANT applicant;
    HCOURSE course;
    struct application *next;
} APPLICATION;

#endif