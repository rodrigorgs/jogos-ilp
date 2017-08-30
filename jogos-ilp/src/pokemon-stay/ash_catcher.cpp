#include "ilpgame.h"

#define TELA_LARGURA 800
#define TELA_ALTURA 480
#define LIM_POKE 3
#define FPS 30
#define DELTATIME (1000 / FPS)

Uint32 lastTime = 0;
TTF_Font *font;
SDL_Color blackcolor = {0, 0, 0, 0};
SDL_Surface *img;
SDL_Surface *imgBola;
SDL_Surface *imgPoke;
SDL_Surface *background;
SDL_Surface *gameover;
Mix_Music *musica;
Mix_Chunk *somcaptura;
Mix_Chunk *somerro;
Mix_Chunk *somgameover;

typedef struct {
  float x, y, h;
} objeto;
objeto bola;
objeto Poke[LIM_POKE];
int pontos, vidas=3;
int coluna1=70, coluna2=280, coluna3=490;
int velocidadeLateral=210;
float velocidadeQueda=5;
float aceleracaoQueda=0.05f;
string totalpontos="0", totalvidas="3";

void debugqueda(int i) {
  bool offset=true;
  if (i==0) {
    if ((Poke[0].x!=Poke[1].x || Poke[0].y > Poke[1].y+Poke[1].h || Poke[1].y > Poke[0].y+Poke[0].h) &&
       (Poke[0].x!=Poke[2].x || Poke[0].y > Poke[2].y+Poke[2].h || Poke[2].y > Poke[0].y+Poke[0].h))
        offset=false;
  }
  else if (i==1) {
    if ((Poke[1].x!=Poke[2].x || Poke[1].y > Poke[2].y+Poke[2].h || Poke[2].y > Poke[1].y+Poke[1].h) &&
       (Poke[1].x!=Poke[0].x || Poke[1].y > Poke[0].y+Poke[0].h || Poke[0].y > Poke[1].y+Poke[1].h))
        offset=false;
  }
  else if (i==2) {
    if ((Poke[2].x!=Poke[0].x || Poke[2].y > Poke[0].y+Poke[0].h || Poke[0].y > Poke[2].y+Poke[2].h) &&
       (Poke[2].x!=Poke[1].x || Poke[2].y > Poke[1].y+Poke[1].h || Poke[1].y > Poke[2].y+Poke[2].h))
      offset=false;
  }
  if (offset) Poke[i].y-=TELA_ALTURA;
}

void inicializaPoke(int i) {
  Poke[i].h= 100;
  Poke[i].x =((rand()%3)*210)+70;
  Poke[i].y =-(rand() % 800)-Poke[i].h;
  debugqueda(i);
}

void init() {
  srand(time(NULL));
  int selectmon;
  selectmon=rand()%3;

  lastTime = SDL_GetTicks();

  font = loadFont("PokemonGB.ttf", 14);
  if (selectmon==0) imgPoke = loadImage("001.png");
  else if (selectmon==1) imgPoke = loadImage("004.png");
  else if (selectmon==2) imgPoke = loadImage("007.png");
  background = loadImage("background.png");
  imgBola = loadImage("ball.png");
  gameover = loadImage("gameover.gif");
  musica = loadMusic("beat.wav");
  somcaptura = loadSound("coin.wav");
  somerro = loadSound("miss.wav");
  somgameover = loadSound("gameover.wav");

  Mix_PlayMusic(musica, -1);
  
  bola.x = coluna2;
  bola.y = 380;
  bola.h = 100;

  for (int i = 0; i < LIM_POKE; i++) {
    inicializaPoke(i);
    debugqueda(i);
  }
}

void destroy() {
  TTF_CloseFont(font);
  SDL_FreeSurface(img);
  SDL_FreeSurface(background);
  SDL_FreeSurface(imgBola);
  SDL_FreeSurface(imgPoke);
  SDL_FreeSurface(gameover);
  Mix_FreeChunk(somcaptura);
  Mix_FreeChunk(somerro);
  Mix_FreeChunk(somgameover);
}

void processEvent(SDL_Event event) {
  SDL_Keycode keycode;

  if (isQuitEvent(event)) {
    endGameLoop();
  }
  else if (event.type == SDL_KEYDOWN) {
    keycode = event.key.keysym.sym;
    if (keycode == SDLK_LEFT && bola.x !=coluna1) bola.x -= velocidadeLateral;
    else if (keycode == SDLK_RIGHT && bola.x!=coluna3) bola.x += velocidadeLateral;
  }
}

void atualizaPoke() {
  int i;

  for (i = 0; i < LIM_POKE; i++) {
    Poke[i].y += velocidadeQueda;
    if (Poke[i].y > TELA_ALTURA) {
      vidas--;
      totalvidas= tostring (vidas);
      Mix_PlayChannel(-1, somerro, 0);
      inicializaPoke(i);
    }
  }
}

void captura(int i) {
  bool capturou=true;
  if (Poke[i].x!=bola.x || Poke[i].y > bola.y+bola.h || bola.y > Poke[i].y+Poke[i].h) {
    capturou=false;
  }

  if (capturou) {
    velocidadeQueda += aceleracaoQueda;
    pontos++;
    totalpontos= tostring (pontos);
    Mix_PlayChannel(-1, somcaptura, 0);
    inicializaPoke(i);
    debugqueda(i);
  }
}

void update() {
  int i;

  Uint32 time = SDL_GetTicks();
  Uint32 dif = time - lastTime;
  if (dif < DELTATIME) {
    SDL_Delay(DELTATIME - dif);
  }
  lastTime = time;

  if (vidas==0) {
    SDL_Delay(6000);
    endGameLoop();
  }
  else {

    atualizaPoke();

    for (i = 0; i < LIM_POKE; i++) {
      captura(i);
    }

    if (vidas==0) {
      Mix_FreeMusic(musica);
      Mix_PlayChannel(-1, somgameover, 0);    
    }

  }

}

void draw() {
  int i;

  drawImage(background, 0, 0);
  drawText(totalpontos , font, blackcolor, 734, 157);
  drawText(totalvidas , font, blackcolor, 734, 235);
  drawImage(imgBola, bola.x, bola.y);
  for (i = 0; i < LIM_POKE; i++) {
    drawImage(imgPoke, Poke[i].x, Poke[i].y);
  }
  if (vidas==0) {
    drawImage(gameover, 202, 190);
  }
}

int main(int argc, char *argv[]) {
  initSDL(TELA_LARGURA, TELA_ALTURA);
  gameLoop();
  return 0;
}
