#include "courses.h"

/**
    @brief Fonction constructeur de la structure Course (matière)
    @return Retourne la variable de type Course construite
*/
Course buildCourse(){
    Course course;
    course.name=NULL;
    course.sizename=0;
    course.coefficient=0;
    course.average=0;
    course.grades=buildGrades();
    return course;
}

/**
    @brief Fonction destructeur de la structure Course (matière)
    @param class Un pointeur de type Course* qui pointe vers la matière à détruire
    @return Un pointeur sur la variable détruite
*/
Course* destroyCourse(Course* course){
    course->sizename=0;
    course->coefficient=0;
    course->average=0;
    course->grades.size=0;
    course->grades.capacity=0;
    free(course);
    course=NULL;
    return course;
}