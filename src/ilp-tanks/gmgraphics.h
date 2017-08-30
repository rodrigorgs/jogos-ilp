#ifndef GMGRAPHICS_H_INCLUDED
#define GMGRAPHICS_H_INCLUDED

/**
Funções e tipos em C para gráficos
Autoria: Gustavo Mota
*/

#include <math.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#define RAD 0.017453

#define CLEAR() SDL_RenderClear(rendererAtual)
#define UPDATE() SDL_RenderPresent(rendererAtual)
#define PONTO(x, y) SDL_RenderDrawPoint(rendererAtual, x, y)
#define RETA(a, b, c, d) SDL_RenderDrawLine(rendererAtual, a, b, c, d)
#define RANDCOR() SDL_SetRenderDrawColor(rendererAtual, rand()%256, rand()%256, rand()%256, 255) //fazer mais funções pra lidar com cor depois
#define SETCOR(r, g, b, a) setCorV(r, g, b, a)

#define MAIOR(x,y) ((x) >= (y)) ? (x) : (y)
#define MENOR(x,y) ((x) <= (y)) ? (x) : (y)
#define CROSS2D(x1, y1, x2, y2) (x1*y2 - x2*y1)

#define CLAMP0(x, a, b) x >= a && x <= b ? x : 0

typedef struct {
	int x;
	int y;
} ponto;

typedef struct {
	int xi;
	int yi;
	int xf;
	int yf;
} linhaReta;    // mudar de linhaReta pra reta

typedef struct {
	int xi;
	int yi;
	float ang;
	float mod;
} vetor;

typedef struct {
	int xc;
	int yc;
	unsigned int l;
	float r;
	float g0;
} poligono;

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} cor;

SDL_Renderer* rendererAtual;

cor corAtual;

void drawPonto(ponto p);
void drawReta(linhaReta reta);
void drawRetaP(ponto p1, ponto p2);
void drawVetor(vetor vet);
void drawVetorP(ponto p, float ang, float mod);
void drawVetorV(float xi, float yi, double ang, float mod);
void drawPoligono(poligono poli);
void drawPoligonoP(ponto p, unsigned int l, float r, float g0);
void drawPoligonoV(float xc, float yc, unsigned int l, float r, float g0);
void setCor(cor c);
void setCorV(int r, int g, int b, int a);
void fillTri(int x1, int y1, int x2, int y2, int x3, int y3);
int getVetorFX(float xi, double ang, float mod);
int getVetorFY(float yi, double ang, float mod);

void drawPonto(ponto p){
    PONTO(p.x, p.y);
}

void drawReta(linhaReta reta){
	RETA(reta.xi, reta.yi, reta.xf, reta.yf);
}

void drawRetaP(ponto p1, ponto p2){
	RETA(p1.x, p1.y, p2.x, p2.y);
}

void drawVetor(vetor vet){
	drawVetorV(vet.xi, vet.yi, vet.ang, vet.mod);
}

void drawVetorP(ponto p, float ang, float mod){
	drawVetorV(p.x, p.y, ang, mod);
}

void drawVetorV(float xi, float yi, double ang, float mod){
	short xf = round(xi+mod*cos(ang));
	short yf = round(yi+mod*sin(ang));
	RETA(xi, yi, xf, yf);
}

int getVetorFX(float xi, double ang, float mod){
    return round(xi+mod*cos(ang));
}

int getVetorFY(float yi, double ang, float mod){
    return round(yi+mod*sin(ang));
}

void drawPoligono(poligono poli){
	drawPoligonoV(poli.xc, poli.yc, poli.l, poli.r, poli.g0);
}

void drawPoligonoP(ponto p, unsigned int l, float r, float g0){
	drawPoligonoV(p.x, p.y, l, r, g0);
}

void drawPoligonoV(float xc, float yc, unsigned int l, float r, float g0){
 	float xi = xc+r*cos(g0*RAD);
	float yi = yc+r*sin(g0*RAD);
	float xf, yf;
	float angrad = (float) 360/l;
	for(; l > 0; l--){
		g0 += angrad;
		xf = xc+r*cos(g0*RAD);
		yf = yc+r*sin(g0*RAD);
		RETA(xi, yi, xf, yf);
		xi = xf;
		yi = yf;
	}
}

void setCor(cor c){
    setCorV(c.r, c.g, c.b, c.a);
}

void setCorV(int r, int g, int b, int a){
    SDL_SetRenderDrawColor(rendererAtual, r, g, b, a);
    corAtual.r = r;
    corAtual.g = g;
    corAtual.b = b;
    corAtual.a = a;
}

void fillTri(int x1, int y1, int x2, int y2, int x3, int y3){

    // bounding box
    int maxX = MAIOR(x1, MAIOR(x2, x3));
    int minX = MENOR(x1, MENOR(x2, x3));
    int maxY = MAIOR(y1, MAIOR(y2, y3));
    int minY = MENOR(y1, MENOR(y2, y3));

    int vs1_x = x2 - x1;
    int vs1_y = y2 - y1;
    int vs2_x = x3 - x1;
    int vs2_y = y3 - y1;

    int x, y, qx, qy;

    float s, t;

    float temp = (float) CROSS2D(vs1_x, vs1_y, vs2_x, vs2_y);

    for (x = minX; x <= maxX; x++){

        for (y = minY; y <= maxY; y++){

            qx = x - x1;
            qy = y - y1;

            s = (float) CROSS2D(qx, qy, vs2_x, vs2_y) / temp;
            t = (float) CROSS2D(vs1_x, vs1_y, qx, qy) / temp;

            if ((s >= 0) && (t >= 0) && (s + t <= 1)){   // dentro

                PONTO(x, y); //essa é a parte lenta
            }
        }
    }
}

#endif // GMGRAPHICS_H_INCLUDED
