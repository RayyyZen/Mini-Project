#include "students.h"

/**
    @brief Fonction constructeur de la structure Student (étudiant)
    @return Retourne la variable de type Student construite
*/
Student buildStudent(){
    Student student;
    student.id=0;
    student.fname=NULL;
    student.sizefname=0;
    student.lname=NULL;
    student.sizelname=0;
    student.age=0;
    student.size=0;
    student.capacity=0;
    student.courses=NULL;
    student.average=0;
    return student;
}

/**
    @brief Fonction destructeur de la structure Student (étudiant)
    @param student Un pointeur de type Student* qui pointe vers l'étudiant à détruire
    @return Un pointeur sur la variable détruite
*/
Student* destroyStudent(Student* student){
    student->id=0;
    student->sizefname=0;
    student->sizelname=0;
    student->age=0;
    student->size=0;
    student->capacity=0;
    student->average=0;
    free(student);
    student=NULL;
    return student;
}