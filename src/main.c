#include <stdio.h>
#include <locale.h>
#include <string.h>

#include "include/utils.h"
#include "include/course.h"
#include "include/text.h"
#include "include/user.h"
#include "include/applicant.h"
#include "include/interface_utils.h"
#include "include/menu.h"
#include "include/application.h"

void test(AREALIST areaList, UNITLIST unitList, HCOURSELIST *hcourseList, APPLICANTLIST *applicantList);

void enrollApplicant(ELEM **listHeader, APPLICANT *newApplicant, eState applicationsState);
void admMenuOpt1(HCOURSELIST *hcourseList, AREALIST areaList, UNITLIST unitList, eState applicationsState);
void admMenuOpt2(HCOURSELIST *hcourseList, AREALIST areaList, UNITLIST unitList, eState applicationsState);
void admMenuOpt3(HCOURSELIST *hcourseList, eState applicationsState);
void admMenuOpt6(ELEM *listHeader, HCOURSELIST hcourseList);

void newHcourseConstructionDialog(HCOURSELIST *hcourseList, AREALIST areaList, UNITLIST unitList, HCOURSE *newHcourse);
void admMenuOpt7(eState *applicationsState);

int main(int argc, char *argv[]){
    setlocale(LC_ALL, "");

    #ifdef _WIN32
    enableANSI();  // ANSI CODES PARA TEXTO COLORIDO NA LINHA DE COMANDOS DO WINDOWS
    #endif

    USERLIST userList = {};
    if(loadUserData(&userList) < 0) userList = createUserList();

    USER loggedUser = {0};
    APPLICANT currentApplicant = {};

    AREALIST areaList = {0};
    UNITLIST unitList = {0};
    HCOURSELIST hcourseList = {0};
    APPLICANTLIST applicantList = {0};
    eState applicationsState;

    ELEM *listHeader = NULL;

    char opc[2];

    loadApplications(&listHeader);

    initMemory(&areaList, &unitList, &hcourseList, &applicantList);

    applicationsState = Open; // REMOVER

    clearScreen();
    loginForm(&userList, &loggedUser, areaList, hcourseList, &currentApplicant, &applicantList, &listHeader);

    if(loggedUser.type == Applicant) enrollApplicant(&listHeader, &currentApplicant, applicationsState);
    saveApplications(listHeader);


    do{
        clearScreen();
        switch(loggedUser.type){
            case Admin: drawAdminMenu(&applicationsState); break;
            case Applicant: drawUserMenu(currentApplicant, applicationsState);break;
        }

        inputNumberMenu(opc, 2);

        if(loggedUser.type == Admin){
            switch(opc[0]){
                case '1': admMenuOpt1(&hcourseList, areaList, unitList, applicationsState); break;
                case '2': admMenuOpt2(&hcourseList, areaList, unitList, applicationsState); break;
                case '3': admMenuOpt3(&hcourseList, applicationsState); break;
                case '4': clearScreen(); listHCoursesAsc(hcourseList); _pause(); break;
                case '5': admMenuOpt5(hcourseList, unitList); break;
                case '6': admMenuOpt6(listHeader, hcourseList); break;
                case '7': admMenuOpt7(&applicationsState); break;
                case '8': admMenuOpt8(listHeader, hcourseList); break;
                case '9': break;
                case 'a': break;
            }
        }else{
            switch(opc[0]){
                case '1': printFilledForm(currentApplicant, hcourseList, Information); _pause(); break;
                case '2': 
                    if(applicationsState == Closed){
                        drawUserMenu(currentApplicant, applicationsState); printColored("A informação não pode ser alterada durante o período de candidaturas fechadas.", Red, 0); _pause();
                    }else registerUserInfoForm(areaList, &currentApplicant, hcourseList, Update);
                    break;
                case '3': printApplicationInfo(currentApplicant, hcourseList);
            }
        }
    }while(opc[0] != '0');
 
    //test(areaList, unitList, &hcourseList, &applicantList);

    saveMemory(userList, hcourseList, applicantList, listHeader);

    free(userList.users);
    free(hcourseList.items);
    //free(unitList.items);
    //free(areaList.items);
    free(applicantList.applicants);

    return 0;
}

void test(AREALIST areaList, UNITLIST unitList, HCOURSELIST *hcourseList, APPLICANTLIST *applicantList){
    listAreas(areaList);
    listUnits(unitList);
    listHCourses(*hcourseList);
    setHCourseState(getHCourse(*hcourseList, "CTESP001"), Closed);
    addHCourse(hcourseList, (HCOURSE) { CTeSP, "CTESP000", "Curso de Teste", 2, getArea(areaList.items, 21), getUnit(unitList.items ,0), Closed});
    editHCourse(getHCourse(*hcourseList, "CTESP000"), (HCOURSE) { CTeSP, "CTESP000", "Curso de Teste Alterado", 2, getArea(areaList.items, 21), getUnit(unitList.items ,0), Closed});
    listHCoursesByUnit(*hcourseList, 0);
    listHCoursesAsc(*hcourseList);

    printf("\033[1;31mThis text is red.\033[0m\n");
    printf("\033[1;32mThis text is green.\033[0m\n");
    printf("\033[1;34mThis text is blue.\033[0m\n");
}

void enrollApplicant(ELEM **listHeader, APPLICANT *newApplicant, eState applicationsState){
    if(applicationsState == Open){
        if(newApplicant->applicationStatus == Pending){
            newApplicant->applicationStatus = Enrolled;
            //if(!applicationExists(listHeader, *newApplicant))
            addApplication(listHeader, *newApplicant); 
        }
    }
}

void admMenuOpt1(HCOURSELIST *hcourseList, AREALIST areaList, UNITLIST unitList, eState applicationsState){
    if(applicationsState == Open){
        printf("\n > "); printColored("Não pode fazer alterações no período de candidaturas abertas!", Red, 0); _pause();
        return;
    }

    HCOURSE newHcourse = {0};

    newHcourseConstructionDialog(hcourseList, areaList, unitList, &newHcourse);

    printf("| Finalizar criação do curso? (S/n): ");
    char opt = '\0';
    opt = getchar();
    if(opt == 's' || opt == 'S'){
        addHCourse(hcourseList, newHcourse);
        printf("\n > "); printColored("Curso criado com sucesso!", Green, 0); _pause();
    }
    clearBuffer();
}

void admMenuOpt2(HCOURSELIST *hcourseList, AREALIST areaList, UNITLIST unitList, eState applicationsState){
    HCOURSE newHcourse = {0};
    unsigned short validInput = 0;
    unsigned char code[CODE_MAX_CHAR] = {0};

    if(applicationsState == Open){
        printf("\n > "); printColored("Não pode fazer alterações no período de candidaturas abertas!", Red, 0); _pause();
        return;
    }
    while(!validInput){
        clearScreen();
        listHCourses(*hcourseList);
        printf("| Código do curso a alterar: ");
        fgets(newHcourse.code, CODE_MAX_CHAR + 1, stdin);
        newHcourse.code[strcspn(newHcourse.code, "\n")] = '\0';
        stringToUpper(newHcourse.code);
        if(!isValidHCourse(*hcourseList, newHcourse.code)){
            printf("\n > "); printColored("O código não existe!", Red, 0); _pause();
        }else{
            validInput = 1;
            strcpy(code, newHcourse.code);
        }
    }

    newHcourseConstructionDialog(hcourseList, areaList, unitList, &newHcourse);

    printf("| Finalizar alteração do curso? (S/n): ");
    char opt = '\0';
    opt = getchar();
    if(opt == 's' || opt == 'S'){
        editHCourse(getHCourse(*hcourseList, code), newHcourse);
        printf("\n > "); printColored("Curso alterado com sucesso!", Green, 0); _pause();
    }
    clearBuffer();

}

void admMenuOpt3(HCOURSELIST *hcourseList, eState applicationsState){
    if(applicationsState == Open){
        printf("\n > "); printColored("Não pode fazer alterações no período de candidaturas abertas!", Red, 0); _pause();
        return;
    }

    unsigned char code[CODE_MAX_CHAR] = {0};
    unsigned short validInput = 0;

    while(!validInput){
        clearScreen();
        listHCourses(*hcourseList);
        printf("| Código: ");
        fgets(code, CODE_MAX_CHAR + 1, stdin);

        code[strcspn(code, "\n")] = '\0';
        stringToUpper(code);
        if(!isValidHCourse(*hcourseList, code)){
            printf("\n > "); printColored("O código não existe!", Red, 0); _pause();
        }else validInput = 1;
    }
    changeHCourseState(getHCourse(*hcourseList, code));
}

void admMenuOpt5(HCOURSELIST hcourseList, UNITLIST unitList){
    unsigned id = 0;
    unsigned validInput = 0;
    while(!validInput){
        clearScreen();
        listUnits(unitList);
        printf("| ID: ");
        scanf(" %d", &id);
        clearBuffer();
        if(id > unitList.count - 1){
            printf("\n > "); printColored("ID inválido!", Red, 0); _pause();
            validInput = 0;
        }else{
            clearScreen();
            listHCoursesByUnit(hcourseList, id);
            _pause();
            validInput = 1;
        }
    }
}

void admMenuOpt6(ELEM *listHeader, HCOURSELIST hcourseList){
    if(listHeader == NULL){
        printf("\n > "); printColored("De momento não existem candidaturas.", Red, 0); _pause(); return;
    }
    unsigned char code[CODE_MAX_CHAR] = {0};
    unsigned short validInput = 0;

    clearScreen();
    listHCourses(hcourseList);
    printf("| Código: ");
    fgets(code, CODE_MAX_CHAR + 1, stdin);
    code[strcspn(code, "\n")] = '\0';
    stringToUpper(code);
    if(!isValidHCourse(hcourseList, code)){
        printf("\n > "); printColored("O código não existe!", Red, 0); _pause();
    }else{
        validInput = 1;
        clearScreen();
        for(ELEM *aux = listHeader; aux != NULL; aux = aux->next){
            if(strcmp(code, aux->info.hcourseCode) == 0){
                displayApplicationInfo(aux->info, hcourseList);
                printf("\n-----------\n");
            }
        }
        _pause();
    }
}

void admMenuOpt7(eState *applicationsState){
    if(*applicationsState == Open){
        *applicationsState = Closed;
        printf("\n > "); printColored("As candidaturas estão agora fechadas!", Red, 0); _pause();
    }else{
        *applicationsState = Open;
        printf("\n > "); printColored("As candidaturas estão agora abertas!", Green, 0); _pause();
    }
}

void admMenuOpt8(ELEM *listHeader, HCOURSELIST hcourseList){
    if(listHeader == NULL){
        printf("\n > "); printColored("De momento não existem candidaturas.", Red, 0); _pause(); return;
    }
    char opc[2] = {0};
    do{
        clearScreen();
        printf(
        "\n+---------------------------------+"
        "\n     IMPRIMIR INFORMAÇÃO"
        "\n+---------------------------------+"
        "\n\n\n"
        "\n [1] Imprimir lista de candidatos"
        "\n [2] Imprimir lista de colocados a um curso"
        "\n [3] Imprimir lista de colocados numa escola"
        "\n [:]"
        "\n [0] Voltar ao menu principal"
        "\n\n > "
        );

        inputNumber(opc, 2);

        switch(opc[0]){
            case '1': // IMPRIMIR LISTA DE CANDIDATOS
                for(ELEM *aux = listHeader; aux != NULL; aux = aux->next) printApplicationState(aux->info, hcourseList);
                printColored("\Informação adicionada: output/applications.txt!", Green, 0);
                _pause();
                break;
            case '2': // IMPRIMIR LISTA DE CANDIDATOS A UM CURSO
                unsigned char code[CODE_MAX_CHAR] = {0};
                unsigned short validInput = 0;

                clearScreen();
                listHCourses(hcourseList);
                printf("| Código: ");
                fgets(code, CODE_MAX_CHAR + 1, stdin);
                code[strcspn(code, "\n")] = '\0';
                stringToUpper(code);
                if(!isValidHCourse(hcourseList, code)){
                    printf("\n > "); printColored("O código não existe!", Red, 0); _pause();
                }else{
                    validInput = 1;
                    for(ELEM *aux = listHeader; aux != NULL; aux = aux->next){
                        if(strcmp(code, aux->info.hcourseCode) == 0 && aux->info.applicationStatus == Accepted){
                            printApplicationStateByCourse(aux->info, hcourseList);
                            printf("\n-----------\n");
                        }
                    }
                    _pause();
                }
                break;
            case '3': //IMPRIMIR LISTA DE COLOCADOS NUMA ESCOLA
                break;
        }
    }while(opc[0] != '0');
}

void newHcourseConstructionDialog(HCOURSELIST *hcourseList, AREALIST areaList, UNITLIST unitList, HCOURSE *newHcourse){
        unsigned int validInput = 0;

    while(!validInput){
        clearScreen();
        listHCoursesAsc(*hcourseList);
        printf("| Novo código: ");
        fgets(newHcourse->code, CODE_MAX_CHAR + 1, stdin);
        newHcourse->code[strcspn(newHcourse->code, "\n")] = '\0';
        stringToUpper(newHcourse->code);
        if(isValidHCourse(*hcourseList, newHcourse->code)){
            printf("\n > "); printColored("O código já existe!", Red, 0); _pause();
        }else validInput = 1;
    }
    do{
        printf("| Descrição: ");
        fgets(newHcourse->description, DESCRIPTION_MAX_CHAR + 1, stdin);
        newHcourse->description[strcspn(newHcourse->description, "\n")] = '\0';
        if(newHcourse->description[0] == '\0'){
            printf("\n > "); printColored("Preenchimento obrigatório!", Red, 0); _pause();
            validInput = 0;
        }else validInput = 1;
    }while(!validInput);
    do{
        clearScreen();
        listAreas(areaList);
        printf("| Área (ID): ");
        scanf(" %d", &newHcourse->area.id);
        clearBuffer();
        if(newHcourse->area.id > areaList.count - 1){
            printf("\n > "); printColored("ID inválido!", Red, 0); _pause();
            validInput = 0;
        }else{
            newHcourse->area = getArea(areaList.items, newHcourse->area.id);
            validInput = 1;
        }
    }while(!validInput);
    do{
        clearScreen();
        listUnits(unitList);
        printf("| Unidade Orgânica (ID): ");
        fscanf(" %d", &newHcourse->school.id);
        clearBuffer();
        if(newHcourse->school.id > unitList.count - 1){
            printf("\n > "); printColored("ID inválido!", Red, 0); _pause();
            validInput = 0;
        }else{
            validInput = 1;
            newHcourse->school = getUnit(unitList.items, newHcourse->school.id);
        }
    }while(!validInput);

    clearScreen();
    listHCoursesAsc(*hcourseList);
    printf("| Vagas disponíveis: ");
    scanf(" %d", &newHcourse->slots);
    clearBuffer();

    newHcourse->state = Closed;
    clearScreen();
    listHCourses(*hcourseList);
    printf(
        "| %-9s | ",
        newHcourse->code
    );
    printFixedWidth(newHcourse->description, ' ', 46); 
    printf(" | ");
    printFixedWidth(newHcourse->area.description, ' ', 34); 
    printf(
        " | %-6s | ",
        newHcourse->school.acronym
    );
    printf(
        "%-6d | "
        , newHcourse->slots
    );   
    newHcourse->state == Open ? printColored("Open", Green, 6) : printColored("Closed", Red, 6);
    newHcourse->slots = 2;
    
    printf("|\n");
    printf("+-----------+-------------------------------------------------+-------------------------------------+--------+--------+--------+\n");
}