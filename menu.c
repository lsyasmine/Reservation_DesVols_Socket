#include<stdio.h>
void affichemenu(){
int choix,x;
while(1)
{   printf("===============Menu serveur================== \n");
    printf("1.consulter les informations d'une vol par leur réference  \n");
    printf("2.consulter la facture d'une agence \n");
    printf("3.consulter l'historique des transactions \n");
    printf("4.quitter \n");
    printf("entrer le choix \n");
    scanf("%d",&choix);
   switch(choix){


   case 1 : printf("donner la reference de vol \n");
            scanf("%d",&x);
            affichervols(x);
            break;

   case 2 : printf("donner la reference de l'agence \n");
           scanf("%d",&x);
           afficherfacture(x);
           break;
  
   case 3: printf("=========l'historique des transactions============\n");
          afficherFichierHisto();
          break;
   case 4: return 0;
   default : printf("choix invalide !! veuillez entrer un choix valide \n");
   }
printf("Appuyer sur une touche pour continuer ..!\n");
getchar();
getchar();
}
}
