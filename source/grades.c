#include "grades.h"

/**
    @brief Fonction constructeur de la structure Grades (notes)
    @return Retourne la variable de type Grades construite
*/
Grades buildGrades(){
    Grades grades;
    grades.size=0;
    grades.capacity=0;
    grades.values=NULL;
    return grades;
}

/**
    @brief Fonction destructeur de la structure Grades (notes)
    @param class Un pointeur de type Grades* qui pointe vers les notes à détruire
*/
void destroyGrades(Grades* grades){
    free(grades->values);
    grades->values=NULL;
    //Il n y a pas de free(grades) car dans la structure Course j y ai mis comme attribut un Grades grades pas un Grades* grades
}