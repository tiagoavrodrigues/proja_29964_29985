#include <stdio.h>
#include "include/org.h"

#define UNIT_ELEMENT_QUANTITY 6

UNITLIST createUnitList(){
    static const UNIT units[UNIT_ELEMENT_QUANTITY] = {
        { 0, "ESTG", "Escola Superior de Tecnologia e Gestão" },
        { 1, "ESS", "Escola Superior de Saúde" },
        { 2, "ESE", "Escola Superior de Educação" },
        { 3, "ESDL", "Escola Superior de Desporto e Lazer" },
        { 4, "ESA", "Escola Superior Agrária"},
        { 5, "ESCE", "Escola Superior de Ciências Empresariais"}
    };
    return (UNITLIST) {UNIT_ELEMENT_QUANTITY, (UNIT *) units};
}

UNIT* getUnit(UNITLIST *unitList ,unsigned short id){
/*     if(unitList == NULL || id >= unitList->count || unitList->items == NULL){
        return NULL;
    } */

}

const char* getUnitAcronym(UNITLIST *unitList, unsigned short id){
    if(unitList == NULL || id >= unitList->count || unitList->items == NULL){
        return NULL;
    }
    return unitList->items[id].acronym;
}

char getUnitDesignation(unsigned short id){

}

void listUnits(UNITLIST *unitList){
    if(unitList == NULL || !unitList->count || unitList->items == NULL) {
        return;
    }

    printf(
        "+-----+----------+------------------------------------------+\n"
        "| ID  | Acronym  | Designation                               \n"
        "+-----+----------+------------------------------------------+\n"
    );
    for (unsigned short i = 0; i < unitList->count; i++) {
        printf(
            "| %3d | %-8.8s | %-42.42s  \n",
            unitList->items[i].id,
            unitList->items[i].acronym,
            unitList->items[i].designation
        );
    }
    printf("+-----+----------+------------------------------------------+\n");
    return;
}