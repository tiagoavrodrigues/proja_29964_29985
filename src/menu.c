#include <stdio.h>
#include <string.h>
#include "include/menu.h"
#include "include/utils.h"
#include "include/user.h"
#include "include/interface_utils.h"

void drawLoginUsername(){
    printf("\n");
    printf(
        "+--------------------------------------+\n"
        "|             LOGIN MENU               |\n"
        "+--------------------------------------+\n"
        "| USERNAME: "
    );
}

void drawLoginPassword(char username[]){
    printf("\n");
    printf(
        "+--------------------------------------+\n"
        "|             LOGIN MENU               |\n"
        "+--------------------------------------+\n"
        "| USERNAME: %s\n"
        "| PASSWORD: ",
        username
    );
}

short loginForm(USERLIST userList, USER *loggedUser){
    char username[USERNAME_MAX_CHAR];
    char password[PASSWORD_MAX_CHAR];

    clearScreen();
    drawLoginUsername();

    fgets(username, USERNAME_MAX_CHAR, stdin);
    username[strcspn(username, "\n")] = '\0';
    if(!userExists(userList, username)){
        char opt;
        printf("\n\n > "); printColored("O utilizador não existe! Deseja criar?\n", Yellow, 0);
        opt = getchar();
        if(opt == 'S' || opt == 's') registerUserInfoForm(); else return -1;
    }

    short result;
    do{
        clearScreen();
        drawLoginPassword(username);
        inputPasswordMask(password);

        USER tempUser = {Applicant};

        strcpy(tempUser.username, username);
        strcpy(tempUser.password, password);
        
        result = authenticateUser(userList, tempUser);

        switch(result){
            case 0: printf("\n > "); printColored("Password inválida! ", Red, 0); _pause(); break;
            case 1: *loggedUser = (USER) { Admin, username, password }; break;
            case 2: *loggedUser = (USER) { Applicant, username, password }; break;
            default: printf("\n > "); printColored("Ocorreu um erro! ", Red, 0); _pause(); break;
        }
    }while(result < 1);

    return 0;
}

void registerUserInfoForm(){
    APPLICANT newApplicant = {};
    
    unsigned short validInput = 0;

    while(validInput == 0){
        validInput = 1;
        clearScreen();
        printf(
            "+------------------------------------------------+\n"
            "|     FORMULÁRIO DE REGISTO - PARTE [1 / 2]      |\n"
            "+------------------------------------------------+\n"
        );
        printf("| Primeiro nome: %s%c", newApplicant.name[0] == '\0' ? "" : newApplicant.name, newApplicant.name[0] == '\0' ? "" : "\n" );
        if(newApplicant.name[0] == '\0'){
            clearBuffer();
            fgets(newApplicant.name, NAME_MAX_CHAR, stdin);
            newApplicant.name[strcspn(newApplicant.name, "\n")] = '\0';
        };
        printf("| Último nome: %s%c", newApplicant.surname[0] == '\0' ? "" : newApplicant.surname, newApplicant.surname[0] == '\0' ? "" : "\n" );
        if(newApplicant.surname[0] == '\0'){
            fgets(newApplicant.surname, NAME_MAX_CHAR, stdin);
            newApplicant.surname[strcspn(newApplicant.surname, "\n")] = '\0';
        };
        printf("| Número de CC: %s%c", newApplicant.nCC[0] == '\0' ? "" : newApplicant.nCC, newApplicant.nCC[0] == '\0' ? "" : "\n" );
        if(newApplicant.nCC[0] == '\0'){
            clearBuffer();
            inputNumber(newApplicant.nCC, NCC_MAX_CHAR);
            if(strlen(newApplicant.nCC) < NCC_MAX_CHAR){
                printf("\n\n > "); printColored("O número de CC não é válido!\n", Red, 0); _pause();
                newApplicant.nCC[0] = '\0';
                validInput = 0;
            }
        }
        if(validInput == 1){
            printf("| NIF:  %s", newApplicant.nif[0] == '\0' ? "" : newApplicant.nif);
            if(newApplicant.nif[0] == '\0'){
                inputNumber(newApplicant.nif, NIF_MAX_CHAR);
                if(strlen(newApplicant.nif) < NIF_MAX_CHAR){
                    printf("\n\n > "); printColored("O NIF não é válido!\n", Red, 0); _pause();
                    newApplicant.nif[0] = '\0';
                    validInput = 0;
                }
            }
        }
        if(validInput == 1){
            printf("| Data de nascimento "); printColored("(dd/mm/aaaa): ", Yellow, 0);
            scanf("%2d/%2d/%4d", &newApplicant.dateofbirth.day, &newApplicant.dateofbirth.month, &newApplicant.dateofbirth.year);
            validInput = isValidDate(newApplicant.dateofbirth.day, newApplicant.dateofbirth.month, newApplicant.dateofbirth.year);
            if(validInput == 0){
                printf("\n\n > "); printColored("A data não é válida!\n", Red, 0); _pause();
            }
        }
    }
    while(validInput == 0){
        validInput = 1;
        clearScreen();
        printf(
            "+------------------------------------------------+\n",
            "|     FORMULÁRIO DE REGISTO - PARTE [2 / 2]      |\n",
            "+------------------------------------------------+\n"
        );
        printf("\n| Escola frequentada: %s", newApplicant.school[0] == '\0' ? "" : newApplicant.school[0]);
        fgets(newApplicant.school, SCHOOL_MAX_CHAR, stdin);
        newApplicant.school[strcspn(newApplicant.school, "\n")] = '\0';
        printf("\n| Média de fim de ano: ");
        scanf(" %f", &newApplicant.mean);
        if(newApplicant.mean < 0 && newApplicant.mean > 20){
            printf("\n\n > "); printColored("Valor inválido! O valor deverá ser entre 0 e 20.", Red, 0); _pause();
            validInput = 0;
        }


    }
}