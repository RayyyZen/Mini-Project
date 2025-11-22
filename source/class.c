#include "class.h"

/**
    @brief Fonction constructeur de la structure Class (promotion)
    @return Retourne la variable de type Class construite
*/
Class buildClass(){
    Class class;
    class.size=0;
    class.capacity=0;
    class.students=NULL;
    class.compare=NULL;
    return class;
}

/**
    @brief Fonction destructeur de la structure Class (promotion)
    @param class Un pointeur de type Class* qui pointe vers la promotion à détruire
    @return Un pointeur sur la variable détruite
*/
Class* destroyClass(Class* class){
    class->size=0;
    class->capacity=0;
    if(class->compare!=NULL){
        free(class->compare);
        class->compare=NULL;
    }
    free(class);
    class=NULL;
    return class;
}