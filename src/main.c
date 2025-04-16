#include <stdio.h>
#include <locale.h>

#include "include/utils.h"
#include "include/course.h"

int main(int argc, char *argv[]){
    setlocale(LC_ALL, "");

    clearScreen();
    AREALIST areaList = createAreaList();
    listAreas(&areaList);
    return 0;
}