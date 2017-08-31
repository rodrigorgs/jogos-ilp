Instru��es para compilar o jogo no Windows:

- Instalar o MinGW com o pacote B�sico e com o Pacote G++ que possue o compilador de C++
Link do Tutorial: https://youtu.be/bEs-5IU_l9w

- Instalar as bibliotecas SDL necess�rias para que rodem fun��es multimidias como: Imagens, �udio e textos
no seu jogo.

Feito isso, ser� necess�rio abrir o Prompt de Comando e localizar o diret�rio onde est� localizado o seu c�digo-fonte e jogo.
Isso pode ser feito atrav�s do seguinte comando sem as aspas: cd "Nome do diret�rio".
Ap�s isso, para compilar o seu jogo, ser� necess�rio digitar no Prompt o seguinte c�digo sem as aspas: g++ "Seu jogo.cpp" -o "Seu jogo.exe" -I "C:\MinGW\include\SDL2" -mwindows -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
Depois de compilar, se estiver tudo correto com o seu c�digo, basta digitar "Seu jogo.exe" sem as aspas que o seu jogo rodar� normalmente.

Intru��es para jogar o Shark Strike:

- Com os arquivos extra�dos numa mesma pasta, basta rodar o arquivo .exe "Shark Striker" que o jogo funcionar�.