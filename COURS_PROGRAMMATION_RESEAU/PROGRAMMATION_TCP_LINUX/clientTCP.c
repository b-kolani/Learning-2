#include <stdio.h>
#include <stdlib.h> /* pour exit */
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define LG_MESSAGE 256

int main()
{
    int descripteurSocket;
    struct sockaddr_in pointDeRencontreDistant;
    socklen_t longueurAdresse;
    char messageEnvoi[LG_MESSAGE];
    char messageRecu[LG_MESSAGE];
    int ecris, lus;
    // int retour;

    //--- Début de l'étape numéro 1:
    // Créer une socket de communication
    descripteurSocket = socket(PF_INET, SOCK_STREAM, 0); /* 0 indique que l'on
    utilisera le protocole par défaut associé à SOCK_STREAM soit TCP */

    // Teste la valeur renvoyée par l'appel systeme socket()
    if (descripteurSocket < 0)
    {                     /* échec ? */
        perror("socket"); // Affiche le message d'erreur
        exit(-1);         // On sort en indiquand un code erreur
    }

    //-- Fin de l'étape numéro 1 !
    printf("Socket créée avec succès ! (%d)\n", descripteurSocket);

    //--- Début de l'étape numéro 2:
    // Obtient la longueur en octets de la structure sockaddr_in
    longueurAdresse = sizeof(pointDeRencontreDistant);
    // Initialise à 0 la structure sockaddr_in
    memset(&pointDeRencontreDistant, 0x00, longueurAdresse);
    // Renseigne la structure sockaddr_in avec les informations du serveur distant
    pointDeRencontreDistant.sin_family = PF_INET;
    // On choisit le numéro de port d'écoute du serveur
    pointDeRencontreDistant.sin_port = htons(IPPORT_USERRESERVED); // = 5000
    // On choisit l'adresse IPv4 du serveur
    // à modifier selon les besoins
    if (inet_aton("127.0.0.1", &pointDeRencontreDistant.sin_addr) == 0)
    {
        perror("inet_aton");
        close(descripteurSocket);
        exit(-1);
    }

    // Débute la connexion vers le processus serveur distant
    if ((connect(descripteurSocket,
                 (const struct sockaddr *)&pointDeRencontreDistant, longueurAdresse)) == -1)
    {
        perror("connect");        // Affiche le message d'erreur
        close(descripteurSocket); // On ferme la ressource avant de quitter
        exit(-2);                 // On sort en indiquant un code erreur
    }
    //--- Fin de l'étape numéro 2 !
    printf("Connexion au serveur réussie avec succès ! \n");

    //--- Début de l'étape numéro 4:
    // initialisé à 0 les messages
    memset(messageEnvoi, 0x0, LG_MESSAGE * sizeof(char));
    memset(messageRecu, 0x0, LG_MESSAGE * sizeof(char));

    sprintf(messageEnvoi, "Hello World!\n");
    ecris = write(descripteurSocket, messageEnvoi, strlen(messageEnvoi)); // message à TAILLE variable
    switch (ecris)
    {
        case -1: /* une erreur */
            perror("write");
            close(descripteurSocket);
            exit(-3);
        case 0: /* la socket a été fermée */
            printf("La socket a été fermée par le serveur !\n\n");
            close(descripteurSocket);
            return 0;
        default: /* envoie de n octets */
            printf("Message %s envoyé avec succès (%d octets)\n\n", messageEnvoi, ecris);
    }

    /* Reception des données du serveur */
    lus = read(descripteurSocket, messageRecu, LG_MESSAGE*sizeof(char)); /* attend un message 
    de taille fixe  */
    switch (lus) {
        case -1: /* uen erreur */
            perror("read");
            close(descripteurSocket);
            exit(-4);
        case 0: /* la socket est fermée */
            printf("La socket a été fermée par le serveur !\n\n");
            return 0;
        default: /* réception de n octets */
            printf("Message reçu du serveur : %s (%d octets)\n\n", messageRecu, lus);
    }
    //--- Fin de l'étape numéro 4

    // On ferme la ressource avant de quitter
    close(descripteurSocket);
    return (0);
}
