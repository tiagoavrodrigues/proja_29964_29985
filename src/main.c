#include <stdio.h>
#include <locale.h>

#include "include/utils.h"
#include "include/course.h"
#include "include/text.h"
#include "include/user.h"

int main(int argc, char *argv[]){
    setlocale(LC_ALL, "");

    #ifdef _WIN32
    enableANSI();  // ANSI CODES PARA TEXTO COLORIDO NA LINHA DE COMANDOS DO WINDOWS
    #endif

    clearScreen();
    AREALIST areaList = createAreaList();
    UNITLIST unitList = createUnitList();
    HCOURSELIST hcourseList = {};

    USERLIST userList = createUserList();

    if(loadHCourseData(&hcourseList) < 0) hcourseList = createHCourseList(areaList.items, unitList.items);

    if(hcourseList.items == NULL){
        printf("\nOut of memory!\n");
        return -1;
    }

    listAreas(&areaList);
    listUnits(&unitList);
    listHCourses(&hcourseList);
    setHCourseState(getHCourse(&hcourseList, "CTESP001"), Closed);
    addHCourse(&hcourseList, (HCOURSE) { CTeSP, "CTESP000", "Curso de Teste", *getArea(areaList.items, 21), *getUnit(unitList.items ,0), Closed});
    editHCourse(getHCourse(&hcourseList, "CTESP000"), (HCOURSE) { CTeSP, "CTESP000", "Curso de Teste Alterado", *getArea(areaList.items, 21), *getUnit(unitList.items ,0), Closed});
    listHCoursesByUnit(&hcourseList, 0);
    listHCoursesAsc(&hcourseList);

    saveHCourseData(&hcourseList);

    printf("\033[1;31mThis text is red.\033[0m\n");
    printf("\033[1;32mThis text is green.\033[0m\n");
    printf("\033[1;34mThis text is blue.\033[0m\n");

    free(userList.users);
    free(hcourseList.items);

    return 0;
}