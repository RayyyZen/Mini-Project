#ifndef STUDENTS_H
#define STUDENTS_H

#include "courses.h"

/**
    \struct Student
    \brief Structure contenant les informations clées d'un etudiant
*/
typedef struct {
    int id;
    int age;
    char *prenom;
    char *nom;
    int prenomtaille;
    int nomtaille;
    int taille;
    int capacite;
    Course *matieres;
    float moyenne;
}Student;

Student constructeurStudent();
void destructeurStudent(Student *student);

#endif