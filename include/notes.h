#ifndef NOTES_H
#define NOTES_H

#include "library.h"

/**
    \struct Grades
    \brief Structure contenant plusieurs notes d'un étudiant dans une matière
*/
typedef struct {
    int taille;
    int capacite;
    float *valeurs;
}Grades;

Grades constructeurGrades();
void destructeurGrades(Grades *grades);

#endif