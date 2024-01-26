#include<pthread.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include"socket.c"
#define ADD_IP "0.0.0.0"
#define PORT 8082
int main(int argc, char *argv[]) {
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
   donneesReservation dataR;
pthread_create(&thread1,NULL, execsocket,NULL);

  pthread_create(&thread4,NULL, affichemenu,NULL);

pthread_join(thread1,NULL);
pthread_join(thread2,NULL);
pthread_join(thread3,NULL);
pthread_join(thread4,NULL);
    return 0;
}
