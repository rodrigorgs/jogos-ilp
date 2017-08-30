--------------------------------------------
||	README.txt do jogo ILP Tanks      ||
--------------------------------------------

-----------------------------
||	Para Compilar      ||
-----------------------------

-> Caso sua máquina rode o sistema operacional Windows:

Pressione as teclas "Windows+R", na janela que aparecer 
digite "cmd.exe" e pressione enter, cole um dos comandos 
abaixo dependendo do compilador que quer usar:

"g++ main.c -lmingw32 -lSDL2main -lSDL2 -mwindows -o ILPTanks.exe", 
para g++

ou

"gcc main.c -lmingw32 -lSDL2main -lSDL2 -mwindows -o ILPTanks.exe", 
para gcc

-> Caso sua máquina rode sistema baseado em GNU/Linux:

Abra o terminal na pasta do jogo, muitas distruibuições possuem essa opção no menu de contexto ou utilizando as teclas "CTRL+ALT+T" e intruduza uma das seguintes linhas de comando:

g++ main.c -lSDL2 -lm -o ILPTanks, para g++

ou

gcc main.c -lSDL2 -lm -o ILPTanks, para gcc

(Nos dois casos, Windows ou Linux, tenha certeza de possuir as bibliotecas, dependências e arquivos necessários, cheque se possui SDL2 e suas dependências.)

-----------------------------
||	Para Executar      ||
-----------------------------

Para executar basta rodar o arquivo criado pelo compilador, as instruções para jogar aparecerão na tela do jogo.

-----------------------------
||	 Para Jogar        ||
-----------------------------

Basta tentar afundar o adversário ou causar dano até que o mesmo seja destruido. O player 1 se move com as setas, mira e ajusta força do canhão também com as setas, muda arma com RCTRL e atira com RSHIFT.
O player 2 se move com WASD, mira e ajusta força do canhão também com WASD, muda arma com Z e atira com X.