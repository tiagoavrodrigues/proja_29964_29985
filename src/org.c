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

UNIT getUnit(unsigned short id){

}

const char* getUnitAcronym(UNITLIST *unitList, unsigned short id){
    if(id > unitList->count || !unitList->items){
        return NULL;
    }
    return unitList->items[id].acronym;
}

char getUnitDesignation(unsigned id){

}