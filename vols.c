#include<pthread.h>
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include <stdbool.h>
typedef struct {
int refVol;
char  destination[30];
int nbPlacesDispo;
int  prixPlace;
}donneesVols;


void  AjouterVol(donneesVols* v){
FILE* fp=fopen("vols.txt","a+");
if(fp == NULL)
   printf("Erreur d'ouverture de fichier de vols");
else {printf("fichier vols ouvert avec succés \n");
  int nbBit=fprintf(fp,"%d\t%s\t%d\t%d\n",v->refVol,v->destination,v->nbPlacesDispo,v->prixPlace);
  fclose(fp);
  if(nbBit<0)
    perror("Erreur d'écriture dans le fichier vols");
}}
//affichageis des vols par leur reference
void affichervols(int refVol){

    FILE *fp = fopen("vols.txt", "r");
    if(fp == NULL)
        printf("Erreur d'ouverture du fichier vols.txt");
    else{
    char ligne[256];
    while(fgets(ligne, sizeof(ligne), fp) != NULL){
        int refVolLigne;
        sscanf(ligne, "%d", &refVolLigne);
        if(refVolLigne == refVol){
         printf("===============================\n");
          printf("RefVol  Dest    NbPlace  prixPlace \n");
            printf("%s",ligne);
           printf("=============================== \n");
        }
    } fclose(fp);

}}

//fonction qui verifie l'existance d'un vol dans le fichier vols.txt
int verifvol(int refVol) {
    int x = 0;
    FILE *fp = fopen("vols.txt", "r");
    if (fp == NULL)
        printf("Erreur d'ouverture du fichier vols.txt");
    else {
        char ligne[256];
        while (fgets(ligne, sizeof(ligne), fp) != NULL) {
            int refVolLigne;
            sscanf(ligne, "%d", &refVolLigne);
            if (refVolLigne == refVol) {
                x = 1;
                break;
            }
        }
        fclose(fp);
    }
    return x;
}



//affichages des nombres des places disponibles pour une vol
int getnbPlaces(int refVol){
    int nb;
    FILE *fp = fopen("vols.txt", "r");
    if(fp == NULL)
        printf("Erreur d'ouverture du fichier vols.txt");
    else{
    char ligne[256];
    while(fgets(ligne, sizeof(ligne), fp) != NULL){
        int refVolLigne;
        sscanf(ligne, "%d", &refVolLigne);
        if(refVolLigne == refVol){
            sscanf(ligne,"%*d%*s%d",&nb);
        }
    } fclose(fp);

} return(nb);}

//recuperation de prix d' une vol
int getprix(int refVol){
    int nb;
    FILE *fp = fopen("vols.txt", "r");
    if(fp == NULL)
        printf("Erreur d'ouverture du fichier vols.txt");
    else{
    char ligne[256];
    while(fgets(ligne, sizeof(ligne), fp) != NULL){
        int refVolLigne;
        sscanf(ligne, "%d", &refVolLigne);
        if(refVolLigne == refVol){
            sscanf(ligne,"%*d%*s%*d%d",&nb);
        }
    } fclose(fp);

} return(nb);}



//mise à jour de nb places dispo
void updatenbPlaces(int refVol, int nb) {
    FILE *fp = fopen("vols.txt", "r+");
    if (fp == NULL) {
        printf("Erreur d'ouverture du fichier vols.txt");
    } else {
        char ligne[256];
        while (fgets(ligne, sizeof(ligne), fp) != NULL) {
            donneesVols d;
            sscanf(ligne, "%d %s %d %d",&d.refVol,d.destination,&d.nbPlacesDispo,&d.prixPlace);
            if (d.refVol == refVol) {
               d.nbPlacesDispo=nb;
                fseek(fp, -strlen(ligne), SEEK_CUR);
            fprintf(fp, "%d\t%s\t%d\t%d ",d.refVol,d.destination,d.nbPlacesDispo,d.prixPlace);

                 break;
            }          
        }
        fclose(fp);
    } 
}
