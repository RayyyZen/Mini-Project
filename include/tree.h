#ifndef TREE_H
#define TREE_H

#include "students.h"

/**
    \struct Tree
    \brief Structure contenant un arbre binaire de recherche permettant le stockage des étudiants afin d'optimiser la recherche de ces derniers lors de l'ajout de notes
*/
typedef struct tree {
    Student *std;
    struct tree *left;
    struct tree *right;
}Tree;

typedef Tree* pTree;

pTree createTree(Student* std);
void display(pTree tree);
pTree addNode(pTree tree, Student* std);
Student* researchNode(pTree a, int id);
void deleteLeft(pTree tree);
void deleteRight(pTree tree);
pTree destroyTree(pTree tree);

#endif