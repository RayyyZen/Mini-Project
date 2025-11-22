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
    int (*compare) (Student* student1, Student* student2);
}Class;

Class buildClass();
Class* destroyClass(Class* class);

#endif