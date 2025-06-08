#include <stdio.h>
#include "include/application.h"
#include "include/utils.h"

short addApplication(ELEM **listHeader, APPLICANT newInfo){
    ELEM *new = (ELEM *) calloc(1, sizeof(ELEM));

    if(new == NULL){
        printf("\nOut of memory!\n");
        return -1;
    }

    new->info = newInfo;
    new->next = NULL;

    if(listHeader == NULL){
        *listHeader = new;
    }else{
        new->next = *listHeader;
        *listHeader = new;
    }
    return 0;
}

short applicationExists(ELEM *listHeader, APPLICANT application){
    if(listHeader == NULL){
         return 0;
    }
    for(ELEM *aux = listHeader; aux != NULL; aux = aux->next){
        if(strcmp(aux->info.user.username, application.user.username) == 0){
            return 1;
        }
    }
    return 0;
}

void saveApplications(ELEM *listHeader) {
    if (listHeader == NULL) return;

    FILE *fp = fopen(APPLICATION_FILENAME, "wb");
    if (fp == NULL) {
        printf("\nErro ao abrir o ficheiro %s!", APPLICATION_FILENAME);
        return;
    }

    for (ELEM *aux = listHeader; aux != NULL; aux = aux->next) {
        fwrite(&aux->info, sizeof(APPLICANT), 1, fp);
    }

    fclose(fp);
}

void loadApplications(ELEM **listHeader){
    FILE *fp = NULL;

    int res = 0;
    APPLICANT infoAux;

    if((fp = fopen(APPLICATION_FILENAME, "rb")) == NULL){
        printColored("\nErro ao abrir o ficheiro!", Red, 0);
        return;
    }

    while(!feof(fp)){
        res = fread(&infoAux, sizeof(APPLICANT), 1, fp);
        if(res) addApplication(&(*listHeader), infoAux);
    };
    fclose(fp);
}

void orderByMeanDesc(ELEM *listHeader){
    if(listHeader == NULL) return;
    unsigned short troca = 0;

    do{
        troca = 0;
        for(ELEM *aux = listHeader; aux != NULL; aux = aux->next){
            if(aux->info.mean < aux->next->info.mean){
                APPLICANT temp = aux->next->info;
                aux->next->info = aux->info;
                aux->info = temp;
                troca = 1;
            }
        }
    }while(troca);
}