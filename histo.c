#include <stdio.h>


#include <stdbool.h>
typedef struct{
  int refVol;
  int agence;
  char transaction[10];
  int valeur;
  char resultat[10];
}donneesReservation ;



//fonction qui ajoute une r�servation au fichier histo.txt
void ajouterReservation(donneesReservation* d){
 
 FILE*fp=fopen("histo.txt","a");
 
 if(fp==NULL){
   
printf("erreur dans l'ouverture du fichier des historiques des vols \n");  }
 
else{ printf(" le fichier histo.txt est ouvert avec succées ! \n"); 
 int nbBit_ecrites=fprintf(fp,"%d\t%d\t%s\t%d\t%s\n",d->refVol,d->agence,d->transaction,d->valeur,d->resultat);
 
 fclose(fp);
  
if(nbBit_ecrites<0){
    perror("Erreur d'écriture dans le fichier d'historique");
  }
}
}




//fonction qui lit et affiche tous les informations à partir du fichier histo.txt
void afficherFichierHisto() {
    FILE* fp = fopen("histo.txt", "r"); // ouvrir le fichier en mode lecture
    if (fp == NULL) { // vérifier si le fichier est ouvert avec succés
        printf("Erreur: impossible d'ouvrir le fichier ");
    }
  else
printf("Refvol  Agence transaction valeur resultat \n");
    int caractere = getc(fp); // lire le premier caractére
    while (caractere != EOF) { // lire les caractéres jusqu'à la fin du fichier
        printf("%c", caractere); // afficher le caractére
        caractere = getc(fp); // lire le caractére suivant
    }
    
    fclose(fp); // fermer le fichier
}


void afficherLignesRefVol(int refVol){
    FILE *fp = fopen("histo.txt", "r");
    if(fp == NULL){
        printf("Erreur d'ouverture du fichier histo.txt");
      
    }
    else{
    char ligne[256];
    while(fgets(ligne, sizeof(ligne), fp) != NULL){
        int refVolLigne;
        sscanf(ligne, "%d", &refVolLigne);
        if(refVolLigne == refVol){
            printf("%s", ligne);
        }
    }
    
    fclose(fp);
}
}


//affichage des transactions d une agence donnees 
void afficherParrefAg(int refag){
    FILE *fp = fopen("histo.txt", "r");
    if(fp == NULL){
        printf("Erreur d'ouverture du fichier histo.txt");
      
    }
    else{
    char ligne[256];
    while(fgets(ligne, sizeof(ligne), fp) != NULL){
        int ref;
        sscanf(ligne, "%*d%d", &ref);
        if(ref == refag){
            printf("%s", ligne);
        }
    }
    
    fclose(fp);
}
}

