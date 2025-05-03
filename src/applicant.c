#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/applicant.h"
#include "include/user.h"
#include "include/utils.h"

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

APPLICANT* getApplicant(APPLICANTLIST applicantList, USER loggedUser){
    if(applicantList.count == 0) return NULL;

    for(unsigned int i = 0; i < applicantList.count; i++){
        if(strcmp(applicantList.applicants[i].user.username, loggedUser.username) == 0
            && strcmp(applicantList.applicants[i].user.password, loggedUser.password) == 0) return &applicantList.applicants[i];
    }

    return NULL;
}

short addApplicant(APPLICANTLIST *applicantList, APPLICANT newApplicant){
    if(applicantList == NULL || !applicantList->count || applicantList->applicants == NULL){
        return -1;
    }

    APPLICANT *newItems = realloc(applicantList->applicants, (applicantList->count + 1) * sizeof(APPLICANT));
    if (newItems == NULL) {
        return -1;
    }

    applicantList->applicants = newItems;
    
    applicantList->applicants[applicantList->count] = newApplicant;
    applicantList->count++;

    return 0;
}

short editApplicantInfo(APPLICANT *applicantInfo, APPLICANT newInfo){
    if(applicantInfo == NULL) return -1;

    *applicantInfo = newInfo;

    return 0;
}

short saveApplicantData(APPLICANTLIST applicantList){
    FILE *fp;

    if((fp = fopen(APPLICANT_FILENAME, "wb")) == NULL){
        printColored("\nErro ao abrir o ficheiro " APPLICANT_FILENAME "!", Red, 0);
        _pause();
        return -1;
    };

    fwrite(&applicantList.count, sizeof(unsigned short), 1, fp);
    fwrite(applicantList.applicants, sizeof(APPLICANT), applicantList.count, fp);

    fclose(fp);
    return 0;
}

short loadApplicantData(APPLICANTLIST *applicantList){
    FILE *fp;

    if((fp = fopen(APPLICANT_FILENAME, "rb")) == NULL){
        return - 1;
    };

    fread(&applicantList->count, sizeof(unsigned short), 1, fp);

    applicantList->applicants = (APPLICANT *) calloc(applicantList->count, sizeof(APPLICANT));

    fread(applicantList->applicants, sizeof(APPLICANT), applicantList->count, fp);

    fclose(fp);
    return 0;
}