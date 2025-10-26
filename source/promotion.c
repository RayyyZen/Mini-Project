#include "promotion.h"

Class constructeurClass(){
    Class class;
    class.taille=0;
    class.capacite=0;
    class.etudiants=NULL;
    return class;
}

void destructeurClass(Class *class){
    int i=0;
    for(i=0;i<class->taille;i++){
        destructeurStudent(&class->etudiants[i]);
    }
    free(class->etudiants);
    class->etudiants=NULL;
    class->taille=0;
    class->capacite=0;
    free(class);
    class=NULL;
}