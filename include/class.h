#ifndef CLASS_H
#define CLASS_H

#include "tree.h"

/**
    \struct Class
    \brief Structure contenant l'ensemble des informations sur les étudiants d'une promotion, ainsi que leur nombre
*/
typedef struct {
    int size;
    int capacity;//Sert à reallouer le tableau d'étudiants si besoin
    Student *students;
}Class;

Class buildClass();
void destroyClass(Class* class);

#endif