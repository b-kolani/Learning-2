#include <unistd.h> /* pour sleep */
#include <stdio.h> 
#include <stdlib.h> /* pour exit */
#include <string.h> /* pour memset */
#include <netinet/in.h> /* pour struct sockaddr_in */
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h> /* pour htons et inet_aton */

#define PORT IPPORT_USERRESERVED // = 5000
#define LG_MESSAGE 256

int main()
{
    int socketEcoute;
    struct sockaddr_in pointDeRencontreLocal;
    socklen_t longueurAdresse;
    int socketDialogue;
    struct sockaddr_in pointDeRencontreDistant;
    char    messageEnvoi[LG_MESSAGE]; /* le message de la couche Application ! */
    char    messageRecu[LG_MESSAGE]; /* le message de la couche Application ! */
    int ecrits, lus; /* nb d'octets ecrits et lus */
    // int retour;

    //--- Début de l'étape numéro 5:
    // Crée un socket de communication
    socketEcoute = socket(PF_INET, SOCK_STREAM, 0); /* O indique que l'on utilisera le
        protocole par défaut assocé à SOCK_STREAM soit TCP */

    // Teste la valeur renvoyée par l'appel système socket()
    if (socketEcoute < 0) /* échec ? */
    {
        perror("socket"); // Affiche le message d'erreur 
        exit(-1); // On sort en indiquant un code d'erreur 
    }
    printf("Socket créée avec succès ! (%d)\n", socketEcoute);

    // On prépare l'adresse d'attachement locale
    longueurAdresse = sizeof(struct sockaddr_in);
    memset(&pointDeRencontreLocal, 0x0, longueurAdresse);
    pointDeRencontreLocal.sin_family = PF_INET;
    pointDeRencontreLocal.sin_addr.s_addr = htonl(INADDR_ANY); // toutes les interfaces locales disponibles 
    pointDeRencontreLocal.sin_port = htons(PORT); // = 5000

    // On demande l'attachement local de la socket
    if ((bind(socketEcoute,
             (const struct sockaddr *)&pointDeRencontreLocal,
             longueurAdresse)) < 0)
    {
        perror("bind");
        close(socketEcoute);
        exit(-2);
    }
    //--- Fin de l'étape numéro 5!
    // On fixe la taille de la file dattente à 5
    // (pour les demandes de connexion non encore traitées)
    printf("Socket attachée avec succès !\n");

    //--- Début de l'étape numéro 6:
    if (listen(socketEcoute, 5) < 0) {
        perror("listen");
        close(socketEcoute);
        exit(-3);
    }
    //--- Fin de l'étape numéro 6 !
    printf("Socket placée en écoute passive ...!\n");

    // On s'endort ... (cf. test)
    // sleep(2);
    //--- Début de l'étape numéro 7:
    // boucle d'attente de connexion: en théorie, un serveur attend indéfinement !
    while (1) {
        memset(messageEnvoi, 0x0, LG_MESSAGE*sizeof(char));
        memset(messageRecu, 0x0, LG_MESSAGE*sizeof(char));
        printf("Attente d'une demande de connexion (quitter avec Ctrl-C)\n\n");
        // c'est un appel bloquant
        socketDialogue = accept(socketEcoute, (struct sockaddr *)&pointDeRencontreDistant, &longueurAdresse);
        if (socketDialogue < 0) {
            perror("acccept");
            close(socketEcoute);
            exit(-4);
        }

        // On réceptionne les données du client (cf. protocole)
        lus = read(socketDialogue, messageRecu, LG_MESSAGE*sizeof(char)); // ici appel bloquant
        switch (lus) {
            case -1: /* une erreur ! */
                perror("read");
                close(socketDialogue);
                exit(-5);
            case 0: /* la socket est fermée */
                fprintf(stderr, "La socket a été fermée par le client !\n\n");
                close(socketDialogue);
                return 0;
            default: /* réception de n octets */
                printf("Message reçu: %s (%d octets)\n\n", messageRecu, lus);
        }

        // On envoie des données vers le client (cf. protocole)
        sprintf(messageEnvoi, "ok\n");
        ecrits = write(socketDialogue, messageEnvoi, strlen(messageEnvoi));
        switch (ecrits) {
            case -1: /* une erreur ! */
                perror("write");
                close(socketDialogue);
                // close(socketEcoute);
                exit(-6);
            case 0: /* la socket est fermée */
                fprintf(stderr, "La scoket a été fermée par le client !\n\n");
                close(socketDialogue);
                // close(socketEcoute);
                return 0;
            default: /* envoi de n octets */
                printf("Message %s envoyé (%d octets)\n\n", messageEnvoi, ecrits);
        }

        // On ferme la socket de dialogue et on se replace en attente ...
        close(socketDialogue);
    }

    //--- Fin de l'étape numéro 7 !

    // On ferme la ressource avant de quitter
    close(socketEcoute);

    return 0;
}