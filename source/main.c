#include "affichage.h"

int main(){
    Class class=constructeurClass();
    stockageDonnees(&class,"Data/data.txt");
    affichePromotion(class);
    printf("1");
    return 0;
}