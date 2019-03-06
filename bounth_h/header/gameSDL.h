#ifndef __GAMESDL_H__
#define __GAMESDL_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <regex.h>

typedef struct      t_Fenetre
{
    // variable de la sdl
    SDL_Point       screenSize;
    SDL_Window      *pWindow;
    SDL_Renderer    *pRenderer;
}                   s_Fenetre;

typedef struct      t_game
{
    //Texture curseurs + background
    SDL_Texture     *pBarre;
    SDL_Texture     *pBarre2;
    SDL_Texture     *pFond;
    SDL_Texture     *pBalle;

    //Rectangle des curseurs
    SDL_Rect        positionBarre;
    SDL_Rect        positionBarre2;
    SDL_Rect        positionBalle;
}                   s_game;

s_Fenetre           *init_fenetre();
void                fenetre_destroy(s_Fenetre *fen);
s_game              *init_game(s_Fenetre *fen, s_game *game);
s_game              *init_position(s_game *game);
void                up_key_event(s_game *game);
void                down_key_event(s_game *game);
void                destroy_game(s_game *game);
void                draw_game(s_Fenetre*fen, s_game *game);
int                 event_game(s_game *game);
void                IA_balle(s_game *game, int *droite, int *angleY, int *score1, int *score2);
int                 game(const char *sTextIp, const char *sTextPort, const char *sTextStatus);
void                calc_score(s_game *game, int *score1, int *score2);

#endif
