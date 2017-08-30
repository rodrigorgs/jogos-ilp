#include "ilpgame.h"
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Lista2.h"
#include <cmath>
#define TELA_LARGURA 640
#define TELA_ALTURA 480

SDL_Surface *background;
TTF_Font *fontPalavras;
TTF_Font *fontPontuacao;
TTF_Font *fontFimDeJogo;
SDL_Color whiteColor = {255, 255, 0, 255};
string TextoDigitado;
string PalavraConferir;
int pontuacao = 0;
string pontuacaostring;
int QTD_MAX_PALAVRAS = 4;
float velocidadeLateral = 1.5f;
float x = 4;
float velocidadeVertical = 0.22855* log(x) + 0.07576;
int vida = 1;
bool FimDeJogo;

typedef struct {
  float x, y;
  float largura, altura;
  string texto;
  bool status;
} ClassePalavra;

ClassePalavra palavras[20];




    string PegaPalavra () {
            string item;
            int a = 1;
            // Seeds the random number generator - it works without this
            // but you will always get the same answer.
           // srand((unsigned)time(0));
            // Rand returns a number between 0 and RAND_MAX. Modulo
            // arithmetic gets it from 0 - 999 - then we add one to get the correct
            // range.
            int b = rand()%500;
            // open a file
            fstream infile("words.por");
            // grab a string of arbitrary length and loop until a == b
            // then output string.
            while (infile >> item) {
                    if (a++ == b) {
                            return item;
                    }
            }
    }

void inicializaPalavras(int i) {

  palavras[i].x = rand() % 500;
  palavras[i].y = - (rand() % 800);
  palavras[i].texto = PegaPalavra();
  AdicionaNaLista(palavras[i].texto,i);
  palavras[i].status = true;
}

void AumentaNumeroPalavras () {
	for (int i; i < 15; i++) {
		QTD_MAX_PALAVRAS = QTD_MAX_PALAVRAS + 1;
		SDL_Delay(5);
	}
}
	
void CalculaPontuacao (string a) {
 	int Resultado;
	Resultado = ProcuraNaLista(a);
	if (Resultado > 0) {
		palavras[Resultado].status = false;
		pontuacao = pontuacao + 10;
		pontuacaostring = to_string (pontuacao);
	} 
}

void init() {
  srand(time(NULL));
  FimDeJogo = false;
  AumentaNumeroPalavras();
  fontPontuacao = loadFont("FreeSans.ttf", 20);
  fontPalavras = loadFont("FreeSans.ttf", 25);
  fontFimDeJogo = loadFont("FreeSans.ttf", 40);
  pontuacaostring = to_string (pontuacao);
  background = loadImage("background.jpg");

  for (int i = 1; i < QTD_MAX_PALAVRAS; i++) {
    inicializaPalavras(i);
  }
}

void destroy() {
  SDL_FreeSurface(background);
}

void processEvent(SDL_Event event) {
  SDL_Keycode keycode;

  if (isQuitEvent(event)) {
    endGameLoop();
  } else if (event.type == SDL_KEYDOWN) {
    keycode = event.key.keysym.sym;

	 if (keycode >= SDLK_a && keycode <= SDLK_z) {
      char letra = 'a' + (keycode - SDLK_a);
      TextoDigitado += letra;
    } else if (keycode == SDLK_BACKSPACE && TextoDigitado.size() > 0) {
      TextoDigitado.erase(TextoDigitado.size() - 1);
	} else if (keycode == SDLK_SPACE or keycode == SDLK_KP_ENTER) {
      if (TextoDigitado != ""){
	  CalculaPontuacao(TextoDigitado);
	  
	  TextoDigitado.erase();
	  }
    }
  }
}


void atualizaPalavras() {
	int i;
	
	for (i = 1; i < QTD_MAX_PALAVRAS; i++) {
		if (palavras[i].status == true) {
			palavras[i].y += velocidadeVertical;
				}
	
		
    if (palavras[i].status == false) {

      
      inicializaPalavras(i);
	  palavras[i].status = true;

      x = x + 10;
    }
  }

}

void detectaPassou(int i) {
  float ax1 = palavras[i].x,
      ay1 = palavras[i].y;

  
  if (palavras[i].y > TELA_ALTURA and palavras[i].status == true) {
    palavras[i].status = false;
	vida = vida - 1;
	if (vida < 0) {
		velocidadeVertical = 0;
		FimDeJogo = true;
	}
  }

}

void update() {
  int i;

  atualizaPalavras();

  for (i = 1; i < QTD_MAX_PALAVRAS; i++) {
    detectaPassou(i);
  }
}

void draw() {
    int i;
    drawImage(background, 0, 0);
	drawText("Pontuacao", fontPontuacao, whiteColor, 200,450 );
	drawText(pontuacaostring, fontPontuacao, whiteColor, 330, 450);
	if (FimDeJogo == false) {
		if (TextoDigitado.size() > 0) {
			drawText(TextoDigitado, fontPalavras, whiteColor, 0,450 );
		}
		for (i = 1; i < QTD_MAX_PALAVRAS; i++) {
			if (palavras[i].status == true) {
				drawText(palavras[i].texto, fontPalavras, whiteColor, palavras[i].x, palavras[i].y);
			}
		}
	} else if (FimDeJogo == true) {
	drawText("FIM DE JOGO", fontFimDeJogo, whiteColor, 200, 300);
	}
}

int main(int argc, char *argv[]) {
  initSDL(TELA_LARGURA, TELA_ALTURA);
  gameLoop();
  return 0;
}

