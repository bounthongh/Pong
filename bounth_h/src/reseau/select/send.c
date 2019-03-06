#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "gameSDL.h"

int   send_client(const char *sTextIp, const char *sTextPort) {
    int sock;
    int server1;
    fd_set readfs;
    struct timeval timeout;
    struct sockaddr_in server;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("socket()");
        exit(errno);
    }

    server.sin_addr.s_addr = inet_addr(sTextIp);
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(sTextPort));

    server1 = connect(sock, (struct sockaddr *) &server, sizeof(server));

    /********** SDL **********/
    char *buffer;
    char *temp;
    char buff[128];
    int score1 = 0;
    int score2 = 0;
    int y;
    int quitGame = 0;
    int droite = 0;
    int angleY = 0;

    temp = malloc(3);
    buffer = malloc(3);
    s_Fenetre *fen = init_fenetre();
    s_game *game = NULL;
    game = init_position(game);
    init_game(fen, game);
    while (quitGame != -1 && score1 != 3 && score2 != 3) {
        draw_game(fen, game);
        quitGame = event_game(game);
        IA_balle(game, &droite, &angleY,&score1,&score2);

        memset(buffer, '\0', 12);
        y = game->positionBarre.y;
        sprintf(buffer,"%d",y);
        strcat(buffer, ";");
        sprintf(temp,"%d",game->positionBalle.x);
        strcat(buffer, temp);
        strcat(buffer, ";");
        sprintf(temp,"%d",game->positionBalle.y);
        strcat(buffer, temp);
        strcat(buffer, ";");

        send(sock,buffer,strlen(buffer),MSG_NOSIGNAL);
        memset(buff, '\0', 4);

        timeout.tv_sec = 0.1;
        timeout.tv_usec = 0;
        FD_ZERO(&readfs);

        FD_SET(server1, &readfs);
        select(server1 + 1, &readfs, NULL, NULL, &timeout);
        recv(server1, buff, 5, 0);
        memset(buff, '\0', 4);

        SDL_Delay(20);
    }
    destroy_game(game);
    fenetre_destroy(fen);
    free(temp);
    free(buffer);
    return (EXIT_SUCCESS);

    close(sock);
    return 0;
}
