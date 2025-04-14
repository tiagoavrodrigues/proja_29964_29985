#include <stdio.h>
#include "include/applicant.h"

int isValidDate(unsigned short day, unsigned short month, unsigned short year){

    if(year < YEAR_MIN || year > YEAR_MAX) return 0;
    if(day == 0 || day > 31) return 0;
    if(month == 0 || month > 12) return 0;
    if(month == 2){
        if(year % 4 == 0 && day > 29) return 0;
        if(day > 28) return 0;
    }

    return 1;
}