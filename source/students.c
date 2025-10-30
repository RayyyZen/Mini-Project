#include "students.h"

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

void destructeurStudent(Student *student){
    int i=0;
    student->id=0;
    free(student->prenom);
    student->prenom=NULL;
    student->nomtaille=0;
    free(student->nom);
    student->nom=NULL;
    student->age=0;
    for(i=0;i<student->taille;i++){
        destructeurCourse(&student->matieres[i]);
    }
    student->taille=0;
    student->capacite=0;
    free(student->matieres);
    student->matieres=NULL;
    student->moyenne=0;
    free(student);
    student=NULL;
}