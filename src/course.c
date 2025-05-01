#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "include/course.h"
#include "include/org.h"
#include "include/utils.h"

AREALIST createAreaList(){

    static const AREA items[AREA_ITEM_QUANTITY] = {
        { 0, "Artes" },
        { 1, "Humanidades" },
        { 2, "Ciências Sociais e do Comportamento" },
        { 3, "Informação e Jornalismo" },
        { 4, "Ciências Empresariais" },
        { 5, "Direito" },
        { 6, "Ciências da Vida" },
        { 7, "Ciências Físicas" },
        { 8, "Matemática e Estatística" },
        { 9, "Informática" },
        { 10, "Engenharia e Técnicas Afins" },
        { 11, "Indústrias Transformadoras" },
        { 12, "Arquitetura e Construção" },
        { 13, "Agricultura, Silvicultura e Pescas" },
        { 14, "Ciências Veterinárias" },
        { 15, "Saúde" },
        { 16, "Serviços Sociais" },
        { 17, "Serviços Pessoais" },
        { 18, "Serviços de Transporte" },
        { 19, "Proteção do Ambiente" },
        { 20, "Serviços de Segurança" },
        { 21, "Desconhecido ou não especificado" }
    };

    return (AREALIST) {AREA_ITEM_QUANTITY, (AREA *)items};
}

AREA* getArea(AREA *areas, unsigned short id){
    if(areas == NULL || id >= AREA_ITEM_QUANTITY) return NULL;

    return &areas[id];
}

void listAreas(AREALIST *areaList){
    if(areaList == NULL || !areaList->count || areaList->items == NULL){
        return;
    }
    printf(
        "+-----+--------------------------------------------+\n"
        "| ID  | Area Description                           |\n"
        "+-----+--------------------------------------------+\n"
    );
    for (unsigned short i = 0; i < areaList->count; i++) {
        printf(
            "| % 3d | ",
            areaList->items[i].id,
            areaList->items[i].description
        );
        printFixedWidth(areaList->items[i].description, ' ', 42);
        printf("|\n");
    }
    printf("+-----+--------------------------------------------+\n");
}

HCOURSELIST createHCourseList(AREA *areas, UNIT *units) {
    HCOURSE *hcourses = (HCOURSE *) calloc(HCOURSE_ITEM_QUANTITY, sizeof(HCOURSE));

    if(hcourses == NULL) return (HCOURSELIST) {HCOURSE_ITEM_QUANTITY, (HCOURSE *) NULL};

    int i = 0;
    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP001", "Gestão Hoteleira", *getArea(areas, 4), *getUnit(units, 0), Open };
    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP002", "Construção e Reabilitação", *getArea(areas, 10), *getUnit(units, 0), Open };
    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP003", "Desenvolvimento Web e Multimédia", *getArea(areas, 9), *getUnit(units, 0), Open };
    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP004", "Impressão 3D e Maquinação Automática", *getArea(areas, 10), *getUnit(units, 0), Closed };
    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP005", "Manutenção Mecânica", *getArea(areas, 10), *getUnit(units, 0), Open };
    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP006", "Manutenção Automóvel", *getArea(areas, 10), *getUnit(units, 0), Open };
    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP007", "Mecatrónica", *getArea(areas, 10), *getUnit(units, 0), Open };
    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP008", "Sistemas Elétricos de Energia", *getArea(areas, 10), *getUnit(units, 0), Open };
    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP009", "Sistemas Eletrónicos e Computadores", *getArea(areas, 10), *getUnit(units, 0), Open };
    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP010", "Tecnologias e Programação de Sistemas de Informação", *getArea(areas, 9), *getUnit(units, 0), Open };
    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP011", "Turismo de Gastronomia e Vinhos", *getArea(areas, 21), *getUnit(units, 0), Closed };

    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP012", "Termalismo e Bem-Estar", *getArea(areas, 15), *getUnit(units, 1), Open };

    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP013", "Arte e Fabricação Digital", *getArea(areas, 0), *getUnit(units, 2), Open };
    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP014", "Artes e Tecnologia [Luz, Som e Imagem]", *getArea(areas, 0), *getUnit(units, 2), Open };
    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP015", "Ilustração e Produção Gráfica", *getArea(areas, 0), *getUnit(units, 2), Open };
    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP016", "Intervenção Educativa em Creche", *getArea(areas, 1), *getUnit(units, 2), Open };
    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP017", "Intervenção Sociocomunitária e Envelhecimento", *getArea(areas, 1), *getUnit(units, 2), Closed };
    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP018", "Serviços Educativos e Património Local", *getArea(areas, 21), *getUnit(units, 2), Closed };

    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP019", "Treino Desportivo", *getArea(areas, 15), *getUnit(units, 3), Open };
    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP020", "Trabalhos em Altura e Acesso por Cordas", *getArea(areas, 10), *getUnit(units, 3), Closed };

    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP021", "Cuidados Veterinários", *getArea(areas, 14), *getUnit(units, 4), Open };
    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP022", "Fruticultura, Viticultura e Enologia", *getArea(areas, 13), *getUnit(units, 4), Open };
    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP023", "Gestão de Empresas Agrícolas", *getArea(areas, 13), *getUnit(units, 4), Open };
    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP024", "Indústrias Biotecnológicas", *getArea(areas, 6), *getUnit(units, 4), Open };
    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP025", "Riscos e Proteção Civil", *getArea(areas, 20), *getUnit(units, 4), Open };
    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP026", "Turismo Rural e de Natureza", *getArea(areas, 4), *getUnit(units, 4), Open };

    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP027", "Contabilidade e Gestão para PME", *getArea(areas, 4), *getUnit(units, 5), Open };
    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP028", "Marketing Digital e E-Commerce", *getArea(areas, 4), *getUnit(units, 5), Open };
    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP029", "Gestão e Melhoria Contínua das Empresas", *getArea(areas, 4), *getUnit(units, 5), Closed };
    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP030", "Transportes e Logística", *getArea(areas, 4), *getUnit(units, 5), Open };

    return (HCOURSELIST) {HCOURSE_ITEM_QUANTITY, (HCOURSE *) hcourses};
}


HCOURSE* getHCourse(HCOURSELIST *hcourseList, unsigned char code[]){
    if(hcourseList == NULL || !hcourseList->count || code == NULL || code[0] == '\0'){
        return NULL;
    }

    for(unsigned short i = 0; i < hcourseList->count; i++){
        if(strcmp(hcourseList->items[i].code, code) == 0) return &(hcourseList->items[i]); 
    }

    return NULL;
}

short setHCourseState(HCOURSE *course, eState newState){
    if (course == NULL) {
        return -1;
    }

    course->state = newState;
    return 0;
}

short addHCourse(HCOURSELIST *hcourseList, HCOURSE newCourse){
    if(hcourseList == NULL || !hcourseList->count || hcourseList->items == NULL){
        return -1;
    }

    HCOURSE *newItems = realloc(hcourseList->items, (hcourseList->count + 1) * sizeof(HCOURSE));
    if (newItems == NULL) {
        return -1;
    }

    hcourseList->items = newItems;
    
    hcourseList->items[hcourseList->count] = newCourse;
    hcourseList->count++;

    return 0;
}

short editHCourse(HCOURSE *hcourse, HCOURSE newCourseInfo){
    if(hcourse == NULL){
        return -1;
    }

    *hcourse = newCourseInfo;
   
    return 0;    
}

void listHCourses(HCOURSELIST *hcourseList){
    if (hcourseList == NULL || !hcourseList->count || hcourseList->items == NULL) {
        return;
    }

    printf(
        "+-----------+-------------------------------------------------+-------------------------------------+--------+--------+\n"
        "| Code      | Course Description                              | Area                                | School | State  |\n"
        "+-----------+-------------------------------------------------+-------------------------------------+--------+--------+\n"
    );
    for (unsigned short i = 0; i < hcourseList->count; i++) {
        printf(
            "| %-9s | ",
            hcourseList->items[i].code
        );
        printFixedWidth(hcourseList->items[i].description, ' ', 46); 
        printf(" | ");
        printFixedWidth(hcourseList->items[i].area.description, ' ', 34); 
            printf(
                " | %-6s | ",
                hcourseList->items[i].school.acronym
            );
            
        hcourseList->items[i].state == Open ? printColored("Open", Green, 6) : printColored("Closed", Red, 6);
        
        printf("|\n");
    }
    printf("+-----------+-------------------------------------------------+-------------------------------------+--------+--------+\n");
}

void listHCoursesAsc(HCOURSELIST *hcourseList){
    HCOURSE *sortedList = (HCOURSE *) calloc(hcourseList->count, sizeof(HCOURSE));

    if(sortedList == NULL){
        printColored("\nOut of memory!\n", Red, 0);
        return;
    }

    for(unsigned short i = 0; i < hcourseList->count; i++){
        sortedList[i] = hcourseList->items[i];
    }

    HCOURSE aux = {};

    unsigned short sorted = 0;
    for(unsigned short i = 0; i < hcourseList->count && !sorted; i++){
        sorted = 1;
        for(unsigned short j = 0; j < hcourseList->count - i - 1; j++){
            if(strcmp(sortedList[j].description, sortedList[j + 1].description) > 0){
                aux = sortedList[j + 1];
                sortedList[j + 1] = sortedList[j];
                sortedList[j] = aux;
                sorted = 0;
            }
        }
    }


    HCOURSELIST newList = (HCOURSELIST) { hcourseList->count, (HCOURSE *) sortedList};

    listHCourses(&newList);
    free(sortedList);
}

void listHCoursesByUnit(HCOURSELIST *hcourseList, unsigned short unitID){
    if (hcourseList == NULL || !hcourseList->count || hcourseList->items == NULL) {
        return;
    }

    printf(
        "+-----------+-------------------------------------------------+-------------------------------------+--------+--------+\n"
        "| Code      | Course Description                              | Area                                | School | State  |\n"
        "+-----------+-------------------------------------------------+-------------------------------------+--------+--------+\n"
    );
    
    for (unsigned short i = 0; i < hcourseList->count; i++) {
        if(hcourseList->items[i].school.id == unitID){
            printf(
                "| %-9s | ",
                hcourseList->items[i].code
            );
            printFixedWidth(hcourseList->items[i].description, ' ', 46); 
            printf(" | ");
            printFixedWidth(hcourseList->items[i].area.description, ' ', 34); 
            printf(
                " | %-6s | ",
                hcourseList->items[i].school.acronym
            );
                
            hcourseList->items[i].state == Open ? printColored("Open", Green, 6) : printColored("Closed", Red, 6);
            
            printf("|\n");
        }
    }
    printf("+-----------+-------------------------------------------------+-------------------------------------+--------+--------+\n");
}

short saveHCourseData(HCOURSELIST *hcourseList){
    FILE *fp;

    if((fp = fopen(COURSE_FILENAME, "rb")) == NULL){
        return -1;
    };

    fwrite(&hcourseList->count, sizeof(unsigned short), 1, fp);
    fwrite(hcourseList->items, sizeof(HCOURSE), hcourseList->count, fp);

    fclose(fp);
    return 0;
}

short loadHCourseData(HCOURSELIST *hcourseList){
    FILE *fp;

    if((fp = fopen(COURSE_FILENAME, "rb")) == NULL){
        return - 1;
    };

    fread(&hcourseList->count, sizeof(unsigned short), 1, fp);

    hcourseList->items = (HCOURSE *) calloc(hcourseList->count, sizeof(HCOURSE));

    fread(hcourseList->items, sizeof(HCOURSE), hcourseList->count, fp);

    fclose(fp);
    return 0;
}