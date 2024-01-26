#include <stdio.h>
#include <stdbool.h>

typedef struct{
int refag;
int somme;
}donneesFacturation;
 

//fonction qui ajoute une facture  au fichier facture.txt
void ajouterFacture(donneesFacturation* d){
 
 FILE*fp=fopen("facture.txt","a");
 
 if(fp==NULL){
     
printf("erreur dans l'ouverture du fichier des factures des agences \n");  }
 
else{ printf(" le fichier facture.txt est ouvert avec succées ! \n");
     int nbBit_ecrites=fprintf(fp,"%d\t%d\n",d->refag,d->somme);
     fclose(fp);
     if(nbBit_ecrites<0){
     perror("Erreur d'écriture dans le fichier des factures");
  } 
}  
}

//consulter la facture d'une agence 
void afficherfacture(int refag){

    FILE *fp = fopen("facture.txt", "r");
    if(fp == NULL) 
        printf("Erreur d'ouverture du fichier facture.txt");
    else{
    char ligne[256];
    while(fgets(ligne, sizeof(ligne), fp) != NULL){
        int refVolLigne;
        sscanf(ligne, "%d", &refVolLigne);
        if(refVolLigne == refag){
            printf("%s", ligne);
        }
    }
    
    fclose(fp);
}}


//recuperation de somme d'une facture
int getsomme(int refag){
    int nb;
    FILE *fp = fopen("facture.txt", "r");
    if(fp == NULL)
        printf("Erreur d'ouverture du fichier facture.txt");
    else{
    char ligne[256];
    while(fgets(ligne, sizeof(ligne), fp) != NULL){
        int ref;
        sscanf(ligne, "%d", &ref);
        if(ref == refag){
            sscanf(ligne,"%*d%d ",&nb);
      }
    } fclose(fp);

} return(nb);}

  
void updatefacture(int refag, int somme) {
    FILE *fp = fopen("facture.txt", "r+");
    if (fp == NULL) {
        printf("Erreur d'ouverture du fichier facture.txt");
    } else {
        char ligne[256];
        int nb_lignes_avant = 0;
        while (fgets(ligne, sizeof(ligne), fp) != NULL) {
            donneesFacturation d;
            sscanf(ligne, "%d %d", &d.refag, &d.somme);
            if (d.refag == refag) {
                d.somme = somme;
                fseek(fp, nb_lignes_avant, SEEK_SET);
                fprintf(fp, "%d\t %d\n", d.refag, d.somme);
                break;
            }
            nb_lignes_avant = ftell(fp);
        }
        fclose(fp);
    }
}

