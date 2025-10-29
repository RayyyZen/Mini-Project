#include "affichage.h"

void affichePromotion(Class class){
    int i=0,j=0,k=0;
    printf("\nPromotion : %d etudiants\n\n",class.taille);
    for(i=0;i<class.taille;i++){
        printf("%d, %s %s, %d ans / Moyenne : %f\n-> Matieres : \n\n",class.etudiants[i].id,class.etudiants[i].nom,class.etudiants[i].prenom,class.etudiants[i].age,class.etudiants[i].moyenne);
        for(j=0;j<class.etudiants[i].taille;j++){
            printf("--> %s / Coefficient : %f / Moyenne : %f\n----> Notes : ",class.etudiants[i].matieres[j].nom,class.etudiants[i].matieres[j].coefficient,class.etudiants[i].matieres[j].moyenne);
            for(k=0;k<class.etudiants[i].matieres[j].notes.taille;k++){
                printf("%f, ",class.etudiants[i].matieres[j].notes.valeurs[k]);
            }
            printf("\n\n");
        }
        printf("\n\n");
    }
}

void afficheEtudiants(Student *tab, int taille, char *matierenom){
    int i=0,j=0;
    if(tab==NULL){
        return ;
    }
    for(i=0;i<taille;i++){
        printf("%d. %d, %s %s, %d ans / Moyenne : %f\n",i+1,tab[i].id,tab[i].nom,tab[i].prenom,tab[i].age,tab[i].moyenne);
        if(matierenom!=NULL){
            for(j=0;j<tab[i].taille;j++){
                if(strcmp(tab[i].matieres[j].nom,matierenom)==0){
                    printf("--> %s / Coefficient : %f / Moyenne : %f\n",tab[i].matieres[j].nom,tab[i].matieres[j].coefficient,tab[i].matieres[j].moyenne);
                }
            }
        }
        printf("\n");
    }
}