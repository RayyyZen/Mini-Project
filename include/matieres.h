#ifndef MATIERES_H
#define MATIERES_H

#include "notes.h"

/**
    \struct Course
    \brief Structure contenant le nom, le coefficient et la moyenne d'une matière, ainsi que les notes d'un étudiant dans cette dernière
*/
typedef struct {
    char *nom;
    int nomtaille;
    float coefficient;
    float moyenne;
    Grades notes;
}Course;

Course constructeurCourse();
void destructeurCourse(Course *course);

#endif