#include "tri.h"

int main(){
    Class class=constructeurClass();
    stockageDonnees(&class,"Data/data.txt");
    affichePromotion(class);

    //restaurer(&class);
    //affichePromotion(class);

    int taille=0;
    Student *tab=meilleuresMoyennes(&class,&taille);
    printf("Les %d étudiants avec la meilleure moyenne de la promotion : \n\n",taille);
    afficheEtudiants(tab,taille,NULL);

    int taille2=0;
    char chaine[20]="Informatique";
    Student *tab2=moyennesMatieres(&class,chaine,&taille2);
    printf("Les %d étudiants avec la meilleure moyenne de la promotion en %s : \n\n",taille2,chaine);
    afficheEtudiants(tab2,taille2,chaine);

    sauvegarder(&class);
    return 0;
}