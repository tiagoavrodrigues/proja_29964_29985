#include <stdio.h>
#include <string.h>
#include "include/menu.h"
#include "include/utils.h"
#include "include/user.h"
#include "include/interface_utils.h"
#include "include/course.h"
#include "include/applicant.h"

void drawLoginUsername(){
    printf("\n");
    printf(
        "+--------------------------------------+\n"
        "|        MENU DE AUTENTICAÇÃO          |\n"
        "+--------------------------------------+\n"
        "| USERNAME: "
    );
}

void drawLoginPassword(char username[]){
    printf("\n");
    printf(
        "+--------------------------------------+\n"
        "|        MENU DE AUTENTICAÇÃO          |\n"
        "+--------------------------------------+\n"
        "| USERNAME: %s\n"
        "| PASSWORD: ",
        username
    );
}

void drawNewPassword(char username[]){
    printf("\n");
    printf(
        "+--------------------------------------+\n"
        "|   POR FAVOR DEFINA A PALAVRA-CHAVE   |\n"
        "+--------------------------------------+\n"
        "| USERNAME: %s\n"
        "| PASSWORD: ",
        username
    );
}



short loginForm(USERLIST *userList, USER *loggedUser, AREALIST areaList, HCOURSELIST hcourseList, APPLICANT *currentApplicant, APPLICANTLIST *applicantList, ELEM **listHeader){
    char username[USERNAME_MAX_CHAR];
    char password[PASSWORD_MAX_CHAR];
    short newRegistration = 0;
    APPLICANT newApplicant = {0};

    clearScreen();
    drawLoginUsername();

    fgets(username, USERNAME_MAX_CHAR, stdin);
    username[strcspn(username, "\n")] = '\0';
    if(!userExists(*userList, username)){
        char opt;
        printf("\n\n > "); printColored("O utilizador não existe! Deseja criar? (S/n)\n", Yellow, 0);
        opt = getchar();
        if(opt == 'S' || opt == 's') {
            registerUserInfoForm(areaList, &newApplicant, hcourseList, Registration);
            newRegistration = 1;
        } else return -1;
    }
    if(newRegistration){
        clearBuffer();
        clearScreen();
        drawNewPassword(username);
        inputPasswordMask(password);
        newApplicant.user.type = Applicant;
        strcpy(newApplicant.user.username, username);
        strcpy(newApplicant.user.password, password);
        *loggedUser = newApplicant.user;
        addUser(userList, newApplicant.user);
        //*loggedUser = newApplicant.user = (USER) {Applicant, &username, &password}; não funca assim
        printColored("\n > Conta criada com sucesso.", Green, 0);
        *currentApplicant = newApplicant;
        addApplicant(applicantList, newApplicant);
        //addApplication(listHeader, newApplicant);
        int abc = 1;
    }
    short result;

    if(!newRegistration){
        do{
            clearScreen();
            drawLoginPassword(username);
            inputPasswordMask(password);

            USER tempUser = {Applicant};

            strcpy(tempUser.username, username);
            strcpy(tempUser.password, password);
            
            result = authenticateUser(*userList, tempUser);

            switch(result){
                case 0: printf("\n > "); printColored("Password inválida! ", Red, 0); _pause(); break;
                case 1: loggedUser->type = Admin; break;  
                case 2: loggedUser->type = Applicant; break;
                default: printf("\n > "); printColored("Ocorreu um erro! ", Red, 0); _pause(); break;
            }
            strcpy(loggedUser->username, username);
            strcpy(loggedUser->password, password);
        }while(result < 1);
        if(loggedUser->type == Applicant){
            currentApplicant->user = *loggedUser;
            getApplicantInfo(currentApplicant, *applicantList);
        }
    }
    return 0;
}

void registerUserInfoForm(AREALIST areaList, APPLICANT *newApplicant, HCOURSELIST hcourseList, eRegistrationType registrationType){
    newApplicant->mean = -1;
    newApplicant->dateofbirth.day = 0;
    newApplicant->dateofbirth.month = 0;
    newApplicant->dateofbirth.year = 0;    
    newApplicant->course.area.id = 99;

    unsigned short validInput = 0;

    clearBuffer();

    while(!validInput){
        validInput = 1;
        clearScreen();
        printf(
            "+------------------------------------------------+\n"
            "|     FORMULÁRIO DE REGISTO - PARTE [1 / 2]      |\n"
            "+------------------------------------------------+\n"
        );
        if(validInput){
            printf("| Primeiro nome: %s%s"
                , newApplicant->name[0] == '\0' ? "" : newApplicant->name
                , newApplicant->name[0] == '\0' ? "" : "\n" 
            );
            if(newApplicant->name[0] == '\0'){
                fgets(newApplicant->name, NAME_MAX_CHAR, stdin);
                newApplicant->name[strcspn(newApplicant->name, "\n")] = '\0';
            };
            if(newApplicant->name[0] == '\0'){
                printf("\n > "); printColored("Preenchimento obrigatório!", Red, 0); _pause();
                validInput = 0;
            }
        }
        if(validInput){
            printf("| Último nome: %s%s"
                , newApplicant->surname[0] == '\0' ? "" : newApplicant->surname
                , newApplicant->surname[0] == '\0' ? "" : "\n"
            );
            if(newApplicant->surname[0] == '\0'){
                fgets(newApplicant->surname, NAME_MAX_CHAR, stdin);
                newApplicant->surname[strcspn(newApplicant->surname, "\n")] = '\0';
            };
            if(newApplicant->surname[0] == '\0'){
                printf("\n > "); printColored("Preenchimento obrigatório!", Red, 0); _pause();
                validInput = 0;
            }
        }
        if(validInput){
            printf("| Número de CC: %s", newApplicant->nCC[0] == '\0' ? "" : newApplicant->nCC);

            if(newApplicant->nCC[0] == '\0'){
                inputNumber(newApplicant->nCC, NCC_MAX_CHAR);
                if(strlen(newApplicant->nCC) < NCC_MAX_CHAR - 1){
                    printf("\n > "); printColored("O número de CC não é válido!\n", Red, 0); _pause();
                    newApplicant->nCC[0] = '\0';
                    validInput = 0;
                }
            }
        }
        if(validInput){
            printf(
                "\n| NIF: %s", newApplicant->nif[0] == '\0' ? "" : newApplicant->nif);
            if(newApplicant->nif[0] == '\0'){
                inputNumber(newApplicant->nif, NIF_MAX_CHAR);
                if(strlen(newApplicant->nif) < NIF_MAX_CHAR - 1){
                    printf("\n > "); printColored("O NIF não é válido!\n", Red, 0); _pause();
                    newApplicant->nif[0] = '\0';
                    validInput = 0;
                }
            }
        }
        if(validInput){
            printf("\n| Data de nascimento "); printColored("(dd/mm/aaaa): ", Green, 0);
            scanf("%2d/%2d/%4d", &newApplicant->dateofbirth.day, &newApplicant->dateofbirth.month, &newApplicant->dateofbirth.year);
            validInput = isValidDate(newApplicant->dateofbirth.day, newApplicant->dateofbirth.month, newApplicant->dateofbirth.year);
            clearBuffer();
            if(validInput = 0){
                printf("\n > "); printColored("A data não é válida!\n", Red, 0); _pause();
            }else validInput = 1;
        }
    }
    do{
        validInput = 1;
        clearScreen();
        printf(
            "+------------------------------------------------+\n"
            "|     FORMULÁRIO DE REGISTO - PARTE [2 / 2]      |\n"
            "+------------------------------------------------+\n"
        );

        printf("| Escola frequentada: %s%s"
            , newApplicant->school[0] == '\0' ? "" : newApplicant->school
            , newApplicant->school[0] == '\0' ? "" : "\n"
        );

        if(newApplicant->school[0] == '\0'){
            fgets(newApplicant->school, SCHOOL_MAX_CHAR, stdin);
            newApplicant->school[strcspn(newApplicant->school, "\n")] = '\0';
        }
        if(newApplicant->school[0] == '\0'){
            printf("\n > "); printColored("Preenchimento obrigatório!", Red, 0); _pause();
            validInput = 0;
        }
        if(validInput){
            if (newApplicant->mean >= 0 && newApplicant->mean <= 20) {
                printf("| Média de fim de ano: %.2f\n", newApplicant->mean);
            } else {
                printf("| Média de fim de ano: ");
            }
            if((newApplicant->mean < 0 || newApplicant->mean > 20)){
                scanf(" %f", &newApplicant->mean);
                clearBuffer();
            }
            if(newApplicant->mean < 0 || newApplicant->mean > 20){
                printf("\n > "); printColored("Valor inválido! O valor deverá ser entre 0 e 20.", Red, 0); _pause();
                validInput = 0;
            }
        }
        if(validInput){
            printf("| Curso frequentado: ");
            fgets(newApplicant->course.description, DESCRIPTION_MAX_CHAR, stdin);
            newApplicant->course.description[strcspn(newApplicant->course.description, "\n")] = '\0';
            if(newApplicant->course.description[0] == '\0'){
                printf("\n > "); printColored("Preenchimento obrigatório!", Red, 0); _pause();
                validInput = 0;
            }else validInput = 1;
        }
    }while(!validInput);
    do{
        clearScreen();
        listAreas(areaList);
        printf("| Área do curso "); printColored("(ID)", Green, 0); printf(": ");
        scanf(" %d", &newApplicant->course.area.id);
        clearBuffer();
        if(newApplicant->course.area.id > areaList.count - 1){
            printf("\n > "); printColored("ID inválido!", Red, 0); _pause();
            validInput = 0;
        }else{
            validInput = 1;
            newApplicant->course.area = getArea(areaList.items, newApplicant->course.area.id);
        }
    }while(!validInput);
    do{
        unsigned char code[CODE_MAX_CHAR] = {0};
        clearScreen();
        listOpenHCourses(hcourseList);
        printf("| Curso a candidatar "); printColored("(COD)", Green, 0); printf(": ");
        fgets(code, CODE_MAX_CHAR + 2, stdin);
        code[strcspn(code, "\n")] = '\0';
        stringToUpper(code);
        if(!isValidHCourse(hcourseList, code)){
            printf("\n > "); printColored("Código inválido!", Red, 0); _pause();
            validInput = 0;
        }else{
            validInput = 1;
            strcpy(newApplicant->hcourseCode, code);
        }
    }while(!validInput);
    if(registrationType == Registration)
        do{
            unsigned char confirmation;
            clearScreen();
            printFilledForm(*newApplicant, hcourseList, Confirmation);
            printf("\n > Confirmar formulário e definir palavra-chave? (S/n): ");
            scanf(" %c", &confirmation);
            if(confirmation == 's' || confirmation == 'S') return;
            if(confirmation == 'n' || confirmation == 'N') {registerUserInfoForm(areaList, newApplicant, hcourseList, Registration); validInput = 1;}
        }while(!validInput)
    ;

}

void printFilledForm(APPLICANT newApplicant, HCOURSELIST hcourseList, eFormType formType){
    if(formType == Confirmation){
        printf(
            "\n\n"
            "+------------------------------------------------+\n"
            "|       FORMULÁRIO DE REGISTO - CONFIRMAÇÃO      |\n"
            "+------------------------------------------------+\n"
        );
    }else{
        printf(
            "\n\n"
            "+------------------------------------------------+\n"
            "|            INFORMAÇÃO DE CANDIDATURA           |\n"
            "+------------------------------------------------+\n"
        );        
    }
    printf(
        "| Primeiro nome: %s\n"
        "| Último nome: %s\n"
        "| Número de CC: %s\n"
        "| NIF: %s\n"
        "| Data de nascimento %d/%d/%d\n"
        "| Média de fim de ano: %.2f\n"
        "| Curso frequentado: %s\n"
        "| Área do curso: %s\n"
        "| Candidato a: %s - %s\n"
        , newApplicant.name
        , newApplicant.surname
        , newApplicant.nCC
        , newApplicant.nif
        , newApplicant.dateofbirth.day , newApplicant.dateofbirth.month, newApplicant.dateofbirth.year
        , newApplicant.mean
        , newApplicant.school
        , newApplicant.course.area.description
        , newApplicant.hcourseCode
        , getHCourse(hcourseList, newApplicant.hcourseCode)->description
    );
    printf( "| Estado: ");
    switch (newApplicant.applicationStatus){
        case Pending: printColored("Pendente", Yellow, 0); break;
        case Enrolled: printColored("Inscrito", Blue, 0); break;
        case Accepted: printColored("Aceite", Green, 0); break;
        case Rejected: printColored("Rejeitada", Red, 0);
    }
    printf("\n+-------------------------------------------------+\n");
};

void drawUserMenu(APPLICANT currentApplicant, eState applicationsState){
    printf(
        "\n+----------------------------------------+"
        "\n        BEM VINDO, %s %s"
        "\n+----------------------------------------+"
        "\n\n\n"
        , currentApplicant.name, currentApplicant.surname
    );
    printf("\n ESTADO DAS CANDIDATURAS: [  ");
    switch(applicationsState){
        case Open: printColored("ABERTAS", Green, 9); break;
        case Closed: printColored("FECHADAS", Red, 6);break;
    }
    printf("]");
    printf("\n ESTADO DA COLOCAÇÃO: [  ");
    switch(currentApplicant.applicationStatus){
        case Pending: printColored("PENDENTE", Yellow, 9); break;
        case Enrolled: printColored("INSCRITO", Blue, 9); break;
        case Accepted: printColored("ACEITE", Green, 6);break;
        case Rejected: printColored("REJEITADA", Yellow, 9);break;
    }
    printf("]");
    printf(
        "\n [1] Listar informação sobre a candidatura"
        "\n [2] Alterar informação"
        "\n [3] Imprimir Informação"
        "\n [:]"
        "\n [0] Sair"
        "\n\n > "
    );
}

void drawAdminMenu(eState *applicationsState){
        printf(
        "\n+---------------------------------+"
        "\n      PAINEL ADMINISTRATIVO"
        "\n+---------------------------------+"
        "\n\n\n"
    );
    printf("\n ESTADO DAS CANDIDATURAS: [  ");
    switch(*applicationsState){
        case Open: printColored("ABERTAS", Green, 9); break;
        case Closed: printColored("FECHADAS", Red, 9);break;
    }
    printf("]");
    printf(
        "\n [1] Acrescentar curso"
        "\n [2] Alterar informação de curso"
        "\n [3] Abrir/fechar curso"
        "\n [4] Listar cursos (A-Z)"
        "\n [5] Listar cursos de uma escola"
        "\n [6] Listar candidatos a um curso"
        "\n [7] Abrir/Fechar candidaturas"
        "\n [8] Imprimir Informação"
        "\n [9] Análise de candidaturas"
        "\n [:]"
        "\n [0] Sair"
        "\n\n > "
    );
}