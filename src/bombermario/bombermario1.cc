#include "ilpgame.h"
#include "SDL_ttf.h"

using namespace std;

#define MAP_WIDTH 56
#define MAP_HEIGHT 64 
#define IMG_WIDTH 64
#define IMG_HEIGHT 64

SDL_Surface *imgbrick;
SDL_Surface *imghero1;
SDL_Surface *imghero2;
SDL_Surface *imgbomb1;
SDL_Surface *imgbomb2;

// se for igual a zero, não tem bomb1a pra explodir
Uint32 tempoParaExplodir1 = 0;
Uint32 tempoParaExplodir2 = 0;

int map[MAP_HEIGHT][MAP_WIDTH] = {
  {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
  {1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1},
  {1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0},
  {1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1},
  {1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1},
  {1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
  {1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0},
};

typedef struct {
  int x, y;
} Posicao;

Posicao player1;
Posicao bomb1;
Posicao bomb2;
Posicao player2;


void init() {
  imgbrick = loadImage("brick.png");
  imghero1 = loadImage("hero.png");
  imgbomb1 = loadImage("bomb1.png");
  imgbomb2 = loadImage("bomb2.png");
  imghero2 = loadImage("hero2.png");

  bomb1.x = -1;
  bomb1.y = -1;
  bomb2.x = 10;
  bomb2.y = 10;
  player1.x = 1;
  player1.y = 1;
  player2.x = 10;
  player2.y = 8;
}

void destroy() {
  SDL_FreeSurface(imgbrick);
  SDL_FreeSurface(imghero1);
  SDL_FreeSurface(imghero2);
}

void draw() {
  int x, y, telax, telay;

  for (y = 0; y < MAP_HEIGHT; y++) {
    for (x = 0; x < MAP_WIDTH; x++) {
      telax = x * IMG_WIDTH;
      telay = y * IMG_HEIGHT;
      if (map[y][x] == 1) {
        drawImage(imgbrick, telax, telay);
      }
    }
  }

  telax = bomb1.x * IMG_WIDTH;
  telay = bomb1.y * IMG_HEIGHT;
  drawImage(imgbomb1, telax, telay);

  telax = bomb2.x * IMG_WIDTH;
  telay = bomb2.y * IMG_HEIGHT;
  drawImage(imgbomb1, telax, telay);

  telax = player1.x * IMG_WIDTH;
  telay = player1.y * IMG_HEIGHT;
  drawImage(imghero1, telax, telay);

  telax = player2.x * IMG_WIDTH;
  telay = player2.y * IMG_HEIGHT;
  drawImage(imghero2, telax, telay);
}

void processEvent(SDL_Event event) {
  SDL_Keycode keycode1;
  SDL_Keycode keycode2;
  Posicao vel1 = {0, 0};
  Posicao vel2 = {0, 0};

  if (isQuitEvent(event)) {
    endGameLoop();
  } else if (event.type == SDL_KEYDOWN) {
    keycode1 = event.key.keysym.sym;

      if ((keycode1 == SDLK_w) && (player1.y >= 1)) {
        vel1.y--;
      }
      else if ((keycode1 == SDLK_s) && (player1.y <= 9)) { // TODO
        vel1.y++;
      }
     else if ((keycode1 == SDLK_a) && (player1.x >= 1)) { // TODO
        vel1.x--;
      }
      else if ((keycode1 == SDLK_d) && (player1.x <= 12)) { // TODO
        vel1.x++;
      }
      else if (keycode1 == SDLK_x) {
        Uint32 tempoAtual1 = SDL_GetTicks();
        tempoParaExplodir1 = tempoAtual1 + 2000;

        bomb1.y = player1.y;
        bomb1.x = player1.x;
      }
    }  

  if (isQuitEvent(event)) {
    endGameLoop();
  } else if (event.type == SDL_KEYDOWN) {
    keycode2 = event.key.keysym.sym;

    if ((keycode2 == SDLK_i) && (player1.y >= 1)) {
      vel2.y--;
    }
    else if ((keycode2 == SDLK_k) && (player1.y <= 9)) { // TODO
      vel2.y++;
    }
    else if ((keycode2 == SDLK_j) && (player1.x >= 1)) { // TODO
      vel2.x--;
    }
    else if ((keycode2 == SDLK_l) && (player1.x <= 12)) { // TODO
      vel2.x++;
    }
    else if (keycode2 == SDLK_y) {
      
      // TODO: só deixa colocar bomb1a se não tiver nenhuma
      //       bomb1a posicionada
      Uint32 tempoAtual2 = SDL_GetTicks();
      tempoParaExplodir2 = tempoAtual2 + 2000;

      bomb2.y = player2.y;
      bomb2.x = player2.x;
    }
  }

  // se a proxima posicao estiver vazia, atualiza posicao
  if (map[player1.y + vel1.y][player1.x + vel1.x] == 0) {
    player1.x += vel1.x;
    player1.y += vel1.y;
  }

  if (map[player2.y + vel2.y][player2.x + vel2.x] == 0) {
    player2.x += vel2.x;
    player2.y += vel2.y;
  }
}

void update() {
  Uint32 tempoAtual1 = SDL_GetTicks();
  Uint32 tempoAtual2 = SDL_GetTicks();

  if (tempoParaExplodir1 != 0 && tempoAtual1 >= tempoParaExplodir1) {
    map[bomb1.y][bomb1.x + 1] = 0;
    map[bomb1.y][bomb1.x - 1] = 0;
    map[bomb1.y + 1][bomb1.x] = 0;
    map[bomb1.y - 1][bomb1.x] = 0;

    // Encerra o jogo depois de 1 segundo se o jogador estiver dentro do alcance da bomba
    if ((player1.x == bomb1.x + 1) && (player1.y == bomb1.y)) {
      SDL_Delay(1000);
      endGameLoop();
    }
    if ((player1.x == bomb1.x - 1) && (player1.y == bomb1.y)) {
      SDL_Delay(1000);
      endGameLoop();
    }
    if ((player1.y == bomb1.y + 1) && (player1.x == bomb1.x)) {
      SDL_Delay(1000);
      endGameLoop();
    }
    if ((player1.y == bomb1.y - 1) && (player1.x == bomb1.x)) {
      SDL_Delay(1000);
      endGameLoop();
    }
    if ((player1.y == bomb1.y) && (player1.x == bomb1.x)) {
      SDL_Delay(1000);
      endGameLoop();
    }
    //
     if ((player2.x == bomb1.x + 1) && (player2.y == bomb1.y)) {
      SDL_Delay(1000);
      endGameLoop();
    }
    if ((player2.x == bomb1.x - 1) && (player2.y == bomb1.y)) {
      SDL_Delay(1000);
      endGameLoop();
    }
    if ((player2.y == bomb1.y + 1) && (player2.x == bomb1.x)) {
      SDL_Delay(1000);
      endGameLoop();
    }
    if ((player2.y == bomb1.y - 1) && (player2.x == bomb1.x)) {
      SDL_Delay(1000);
      endGameLoop();
    }
    if ((player2.y == bomb1.y) && (player2.x == bomb1.x)) {
      SDL_Delay(1000);
      endGameLoop();
    }

    tempoParaExplodir1 = 0;

    bomb1.x = -1;
    bomb1.y = -1;
  }

    if (tempoParaExplodir2 != 0 && tempoAtual2 >= tempoParaExplodir2) {
      map[bomb2.y][bomb2.x + 1] = 0;
      map[bomb2.y][bomb2.x - 1] = 0;
      map[bomb2.y + 1][bomb2.x] = 0;
      map[bomb2.y - 1][bomb2.x] = 0;

      if ((player2.x == bomb2.x + 1) && (player2.y == bomb2.y)) {
        SDL_Delay(1000);
        endGameLoop();
      }
      if ((player2.x == bomb2.x - 1) && (player2.y == bomb2.y)) {
        SDL_Delay(1000);
        endGameLoop();
      }
      if ((player2.y == bomb2.y + 1) && (player2.x == bomb2.x)) {
        SDL_Delay(1000);
        endGameLoop();
      }
      if ((player2.y == bomb2.y - 1) && (player2.x == bomb2.x)) {
        SDL_Delay(1000);
        endGameLoop();
      }
      if ((player2.x == bomb2.y) && (player2.x == bomb2.x)) {
        SDL_Delay(1000);
        endGameLoop();
      }
      //
      if ((player1.x == bomb2.x + 1) && (player1.y == bomb2.y)) {
        SDL_Delay(1000);
        endGameLoop();
      }
      if ((player1.x == bomb2.x - 1) && (player1.y == bomb2.y)) {
        SDL_Delay(1000);
        endGameLoop();
      }
      if ((player1.y == bomb2.y + 1) && (player1.x == bomb2.x)) {
        SDL_Delay(1000);
        endGameLoop();
      }
      if ((player1.y == bomb2.y - 1) && (player1.x == bomb2.x)) {
        SDL_Delay(1000);
        endGameLoop();
      }
      if ((player1.x == bomb2.y) && (player1.x == bomb2.x)) {
        SDL_Delay(1000);
        endGameLoop();
      }
      
      // TODO: fazer para outras posições
      tempoParaExplodir2 = 0;

      bomb2.x = -1;
      bomb2.y = -1;
    }
}

int main(int argc, char *argv[]) {
  initSDL();
  gameLoop();
  return 0;
}
