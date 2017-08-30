Introducao
===============

O jogo funciona da seguinte maneira: O algoritmo sorteia palavras de uma lista de 500 palavras.
Essas palavras são exibidas deslizando na tela do usuario de cima para baixo.
O usuario devera digitar corretamente as palavras. Caso nao consiga e a palavra atravessar a travessa, perde 1 vida.
Se o usuario falhar duas vezes, as palavras somem e o jogo exibe uma mensagem de "FIM DE JOGO".
Cada palavra acertada vale 10 pontos.
Atencao:
Cada vez que o usuario acerta uma palavra, a velocidade das palavras aumenta, tornando o jogo mais  dificil. Assim como, a cada 10 segundos, o numero maximo de palavras que podem ser criadas na tela simultaneamente aumenta. 
O numero maximo de palavras criadas é de 15 palavras.

Como jogar
===============
Utilize as teclas do teclado para digitar a palavra e aperte espaco. Use o backspace para apagar um caractere por vez, caso tenha errado.
Se voce acertou a palavra, esta devera sumir.

Intrucoes de compilacao
===============

Descompacte o arquivo zip em uma pasta.

Esta devera conter os arquivos Lista2.cc, words.por, JogoPalavras.cc, FreeSans.TTF, ilpgame.h, background.jpg.

Abra o diretorio onde voce descompactou com o terminal e rode o codigo "g++ JogoPalavras.cc -o teste.exe -I "Diretorio do SDL" -mwindows -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf" sem aspas, caso seja windows. Atente-se que o "Diretorio do SDL" deve ser substituido pelo diretorio do SDL no seu computador.

Caso seja linux, utilize o codigo "g++ JogoPalavras.cc `sdl2-config --cflags --libs` -lSDL2_ttf -lSDL2_image -lSDL2_mixer".