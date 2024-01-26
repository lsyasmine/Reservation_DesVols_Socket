#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include "histo.c"
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<arpa/inet.h>
int main(int argc,char* argv[]){
typedef struct{
	int refag ;
	int somme ;
}donneesFacturation;
	int choix=0 ;
int sid_client ;//descripteur du fichier du socket
struct sockaddr_in server_adress ; //structure prédéfinie dans netinet/in.h 
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8082
donneesReservation dt;
donneesFacturation df;

//********************************création du socket client
sid_client = socket(AF_INET, SOCK_STREAM,0);
//AF_INET spécifie qu'on utilise le domaine internet et précisemment ladresse ipv4
//SOCK_STREAM précise qu'on utilise le mode connecté de transmission (protocole TCP/Ip)
//le paramétre protocole n'est plus utile donc on le met à zero (protocole par defaur du socket )
if (sid_client == -1){
	printf("Erreur au niveau de la création du socket \n");
	return 1;//on sort du programme
}

else printf ("socket crée avec succés ! \n");
//*****************************Paramétrage du socket
// la structure sockaddr_in danslaquelle on va stocker les infos de configuration ( port et adresse ip de serveur )
server_adress.sin_family= AF_INET;  //spécifie la famille d'adresse :ipv4 (AF_INT)
server_adress.sin_port=htons(SERVER_PORT); //spécifie le numero de port
//htons() permet de convertir le numero de port du serveur en un format compréhensible par la fonction connect()
server_adress.sin_addr.s_addr=inet_addr(SERVER_IP); //spécifie l adresse ip
//inet_addr() permet de convertir l adresse ip du chaine de caractére en format binaire utilisable par la structure sockaddr_in

//******************************Connexion avec le serveur 
if ((connect(sid_client,(struct sockaddr_in *) &server_adress , sizeof(server_adress)) )<0)
{ printf ("Erreur au niveau de la connexion avec le serveur \n ");
	return 1; 
	}
	else printf("Vous etes connecté au serveur avec succés !\n ");



//*****************************Menu

while(choix != 4)
{       printf ("****  reservation des vols en ligne  ***** \n");
	printf ("****************bienvenue******************* \n");
	printf("=======================menu===================== \n");
	printf("1. demande de reservation d'un vol \n ");
	printf("2. demande d'annulation d'un vol   \n ");
        printf("3. recevoir la facture \n ");
        printf("4. quitter \n");
	printf("entrez votre choix");
	scanf("%d",&choix);
	switch(choix){
	case 1 : printf("option 1 sélectionné : demande de reservation d'un vol \n ");
	//saisie des données
	printf("entrer la référence du vol \n");
	scanf("%d",&dt.refVol);
	printf("entrer le numero d'agence \n");
	scanf("%d",&dt.agence);
	//puisque c'est une demande , le champ de transaction sera toujours : Demande
	strcpy(dt.transaction,"Demande_RES");
	printf(" entrer le nombre de place à reserver \n");
	scanf("%d",&dt.valeur );
	//puisque le dernier champ sera traité par le serveur , son valeur sera vide
	strcpy(dt.resultat,"chaine NULL");
	//envoi des données au serveur
	if (send(sid_client,&dt,sizeof(donneesReservation),0)== -1)
	printf("Erreur lors d'envoi des données au serveur \n");
	else printf(" demande envoyé avec succés ! \n");
	char buffer[1024];
	int n = recv(sid_client,buffer,sizeof(buffer),0);
	buffer[n]='\0';
	if (n<0) printf("erreur lors de la réception");
	else printf("Le message reçu de la part du serveur est %s \n" ,buffer);
break;
	case 2 :printf("option 2 sélectionné : demande d'annulation d'un vol \n ");
	//saisie des données
	printf("entrer la référence du vol \n");
	scanf("%d",&dt.refVol);
	printf("entrer le numero d'agence \n");
	scanf("%d",&dt.agence);
	//puisque c'est une demande , le champ de transaction sera toujours : Annulation
	strcpy(dt.transaction,"annulation");
	printf(" entrer le nombre de place à annuler \n");
	scanf("%d",&dt.valeur );
	//le dernier champs sera toujours succes en cas d'annulation
	strcpy(dt.resultat,"succés");
	//envoi des données au serveur
	if (send(sid_client,&dt,sizeof(donneesReservation),0)== -1)
	printf("Erreur lors d'envoi des données au serveur \n");
	else printf("demande d'annulation envoyé  avec succées ! \n");
	char buffer1[1024];

	int n1 = recv(sid_client,buffer1,sizeof(buffer1),0);
	buffer1[n1]='\0'; //garanatit qu'il ne lit pas des caratéres aléatoires au dela de la chaine 
	if (n1<0) printf("erreur lors de la réception");
	else printf("from server :%s \n" ,buffer1);
	break;
	case 3 : printf("option 3 sélectionné : reception du facture \n ");
		 //saisie de données 
		 printf("entrer la référence d'agence \n");
		 scanf("%d", &df.refag);
		 //le champs de la somme sera nul au depart et mis à jour de la part de serveur à chaque transaction
		df.somme=0;
		 //envoi de données au serveur 
		 if (send(sid_client,&df,sizeof(donneesFacturation),0) ==-1)
			 printf("Erreur lors d'envoi des données au serveur \n");
		 else printf("demande de reception de la facture est envoyé avec succés \n");
		 char buffer2[1024];
		 int n2= recv(sid_client,buffer2,sizeof(buffer2),0);
		 buffer2[n2]='\0';
		 if (n2<0) printf("erreur lors de la réception");
		 else printf("from server :%s \n",buffer2);
	break;
	case 4: printf("au revoir ! \n ");
		return 0 ;
	default : 
		printf("choix invalide!!veuillez entrer un choix valide \n ");
	}
printf("Appuyer sur une touche pour continuer .. ! \n" );
getchar();
getchar();}








//*****************************Fermuture du socket 
close (sid_client);
}
