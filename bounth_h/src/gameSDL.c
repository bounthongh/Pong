#include "../header/menuGTK.h"
#include "../header/gameSDL.h"

s_Fenetre       *init_fenetre()
{
    s_Fenetre   *fen = NULL;

    fen = malloc(sizeof(s_Fenetre));
    fen->screenSize.x = 1000;
    fen->screenSize.y = 750;
    fen->pWindow = NULL;
    fen->pRenderer = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "Impossible d'initialiser la SDL : %s\n", SDL_GetError());
        fenetre_destroy(fen);
    }
    fen->pWindow = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, fen->screenSize.x, fen->screenSize.y, SDL_WINDOW_SHOWN);
    if (fen->pWindow)
    {
        fen->pRenderer = SDL_CreateRenderer(fen->pWindow, -1, SDL_RENDERER_ACCELERATED);
        if (!fen->pRenderer)
        {
            fprintf(stderr, "Impossible d'initialiser le renderer : %s\n", SDL_GetError());
            fenetre_destroy(fen);
            return (NULL);
        }
    }
    else
    {
        fprintf(stderr, "Impossible d'initialiser la fen : %s\n", SDL_GetError());
        fenetre_destroy(fen);
        return (NULL);
    }
    return (fen);
}



void            fenetre_destroy(s_Fenetre *fen)
{
    if (fen)
    {
        if (fen->pRenderer)
        {
            SDL_DestroyRenderer(fen->pRenderer);
        }
        if (fen->pWindow)
        {
            SDL_DestroyWindow(fen->pWindow);
        }
        SDL_Quit();
        free(fen);
    }
}




s_game              *init_game(s_Fenetre *fen, s_game *game)
{
    SDL_Surface *fondEcranSurface = IMG_Load("img/fond_pong.png");
    SDL_Surface *barreSurface = IMG_Load("img/barre_pong.png");
    SDL_Surface *barreSurface2 = IMG_Load("img/barre_pong.png");
    SDL_Surface *balleSurface = IMG_Load("img/balle_pong.png");

    if (fondEcranSurface)
    {
        game->pFond = SDL_CreateTextureFromSurface(fen->pRenderer, fondEcranSurface);
    }

    if (barreSurface)
    {
        game->pBarre = SDL_CreateTextureFromSurface(fen->pRenderer, barreSurface);
    }
    if (barreSurface2)
    {
        game->pBarre2 = SDL_CreateTextureFromSurface(fen->pRenderer, barreSurface2);
    }

    if (balleSurface)
    {
        game->pBalle = SDL_CreateTextureFromSurface(fen->pRenderer, balleSurface);
    }

    SDL_FreeSurface(balleSurface);
    SDL_FreeSurface(barreSurface);
    SDL_FreeSurface(fondEcranSurface);
    return game;
}




void            destroy_game(s_game *game)
{
    if (game)
    {
        if (game->pBarre)
        {
            SDL_DestroyTexture(game->pBarre);
        }
        if (game->pFond)
        {
            SDL_DestroyTexture(game->pFond);
        }
        free(game);
    }
}





void            draw_game(s_Fenetre *fen, s_game *game)
{
    SDL_RenderCopy(fen->pRenderer, game->pFond, NULL, NULL);
    SDL_RenderCopy(fen->pRenderer, game->pBarre, NULL, &game->positionBarre);
    SDL_RenderCopy(fen->pRenderer, game->pBarre, NULL, &game->positionBarre2);
    SDL_RenderCopy(fen->pRenderer, game->pBalle, NULL, &game->positionBalle);
    SDL_RenderPresent(fen->pRenderer);
}




s_game              *init_position(s_game *game)
{
    game = NULL;
    game = malloc(sizeof(s_game));

    game->positionBarre.x = 20;
    game->positionBarre.y = 150;
    game->positionBarre.w = 20;
    game->positionBarre.h = 150;

    game->positionBarre2.x = 960;
    game->positionBarre2.y = 150;
    game->positionBarre2.w = 20;
    game->positionBarre2.h = 150;

    game->positionBalle.x = 500;
    game->positionBalle.y = 375;
    game->positionBalle.w = 20;
    game->positionBalle.h = 20;
    return (game);
}

int                 event_game(s_game *game)
{
    int quit = 0;
    SDL_Event event;
    if (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            quit = -1;
        }
        else if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    quit = -1;
                    break;
                case SDLK_DOWN:
                    down_key_event(game);
                    break;
                case SDLK_UP:
                    up_key_event(game);
                    break;
                default:
                    quit = 0;
            }
        }
    }
    return (quit);
}

void                up_key_event(s_game *game)
{
    if (game->positionBarre.y > 0)
    {
        game->positionBarre.y = game->positionBarre.y - 30;
    }
}

void                down_key_event(s_game *game)
{
    if (game->positionBarre.y < 600)
    {
        game->positionBarre.y = game->positionBarre.y + 30;
    }
}

void                IA_balle(s_game *game, int *droite, int *angleY, int *score1, int *score2)
{
    /* Collision bordure haut et bas */
    if (game->positionBalle.y <= 0 ||  game->positionBalle.y >= 750){
        *angleY = *angleY * (-1);
    }
    /* Si droite = 0 alors la balle part a gauche */
    if (*droite == 0){
        /* Collision Joueur Gauche */
        if (game->positionBalle.x == game->positionBarre.x &&
            game->positionBalle.y > game->positionBarre.y &&
            game->positionBalle.y < game->positionBarre.y + 150) {
            *droite = 1;
            /* Calcule d'angle */
            *angleY = (game->positionBalle.y - (game->positionBarre.y + 75))/10;
            game->positionBalle.x = game->positionBalle.x + 5;
        }
        /* Deplacement balle */
        game->positionBalle.x = game->positionBalle.x - 2;
        game->positionBalle.y = game->positionBalle.y + *angleY;

        if(game->positionBalle.x < game->positionBarre.x){
            game->positionBalle.x = 500;
            *droite = 1;
            *score2 = *score2 + 1 ;
            SDL_Delay(1000);
        }
    }
    else{
        if (game->positionBalle.x > 980){
            game->positionBalle.x = 500;
            *droite = 0;
            *score1 = *score1 + 1;
            SDL_Delay(1000);
        }
        if (game->positionBalle.x == game->positionBarre2.x &&
            game->positionBalle.y > game->positionBarre2.y &&
            game->positionBalle.y < game->positionBarre2.y + 150) {
            *droite = 0;
            /* Calcule d'angle */
            *angleY = (game->positionBalle.y - (game->positionBarre2.y + 75))/10;
            game->positionBalle.x = game->positionBalle.x + 5;
        }
        /* Deplacement balle */
        game->positionBalle.x = game->positionBalle.x + 2;
        game->positionBalle.y = game->positionBalle.y + *angleY;
    }
}
int                 game(const char *sTextIp, const char *sTextPort, const char *sTextStatus)
{

    /********************************/
    if(!strcmp(sTextStatus, "s")){
        recv_serveur(sTextIp,sTextPort);
    }
    else if(!strcmp(sTextStatus, "c")){
        send_client(sTextIp,sTextPort);
    }
    /********************************/
    return(0);
}
