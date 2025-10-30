#include "courses.h"

Course constructeurCourse(){
    Course course;
    course.nom=NULL;
    course.nomtaille=0;
    course.coefficient=0;
    course.moyenne=0;
    course.notes=constructeurGrades();
    return course;
}

void destructeurCourse(Course *course){
    free(course->nom);
    course->nom=NULL;
    course->nomtaille=0;
    course->coefficient=0;
    course->moyenne=0;
    destructeurGrades(&course->notes);
    free(course);
    course=NULL;
}