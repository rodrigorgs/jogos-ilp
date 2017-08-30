#ifndef TANKS_H_INCLUDED
#define TANKS_H_INCLUDED

/**
Header principal do jogo
Parte do jogo ILP Tanks
Autoria: Gustavo Mota
*/

#include <math.h>
#include <string.h>

#include "gmbitmap.h"

#ifndef FORCAMAX
#define FORCAMAX 200
#endif

extern Uint16 terra[640];
extern Uint16 terraMin;
extern Uint16 terraMax;

extern SDL_Surface* surface;
extern SDL_Surface* terraSurface;
extern SDL_Surface* terraSp;

extern SDL_Surface* marframe1;
extern SDL_Surface* marframe2;
extern SDL_Surface* marframe3;
extern SDL_Surface* marframe4;
extern SDL_Surface* marframe5;

extern SDL_Surface* armas[6];

#define FIM -128

typedef struct {
    int centroX;
    int centroY;
    int canhaoX;
    int canhaoY;
    bool caindo;
    char movendo;
    char mirando;
    double angulo;
    double anguloCanhao;
    const char *vertices;
    const char *canhao;
    const char *verticesO;
    const char *canhaoO;
    int vida;
    cor corInterna;
    bool canhaoTravado;
    int forca;
    cor corExterna;
    int armaInt;
    int combustivel;
    int municao[6];
} tank;

const char verticesTankO[] = {12, -6, 6, -12, -6, -12, -12, -6, -12, 0, 12, 0, 12, -6, -12, -6, FIM};
const char verticesTank[] = {12, 0, -12, 0, 12, -6, -12, -6, 6, -12, -6, -12, FIM};
const char verticesCanhaoO[] = {3, 0, 3, -12, -3, -12, -3, 0, 3, 0, FIM};
const char verticesCanhao[] = {3, 0, -3, 0, 3, -12, -3, -12, FIM};

char a, b, c, d, e, f, d1, d2, d3, d4, d5, d6;

double cosineInterpolate(double y1, double y2, double mu);
unsigned int nivel(float x);
int valorMedio(int xi, int xf);
double declividade(int xc);
void drawCanhaoOut(tank *t);
void drawCanhao(tank *t);
void drawTankOut(tank *t);
void drawTank(tank *t);
void setPosCanhao(tank *t);
void drawMira(tank *t, int tamanho, float abertura, bool travado);
void explodir(int centro, int r, int queda);
void explosaoTeste();
void gerarTerreno();
void drawTerra();
void desenharTank(tank *t);
void drawHUD(tank *t);
void indicarTurno(tank *t);

double cubicInterpolate(double y0, double y1, double y2, double y3, double mu){

   double a0,a1,a2,a3,mu2;

   mu2 = mu*mu;

   a0 = -0.5*y0 + 1.5*y1 - 1.5*y2 + 0.5*y3;
   a1 = y0 - 2.5*y1 + 2*y2 - 0.5*y3;
   a2 = -0.5*y0 + 0.5*y2;
   a3 = y1;

   return round((a0*mu*mu2+a1*mu2+a2*mu+a3));
}

double cosineInterpolate(double y1, double y2, double mu){
   double mu2 = (1-cos(mu*M_PI))/2;
   return(y1*(1-mu2)+y2*mu2);
}

unsigned int nivel(float x){
    return (round(a*sin(x/d1) - b*sin(x/d2) + c*sin(x/d3) - d*sin(x/d4) + e*sin(x/d5) - f*sin(x/d6))) + 319;
}

int valorMedio(int xi, int xf){
    int num = 0, soma = 0;
    for(; xi <= xf; xi++){
        soma += terra[xi];
        num++;
    }
    return soma/num;
}

double declividade(int xc){
    int i, n = 0;
    double Sxi = 0, Syi = 0, Sxi2 = 0, Sxi_2 = 0, Sxiyi = 0;
    for(i = xc-12; i <= xc+12; i++){
        if(i < 0 || i > 639) continue;
        Sxi += i;
        Syi += terra[i];
        Sxi2 += i*i;
        Sxiyi += i*terra[i];
        n++;
    }
    Sxi_2 = Sxi*Sxi;

    return (n*Sxiyi - Sxi*Syi)/(n*Sxi2 - Sxi_2);
}

void drawCanhaoOut(tank *t){
    int i = 4;
    char listaV[11];
    char listaV2[11];
    while(1){

        //ajuste do angulo do canhao (-9 pra centralizar direito)
        listaV[i-4] = (*(t->canhaoO+i-4))*cos(t->anguloCanhao) - (*(t->canhaoO+i-3))*sin(t->anguloCanhao);
        listaV[i-3] = (*(t->canhaoO+i-4))*sin(t->anguloCanhao) + (*(t->canhaoO+i-3))*cos(t->anguloCanhao);
        listaV[i-2] = (*(t->canhaoO+i-2))*cos(t->anguloCanhao) - (*(t->canhaoO+i-1))*sin(t->anguloCanhao);
        listaV[i-1] = (*(t->canhaoO+i-2))*sin(t->anguloCanhao) + (*(t->canhaoO+i-1))*cos(t->anguloCanhao);

        //-9
        listaV[i-3] -= 9;
        listaV[i-1] -= 9;

        //ajuste no angulo do tanque
        listaV2[i-4] = listaV[i-4]*cos(t->angulo) - listaV[i-3]*sin(t->angulo);
        listaV2[i-3] = listaV[i-4]*sin(t->angulo) + listaV[i-3]*cos(t->angulo);
        listaV2[i-2] = listaV[i-2]*cos(t->angulo) - listaV[i-1]*sin(t->angulo);
        listaV2[i-1] = listaV[i-2]*sin(t->angulo) + listaV[i-1]*cos(t->angulo);

        RETA(t->centroX + listaV2[i-4], t->centroY + listaV2[i-3],
             t->centroX + listaV2[i-2], t->centroY + listaV2[i-1]);

        if(*(t->canhaoO+i) == -128) break;
        i += 2;
    }
}


void drawCanhao(tank *t){
    int i = 6;
    char listaV[9];
    char listaV2[9];

    listaV[0] = (*(t->canhao))*cos(t->anguloCanhao) - (*(t->canhao+1))*sin(t->anguloCanhao);
    listaV[1] = (*(t->canhao))*sin(t->anguloCanhao) + (*(t->canhao+1))*cos(t->anguloCanhao) - 9;
    listaV[2] = (*(t->canhao+2))*cos(t->anguloCanhao) - (*(t->canhao+3))*sin(t->anguloCanhao);
    listaV[3] = (*(t->canhao+2))*sin(t->anguloCanhao) + (*(t->canhao+3))*cos(t->anguloCanhao) - 9;

    listaV2[0] = listaV[0]*cos(t->angulo) - listaV[1]*sin(t->angulo);
    listaV2[1] = listaV[0]*sin(t->angulo) + listaV[1]*cos(t->angulo);
    listaV2[2] = listaV[2]*cos(t->angulo) - listaV[3]*sin(t->angulo);
    listaV2[3] = listaV[2]*sin(t->angulo) + listaV[3]*cos(t->angulo);

    while(1){

        listaV[i-2] = (*(t->canhao+i-2))*cos(t->anguloCanhao) - (*(t->canhao+i-1))*sin(t->anguloCanhao);
        listaV[i-1] = (*(t->canhao+i-2))*sin(t->anguloCanhao) + (*(t->canhao+i-1))*cos(t->anguloCanhao) - 9;

        listaV2[i-2] = listaV[i-2]*cos(t->angulo) - listaV[i-1]*sin(t->angulo);
        listaV2[i-1] = listaV[i-2]*sin(t->angulo) + listaV[i-1]*cos(t->angulo);

        fillTri(listaV2[i-6] + t->centroX, listaV2[i-5] + t->centroY,
                listaV2[i-4] + t->centroX, listaV2[i-3] + t->centroY,
                listaV2[i-2] + t->centroX, listaV2[i-1] + t->centroY);

        if(*(t->canhao+i) == -128) break;
        i += 2;
    }
}

void drawTankOut(tank *t){
    int i = 4;
    char listaV[17];
    while(1){
        //ajuste do angulo do canhao por transformação linear
        listaV[i-4] = (*(t->verticesO+i-4))*cos(t->angulo) - (*(t->verticesO+i-3))*sin(t->angulo);
        listaV[i-3] = (*(t->verticesO+i-4))*sin(t->angulo) + (*(t->verticesO+i-3))*cos(t->angulo);
        listaV[i-2] = (*(t->verticesO+i-2))*cos(t->angulo) - (*(t->verticesO+i-1))*sin(t->angulo);
        listaV[i-1] = (*(t->verticesO+i-2))*sin(t->angulo) + (*(t->verticesO+i-1))*cos(t->angulo);

        RETA(t->centroX + listaV[i-4], t->centroY + listaV[i-3],
             t->centroX + listaV[i-2], t->centroY + listaV[i-1]);
        if(*(t->verticesO+i) == -128) break;
        i += 2;
    }
}


void drawTank(tank *t){
    int i = 6;
    char listaV[13];

    listaV[0] = (*(t->vertices))*cos(t->angulo) - (*(t->vertices+1))*sin(t->angulo);
    listaV[1] = (*(t->vertices))*sin(t->angulo) + (*(t->vertices+1))*cos(t->angulo);
    listaV[2] = (*(t->vertices+2))*cos(t->angulo) - (*(t->vertices+3))*sin(t->angulo);
    listaV[3] = (*(t->vertices+2))*sin(t->angulo) + (*(t->vertices+3))*cos(t->angulo);

    while(1){

        listaV[i-2] = (*(t->vertices+i-2))*cos(t->angulo) - (*(t->vertices+i-1))*sin(t->angulo);
        listaV[i-1] = (*(t->vertices+i-2))*sin(t->angulo) + (*(t->vertices+i-1))*cos(t->angulo);

        fillTri(listaV[i-6] + t->centroX, listaV[i-5] + t->centroY,
                listaV[i-4] + t->centroX, listaV[i-3] + t->centroY,
                listaV[i-2] + t->centroX, listaV[i-1] + t->centroY);

        if(*(t->vertices+i) == -128) break;
        i += 2;
    }
}

void setPosCanhao(tank *t){
    double x, y;
    x = 12*sin(t->anguloCanhao);
    y = -12*cos(t->anguloCanhao) - 9;
    t->canhaoX = t->centroX + x*cos(t->angulo) - y*sin(t->angulo);
    t->canhaoY = t->centroY + x*sin(t->angulo) + y*cos(t->angulo);
}

void drawMira(tank *t, int tamanho, float abertura, bool travado){
    if(travado){
        float a = t->angulo+t->anguloCanhao-(M_PI/2);
        abertura = 180/(abertura/2);

        int x1, y1, x2, y2;

        x1 = getVetorFX(t->canhaoX, a-(M_PI/abertura), tamanho);
        y1 = getVetorFY(t->canhaoY, a-(M_PI/abertura), tamanho);
        x2 = getVetorFX(t->canhaoX, a+(M_PI/abertura), tamanho);
        y2 = getVetorFY(t->canhaoY, a+(M_PI/abertura), tamanho);

        fillTri(x1, y1, x2, y2, t->canhaoX, t->canhaoY);

        SETCOR(220, 220, 220, 255);
        RETA(t->canhaoX, t->canhaoY, x1, y1);
        RETA(x1, y1, x2, y2);
        RETA(x2, y2, t->canhaoX, t->canhaoY);
    } else {
        drawVetorV(t->canhaoX, t->canhaoY, t->angulo+t->anguloCanhao-(M_PI/2), 16); //desenhar vetor no angulo de um composto com outro
    }
}


void explodir(int centro, int r, int queda){
    int x, xmin, xmax;
    int y1, y2;
    double raio;
    double mu, inc;
    terra[centro] += queda;
    raio = r;
    inc = 1/raio;
    mu = 0;
    xmin = centro - raio;
    xmax = centro + raio;
    y1 = xmin - 1 < 0 ?  valorMedio(0, xmax) : terra[xmin - 1];
    y2 = xmax + 1 > 639 ? valorMedio(xmin, 639) : terra[xmax + 1];
    for(x = xmin; x < centro; x++){
        mu += inc;
        if(x < 0 || x > 639) continue;
        terra[x] = cosineInterpolate(y1, terra[centro], mu) < terra[x] ? terra[x] : cosineInterpolate(y1, terra[centro], mu);
        if(terra[x] > terraMin) terraMin = terra[x];
		if(terra[x] < terraMax) terraMax = terra[x];
    }
    mu = 0;
    for(x = centro + 1; x <= xmax; x++){
        mu += inc;
        if(x < 0 || x > 639) continue;
        terra[x] = cosineInterpolate(terra[centro], y2, mu) < terra[x] ? terra[x] : cosineInterpolate(terra[centro], y2, mu);
        if(terra[x] > terraMin) terraMin = terra[x];
		if(terra[x] < terraMax) terraMax = terra[x];
    }
}

void gerarTerreno(){
    bool reverso;
    int start, i, j;
    reverso = rand()%2;
    start = rand()%1279-639;
    a = rand()%33;
    b = a+rand()%17;
    c = a+rand()%17;
    d = a+rand()%17;
    e = a+rand()%17;
    f = a+rand()%17;
    d1 = rand()%16+32;
    d2 = rand()%16+32;
    d3 = rand()%16+32;
    d4 = rand()%16+32;
    d5 = rand()%16+32;
    d6 = rand()%16+32;

    if(reverso){
        for(i = 0; i < 640; i++){
            terra[639-i] = nivel(start+i);
        }
    } else {
        for(i = 0; i < 640; i++){
            terra[i] = nivel(start+i);
        }
    }

    //explodindo a terra
    for(i = 1+rand()%65; i < 640; i += rand()%65){
        explodir(i, 12+rand()%21, 7+rand()%11); //nao da pra explodir negativo devido a uma restricao da funcao explodir (rand()%2 ? -1 : 1)*
    }

    //corrigindo pequenos picos de um pixel de largura:
    for(j = 0; j < 3; j++){
        for(i = 1; i < 640-1; i++){
            if ((terra[i] < terra[i-1] && terra[i] < terra[i+1]) ||
                (terra[i] > terra[i-1] && terra[i] > terra[i+1])){
                terra[i] = round((terra[i-1]+terra[i+1])/2);
            }
        }
    }

    for(i = 0; i < 640; i++){
        if(terra[i] > terraMin) terraMin = terra[i];
		if(terra[i] < terraMax) terraMax = terra[i];
    }
}

void drawTerra(){
    int i;

    SDL_Rect crop;
    crop.x = 0;
    crop.y = terraMax;
    crop.w = 640;
    crop.h = terraMin-terraMax;

    SDL_BlitSurface(terraSp, &crop, terraSurface, &crop);

    SETCOR(255, 0, 255, 255);
    for(i = 0; i < 640; i++){
        RETA(i, terraMax-2, i, terra[i]-1); //ver se tem esse -1 mesmo
    }

    //blitsurfaceaqui
    SDL_BlitSurface(terraSurface, &crop, surface, &crop);

    crop.y = terraMin;
    crop.h = 640-100-terraMin;

    SDL_BlitSurface(terraSp, &crop, surface, &crop);
}

void drawMar(int frame){
    switch(frame){
        case 1:
            printBMP(marframe1, surface, 0, 640-100);
            break;
        case 2:
            printBMP(marframe2, surface, 0, 640-100);
            break;
        case 3:
            printBMP(marframe3, surface, 0, 640-100);
            break;
        case 4:
            printBMP(marframe4, surface, 0, 640-100);
            break;
        case 5:
            printBMP(marframe5, surface, 0, 640-100);
            break;
    }
}

void desenharTank(tank *t){
    SETCOR(t->corInterna.r, t->corInterna.g, t->corInterna.b, t->corInterna.a);
    drawTank(t);
    SETCOR(t->corExterna.r, t->corExterna.g, t->corExterna.b, t->corExterna.a);
    drawTankOut(t);

    SETCOR(t->corInterna.r, t->corInterna.g, t->corInterna.b, t->corInterna.a);
    drawCanhao(t);
    SETCOR(t->corExterna.r, t->corExterna.g, t->corExterna.b, t->corExterna.a);
    drawCanhaoOut(t);


    if(!t->caindo){
        SETCOR(220, 220, 220, 255);
        drawMira(t, FORCAMAX/4, 15, t->canhaoTravado);
        if(t->canhaoTravado){
            SETCOR(235, 20, 20, 255);
            drawMira(t, round((float) t->forca/4), 15, t->canhaoTravado);
        }
    }
}

void drawHUD(tank *t){

    int i, x0, y0;

    x0 = t->centroX-15;
    y0 = t->centroY+15;

    SETCOR(220, 220, 220, 255);

    RETA(x0-1, y0-1, x0+30+1, y0-1);
    for(i = 0; i < 6; i++){
        RETA(x0-1, y0+i, x0+30+1, y0+i);
    }

    SETCOR(100, 100, 100, 225);

    for(i = 0; i < 5; i++){
        RETA(x0, y0+i, x0+30, y0+i);
    }

    if(t->vida > 200){
        SETCOR(110, 230, 70, 255);
    } else if(t-> vida > 100){
        SETCOR(230, 200, 0, 255);
    } else {
        SETCOR(230, 40, 10, 255);
    }

    for(i = 0; i < 5; i++){
        RETA(x0, y0+i, x0+(t->vida)/10, y0+i);
    }

    SETCOR(100, 100, 100, 225);

    for(i = 0; i < 2; i++){
        RETA(x0-1, y0+i+8, x0-1+32, y0+i+8);
    }

    SETCOR(255, 180, 0, 255);

    for(i = 0; i < 2; i++){
        RETA(x0-1, y0+i+8, x0-1+(t->combustivel)/3, y0+i+8);
    }

    if(t->municao[t->armaInt] <= 0 && !t->canhaoTravado) printBMP(semMunicao, surface, x0+8, y0+12);
    else printBMP(armas[t->armaInt], surface, x0+8, y0+12);

}

void indicarTurno(tank *t){
    static int xinc = 0, largura = 5;
    int tX = t->centroX, tY = t->centroY;
    SETCOR(240, 200, 0, 255);
    fillTri(tX, tY-32+(xinc/20), tX-largura, tY-32+(xinc/20)-12, tX+largura, tY-32+(xinc/20)-12);
    xinc += 2;
    if(xinc > 79) xinc = 0;
}

#endif // TANKS_H_INCLUDED
