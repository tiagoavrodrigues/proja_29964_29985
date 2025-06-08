#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/applicant.h"
#include "include/user.h"
#include "include/utils.h"

unsigned short isValidDate(unsigned short day, unsigned short month, unsigned short year){

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

short printApplicationInfo(APPLICANT applicant, HCOURSELIST hcourseList){
    FILE *fp = NULL;

    if((fp = fopen(APPLICANT_FILENAME_PRINT, "w")) == NULL){
        printColored("\nErro ao abrir o ficheiro " APPLICANT_FILENAME_PRINT "!", Red, 0);
        _pause();
        return -1;
    }

    fprintf(fp,
        "Nome:%s %s\n"
        "CC: %s\n"
        "NIF: %s\n"
        "Data de nascimento: %02d/%02d/%04d\n" 
        "Candidato a: %s - %s\n"
        "Curso Secundário: %s\n"
        "Área: %d - %s\n"
        "Escola: %s\n"
        "Média: %.2f\n"
        , applicant.name
        , applicant.surname
        , applicant.nCC
        , applicant.nif
        , applicant.dateofbirth.day
        , applicant.dateofbirth.month
        , applicant.dateofbirth.year
        , applicant.hcourseCode, getHCourse(hcourseList, applicant.hcourseCode)->description
        , applicant.course.description
        , applicant.course.area.id
        , applicant.course.area.description
        , applicant.school
        , applicant.mean
        , applicant.applicationStatus
    );
    switch(applicant.applicationStatus){
        case 0: fprintf(fp, "Estado da candidatura: Pendente\n"); break;
        case 1: fprintf(fp, "Estado da candidatura: Inscrito\n"); break;
        case 2: fprintf(fp, "Estado da candidatura: Aceite\n"); break;
        case 3: fprintf(fp, "Estado da candidatura: Rejeiteda\n"); break;
    }

    printColored("\nFicheiro criado: " APPLICANT_FILENAME_PRINT "!", Green, 0);
    _pause();
    if(fp) fclose(fp);
    return 0;
};

void getApplicantInfo(APPLICANT *currentApplicant, APPLICANTLIST applicantList){
    if(currentApplicant == NULL || applicantList.count == 0) return;
    for(unsigned int i = 0; i < applicantList.count; i++){
        if(strcmp(currentApplicant->user.username, applicantList.applicants[i].user.username) == 0
            && strcmp(currentApplicant->user.password, applicantList.applicants[i].user.password) == 0){
            *currentApplicant = applicantList.applicants[i];
            return;
        }
    }
}

short displayApplicationInfo(APPLICANT applicant, HCOURSELIST hcourseList){
    printf(
        "Nome:%s %s\n"
        "CC: %s\n"
        "NIF: %s\n"
        "Data de nascimento: %02d/%02d/%04d\n" 
        "Candidato a: %s - %s\n"
        "Curso Secundário: %s\n"
        "Área: %d - %s\n"
        "Escola: %s\n"
        "Média: %.2f\n"
        , applicant.name
        , applicant.surname
        , applicant.nCC
        , applicant.nif
        , applicant.dateofbirth.day
        , applicant.dateofbirth.month
        , applicant.dateofbirth.year
        , applicant.hcourseCode, getHCourse(hcourseList, applicant.hcourseCode)->description
        , applicant.course.description
        , applicant.course.area.id
        , applicant.course.area.description
        , applicant.school
        , applicant.mean
        , applicant.applicationStatus
    );
    switch(applicant.applicationStatus){
        case 0: printf("Estado da candidatura: Pendente\n"); break;
        case 1: printf("Estado da candidatura: Inscrito\n"); break;
        case 2: printf("Estado da candidatura: Aceite\n"); break;
        case 3: printf("Estado da candidatura: Rejeiteda\n"); break;
    }
}

short printApplicationState(APPLICANT applicant, HCOURSELIST hcourseList){
    FILE *fp = NULL;

    if((fp = fopen("output/applications.txt", "a+")) == NULL){
        printColored("\nErro ao abrir o ficheiro output/applications.txt!", Red, 0);
        _pause();
        return -1;
    }

    fprintf(fp,
        "Nome:%s %s\n"
        "CC: %s\n"
        "Candidato a: %s - %s\n"
        "Média: %.2f\n"
        , applicant.name
        , applicant.surname
        , applicant.nCC
        , applicant.hcourseCode, getHCourse(hcourseList, applicant.hcourseCode)->description
        , applicant.mean
    );
    switch(applicant.applicationStatus){
        case 0: fprintf(fp, "Estado da candidatura: Pendente\n"); break;
        case 1: fprintf(fp, "Estado da candidatura: Inscrito\n"); break;
        case 2: fprintf(fp, "Estado da candidatura: Aceite\n"); break;
        case 3: fprintf(fp, "Estado da candidatura: Rejeiteda\n"); break;
    }
    fprintf(fp, "\n---------------------\n");

    printColored("\nFicheiro criado: output/applications.txt!", Green, 0);
    _pause();
    if(fp) fclose(fp);
    return 0;
};

short printApplicationStateByCourse(APPLICANT applicant, HCOURSELIST hcourseList){
    FILE *fp = NULL;

    char filename[strlen("output/") + strlen(applicant.hcourseCode) + strlen(".txt") + 1];
    strcpy(filename, "output/");
    strcat(filename, applicant.hcourseCode);
    strcat(filename, ".txt");

    if((fp = fopen(filename, "a+")) == NULL){
        printColored("\nErro ao abrir o ficheiro!", Red, 0);
        _pause();
        return -1;
    }

    fprintf(fp,
        "Nome:%s %s\n"
        "CC: %s\n"
        "NIF: %s\n"
        "Data de nascimento: %02d/%02d/%04d\n" 
        "Candidato a: %s - %s\n"
        "Curso Secundário: %s\n"
        "Área: %d - %s\n"
        "Escola: %s\n"
        "Média: %.2f\n"
        , applicant.name
        , applicant.surname
        , applicant.nCC
        , applicant.nif
        , applicant.dateofbirth.day
        , applicant.dateofbirth.month
        , applicant.dateofbirth.year
        , applicant.hcourseCode, getHCourse(hcourseList, applicant.hcourseCode)->description
        , applicant.course.description
        , applicant.course.area.id
        , applicant.course.area.description
        , applicant.school
        , applicant.mean
        , applicant.applicationStatus
    );
    switch(applicant.applicationStatus){
        case 0: fprintf(fp, "Estado da candidatura: Pendente\n"); break;
        case 1: fprintf(fp, "Estado da candidatura: Inscrito\n"); break;
        case 2: fprintf(fp, "Estado da candidatura: Aceite\n"); break;
        case 3: fprintf(fp, "Estado da candidatura: Rejeiteda\n"); break;
    }

    printColored("\nFicheiro criado: " APPLICANT_FILENAME_PRINT "!", Green, 0);
    _pause();
    if(fp) fclose(fp);
    return 0;
}