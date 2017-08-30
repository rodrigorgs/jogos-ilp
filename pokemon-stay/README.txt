Jogo Pokémon Stay, desenvolvido usando as SDL_2.0


Como compilar usando Linux:

Baixar biblioteca SDL_2.0
>> sudo apt-get install libsdl2*dev

Abrir o terminal Linux.
>> acessar o diretorio do jogo.
>> localizar o arquivo.cpp

>> compilar usando g++ ash_catcher.cpp `sdl2-config --cflags --libs` -lSDL2_ttf -lSDL2_image -lSDL2_mixer

>> se não houver erro, executar usando ./a.out e o jogo será iniciado.

Como jogar:

O jogo começa com o objeto bola centralizado na parte inferior da tela e os objetos pokemom caindo da parte superior, o objetivo do jogo é não deixar nenhum objeto tocar no chão (inferior da tela).
A movimentação da bola é para direita e esquerda, usando as telhas.
A cada captura, o jogo fica mais rapido, e lembramos que no inicio, começamos com 3 vidas e a cada colisão no chao perdemos uma.
Para sair do jogo, pode clicar na tecla Esc ou no "x" na tela do jogo.
