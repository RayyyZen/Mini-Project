#ifndef TREE_H
#define TREE_H

#include "students.h"

/**
    \struct Arbre
    \brief Structure contenant un arbre binaire permettant le stockage des étudiants afin d'optimiser la recherche
*/
typedef struct arbre {
    Student *etu;
    struct arbre *fg;
    struct arbre *fd;
}Arbre;

typedef Arbre* pArbre;

pArbre creerArbre(Student *etu);
void afficher(pArbre a);
pArbre ajoutNoeud(pArbre a, Student *etu);
Student* rechercheNoeud(pArbre a, int id);
void supprimerFilsGauche(pArbre a);
void supprimerFilsDroit(pArbre a);
pArbre destructeurArbre();

#endif