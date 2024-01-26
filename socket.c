#include <stdio.h>
#include<pthread.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "vols.c"
#include "facture.c"
#include"menu.c"
#include "histo.c"
#define ADD_IP "0.0.0.0"
#define PORT 8082
pthread_mutex_t m1,m2,m3;

    int server_s, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024];
    char* message = "échec réference de vol est invalide !!\n";
    char* message2 = "Votre transaction est effectuée avec succés\n";
    char* message3 = "Nombre de places invalide !!\n";
    int choix,x;
pthread_t thread1,thread2,thread3,thread4;
pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m3 = PTHREAD_MUTEX_INITIALIZER;

   donneesReservation dataR;

void execsocket(){

  // Créer le socket serveur
    server_s = socket(AF_INET, SOCK_STREAM, 0);
    if (server_s <0){ 
        perror("Erreur de socket");
        return 1;}
     printf("socket crée avec succés! \n");
     
    
  // Attacher le socket à un port donné
   
    address.sin_family =AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr =inet_addr(ADD_IP);
   

   // lier  le socket au port et écouter les connexions entrantes
    if (bind(server_s, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("Erreur de bind de socket \n");
        return 1;
    } else printf("bind avec succés \n"); 
    if (listen(server_s, 3) < 0) {//Au moins 3 connexions
        perror("Erreur d'écoute de serveur \n");
        return 1;

    } else { 
          printf("Serveur disponible \n");
          printf("En attente pour les requtes des agences..\n");} 
 
    // Accepter les connexions entrantes et envoyer un message de bienvenue
  
 if ((new_socket = accept(server_s, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
        perror("Erreur d'acceptation de connexion \n");
        return 1;
    }else
        printf("acceptation de la connexion de la part du serveur \n");


   //réception des demandes 
while(1){
    valread = recv(new_socket,&dataR, sizeof(dataR),0);
    if (valread == -1){
          perror("Erreur de réception des donnees du client \n");
          break;}
     if (valread == 0){
          break;}
   printf("donnees reçu \n");
   int x = verifvol(dataR.refVol) ;
if( x == 1){//verification de l'existance de reference de vol
  if(strcmp(dataR.transaction , "annulation") == 0){ 
       ajouterReservation(&dataR);
       int y = getnbPlaces(dataR.refVol)+dataR.valeur;
       updatenbPlaces(dataR.refVol,y);
       send(new_socket,message2,strlen(message2), 0); }
 else {
        int nb =getnbPlaces(dataR.refVol);
      //verification de nb de places disponible
     if(nb>=dataR.valeur ){
         //calcul facture
      int somme=getprix(dataR.refVol)*nb+getsomme(dataR.agence);

   pthread_mutex_lock(&m1);
updatefacture(dataR.agence,somme);
   pthread_mutex_unlock(&m1); 
 //mise à jour de resultat
      strcpy(dataR.resultat,"succés");
     pthread_mutex_lock(&m2);
ajouterReservation(&dataR);

  pthread_mutex_unlock(&m2);  
     //mise à jour de nb places  dispo dans vols.txt  
    int z = getnbPlaces(dataR.refVol)-dataR.valeur; 
   pthread_mutex_lock(&m3);
updatenbPlaces(dataR.refVol,z);
   pthread_mutex_unlock(&m3);

      send(new_socket,message2,strlen(message2), 0);
      
    }
     else  {strcpy(dataR.resultat,"impossible");
   // pthread_create(&thread2,NULL, ajouterReservation,(void*)&dataR);
ajouterReservation(&dataR);     
send(new_socket,message3,strlen(message3), 0); }
      }
  }
else
 send(new_socket,message,strlen(message), 0);
   
}
pthread_mutex_destroy(&m1);
pthread_mutex_destroy(&m2);
pthread_mutex_destroy(&m3);
   close(server_s);

}
