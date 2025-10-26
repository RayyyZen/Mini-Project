#include "promotion.h"

Class constructeurClass(){
    Class class;
    class.taille=0;
    class.capacite=0;
    class.etudiants=NULL;
    return class;
}

void constructeurClass(Class *class){
    int i=0;
    for(i=0;i<class->taille;i++){
        destructeurStudent(&class->student[i]);
    }
    free(class->student);
    class->student=NULL;
    class->taille=0;
    class->capacite=0;
    free(class);
    class=NULL;
}