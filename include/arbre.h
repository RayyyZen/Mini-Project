#ifndef ARBRE_H
#define ARBRE_H

#include "etudiants.h"

/**
    \struct Arbre
    \brief Structure contenant un arbre binaire permettant le stockage des étudiants afin d'optimiser la recherche
*/
typedef struct arbre {
    Student *etu;
    arbre *fg;
    arbre *fd;
}Arbre;

typedef Arbre* pArbre;

pArbre constructeurArbre();

#endif