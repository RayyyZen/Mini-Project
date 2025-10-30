#ifndef CLASS_H
#define CLASS_H

#include "tree.h"

/**
    \struct Class
    \brief Structure contenant l'ensemble des informations sur les étudiants d'une promotion, ainsi que leur nombre
*/
typedef struct {
    int taille;
    int capacite;
    Student *etudiants;
}Class;

Class constructeurClass();
void destructeurClass(Class *class);

#endif