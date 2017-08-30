#ifndef GMBITMAP_H_INCLUDED
#define GMBITMAP_H_INCLUDED

/**
Header para lidar com bitmaps
Parte do jogo ILP Tanks
Autoria: Gustavo Mota
*/

#include <stdio.h>

#include "gmgraphics.h"

extern bool running;

// DECLARACAO DE SPRITES
SDL_Surface* fundo;
SDL_Surface* terraSp;
SDL_Surface* mar;
SDL_Surface* small_bullet;
SDL_Surface* bomb;
SDL_Surface* marframe1;
SDL_Surface* marframe2;
SDL_Surface* marframe3;
SDL_Surface* marframe4;
SDL_Surface* marframe5;
SDL_Surface* gameover;

SDL_Surface* armas[6];
SDL_Surface* semMunicao;
SDL_Surface* vencedor;

SDL_Surface* instrucoes;

void erro(const char *mensagem);
void carregarSprites();
void printBMP(SDL_Surface* sprite, SDL_Surface *surf, int x0, int y0);
void printBMPfile(char *nomeArquivo, SDL_Surface *surf, int x0, int y0);
void freeBMPsurfaces();

void erro(const char *mensagem){
	// liberar recursos
    printf("%s\n", mensagem);
    running = false;
    //exit(-1);
}

void carregarSprites(){
    fundo = SDL_LoadBMP("fundo.bmp");
    if(fundo == NULL) erro("Nao foi possivel carregar uma imagem.");

    terraSp = SDL_LoadBMP("terra.bmp");
    if(terraSp == NULL) erro("Nao foi possivel carregar uma imagem.");

    small_bullet = SDL_LoadBMP("small_bullet.bmp");
    if(small_bullet == NULL) erro("Nao foi possivel carregar uma imagem.");
    SDL_SetColorKey(small_bullet, SDL_TRUE, SDL_MapRGB(small_bullet->format, 255, 0, 255));

    bomb = SDL_LoadBMP("bomb.bmp");
    if(bomb == NULL) erro("Nao foi possivel carregar uma imagem.");
    SDL_SetColorKey(bomb, SDL_TRUE, SDL_MapRGB(bomb->format, 255, 0, 255));

    marframe1 = SDL_LoadBMP("marframe1.bmp");
    if(marframe1 == NULL) erro("Nao foi possivel carregar uma imagem.");
    marframe2 = SDL_LoadBMP("marframe2.bmp");
    if(marframe2 == NULL) erro("Nao foi possivel carregar uma imagem.");
    marframe3 = SDL_LoadBMP("marframe3.bmp");
    if(marframe3 == NULL) erro("Nao foi possivel carregar uma imagem.");
    marframe4 = SDL_LoadBMP("marframe4.bmp");
    if(marframe4 == NULL) erro("Nao foi possivel carregar uma imagem.");
    marframe5 = SDL_LoadBMP("marframe5.bmp");
    if(marframe5 == NULL) erro("Nao foi possivel carregar uma imagem.");

    armas[0] = SDL_LoadBMP("0.bmp");
    if(armas[0] == NULL) erro("Nao foi possivel carregar uma imagem.");
    armas[1] = SDL_LoadBMP("1.bmp");
    if(armas[1] == NULL) erro("Nao foi possivel carregar uma imagem.");
    armas[2] = SDL_LoadBMP("2.bmp");
    if(armas[2] == NULL) erro("Nao foi possivel carregar uma imagem.");
    armas[3] = SDL_LoadBMP("3.bmp");
    if(armas[3] == NULL) erro("Nao foi possivel carregar uma imagem.");
    armas[4] = SDL_LoadBMP("4.bmp");
    if(armas[4] == NULL) erro("Nao foi possivel carregar uma imagem.");
    armas[5] = SDL_LoadBMP("5.bmp");
    if(armas[5] == NULL) erro("Nao foi possivel carregar uma imagem.");

    semMunicao = SDL_LoadBMP("semmunicao.bmp");
    if(semMunicao == NULL) erro("Nao foi possivel carregar uma imagem.");

    gameover = SDL_LoadBMP("gameover.bmp");
    if(gameover == NULL) erro("Nao foi possivel carregar uma imagem.");
    SDL_SetColorKey(gameover, SDL_TRUE, SDL_MapRGB(gameover->format, 255, 0, 255));

    vencedor = SDL_LoadBMP("vencedor.bmp");
    if(vencedor == NULL) erro("Nao foi possivel carregar uma imagem.");
    SDL_SetColorKey(vencedor, SDL_TRUE, SDL_MapRGB(vencedor->format, 255, 0, 255));

    instrucoes = SDL_LoadBMP("instrucoes.bmp");
    if(instrucoes == NULL) erro("Nao foi possivel carregar uma imagem.");
}

void printBMP(SDL_Surface* sprite, SDL_Surface *surf, int x0, int y0) {

    SDL_Rect destRect;
    destRect.x = x0;
    destRect.y = y0;
    destRect.w = sprite->w;
    destRect.h = sprite->h;

    SDL_BlitSurface(sprite, NULL, surf, &destRect);
}

//lento, evitar
void printBMPfile(char *nomeArquivo, SDL_Surface *surf, int x0, int y0) {

    SDL_Surface *sprite = SDL_LoadBMP(nomeArquivo);
    if(sprite == NULL) erro("Nao foi possivel carregar uma imagem.");

    SDL_Rect destRect;
    destRect.x = x0;
    destRect.y = y0;
    destRect.w = sprite->w;
    destRect.h = sprite->h;

    SDL_BlitSurface(sprite, NULL, surf, &destRect);
}

void freeBMPsurfaces(){
    SDL_FreeSurface(fundo);
    SDL_FreeSurface(terraSp);
    SDL_FreeSurface(mar);
    SDL_FreeSurface(small_bullet);
    SDL_FreeSurface(bomb);
    SDL_FreeSurface(marframe1);
    SDL_FreeSurface(marframe2);
    SDL_FreeSurface(marframe3);
    SDL_FreeSurface(marframe4);
    SDL_FreeSurface(marframe5);
    SDL_FreeSurface(gameover);
    SDL_FreeSurface(armas[0]);
	SDL_FreeSurface(armas[1]);
	SDL_FreeSurface(armas[2]);
	SDL_FreeSurface(armas[3]);
	SDL_FreeSurface(armas[4]);
    SDL_FreeSurface(semMunicao);
    SDL_FreeSurface(vencedor);
    SDL_FreeSurface(instrucoes);
}

#endif // GMBITMAP_H_INCLUDED
