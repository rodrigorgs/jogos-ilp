#include <cmath>
#include "ilpgame.h"

SDL_Surface *road;
SDL_Surface *bullet;
SDL_Surface *shooter;
SDL_Surface *zombie;

	struct position {
	SDL_Surface* surface;
	float x,y;	
};

position shooter;
position zombie;
position bullet;

float velocidade = 0.0001f, speed = 5 ;
float bulletx = shooterx +70, bullety = shootery + 45;
bool tiro = false;

void init(){
	
	//road = loadImage("road.jpg");
	bullet = loadImage("bullet.png");
	shooter = loadImage("shooter.gif");
	zombie = loadImage("zombie.png");
	shooter.x = 0, shooter.y = 150;
	zombie.x = 700, zombie.y = 150;
	bullet.x = shooter.x + 70, bullet.y = shooter.y + 45;

}

void destroy() {
  SDL_FreeSurface(shooter);
}

void processEvent(SDL_Event event) {
	bool shoot;
	SDL_Keycode keycode;
  if (isQuitEvent(event))
    endGameLoop();
else if (event.type == SDL_KEYDOWN){
	keycode = event.key.keysym.sym;
	if (keycode == SDLK_DOWN) shooter.y += speed;
	if (keycode == SDLK_UP) shooter.y -= speed;
	if (keycode == SDLK_SPACE) tiro = true ;
}
}

void draw() {
	drawImage(road,0,0);
	if(tiro) drawImage(bullet, shooterx +70, shootery + 45);
	drawImage(shooter, shooter.x, shooter.y);
	drawImage(zombie, zombie.x, zombie.y);
}

void atualizaTiro(){
	drawImage(bullet, bullet.x, bullet.y);
}

void atualizaZombie(){
	zombie.x -= velocidade;

}


void update() {
	atualizaZombie();
	//if(tiro = true) {bulletx = bulletx + 10;}


}

int main(int argc, char *argv[]) {
  initSDL();
  gameLoop();

  return 0;
}
