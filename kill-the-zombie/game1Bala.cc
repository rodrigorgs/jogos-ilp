#include "ilpgame.h"

 //QtdMax = 4;
SDL_Surface *background;
SDL_Surface *bullet;
SDL_Surface *shooter;
SDL_Surface *zombie;
SDL_Surface *zombie2;

int tempo = 0;

struct position {
	SDL_Surface* surface;
	float x;
	float y;
	bool naTela;
	bool colisao;
};
int i;
position bala;
position atirador;
position monster[6];
bool tiro = false;

float velocidadeY = 1.5f;
float velocidadeX = 0.5f;

void startAtirador() {
	atirador.x = 0, atirador.y = 200;
}

/*void startbala() {
	bala.x = atirador.x + 70, bala.y = atirador.y + 45;
}*/

void startMonster(int i) {
	monster[i].x = 700;
	monster[i].y = rand() % 400;
	if ( i > 0 ) {
		monster[i].x = monster[i - 1].x + 100;
		monster[i].y = rand() % 400;
	} 
}

void init() {
	srand(time(NULL));
	int i = 0;
	background = loadImage("road.jpg");
	bullet = loadImage("bullet.png");
	shooter = loadImage("shooter.gif");
	zombie = loadImage("zombie.gif");
	zombie2 = loadImage("zombie2.gif");

	startAtirador();
	for (i = 0; i < 6; i++) {
    	startMonster(i);
  }
}
	
void destroy() {
	SDL_FreeSurface(background);
	SDL_FreeSurface(bullet);
	SDL_FreeSurface(shooter);
	SDL_FreeSurface(zombie);
	SDL_FreeSurface(zombie2);
}

void processEvent(SDL_Event event) {
	SDL_Keycode keycode;

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

    if (keycode == SDLK_SPACE) {
      if(tiro == false){ 
    	tiro = true;
	for (int i = 0; i < 6; i++)
    	bala.x = atirador.x + 70, bala.y = atirador.y + 45;
    }  }  
  }
}

void draw() {
	int i;
	drawImage( background, 0 , 0 );
	drawImage( shooter, atirador.x, atirador.y );
	for(i = 0; i < 6; i++) {
		if( tempo % 100 <= 49 )
	  		drawImage(zombie, monster[i].x, monster[i].y);
		else{
			drawImage(zombie2, monster[i].x, monster[i].y);
		}
	}
	if (tiro) drawImage(bullet, bala.x, bala.y);
}

void detectaColisaoAtirador(int i) {
	float bx1 = atirador.x,
		by1 = atirador.y,
		bx2 = atirador.x + 80,
		by2 = atirador.y + 68;
	float zx1 = monster[i].x,
		zy1 = monster[i].y,
		zx2 = monster[i].x + 80,
		zy2 = monster[i].y + 74;
		bool colidiu = true;
		if ( bx1 > zx2 || bx2 < zx1 || by1 < zy2 || by2 > zy1 ){
			colidiu = false;
		}
		if (colidiu == true){
			endGameLoop();
		}
}

void atualizaMonstro() {
	int i;
	for(i = 0; i < 6; i++) {
		monster[i].x = monster[i].x - velocidadeX;
		if(monster[i].x < 10) {
			startMonster(i);
		}
	}
	tempo += 1;
}


void atualizabala() {
	bala.x = bala.x + 2.0f;
}

void update() {
	atualizaMonstro();
	if(tiro) bala.x = bala.x += 0.5f;
		atualizabala();
	if(bala.x > 800) {
		tiro = false;
	}
	if(atirador.y < -10) {
		atirador.y = -10;
	}
	if(atirador.y > 540){
		atirador.y = 540;
	}

	for (int i = 0; i < 6; i++) {
    detectaColisaoAtirador(i);
	}
}
int main(int argc, char *argv[]) {
  initSDL();
  gameLoop();

	return 0;
}
