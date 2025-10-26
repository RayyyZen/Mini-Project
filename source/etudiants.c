#include "etudiants.h"

Student constructeurStudent(){
    Student student;
    student.id=0;
    student.prenom=NULL;
    student.nomtaille=0;
    student.nom=NULL;
    student.age=0;
    student.taille=0;
    student.capacite=0;
    student.matieres=NULL;
    student.moyenne=0;
    return student;
}