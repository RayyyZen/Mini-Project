#ifndef ETUDIANTS_H
#define ETUDIANTS_H

#include "matieres.h"

/**
    \struct Student
    \brief Structure contenant les informations clées d'un etudiant
*/
typedef struct {
    int id;
    char *prenom;
    int prenomtaille;
    char *nom;
    int nomtaille;
    int age;
    int taille;
    int capacite;
    Course *matieres;
    float moyenne;
}Student;

Student constructeurStudent();

#endif