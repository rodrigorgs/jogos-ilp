#include "ilpgame.h"

SDL_Surface *img1;
SDL_Surface *img2;
SDL_Surface *img3;
SDL_Surface *img4;
SDL_Surface *img5;
SDL_Surface *img6;
SDL_Surface *img7;
SDL_Surface *img8;
SDL_Surface *bg;
SDL_Surface *loser;
SDL_Surface *win;
int i, j, k;
int x, y;
int restart = 0;
bool selected1 = false;
bool selected2 = false;
bool lost = false;
string selected1XY = "";
string selected2XY = "";

int imgSelected1 = -1;
int timer = 0;
string found [16] = { "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "" };
int freeposition = 0;

int elements [16] = { 7, 5, 2, 8, 4, 6, 3, 4, 5, 1, 3, 6, 7, 1, 2, 8 };


void init() {
    img1 = loadImage("meme1.jpg");
    img2 = loadImage("meme2.jpg");
    img3 = loadImage("meme3.jpg");
    img4 = loadImage("meme4.png");
    img5 = loadImage("meme5.jpg");
    img6 = loadImage("meme6.jpg");
    img7 = loadImage("meme7.jpg");
    img8 = loadImage("meme8.jpg");
    bg = loadImage("bg.png");
    loser = loadImage("loser.jpg");
    win = loadImage("win.png");
}

void destroy() {
    SDL_FreeSurface(img1);
    SDL_FreeSurface(img2);
    SDL_FreeSurface(img3);
    SDL_FreeSurface(img4);
    SDL_FreeSurface(img5);
    SDL_FreeSurface(img6);
    SDL_FreeSurface(img7);
    SDL_FreeSurface(img8);
    SDL_FreeSurface(bg);
    SDL_FreeSurface(loser);
    SDL_FreeSurface(win);
}

void processEvent(SDL_Event event) {    
    if (isQuitEvent(event)){
        endGameLoop();        
    }
    
}

void update() {
}

void verify(){
    Uint32 mouse = SDL_GetMouseState(&x, &y);
    int index = 0;    
    for(i=0; i<4; i++){
        for(j=0; j<4; j++){
            int img = elements[index];
            index++;  
            // verifica se o mouse ta pressionado          
            if (mouse & SDL_BUTTON(SDL_BUTTON_LEFT)) {
                //verifica se estou no bloco correto
                if( x < (i*200+200) && x > i*200){
                    if( y < (j*200+200) && y > j*200){
                        //busca pra ver se ja foi selecionado
                        string xy = std::to_string(i) + "-" + std::to_string(j);                        
                        bool search = false;
                        for(k=0; k<=16; k++){
                            if(xy == found[k]){
                                search = true;
                            }
                        } 
                        //caso nao tenha sido selecionado selecionar
                        if(search == false){
                            //selecionar para 1 caso nao tenha selecionado nenhum ainda
                            if(selected1 == false){
                                selected1 = true;
                                imgSelected1 = img;
                                selected1XY = xy;
                            }
                            //selecionar para 2 caso 1 ja tenha sido selecionado
                            else if(selected2 == false && selected1XY != xy)
                            {
                                selected2 = true;                            
                                selected2XY = xy;

                                // verifica se acertou, caso acertado inserir no array found
                                if(imgSelected1 == img){
                                    found[freeposition] = selected1XY;
                                    freeposition++;
                                    found[freeposition] = selected2XY;
                                    freeposition++;
                                }
                            }
                        }
                    }
                }
            }                
        }
    }
}

// renderiza as imagens dos memes de acordo com o array elements
void renderMemes(){
    int index = 0;    
    for(i=0; i<4; i++){
        for(j=0; j<4; j++){
            int img = elements[index];
            switch (img) {
                case 1 : drawImage(img1, i*200, j*200); break;
                case 2 : drawImage(img2, i*200, j*200); break;
                case 3 : drawImage(img3, i*200, j*200); break;
                case 4 : drawImage(img4, i*200, j*200); break;
                case 5 : drawImage(img5, i*200, j*200); break;
                case 6 : drawImage(img6, i*200, j*200); break;
                case 7 : drawImage(img7, i*200, j*200); break;
                case 8 : drawImage(img8, i*200, j*200); break;
            }
            index += 1;                                      
        }
    }
}

void renderCover(){

     // renderiza a imagem que fica em cima com a interrogação
     for(i=0; i<4; i++){
        for(j=0; j<4; j++){
            string xy = std::to_string(i) + "-" + std::to_string(j);

            bool render = true;
            if(selected1XY == xy){
                render = false;
            }
            if(selected2XY == xy){
                render = false;
            }

            for(k=0; k<=16; k++){
                if(xy == found[k]){
                    render = false;
                }
            }                

            if(render){
                drawImage(bg, i*200, j*200);                                
            }
        }
    }

}

// reseta as seleções quando o segundo card é selecionado
void reset(){
    if(selected1 && selected2){
        restart++;        
        if(restart >= 300){
            lost = false;
            restart = 0;
            selected1 = false;
            selected1XY = "";
            selected2 = false;                            
            selected2XY = "";
        }
    }
}

void draw() {
    
        // verifica tudo do jogo
        verify();
        
        // renderiza os memes
        renderMemes();
    
        // renderiza a capa
        renderCover();
    
        // mostra a imagem "you lose" quando perde
       
        // mostra a imagem de sucesso quando ganha
        if(freeposition >= 16){
            drawImage(win, 0, 0);
        }
		
		else
		{
			//tempo p saber se perdeu
			if(timer >= 13000){
				drawImage(loser, 0, 0);        
			}
			else
			{
				timer++;
			}
		}
    
        // recomeçar os turnos caso tenha selecionado os 2 elementos
        reset();    
    }

int main(int argc, char *argv[]) {
  initSDL(800,800);
  gameLoop();
  return 0;
}

// g++ main.cc `sdl2-config --cflags --libs` && ./a.out

//g++ main.cc `sdl2-config --cflags --libs` -lSDL2_ttf -lSDL2_image -lSDL2_mixer && ./a.out
//g++ main.cc -I "C:\MinGW\include\SDL2" -mwindows -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_ttf -lSDL2_image
