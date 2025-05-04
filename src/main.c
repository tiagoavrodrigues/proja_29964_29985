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

void test();

int main(int argc, char *argv[]){
    setlocale(LC_ALL, "");

    #ifdef _WIN32
    enableANSI();  // ANSI CODES PARA TEXTO COLORIDO NA LINHA DE COMANDOS DO WINDOWS
    #endif

    USERLIST userList = {};
    if(loadUserData(&userList) < 0) userList = createUserList();

    USER loggedUser = {};

    clearScreen();

    loginForm(userList, &loggedUser);

    clearScreen();
    
    AREALIST areaList = {};
    UNITLIST unitList = {};
    HCOURSELIST hcourseList = {};
    APPLICANTLIST applicantList = {};

    initMemory(&areaList, &unitList, &hcourseList, &applicantList);
    
    char* opt[2] = { "A", "B" };

    menuSelect(opt, 0, "wW", "sS", 2, "*", "", ' ', CLEAR);
    
    test(areaList, unitList, &hcourseList, &applicantList);

    saveMemory(userList, hcourseList, applicantList);

    free(userList.users);
    free(hcourseList.items);

    return 0;
}

void test(AREALIST areaList, UNITLIST unitList, HCOURSELIST *hcourseList, APPLICANTLIST *applicantList){
    listAreas(areaList);
    listUnits(unitList);
    listHCourses(*hcourseList);
    setHCourseState(getHCourse(*hcourseList, "CTESP001"), Closed);
    addHCourse(hcourseList, (HCOURSE) { CTeSP, "CTESP000", "Curso de Teste", getArea(areaList.items, 21), getUnit(unitList.items ,0), Closed});
    editHCourse(getHCourse(*hcourseList, "CTESP000"), (HCOURSE) { CTeSP, "CTESP000", "Curso de Teste Alterado", getArea(areaList.items, 21), getUnit(unitList.items ,0), Closed});
    listHCoursesByUnit(*hcourseList, 0);
    listHCoursesAsc(*hcourseList);

    printf("\033[1;31mThis text is red.\033[0m\n");
    printf("\033[1;32mThis text is green.\033[0m\n");
    printf("\033[1;34mThis text is blue.\033[0m\n");
}