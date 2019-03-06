#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>
#include "gameSDL.h"

int  read_client(int client, s_game *game)
{
    int  n;
    int b = 0;
    int a = 0;
    char buff[128];
    char barreY[4];
    char balleX[4];
    char balleY[4];
    if (client == -1)
    {
        return 1;
    }

    n = 0;
    memset(buff, '\0', 15);
    n = recv(client, buff, 12, 0);
    {
        if (n == 0)
        {
            return -1;
        }

        for (unsigned int i=0; buff[i] != '\0'; i++){
            if (buff[i] == ';'){
                b = 0;
                i++;
                a++;
            }
            if(a == 0){
                barreY[b] = buff[i];
            }
            if(a == 1){
                balleX[b] = buff[i];
            }
            if(a == 2){
                balleY[b] = buff[i];
            }
            b++;
        }
        game->positionBarre.y = atoi(barreY);
        game->positionBalle.x = atoi(balleX);
        game->positionBalle.y = atoi(balleY);

        memset(buff, '\0', 15);
    }
    return 0;
}

void calc_score(s_game *game, int *score1, int *score2){
    if(game->positionBalle.x < game->positionBarre.x){
        game->positionBalle.x = 500;
        *score2 = *score2 + 1 ;
        SDL_Delay(1000);
    }
    if (game->positionBalle.x > 980){
        game->positionBalle.x = 500;
        *score1 = *score1 + 1;
        SDL_Delay(1000);
    }
}
int   recv_serveur(const char *sTextIp, const char *sTextPort)
{
    char *buffer;
    buffer = calloc(3, sizeof(char));
    int y;
    int sock;
    int client1;
    int score1 = 0;
    int score2 = 0;
    socklen_t client_addr_len;
    struct sockaddr_in server;
    struct sockaddr_in client_addr;

    fd_set readfs;
    struct timeval timeout;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        perror("socket()");
        return 1;
    }

    server.sin_addr.s_addr = inet_addr(sTextIp);
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(sTextPort));

    if (bind(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("bind()");
        return 1;
    }

    listen(sock, 5);

    puts("waiting clients...");
    puts("waiting for accept");
    client1 = accept(sock, (struct sockaddr *)&client_addr, &client_addr_len);

    if (client1 < 0 )
    {
        perror("accept()");
        return 1;
    }
    puts("new clients");


    s_Fenetre *fen = init_fenetre();
    int quitGame = 0;
    s_game *game = NULL;
    game = init_position(game);
    init_game(fen, game);

    while (quitGame != -1 && score1 != 3 && score2 != 3)
    {
        draw_game(fen, game);
        quitGame = event_game(game);
        calc_score(game,&score1,&score2);
        /*****************************************/
        timeout.tv_sec = 0.1;
        timeout.tv_usec = 0;

        FD_ZERO(&readfs);

        FD_SET(client1, &readfs);

        select(client1 + 1, &readfs, NULL, NULL, &timeout);

        if (FD_ISSET(client1, &readfs))
        {
            read_client(client1, game);
        }
        memset(buffer, '\0', 5);
        y = game->positionBarre2.y;
        sprintf(buffer,"%d",y);
        strcat(buffer, ";");
        send(sock,buffer,strlen(buffer),MSG_NOSIGNAL);
        memset(buffer, '\0', 5);
        /**********************************************/
        SDL_Delay(20);
    }
    free(buffer);
    destroy_game(game);
    fenetre_destroy(fen);
    return (EXIT_SUCCESS);

    close(sock);
    return 0;
}
