Comando para compilação do jogo:
	Mac ou Linux:
		`sdl2-config --cflags --libs` -lSDL2_ttf -lSDL2_image -lSDL2_mixer
	Windows:
		-I "C:\MinGW\include\SDL2" -mwindows -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
	OBS: O arquivo que deve ser compilado é o Main.cpp

Como jogar ?
	Objetivo do jogo: Passar entre o maior número de canos possíveis.
	Instruções: Use cliques no botão de espaço para fazer o passarinho voar.
	OBS: Ao perder as 3 vidas é necessário reiniciar o jogo.