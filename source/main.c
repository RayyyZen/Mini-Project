#include "sort.h"

int main(){
    Class class=buildClass();
    int size=0,verif=0,choice=-1,check=checkFile("Data/class.bin"),save=1;
    Student *array=NULL;
    char coursename[50];

    do{
        printf("\n1. Traiter les données de la promotion contenues dans le fichier Data/data.txt\n");
        printf("2. Restaurer les données de la promotion à partir des fichiers sauvegardées");
        if(check==0 && choice==2){
            printf(" (Aucun fichier de sauvegarde pour le moment)");
        }
        printf("\n3. Quitter\n\n");
        printf("Faites votre choix : ");
        verif=scanf("%d",&choice);
        while(getchar()!='\n'){}
        //Pour vider le buffer afin d'éviter les boucles infinies suite à la saisie de caractères au lieu de chiffres
    }while(verif!=1 || (choice!=1 && choice!=2 && choice!=3) || (choice==2 && check==0));

    if(choice!=3){
        if(choice==1){
            dataStorage(&class,"Data/data.txt");
            printf("\nLa sauvegarde a été effectuée avec succès !\n\n");
        }
        else{//choice==2
            recoverData(&class);
            printf("\nLa restauration a été effectuée avec succès !\n\n");
            save=0;
            //Pour ne pas sauvegarder les données à la fin du programme
        }
        choice=-1;
        //Pour initier un nouveau choix

        do{
            printf("1. Afficher les informations de la promotion d'étudiants\n");
            printf("2. Afficher les 10 étudiants avec la meilleure moyenne de la promotion\n");
            printf("3. Afficher les 3 étudiants avec la meilleure moyenne de la promotion dans une certaine matière\n");
            printf("4. Quitter\n\n");
            printf("Faites votre choix : ");
            verif=scanf("%d",&choice);
            while(getchar()!='\n'){}
            //Pour vider le buffer afin d'éviter les boucles infinies suite à la saisie de caractères au lieu de chiffres
        }while(verif!=1 || (choice!=1 && choice!=2 && choice!=3 && choice!=4));
        if(choice==4){
            return 0;
        }
        else if(choice==1){
            displayClass(class);
        }
        else if(choice==2){
            array=bestAverages(&class,&size);
            printf("Les %d étudiants avec la meilleure moyenne de la promotion : \n\n",size);
            displayStudents(array,size,NULL);
        }
        else if(choice==3){
            do{
                do{
                    printf("Choisissez une matière : ");
                    verif=scanf("%s",coursename);
                    while(getchar()!='\n'){}
                    //Pour vider le buffer
                }while(verif!=1);
                array=bestCourseAverages(&class,coursename,&size);
                if(array==NULL){
                    printf("Aucun etudiant n'a de notes dans cette matière\n");
                }
            }while(array==NULL);
            printf("Les %d étudiants avec la meilleure moyenne de la promotion en %s : \n\n",size,coursename);
            displayStudents(array,size,coursename);
        }

        if(save!=0){
            saveData(&class);
            //La sauvegarde détruit toutes les données de la variable class c'est pour cela que je la mets à la fin
        }
    }

    return 0;
}