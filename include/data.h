#ifndef DATA_H
#define DATA_H

#include "class.h"

void ajoutEtudiant(Class *class, char *ligne);
void ajoutMatiere(Student *student, char *ligne);
void ajoutNote(Class *class, Student *totalmatieres, pArbre a, char *ligne);
void stockageDonnees(Class *class, char *chemin);

#endif