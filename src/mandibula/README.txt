Instruções para compilar o jogo no Windows:

- Instalar o MinGW com o pacote Básico e com o Pacote G++ que possue o compilador de C++
Link do Tutorial: https://youtu.be/bEs-5IU_l9w

- Instalar as bibliotecas SDL necessárias para que rodem funções multimidias como: Imagens, áudio e textos
no seu jogo.

Feito isso, será necessário abrir o Prompt de Comando e localizar o diretório onde está localizado o seu código-fonte e jogo.
Isso pode ser feito através do seguinte comando sem as aspas: cd "Nome do diretório".
Após isso, para compilar o seu jogo, será necessário digitar no Prompt o seguinte código sem as aspas: g++ "Seu jogo.cpp" -o "Seu jogo.exe" -I "C:\MinGW\include\SDL2" -mwindows -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
Depois de compilar, se estiver tudo correto com o seu código, basta digitar "Seu jogo.exe" sem as aspas que o seu jogo rodará normalmente.

Intruções para jogar o Shark Strike:

- Com os arquivos extraídos numa mesma pasta, basta rodar o arquivo .exe "Shark Striker" que o jogo funcionará.