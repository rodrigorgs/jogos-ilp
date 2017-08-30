#ifndef BULLETS_H_INCLUDED
#define BULLETS_H_INCLUDED

/**
Header para lidar com projeteis
Parte do jogo ILP Tanks
Autoria: Gustavo Mota
*/

#include <math.h>
#include <stdlib.h>

#include "gmbitmap.h"
#include "gmgraphics.h"
#include "tanks.h"

#define NUMPART 40
#define G 22
#define RESISTENCIA 0.001

typedef enum {bala = 0, canhao = 1, bomba = 2, napalm = 3, acido = 4, aerial = 5} tipoProjetil;
typedef enum {particula = 0, pequena = 1, grande = 2} tipoSprite;

extern SDL_Surface* small_bullet;
extern SDL_Surface* bomb;

extern bool tirosVoando;

extern tank *pTank[2];

typedef struct {
    float x;
    float y;
    float vel_x;
    float vel_y;
    float acel_x;
    float acel_y;
    unsigned int timeToLive;
    bool isAlive;
    unsigned char r;
    unsigned char g;
    unsigned char b;
    tipoProjetil tipo;
    tipoSprite sprite;
    int raioExp;
    int quedaExp;
    int dano;
} projetil;

void criarProjetil(tank *t, tipoProjetil classe, int forca);
void atualizar(float t);
void checarColisao();
void drawParticulas();
void deflagrar(projetil *b);

projetil artilharia[NUMPART];

void criarProjetil(tank *t, tipoProjetil classe, int forca){
    int i;
    for(i = 0; i < NUMPART; i++){
        if(!artilharia[i].isAlive){
            artilharia[i].isAlive = true;
            break;
        }
    }
    if(i == NUMPART) return;
    switch(classe){
        default:
        case bala:
            artilharia[i].x = t->canhaoX;
            artilharia[i].y = t->canhaoY;
            artilharia[i].vel_x = forca*cos(t->angulo+t->anguloCanhao-(M_PI/2));
            artilharia[i].vel_y = forca*sin(t->angulo+t->anguloCanhao-(M_PI/2));
            artilharia[i].acel_x = 0;
            artilharia[i].acel_y = G;
            artilharia[i].timeToLive = 0;
            artilharia[i].r = 255;
            artilharia[i].g = 255;
            artilharia[i].b = 255;
            artilharia[i].tipo = bala;
            artilharia[i].sprite = particula;
            artilharia[i].raioExp = 12;
            artilharia[i].quedaExp = 16;
            artilharia[i].dano = 20;
            break;
        case napalm:
            artilharia[i].x = t->canhaoX - 1 + rand()%3;
            artilharia[i].y = t->canhaoY - 1 + rand()%3;
            artilharia[i].vel_x = forca*(cos(t->angulo+t->anguloCanhao-(M_PI/2))-0.05+(float)(rand()%101)*0.001);
            artilharia[i].vel_y = forca*(sin(t->angulo+t->anguloCanhao-(M_PI/2))-0.05+(float)(rand()%101)*0.001);
            artilharia[i].acel_x = 0;
            artilharia[i].acel_y = G;
            artilharia[i].timeToLive = 0;
            artilharia[i].r = 255;
            artilharia[i].g = 255-rand()%206;
            artilharia[i].b = 0;
            artilharia[i].tipo = napalm;
            artilharia[i].sprite = particula;
            artilharia[i].raioExp = 8;
            artilharia[i].quedaExp = 0;
            artilharia[i].dano = 8;
            break;
        case acido:
            artilharia[i].x = t->canhaoX - 1 + rand()%3;
            artilharia[i].y = t->canhaoY - 1 + rand()%3;
            artilharia[i].vel_x = forca*(cos(t->angulo+t->anguloCanhao-(M_PI/2))-0.075+(float)(rand()%151)*0.001);
            artilharia[i].vel_y = forca*(sin(t->angulo+t->anguloCanhao-(M_PI/2))-0.075+(float)(rand()%151)*0.001);
            artilharia[i].acel_x = 0;
            artilharia[i].acel_y = G;
            artilharia[i].timeToLive = 0;
            artilharia[i].r = 0;
            artilharia[i].g = 255;
            artilharia[i].b = 255-rand()%106;
            artilharia[i].tipo = acido;
            artilharia[i].sprite = particula;
            artilharia[i].raioExp = 7;
            artilharia[i].quedaExp = 11;
            artilharia[i].dano = 7;
            break;
        case canhao:
            artilharia[i].x = t->canhaoX;
            artilharia[i].y = t->canhaoY;
            artilharia[i].vel_x = forca*cos(t->angulo+t->anguloCanhao-(M_PI/2));
            artilharia[i].vel_y = forca*sin(t->angulo+t->anguloCanhao-(M_PI/2));
            artilharia[i].acel_x = 0;
            artilharia[i].acel_y = G;
            artilharia[i].timeToLive = 0;
            artilharia[i].r = 255;
            artilharia[i].g = 0;
            artilharia[i].b = 0;
            artilharia[i].tipo = canhao;
            artilharia[i].sprite = pequena;
            artilharia[i].raioExp = 18;
            artilharia[i].quedaExp = 18;
            artilharia[i].dano = 35;
            break;
        case bomba:
            artilharia[i].x = t->canhaoX;
            artilharia[i].y = t->canhaoY;
            artilharia[i].vel_x = forca*cos(t->angulo+t->anguloCanhao-(M_PI/2));
            artilharia[i].vel_y = forca*sin(t->angulo+t->anguloCanhao-(M_PI/2));
            artilharia[i].acel_x = 0;
            artilharia[i].acel_y = G;
            artilharia[i].timeToLive = 0;
            artilharia[i].r = 255;
            artilharia[i].g = 0;
            artilharia[i].b = 0;
            artilharia[i].tipo = bomba;
            artilharia[i].sprite = grande;
            artilharia[i].raioExp = 34;
            artilharia[i].quedaExp = 34;
            artilharia[i].dano = 50;
            break;
        case aerial:
            artilharia[i].x = t->canhaoX;
            artilharia[i].y = t->canhaoY;
            artilharia[i].vel_x = forca*cos(t->angulo+t->anguloCanhao-(M_PI/2));
            artilharia[i].vel_y = forca*sin(t->angulo+t->anguloCanhao-(M_PI/2));
            artilharia[i].acel_x = 0;
            artilharia[i].acel_y = G;
            artilharia[i].timeToLive = 0;
            artilharia[i].r = 255;
            artilharia[i].g = 255;
            artilharia[i].b = 255;
            artilharia[i].tipo = aerial;
            artilharia[i].sprite = particula;
            artilharia[i].raioExp = 0;
            artilharia[i].quedaExp = 0;
            artilharia[i].dano = 0;
            break;
    }
}

void atualizar(float t){
    int i;
    bool particulasVivas = false;
    for(i = 0; i < NUMPART; i++){
        if(artilharia[i].isAlive){
            artilharia[i].acel_x = -1*artilharia[i].vel_x*abs(artilharia[i].vel_x)*RESISTENCIA;
            artilharia[i].acel_y = -1*artilharia[i].vel_y*abs(artilharia[i].vel_y)*RESISTENCIA + G;
            artilharia[i].vel_x += artilharia[i].acel_x*t;
            artilharia[i].vel_y += artilharia[i].acel_y*t;
            artilharia[i].x += artilharia[i].vel_x*t;
            artilharia[i].y += artilharia[i].vel_y*t;
            particulasVivas = true;
        }
    }
    tirosVoando = particulasVivas;
}

void checarColisao(){
    int i;
    for(i = 0; i < NUMPART; i++){
        if(artilharia[i].isAlive){
            if(artilharia[i].timeToLive == 1 || artilharia[i].y >= terra[(int) round(artilharia[i].x)]){
                deflagrar(&artilharia[i]); //explodir e matar a particula nessa função
            } else if(artilharia[i].x < 0 || artilharia[i].x > 639 || artilharia[i].y > 639){
                artilharia[i].isAlive = false;
            }
        }
    }
}

void drawParticulas(){
    int i;
    for(i = 0; i < NUMPART; i++){
        if(artilharia[i].isAlive){
            SETCOR(artilharia[i].r, artilharia[i].g, artilharia[i].b, 255);
            switch(artilharia[i].sprite){
                default:
                case particula:
                    PONTO(round(artilharia[i].x), round(artilharia[i].y));
                    //
                    PONTO(round(artilharia[i].x-1), round(artilharia[i].y));
                    PONTO(round(artilharia[i].x+1), round(artilharia[i].y));
                    PONTO(round(artilharia[i].x), round(artilharia[i].y-1));
                    PONTO(round(artilharia[i].x), round(artilharia[i].y+1));
                    break;
                case pequena:
                    printBMP(small_bullet, surface, (int) round(artilharia[i].x)-3, (int) round(artilharia[i].y)-3);
                    break;
                case grande:
                    printBMP(bomb, surface, (int) round(artilharia[i].x)-3, (int) round(artilharia[i].y)-3);
                    break;
            }
        }
    }
}

void deflagrar(projetil *b){
    int i;
    if(b->tipo == aerial){
        tank temp;
        temp.canhaoX = b->x-14;
        temp.canhaoY = 1;
        //temp.forca = 0;
        criarProjetil(&temp, canhao, 0);
        temp.canhaoX = b->x;
        criarProjetil(&temp, canhao, 0);
        temp.canhaoX = b->x+14;
        criarProjetil(&temp, canhao, 0);

    }else if(b->x >= 0 && b->x <= 639){
        for(i = 0; i < 2; i++){
            if(abs(pTank[i]->centroX - (int)(b->x)) <= b->raioExp && abs(pTank[i]->centroY - (int)(b->y)) <= b->raioExp) pTank[i]->vida -= b->dano;
            if(pTank[i]->vida < 0) pTank[i]->vida = 0;
        }
        explodir(b->x, b->raioExp, b->quedaExp);
    }
    b->isAlive = false;
}

#endif // BULLETS_H_INCLUDED
