#include "ilpgame.h"

#define TELA_LARGURA 800
#define TELA_ALTURA 600

#define QTD_MAX_TUBARAO 5

#define TUBARAO_LARGURA 69
#define TUBARAO_ALTURA 149

#define MERGULHADOR_LARGURA 27
#define MERGULHADOR_ALTURA 84

SDL_Surface *imgMergulhador;
SDL_Surface *imgTubarao;
SDL_Surface *background;
Mix_Music *musica;

typedef struct {
  float x, y;
  float largura, altura;
} retangulo;
retangulo jogador;
retangulo tubaroes[QTD_MAX_TUBARAO];
float velocidadeLateral = 1.0f;
float velocidadeVertical = 0.1f;
float aceleracaoVertical = 0.02f;

void inicializaTubarao(int i) {
  
  tubaroes[i].largura = TUBARAO_LARGURA;
  tubaroes[i].altura = TUBARAO_ALTURA;
  tubaroes[i].x = rand() % 700;
  tubaroes[i].y = tubaroes[i].y=tubaroes[i].altura+(rand()%1300);

  
  }

void init() {
  
  musica = loadMusic("tubarao.ogg");
  background = loadImage("background.jpg");
  imgMergulhador = loadImage("mergulhador.gif");
  imgTubarao = loadImage("tubarao.gif");
  
  jogador.x = 400;
  jogador.y = 0;
  jogador.largura = MERGULHADOR_LARGURA;
  jogador.altura = MERGULHADOR_ALTURA;

   Mix_PlayMusic(musica, -1);
  for (int i = 0; i < QTD_MAX_TUBARAO; i++) {
    inicializaTubarao(i);
  }
}

void destroy() {
  SDL_FreeSurface(background);
  SDL_FreeSurface(imgMergulhador);
  SDL_FreeSurface(imgTubarao);
  Mix_FreeMusic(musica);
}

void processEvent(SDL_Event event) {
  SDL_Keycode keycode;

  if (isQuitEvent(event)) {
    endGameLoop();
  } else if (event.type == SDL_KEYDOWN) {
    keycode = event.key.keysym.sym;
    if (keycode == SDLK_SPACE) {
      jogador.y = jogador.y + 30;

    }
  }
}

void atualizaPosicaoJogador() {
  const Uint8 *keyboard = SDL_GetKeyboardState(NULL);
  float velocidade = 0.0f;

  if (keyboard[SDL_SCANCODE_LEFT]) {
    velocidade -= velocidadeLateral;
  }
  if (keyboard[SDL_SCANCODE_RIGHT]) {
    velocidade += velocidadeLateral;
  }



  jogador.x += velocidade;
}

void atualizaTubaroes() {
  int i;

  for (i = 0; i < QTD_MAX_TUBARAO; i++) {
    tubaroes[i].y -= velocidadeVertical;
    if (tubaroes[i].y < 0) {
      
      
      inicializaTubarao(i);

      velocidadeVertical += aceleracaoVertical;
    }
  }

}

void detectaColisao(int i) {
  float tx1 = tubaroes[i].x,
      ty1 = tubaroes[i].y,
      tx2 = tubaroes[i].x + tubaroes[i].largura,
      ty2 = tubaroes[i].y + tubaroes[i].altura;
  float jx1 = jogador.x,
      jy1 = jogador.y,
      jx2 = jogador.x + jogador.largura,
      jy2 = jogador.y + jogador.altura;
  bool colidiu = true;
  if (tx1 > jx2 || ty1 > jy2 || jx1 > tx2 || jy1 > ty2) {
    colidiu = false;
  }

  if (colidiu) {
    endGameLoop();
  }
}

void update() {
  int i;

  atualizaPosicaoJogador();
  atualizaTubaroes();

  for (i = 0; i < QTD_MAX_TUBARAO; i++) {
    detectaColisao(i);
  }
}

void draw() {
  int i;

  drawImage(background, 0, 0);
  drawImage(imgMergulhador, jogador.x, jogador.y);
  for (i = 0; i < QTD_MAX_TUBARAO; i++) {
    drawImage(imgTubarao,
      tubaroes[i].x, tubaroes[i].y);
  }
}

int main(int argc, char *argv[]) {
  initSDL(TELA_LARGURA, TELA_ALTURA);
  gameLoop();
  return 0;
}

