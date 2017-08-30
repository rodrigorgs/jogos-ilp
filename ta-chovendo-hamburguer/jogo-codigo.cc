#include "ilpgame.h"
#include <time.h>

#define TELA_LARGURA 700
#define TELA_ALTURA 400

#define QTD_MAX_ARVORES 8

#define ARVORE_LARGURA 30
#define ARVORE_ALTURA 30

#define MALE_LARGURA 44
#define MALE_ALTURA 77

#define POSICAO_CHAO 300

SDL_Surface *imgMale;
SDL_Surface *imgArvore;
SDL_Surface *background;

TTF_Font *font;
SDL_Color whiteColor = {000, 000, 000, 255};
Uint32 tempoInicial;
string textoContador;

Mix_Music *musica;

typedef struct {
  float x, y;
  float velx, vely;
  float largura, altura;
} retangulo;
retangulo player;
retangulo arvores[QTD_MAX_ARVORES];
float velocidade = 10.0f;
float velocidadeVertical = 0.07f;
float aceleracaoVertical = 0.005f;

void inicializaArvore(int i) {
  arvores[i].largura = ARVORE_LARGURA;
  arvores[i].altura = ARVORE_ALTURA;
  arvores[i].x = rand() % 656;
  arvores[i].y = -arvores[i].largura - (rand() % 656);
}

void init() {
  srand(time(NULL));
  
  musica = loadMusic("happy.mp3");
  Mix_PlayMusic(musica, -1);
  
  background = loadImage("background.jpg");
  imgMale = loadImage("male.png");
  imgArvore = loadImage("arvore.jpg");
  
  player.x = POSICAO_CHAO;
  player.y = 650.0f;
  player.largura = MALE_LARGURA;
  player.altura = MALE_ALTURA;

  for (int i = 0; i < QTD_MAX_ARVORES; i++) {
    inicializaArvore(i);
  }
  font = loadFont("FreeSans.ttf", 40);
  tempoInicial = SDL_GetTicks();
}

void destroy() {
  Mix_FreeMusic(musica);
  SDL_FreeSurface(background);
  SDL_FreeSurface(imgMale);
  SDL_FreeSurface(imgArvore);
  TTF_CloseFont(font);
}

void processEvent(SDL_Event event) {
  SDL_Keycode keycode;

   if (isQuitEvent(event)) {
    endGameLoop();
  } else if (event.type == SDL_KEYDOWN) {
    keycode = event.key.keysym.sym;
    if (keycode == SDLK_LEFT) player.x -= velocidade;
    else if (keycode == SDLK_RIGHT) player.x += velocidade;
  }
}

void atualizaPosicaoplayer() {
  player.velx = player.velx;
  player.x = player.x + player.velx;

  if (player.y > POSICAO_CHAO) {
    player.y = POSICAO_CHAO;
  }
   if (player.x >= TELA_LARGURA - MALE_LARGURA) {
    player.x = TELA_LARGURA - MALE_LARGURA;
  }
  if (player.x <= 0){
  	player.x = 0;
  }
}

void atualizaArvores() {
  int i;

  for (i = 0; i < QTD_MAX_ARVORES; i++) {
    arvores[i].y += velocidadeVertical;
    if (arvores[i].y > TELA_ALTURA) {
      
      inicializaArvore(i);

      velocidadeVertical += aceleracaoVertical;
      if (velocidadeVertical>1.0f){
      	velocidadeVertical=1.0f;
	  }
    }
  }

}

void detectaColisao(int i) {
  float ax1 = arvores[i].x,
      ay1 = arvores[i].y,
      ax2 = arvores[i].x + arvores[i].largura,
      ay2 = arvores[i].y + arvores[i].altura;
  float jx1 = player.x,
      jy1 = player.y,
      jx2 = player.x + player.largura,
      jy2 = player.y + player.altura;
  bool colidiu = true;
  if (ax1 > jx2 || ay1 > jy2 || jx1 > ax2 || jy1 > ay2) {
    colidiu = false;
  }

  if (colidiu) {
    endGameLoop();
  }
}

void update() {
  int i;

  int segundosDecorridos = (SDL_GetTicks() - tempoInicial) / 1000;
  textoContador = tostring(segundosDecorridos);
  
  atualizaPosicaoplayer();
  atualizaArvores();
  

  for (i = 0; i < QTD_MAX_ARVORES; i++) {
    detectaColisao(i);
  }
}

void draw() {
  int i;

  drawImage(background, 0, 0);
  drawImage(imgMale, player.x, player.y);
  for (i = 0; i < QTD_MAX_ARVORES; i++) {
    drawImage(imgArvore,
      arvores[i].x, arvores[i].y);
  }
  drawText(textoContador, font, whiteColor, 10, 30);
}

int main(int argc, char *argv[]) {
  initSDL(TELA_LARGURA, TELA_ALTURA);
  gameLoop();
  return 0;
}

