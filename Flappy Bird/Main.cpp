/*
*Nome: Flappy Bird
*Descrição: Recriação do jogo Flappy Bird
*Última modificação: 28/08/2017
*/
#include "ilpgame.h"
#include <ctime>
#define LARGURA_TELA 900
#define ALTURA_TELA 501
#define GRAVIDADE 0.7

typedef struct {
    float posicaoHorizontal;
    float posicaoVertical;
    float velocidadeHorizontal;
    float velocidadeVertical;
    SDL_Surface *img;
    TTF_Font *txt;
} ponto;

ponto passaro;
ponto canoDeBaixo;
ponto canoDeCima;
ponto fundoPrimario;
ponto fundoSecundario;
ponto gameOver;
ponto coracao;
ponto pontos;
ponto vidas;
ponto maiorPontuacao;

SDL_Color whiteColor = {255, 255, 255, 255};
Mix_Music *song;
Mix_Music *plus_one;
Mix_Music *bateu;

int pontuacao;
int numeroVidas;
int melhorPontuacao;
string strPontuacao;
string strNumeroVidas;
string recorde;
bool podeComecar;
bool podeVoar;

void init() {
  fundoPrimario.img = loadImage("background.png");
  fundoSecundario.img = loadImage("background.png");
  passaro.img = loadImage("bird.png");
  canoDeBaixo.img = loadImage("wallDown.gif");
  canoDeCima.img = loadImage("wallUp.gif");
  coracao.img = loadImage("heart.gif");

  canoDeBaixo.posicaoHorizontal = 800.f;
  canoDeBaixo.velocidadeHorizontal = 10.f;
  canoDeBaixo.posicaoVertical = 200.f;

  canoDeCima.posicaoHorizontal = 800.f;
  canoDeCima.velocidadeHorizontal = 10.f;
  canoDeCima.posicaoVertical = canoDeBaixo.posicaoVertical - 450;

  pontos.txt = loadFont("font.ttf", 28);
  vidas.txt = loadFont("font.ttf", 40);
  gameOver.txt = loadFont("font.ttf", 90);
  maiorPontuacao.txt = loadFont("font.ttf", 20);
  song = loadMusic("song.ogg");
  plus_one = loadMusic("plusOne.ogg");
  bateu = loadMusic("break.ogg");

  passaro.posicaoVertical = ALTURA_TELA / 2;
  passaro.velocidadeVertical = 0.f;

  podeComecar = false;
  podeVoar = true;
  pontuacao = 0;
  strPontuacao = to_string(pontuacao);
  numeroVidas = 3;
  strNumeroVidas = to_string(numeroVidas);
  fundoPrimario.posicaoHorizontal = 0.f;
  fundoSecundario.posicaoHorizontal = 899.f;
  fundoPrimario.velocidadeHorizontal = 1.f;
  fundoSecundario.velocidadeHorizontal = 1.f;
  gameOver.velocidadeVertical = -4.f;
  gameOver.posicaoVertical = 500.f;
  coracao.posicaoVertical = 10.f;
  coracao.posicaoHorizontal = 10.f;
  pontos.posicaoHorizontal = 30.f;
  vidas.posicaoHorizontal = 60.f;
  melhorPontuacao = 0;
  recorde = ".";
  srand(time(NULL));
}

void destroy() {
  SDL_FreeSurface(fundoPrimario.img);
  SDL_FreeSurface(fundoSecundario.img);
  SDL_FreeSurface(passaro.img);
  SDL_FreeSurface(canoDeBaixo.img);
  SDL_FreeSurface(canoDeCima.img);
  SDL_FreeSurface(coracao.img);
  TTF_CloseFont(pontos.txt);
  TTF_CloseFont(vidas.txt);
  TTF_CloseFont(gameOver.txt);
  TTF_CloseFont(maiorPontuacao.txt);
  Mix_FreeMusic(song);
  Mix_FreeMusic(plus_one);
  Mix_FreeMusic(bateu);
}

void processEvent(SDL_Event event) {
  SDL_Keycode keycode;
  if (isQuitEvent(event))
    endGameLoop();
  if (event.type == SDL_KEYDOWN) {
    keycode = event.key.keysym.sym;
    if (keycode == SDLK_SPACE && podeVoar) {
      podeComecar = true;
      passaro.velocidadeVertical = -10; 
      if (canoDeBaixo.posicaoHorizontal != 180 && canoDeBaixo.posicaoHorizontal >= 183)
        Mix_PlayMusic(song, 0);
    }
  }
}
/*Inicio do ambiente para criação de funções*/

void morreu() {
  Mix_PlayMusic(bateu, 0);
  if (pontuacao > melhorPontuacao) {
    melhorPontuacao = pontuacao;
  }
  pontuacao = 0;
  strPontuacao = to_string(pontuacao);
  numeroVidas--;
  strNumeroVidas = to_string(numeroVidas);
  SDL_Delay(1000);
  //retorna a posição inicial
  passaro.posicaoVertical = ALTURA_TELA / 2;
  passaro.velocidadeVertical = 0.f;
  canoDeBaixo.posicaoHorizontal = 800.f;
  canoDeCima.posicaoHorizontal = 800.f;
  podeComecar = false;
}
void colisao() {
  if ((canoDeBaixo.posicaoHorizontal >= 180 && canoDeBaixo.posicaoHorizontal <= 290) && (
    passaro.posicaoVertical > canoDeBaixo.posicaoVertical - 70 || 
    passaro.posicaoVertical < canoDeBaixo.posicaoVertical -140)) {
      morreu();
    }
}
void movimentarFundo() {
  if (fundoPrimario.posicaoHorizontal < -899)
      fundoPrimario.posicaoHorizontal = 899;
  if (fundoSecundario.posicaoHorizontal < -899)
    fundoSecundario.posicaoHorizontal = 899;
  fundoPrimario.posicaoHorizontal -= fundoPrimario.velocidadeHorizontal;
  fundoSecundario.posicaoHorizontal -= fundoSecundario.velocidadeHorizontal;
}

//impede que o passaro saia da tela
void gaiola() {
  //estabelece o teto
  if (passaro.posicaoVertical <= -45) {
      passaro.velocidadeVertical = 0;
      passaro.posicaoVertical = -45;
  }
  //estabelece o chão
  if (passaro.posicaoVertical >= ALTURA_TELA - 75) {
    morreu();
  }
}
/*Fim do ambiente para criação de funções*/
void update() {
  if (podeComecar) {
    passaro.velocidadeVertical += GRAVIDADE;
    passaro.posicaoVertical += passaro.velocidadeVertical;
    canoDeBaixo.posicaoHorizontal -= canoDeBaixo.velocidadeHorizontal;
    canoDeCima.posicaoHorizontal -= canoDeCima.velocidadeHorizontal;

    gaiola();
    //cria canoDeBaixos com tamanhos aletorios
    if (canoDeBaixo.posicaoHorizontal < -100) {
      canoDeBaixo.posicaoVertical = (rand() % (400 - 200 + 1) + 200);
      canoDeBaixo.posicaoHorizontal = 1000;
      canoDeCima.posicaoHorizontal = 1000;
      canoDeCima.posicaoVertical = canoDeBaixo.posicaoVertical - 450;
    }
    colisao();
    //conta o numero de pontos ganhos
    if (canoDeBaixo.posicaoHorizontal == 160) {
      pontuacao++;
      strPontuacao = to_string(pontuacao);
      Mix_PlayMusic(plus_one, 0);
    }
    movimentarFundo();
  }
  //encerra o jogo
  if (numeroVidas == 0 && gameOver.posicaoVertical > 100) {
    podeVoar = false;
    gameOver.posicaoVertical += gameOver.velocidadeVertical;
    //limpa a tela
    pontos.posicaoHorizontal = -100;
    vidas.posicaoHorizontal = -100;
    coracao.posicaoHorizontal = -100;
    recorde = "Recorde: " + to_string(melhorPontuacao);
  }
}

void draw() {
  drawImage(fundoPrimario.img, fundoPrimario.posicaoHorizontal, 0);
  drawImage(fundoSecundario.img, fundoSecundario.posicaoHorizontal, 0);
  drawImage(passaro.img, 200, passaro.posicaoVertical);
  drawImage(canoDeBaixo.img, canoDeBaixo.posicaoHorizontal, canoDeBaixo.posicaoVertical);
  drawImage(canoDeCima.img, canoDeCima.posicaoHorizontal, canoDeCima.posicaoVertical);
  drawImage(coracao.img, coracao.posicaoHorizontal, coracao.posicaoVertical);
  drawText(strPontuacao, pontos.txt, whiteColor, pontos.posicaoHorizontal, 90);
  drawText(strNumeroVidas, vidas.txt, whiteColor, vidas.posicaoHorizontal, 18);
  drawText("GAME OVER", gameOver.txt, whiteColor, 92, gameOver.posicaoVertical);
  drawText(recorde, maiorPontuacao.txt, whiteColor, 150, gameOver.posicaoVertical + 100);
  SDL_Delay(1000 / 60);
}
int main(int argc, char *argv[]) {
  initSDL(LARGURA_TELA, ALTURA_TELA);
  gameLoop();
  return 0;
}