/**
Arquivo principal
Parte do jogo ILP Tanks
Autoria: Gustavo Mota
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>

#include <SDL2/SDL.h>

#include "gmgraphics.h"
#include "tanks.h"
#include "bullets.h"
#include "gmbitmap.h"

#define FORCAMAX 200
#define FATORATT 300 //Isso faz os projeteis percorrerem a trajetoria mais rapido ou mais lento (Default: 300)

typedef struct {
    Uint32 velho;
    Uint32 novo;
    Uint32 limite;
} tempo;

Uint16 terra[640];
Uint16 terraMin;
Uint16 terraMax;

SDL_Surface* surface;

SDL_Surface* terraSurface;

extern SDL_Surface* gameover;
bool partidaAcabou;

tank *pTank[2];

unsigned int contaFrame, contaRun;
unsigned int fps;

bool running;

bool tirosVoando;

int main(int argc, char** argv)
{
    // Initialize the random number generator
    srand (time(NULL));

    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Open a 640x640 window and define an accelerated renderer
    SDL_Window* window = SDL_CreateWindow("ILP Tanks", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          640, 640, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    surface = SDL_GetWindowSurface(window);
    SDL_SetColorKey(surface, SDL_TRUE, 0x000000FF);

    Uint32 rmask, gmask, bmask, amask;

    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        rmask = 0xff000000;
        gmask = 0x00ff0000;
        bmask = 0x0000ff00;
        amask = 0x000000ff;
    #else
        rmask = 0x000000ff;
        gmask = 0x0000ff00;
        bmask = 0x00ff0000;
        amask = 0xff000000;
    #endif

    terraSurface = SDL_CreateRGBSurface(0, 640, 640, 32, rmask, gmask, bmask, amask);
    if (surface == NULL) {
        SDL_Log("SDL_CreateRGBSurface() failed: %s", SDL_GetError());
        exit(1);
    }

    SDL_SetColorKey(terraSurface, SDL_TRUE, SDL_MapRGB(terraSurface->format, 255, 0, 255));

    SETCOR(0, 0, 0, 255);
    CLEAR();

    SDL_Renderer* renderPrincipal = SDL_CreateSoftwareRenderer(surface);
    rendererAtual = renderPrincipal;

    SDL_Renderer* renderTerra = SDL_CreateSoftwareRenderer(terraSurface);

    // LOAD SPRITES
    carregarSprites();

    //inicialização dos globais
    terraMin = 0;
    terraMax = 9999;
    partidaAcabou = false;
    running = true;
    tirosVoando = false;

    //declaracao dos locais

    bool teste;
    int i, j, turno;
    //teclado
    const Uint8 *teclado = SDL_GetKeyboardState(NULL);
    //definicoes do mar (lava)
    int marframe, marinc;
    tempo t_mar;
    //geracao de terreno
    bool escolhendo;
    SDL_Event event;
    int cont;
    //declaracao dos tanks
    tank tank1;
    tank tank2;
    //tempos
    tempo umSegundo;
    tempo t_frame;
    tempo t_renderTank;
    tempo t_part;
    //declaracoes de armas
    int armaInt;
    tipoProjetil arma;
    bool mudarArma;
    //reiniciar partida;
    bool restart;


    // LOOP PARTIDA
    while(running){

        restart = false;

        j = 0;
        turno = rand()%2;

        //definicoes do mar (lava)
        marframe = 1;
        t_mar.velho = 0;
        t_mar.limite = 200;

        // geracao de terreno
        gerarTerreno();
        // fundo
        printBMP(fundo, surface, 0, 0);
        // terra
        rendererAtual = renderTerra;
        drawTerra();
        rendererAtual = renderPrincipal;
        // mar
        drawMar(marframe);
        // instrucoes
        printBMP(instrucoes, surface, 0, 0);
        // update
        SDL_UpdateWindowSurface(window);
        escolhendo = true;
        cont = 0;
        while(escolhendo){
            cont++;

            while (SDL_PollEvent(&event)){
                if(event.type == SDL_QUIT){
                    escolhendo = false;
                    running = false;
                }
            }

            if(teclado[SDL_SCANCODE_RETURN]) escolhendo = false;
            //printf("\r%i\t\t\t\t", teclado[SDL_SCANCODE_RETURN]);

            if(teclado[SDL_SCANCODE_SPACE] && cont >= 5){
                gerarTerreno();
                cont = 0;
            }

            // fundo
            printBMP(fundo, surface, 0, 0);
            // terra
            rendererAtual = renderTerra;
            drawTerra();
            rendererAtual = renderPrincipal;
            // mar
            drawMar(marframe);
            // instrucoes
            printBMP(instrucoes, surface, 0, 0);
            // update
            SDL_UpdateWindowSurface(window);

            SDL_Delay(20);
        }

        // Inicializacao dos tanks
        pTank[0] = &tank1;
        pTank[1] = &tank2;

        tank1.centroX = 340+rand()%280;
        tank1.centroY = 100;
        tank1.vertices = verticesTank;
        tank1.canhao = verticesCanhao;
        tank1.verticesO = verticesTankO;
        tank1.canhaoO = verticesCanhaoO;
        tank1.anguloCanhao = 0; //limites sao -pi/2 e pi/2
        tank1.caindo = true;
        tank1.movendo = 0;
        tank1.canhaoTravado = false;
        tank1.forca = 100;
        tank1.corInterna.r = 30;
        tank1.corInterna.g = 130;
        tank1.corInterna.b = 220;
        tank1.corInterna.a = 255;
        tank1.corExterna.r = 200;
        tank1.corExterna.g = 200;
        tank1.corExterna.b = 200;
        tank1.corExterna.a = 255;
        tank1.vida = 300;
        tank1.combustivel = 96;
        tank1.municao[0] = INT_MAX;
        tank1.municao[1] = 4;
        tank1.municao[2] = 2;
        tank1.municao[3] = 2;
        tank1.municao[4] = 2;
        tank1.municao[5] = 2;
        tank1.angulo = 0;
        tank1.armaInt = 0;
        setPosCanhao(&tank1);

        tank2.centroX = 20+rand()%280;
        tank2.centroY = 100;
        tank2.vertices = verticesTank;
        tank2.canhao = verticesCanhao;
        tank2.verticesO = verticesTankO;
        tank2.canhaoO = verticesCanhaoO;
        tank2.anguloCanhao = 0; //limites sao -pi/2 e pi/2
        tank2.caindo = true;
        tank2.movendo = 0;
        tank2.canhaoTravado = false;
        tank2.forca = 100;
        tank2.corInterna.r = 230;
        tank2.corInterna.g = 60;
        tank2.corInterna.b = 30;
        tank2.corInterna.a = 255;
        tank2.corExterna.r = 45;
        tank2.corExterna.g = 45;
        tank2.corExterna.b = 45;
        tank2.corExterna.a = 255;
        tank2.vida = 300;
        tank2.combustivel = 96;
        tank2.municao[0] = INT_MAX;
        tank2.municao[1] = 4;
        tank2.municao[2] = 2;
        tank2.municao[3] = 2;
        tank2.municao[4] = 2;
        tank2.municao[5] = 2;
        tank2.angulo = 0;
        tank2.armaInt = 0;
        setPosCanhao(&tank2);

        contaFrame = 0;
        contaRun = 0;
        umSegundo.velho = 0;
        umSegundo.limite = 1000;
        t_frame.velho = 0;
        t_frame.limite = 16;

        t_part.velho = 0;
        t_renderTank.velho = 0;
        t_renderTank.limite = 15; //10

        armaInt = 0;
        arma = (tipoProjetil) 0;
        mudarArma = false;

        // MAIN GAME LOOP
        while (running)
        {
            // Resetar as coisas ativadas por teclas:
            mudarArma = false;
            teste = false;
            pTank[turno]->movendo = 0;
            pTank[turno]->mirando = 0;
            // Check for various events (keyboard, mouse, touch, close)

            //Checar fechamento da janela
            while (SDL_PollEvent(&event)) if (event.type == SDL_QUIT) running = false;

            //Checagem de pressionamento das teclas
            if(!partidaAcabou && !tirosVoando && !pTank[turno]->caindo){
                if ((turno == 0 && teclado[SDL_SCANCODE_RIGHT]) || (turno == 1 && teclado[SDL_SCANCODE_D]))
                {
                    if(!pTank[turno]->canhaoTravado){
                        pTank[turno]->movendo = 1;
                        if(pTank[turno]->anguloCanhao < 0) pTank[turno]->anguloCanhao *= -1;
                    }
                }
                else if ((turno == 0 && teclado[SDL_SCANCODE_LEFT]) || (turno == 1 && teclado[SDL_SCANCODE_A]))
                {
                    if(!pTank[turno]->canhaoTravado){
                        pTank[turno]->movendo = -1;
                        if(pTank[turno]->anguloCanhao > 0) pTank[turno]->anguloCanhao *= -1;
                    }
                }
                else if ((turno == 0 && teclado[SDL_SCANCODE_UP]) || (turno == 1 && teclado[SDL_SCANCODE_W]))
                {
                    pTank[turno]->mirando = -1;
                }
                else if ((turno == 0 && teclado[SDL_SCANCODE_DOWN]) || (turno == 1 && teclado[SDL_SCANCODE_S]))
                {
                    pTank[turno]->mirando = 1;
                }
                else if ((turno == 0 && teclado[SDL_SCANCODE_RSHIFT]) || (turno == 1 && teclado[SDL_SCANCODE_X]))
                {
                    teste = true;
                }
                else if ((turno == 0 && teclado[SDL_SCANCODE_RCTRL]) || (turno == 1 && teclado[SDL_SCANCODE_Z]))
                {
                    mudarArma = true;
                }
            } else if(partidaAcabou && teclado[SDL_SCANCODE_RETURN]) restart = true;

            //checar se algum dos tanks morreu
            for(i = 0; i < 2; i++){
                if(pTank[i]->vida <= 0){
                    pTank[i]->corInterna.r = 80;
                    pTank[i]->corInterna.g = 80;
                    pTank[i]->corInterna.b = 80;
                    partidaAcabou = true;
                }
            }

            t_renderTank.novo = SDL_GetTicks();
            if(t_renderTank.novo - t_renderTank.velho >= t_renderTank.limite)
            {
                for(i = 0; i < 2; i++){
                    if(pTank[i]->centroY < terra[pTank[i]->centroX]-2){
                        // esta caindo
                        pTank[i]->caindo = true;
                        if(pTank[i]->centroY < terra[pTank[i]->centroX]-1){
                            // pode cair 2
                            pTank[i]->centroY += 2;
                        } else {
                            // so pode cair 1
                            pTank[i]->centroY++;
                        }
                    } else {
                        // nao esta caindo
                        pTank[i]->caindo = false;
                    }
                }

                //
                if(pTank[turno]->movendo != 0 && !pTank[turno]->caindo && pTank[turno]->combustivel > 0){
                    if(pTank[turno]->centroY-3 <= terra[pTank[turno]->centroX+pTank[turno]->movendo]){
                        if(pTank[turno]->centroY-3 <= terra[pTank[turno]->centroX+(pTank[turno]->movendo)*2] && pTank[turno]->combustivel >= 2){
                            //pode andar 2 de vez
                            pTank[turno]->centroY = terra[pTank[turno]->centroX+(pTank[turno]->movendo)*2]-1;
                            pTank[turno]->centroX += 2*pTank[turno]->movendo;
                            pTank[turno]->combustivel -= 2;
                        } else {
                            //pode andar um so
                            pTank[turno]->centroY = terra[pTank[turno]->centroX+pTank[turno]->movendo]-1;
                            pTank[turno]->centroX += pTank[turno]->movendo;
                            pTank[turno]->combustivel--;
                        }

                        if(pTank[turno]->centroX < 0){
                            pTank[turno]->centroX = 0;
                            pTank[turno]->centroY = terra[0]+1;
                        } else if(pTank[turno]->centroX > 639){
                            pTank[turno]->centroX = 639;
                            pTank[turno]->centroY = terra[639]+1;
                        }
                    }
                    //else nao pode andar
                }

                //checar se caiu na lava
                for(i = 0; i < 2; i++){
                    if(pTank[i]->centroY > 640-100){
                        pTank[i]->vida = 0;
                        partidaAcabou = true;
                    }
                }

                for(i = 0; i < 2; i++){
                    if(!pTank[i]->caindo){
                        pTank[i]->angulo = atan(declividade(pTank[i]->centroX));
                    }
                }

                if(pTank[turno]->mirando != 0 && !pTank[turno]->caindo){
                    if(pTank[turno]->canhaoTravado){
                        pTank[turno]->forca += (-2)*pTank[turno]->mirando;
                        if(pTank[turno]->forca < 0 || pTank[turno]->forca > FORCAMAX){
                            pTank[turno]->forca = ((-1)*FORCAMAX*pTank[turno]->mirando+FORCAMAX)/2;
                        }

                    } else {
                        pTank[turno]->anguloCanhao += M_PI/90*pTank[turno]->mirando;
                        if(pTank[turno]->anguloCanhao < -1*M_PI/2 || pTank[turno]->anguloCanhao > M_PI/2)
                            pTank[turno]->anguloCanhao = pTank[turno]->mirando*M_PI/2;
                    }
                }

                setPosCanhao(pTank[0]);
                setPosCanhao(pTank[1]);

                j++;
                if(j >= 20 && mudarArma){
                    armaInt++;
                    while(pTank[turno]->municao[armaInt] <= 0 && armaInt < 6) armaInt++;
                    if(armaInt > 5) armaInt = 0;
                    arma = (tipoProjetil) armaInt;
                    pTank[turno]->armaInt = armaInt;
                    j = 0;
                } else if(j >= 20 && teste && !pTank[turno]->caindo){

                    if(pTank[turno]->canhaoTravado){
                        if(arma == acido){
                            for(i = 0; i < 30; i++) criarProjetil(pTank[turno], arma, pTank[turno]->forca);
                        } else if(arma == napalm){
                            for(i = 0; i < 16; i++) criarProjetil(pTank[turno], arma, pTank[turno]->forca);
                        } else {
                            criarProjetil(pTank[turno], arma, pTank[turno]->forca);
                        }
                        pTank[turno]->canhaoTravado = false;

                        pTank[turno]->armaInt = armaInt;
                        if(turno == 0) turno = 1;
                        else turno = 0;
                        armaInt = pTank[turno]->armaInt;
                        arma = (tipoProjetil) armaInt;
                        pTank[turno]->combustivel += 48;
                        if(pTank[turno]->combustivel > 96) pTank[turno]->combustivel = 96;
                    } else {
                        if(pTank[turno]->municao[pTank[turno]->armaInt] > 0){
                            pTank[turno]->municao[pTank[turno]->armaInt]--;
                            pTank[turno]->canhaoTravado = true;
                        }
                    }

                    j = 0;
                }

                t_renderTank.velho = t_renderTank.novo;
            }

            // atualizacao das particulas
            t_part.novo = SDL_GetTicks();
            atualizar((float) (t_part.novo-t_part.velho)/FATORATT);
            t_part.velho = t_part.novo;
            checarColisao();

            // PARTE DO DESENHO

            t_frame.novo = SDL_GetTicks();
            if(t_frame.novo - t_frame.velho >= t_frame.limite){

                printBMP(fundo, surface, 0, 0);

                // TERRA
                rendererAtual = renderTerra;
                drawTerra();
                rendererAtual = renderPrincipal;

                //mar
                drawMar(marframe);

                for(i = 0; i < 2; i++){
                    if(pTank[i]->centroY <= 640-100){
                        //Desenhar os tanks
                        desenharTank(pTank[i]);
                        //desenhar barras de vida e combustivel
                        drawHUD(pTank[i]);
                    }
                }

                if(!partidaAcabou && !tirosVoando && !pTank[turno]->caindo) indicarTurno(pTank[turno]);

                // desenhar projeteis
                drawParticulas();

                if(partidaAcabou){
                    printBMP(gameover, surface, 120, 100);
                    if(pTank[0]->vida == 0) printBMP(vencedor, surface, pTank[1]->centroX-47, pTank[1]->centroY-48);
                    if(pTank[1]->vida == 0) printBMP(vencedor, surface, pTank[0]->centroX-47, pTank[0]->centroY-48);
                }

                // UPDATE
                SDL_UpdateWindowSurface(window);
                //UPDATE();

                //AQUI JA JOGOU O FRAME NA TELA
                contaFrame++;
                t_frame.velho = t_frame.novo;
            }

            contaRun++;

            t_mar.novo = SDL_GetTicks();
            if(t_mar.novo - t_mar.velho >= t_mar.limite){
                if(marframe == 1) marinc = 1;
                else if(marframe == 5) marinc = -1;
                marframe += marinc;
                t_mar.velho = t_mar.novo;
            }

            umSegundo.novo = SDL_GetTicks();
            if(umSegundo.novo - umSegundo.velho >= umSegundo.limite){
                //printf("\rRPS: %i\tFPS: %i\t\t\t", contaRun, contaFrame);    // FPS \r no comeco
                contaFrame = 0;
                contaRun = 0;
                umSegundo.velho = umSegundo.novo;
            }

            if(restart){
                partidaAcabou = false;
                SDL_Delay(200);
                break;
            }
        }

    }

    // Liberacao de recursos
    SDL_FreeSurface(surface);
    SDL_FreeSurface(terraSurface);
    freeBMPsurfaces();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyRenderer(renderPrincipal);
    SDL_DestroyRenderer(renderTerra);
    SDL_DestroyRenderer(rendererAtual);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
