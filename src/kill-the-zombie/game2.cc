#include "ilpgame.h"
#include <iostream>
#include <stdio.h>

#define NO_STDIO_REDIRECT
#define FPS (30)
#define TEMPO (1000 / FPS)

SDL_Surface *background;
SDL_Surface *bullet;
SDL_Surface *shooter;
SDL_Surface *shooter2;
SDL_Surface *zombie;
SDL_Surface *zombie2;
SDL_Surface *Life3;
SDL_Surface *Life2;
SDL_Surface *Life1;

Mix_Chunk *shoot;
Mix_Music *musica;

int tempo = 0, contador = 0, kills = 0, qntd ;

struct position {
	SDL_Surface* surface;
	float x;
	float y;
	bool colisao = false;
	bool tiro = false;
};
position bala[6];
position atirador;
position monster[5];
float velocidadeX = 3.5f;

Uint32 lastTime = 0;

void startAtirador() {
	atirador.x = 0, atirador.y = 200;
}

void startMonster(int i) {
	monster[i].x = 700;
	monster[i].y = (rand() % 400) + 50;
	if ( i > 0 ) {
		monster[i].x = 700 + (rand() % 300);
		monster[i].y = (rand() % 400) + 50;
	} 
}
    // ---------- TIRO ---------- //

void startBullet(int j) {
    	bala[j].tiro = true;
    	bala[j].x = atirador.x + 70, bala[j].y = atirador.y + 45;
}

void init() {
	musica = loadMusic("survival.mp3");
	srand(time(NULL));
	int i = 0;
	int j = 0;
	background = loadImage("road.jpg");
	bullet = loadImage("bullet.png");
	shooter = loadImage("shooter.gif");
	shooter2 = loadImage("shooter2.gif");
	zombie = loadImage("zombie.gif");
	zombie2 = loadImage("zombie2.gif");
	Life3 = loadImage("0.gif");
	Life2 = loadImage("1.gif");
	Life1 = loadImage("2.gif");
	shoot = loadSound("shoot.wav");
	
	startAtirador();
	for (i = 0; i < 5; i++) {
    	startMonster(i);
	}
	Mix_PlayMusic(musica, -1);
}
	
void destroy() {
	SDL_FreeSurface(background);
	SDL_FreeSurface(bullet);
	SDL_FreeSurface(shooter);
	SDL_FreeSurface(zombie);
	SDL_FreeSurface(zombie2);
	Mix_FreeChunk(shoot);
	Mix_FreeMusic(musica);
}

void processEvent(SDL_Event event) {
	SDL_Keycode keycode;
	int j;
	if (isQuitEvent(event)) {
    	endGameLoop();
  } else if (event.type == SDL_KEYDOWN) {
    keycode = event.key.keysym.sym;
    	if (keycode == SDLK_DOWN) {
    		atirador.y = atirador.y + 30;
    	}
   		if (keycode == SDLK_UP) {
    		atirador.y = atirador.y - 30;
    	} 
    	
     // ---------- TIRO ---------- //

    	for(j = 0; j < qntd; j += 1) {
    		if (keycode == SDLK_SPACE) {
    			if (bala[j].tiro == false) {  
    				startBullet(j);	
    				Mix_PlayChannel(-1, shoot, 0);
    				break;
    			}	  
			}	
		}  
  	}
}

void draw() {
	int i, j = 0;
	drawImage(background, 0 , -30);
	if (kills <= 15 )
	drawImage(shooter, atirador.x, atirador.y);
	else drawImage(shooter2, atirador.x, atirador.y);
	// HP
	if (contador == 0) drawImage (Life3, 650, 20);
	if (contador == 1) drawImage (Life2, 650, 20); 
	if (contador == 2) drawImage (Life1, 650, 20);	

	for(i = 0; i < 5; i++) {
		if (tempo % 10 <= 4)
	  		drawImage(zombie, monster[i].x, monster[i].y);
		else{
			drawImage(zombie2, monster[i].x, monster[i].y);
		}
	}
	for (j = 0; j < qntd; j++) {
		if (bala[j].tiro) {
			drawImage(bullet, bala[j].x, bala[j].y);
		}
	}
}

void atualizaMonstro() {
	int i;
	for(i = 0; i < 5; i++) {
		monster[i].x = monster[i].x - velocidadeX;
		if(monster[i].x < - 20) {
			startMonster(i);
			contador += 1;
		}
	}
	tempo += 1;
}


/*------------ Detecta quando o zumbi colide com o atirador -----------*/


void detectaColisaoAtirador(int i) {
	float ax1 = atirador.x,
		  ay1 = atirador.y,
		  ax2 = atirador.x + 30,
		  ay2 = atirador.y + 38;
	float bx1 = monster[i].x,
		  by1 = monster[i].y + 10,
		  bx2 = monster[i].x + 80,
		  by2 = monster[i].y + 54;
		bool colidiu = true;

  if (ax1 > bx2 || ay1 > by2 || bx1 > ax2 || by1 > ay2) {
    colidiu = false;
  }

  if (colidiu) {
    endGameLoop();
}
	}

void detectaColisaoBala(int j) {
	int i = 0;
	for (i = 0; i < qntd; i++) {
	float ax1 = bala[i].x,
		  ax2 = bala[i].x + 10,
		  ay1 = bala[i].y,
		  ay2 = bala[i].y + 10;
	float bx1 = monster[j].x,
		  by1 = monster[j].y + 10,
		  bx2 = monster[j].x + 80,
		  by2 = monster[j].y + 54;
		  bool acertou = true;

	if (ax1 > bx2 || ay1 > by2 || bx1 > ax2 || by1 > ay2) {
    	acertou = false;
    	bala[j].x = bala[j].x + 6.1f;
  	}
  	//for(j = 0; j < 6; j++) 
	if (acertou) {
		bala[i].x = 790;
		//bala[j].x += 5.0f;
  		monster[j].x = 700;
		monster[j].y = (rand() % 400) + 50;
		kills += 1;
		bala[i].tiro = false;
		velocidadeX += 0.05f;
	}
	}

}

void update() {
	Uint32 time = SDL_GetTicks();
	if (time - lastTime < TEMPO) {
		SDL_Delay(TEMPO - (time - lastTime));
	}
	lastTime = time;

	if (kills < 15)
	{
		qntd = 3;
	}
	else {
		qntd = 6;
	}
	atualizaMonstro();

	for(int j = 0; j < qntd; j++) {
		if(bala[j].tiro) 
	//	bala[j].x += 6.1f;
		detectaColisaoBala(j); //
		if(bala[j].x > 800) {
			bala[j].tiro = false;
		}
	}
	if(atirador.y < -10) {
		atirador.y = -10;
	}
	if(atirador.y > 540) {
		atirador.y = 540;
	}

	int i, j;

    for( i = 0; i < 5; i++) {
    	detectaColisaoAtirador(i);
    }
    for( j = 0; j < 5; j++) {
    	detectaColisaoBala(j);
    }

	SDL_Delay(20);

	if (contador == 3){
		endGameLoop();
	}
}

int main(int argc, char *argv[]) {
	initSDL();
	gameLoop();

	return 0;
}