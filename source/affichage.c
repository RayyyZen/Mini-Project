#include "affichage.h"

void affichePromotion(Class class){
    int i=0,j=0,k=0;
    printf("Promotion : %d etudiants\n",class.taille);
    for(i=0;i<class.taille;i++){
        printf("%d, %s %s, %d ans / Moyenne : %f\nMatieres : \n",class.etudiants[i].id,class.etudiants[i].nom,class.etudiants[i].prenom,class.etudiants[i].age,class.etudiants[i].moyenne);
        for(j=0;j<class.etudiants[i].taille;j++){
            printf("%s / Coefficient : %f / Moyenne : %f\n Notes : ",class.etudiants[i].matieres[j].nom,class.etudiants[i].matieres[j].coefficient,class.etudiants[i].matieres[j].moyenne);
            for(k=0;k<class.etudiants[i].matieres[j].notes.taille;k++){
                printf("%f, ",class.etudiants[i].matieres[j].notes.valeurs[k]);
            }
            printf("\n");
        }
        printf("\n");
    }
}