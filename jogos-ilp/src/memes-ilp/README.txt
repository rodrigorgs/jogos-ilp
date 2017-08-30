Compilar para Windows:
g++ main.cc -I "C:\MinGW\include\SDL2" -mwindows -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_ttf -lSDL2_image

Compilar para MAC:
g++ main.cc `sdl2-config --cflags --libs` -lSDL2_ttf -lSDL2_image -lSDL2_mixer && ./a.out

