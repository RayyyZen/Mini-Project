#include "notes.h"

Grades constructeurGrades(){
    Grades grades;
    grades.taille=0;
    grades.capacite=0;
    grades.valeurs=NULL;
    return grades;
}

void destructeurGrades(Grades *grades){
    Grades grades;
    grades->taille=0;
    grades->capacite=0;
    free(grades->valeurs);
    grades->valeurs=NULL;
    free(grades);
    grades=NULL;
}