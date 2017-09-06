#!/bin/bash

cd mandibula; ../emscripten.sh Mandibula.cpp -o ../../build/mandibula.html; cd ..
cd bombermario; ../emscripten.sh bombermario1.cc -o ../../build/bombermario.html; cd ..
cd cai-tudo; ../emscripten.sh JogoPalavras.cc -o ../../build/cai-tudo.html; cd ..
cd flappy-bird; ../emscripten.sh Main.cpp -o ../../build/flappy-bird.html; cd ..
cd kill-the-zombie; ../emscripten.sh game2.cc -o ../../build/kill-the-zombie.html; cd ..
cd memes-ilp; ../emscripten.sh main.cc -o ../../build/memes-ilp.html; cd ..
cd pokemon-stay; ../emscripten.sh ash_catcher.cpp -o ../../build/pokemon-stay.html; cd ..
cd ta-chovendo-hamburguer; ../emscripten.sh jogo-codigo.cc -o ../../build/ta-chovendo-hamburguer.html; cd ..