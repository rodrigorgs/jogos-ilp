#include <iostream>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string>
#include <time.h>

using namespace std;


//Number of Maps
const int numberOfMaps = 4;
//Current map number
int currentMap = 0;
//Map                                          0 == Non-Wall Space      1 == Wall
const int Map[numberOfMaps][30][40] = {

	//Map 1
	{
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	},
	//Map 2
	{
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
		{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
		{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	},

	//Map 3
	{
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}
	},

	//Map 4
	{
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	}
};

//Defines max size
const int maxSize = 300;

//Defines time per ScreenUpdate in miliseconds
const int upTime = 100;

//Score in number
int score = 0;
//Time since start turn
int totalTime = 0;
//Time in reset
int resetTime = 0;

//Define Window sizes
const int WINDOW_SIZE_X = 1000, WINDOW_SIZE_Y = 600;

//Checks if snake will crash
bool willCrash = false;
//Checks if randomized food position is free
bool isPosFree = false;

//Window
SDL_Window* gWindow = NULL;

//Surface in Screen
SDL_Surface* gScreenSurface = NULL;	
//Player image (Cobrinha)
SDL_Surface* pImage = NULL;
//Food Image
SDL_Surface* foodImage = NULL;
//Wall Image
SDL_Surface* wallImage = NULL;

//Audio that plays on item get
Mix_Chunk *AudioItem = NULL;
//Audio played on death
Mix_Chunk *AudioDeath = NULL;

//Font size
const int fontSize = 24;
//Text Font
TTF_Font* tFont = NULL;
//Title Font
TTF_Font* tTitleFont = NULL;
//Color of text
SDL_Color tColor = {255, 0, 0};
//Title surface text
SDL_Surface* tTitleSurface = NULL;
//Text surface
SDL_Surface* tSurface = NULL;

//Text rect
SDL_Rect tRect;
//Player rect in screen
SDL_Rect playerRect;
//Wall rect in screen
SDL_Rect wallRect;
//Difine Rect to paint black and white 
SDL_Rect blackRect, whiteRect;
	

//Player speed (-20 or 0 or 20)  in x and y
typedef struct {
	int x;
	int y;
} speed;

//Player position x and y
typedef struct {
	int x;
	int y;
} position;

void Initialize() {

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO);

	IMG_Init(IMG_INIT_PNG);

	TTF_Init();

	Mix_OpenAudio(44100, AUDIO_S16, 2, 512);
	
	gWindow = SDL_CreateWindow("Cobrinha", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_SIZE_X, WINDOW_SIZE_Y, SDL_WINDOW_OPENGL);

	gScreenSurface = SDL_GetWindowSurface(gWindow);

	//Random seed for rand() function
	srand (time(NULL));
}

void LoadAssets() {

	//Load player image
	pImage = IMG_Load("Assets/Art/player.png");
	//Load food image
	foodImage = IMG_Load("Assets/Art/food.png");
	//Load wall image
	wallImage = IMG_Load("Assets/Art/wall.png");

	//Load font
	tFont = TTF_OpenFont("Assets/Fonts/OpenSans-Regular.ttf", fontSize);
	//Load title font
	tTitleFont = TTF_OpenFont("Assets/Fonts/OpenSans-Regular.ttf", fontSize + 6);
	//Make surface with font
    tTitleSurface = TTF_RenderText_Solid(tTitleFont, "Snake", tColor);    

    //Load audio files
    AudioItem = Mix_LoadWAV("Assets/Audio/itemgetaudio.wav");
    AudioDeath = Mix_LoadWAV("Assets/Audio/audiodeath.wav");
}

void UpdateGameScreen(position pPos[], SDL_Rect fPos, int size) {		

	//Paints game background
	SDL_FillRect(gScreenSurface, &blackRect, SDL_MapRGB(gScreenSurface->format, 0, 0, 0));
	//Paints score menu background
	SDL_FillRect(gScreenSurface, &whiteRect, SDL_MapRGB(gScreenSurface->format, 255, 255, 255));

		
	//Paints Wall on screen
	for (int i = 0; i < 30; i++) {

		for (int k = 0; k < 40; k++) {

			if (Map[currentMap][i][k] == 1) {
				wallRect.x = k * 20;
				wallRect.y = i * 20;

				SDL_BlitSurface(wallImage, NULL, gScreenSurface, &wallRect);
			}
		}
	}

	//Paints Player on screen
	for (int i = 0; i < size; i++) {
		
		playerRect.x = pPos[i].x;
		playerRect.y = pPos[i].y;					

		SDL_BlitSurface(pImage, NULL, gScreenSurface, &playerRect);
	}			

	//Paints Food on screen
	SDL_BlitSurface(foodImage, NULL, gScreenSurface, &fPos);	
	
}

void WriteText() {
	
	tRect.x = 850; //Center title
	tRect.y = 10;
	//Title
	SDL_BlitSurface(tTitleSurface, NULL, gScreenSurface, &tRect);

	//Score
	tRect.x = 835; //Change rect pos x
	tRect.y = 100; //Change rect pos y
	//Cleans Surface
	SDL_FreeSurface(tSurface);
	tSurface = TTF_RenderText_Solid(tFont, "Tempo:", tColor);	
	SDL_BlitSurface(tSurface, NULL, gScreenSurface, &tRect);
	tRect.x = 920; //Change rect pos x
	tRect.y = 100; //Change rect pos y
	//Cleans Surface
	SDL_FreeSurface(tSurface);
	tSurface = TTF_RenderText_Solid(tFont, to_string(totalTime).c_str(), tColor); // Draws time
	SDL_BlitSurface(tSurface, NULL, gScreenSurface, &tRect);
	
	tRect.x = 840; //Change rect pos x
	tRect.y = 180; //Change rect pos y
	//Cleans Surface
	SDL_FreeSurface(tSurface);
	tSurface = TTF_RenderText_Solid(tFont, "Pontos:", tColor);
	SDL_BlitSurface(tSurface, NULL, gScreenSurface, &tRect);
	tRect.x = 930; //Change rect pos x	
	//Cleans Surface
	SDL_FreeSurface(tSurface);
	tSurface = TTF_RenderText_Solid(tFont, to_string(score).c_str(), tColor);
	SDL_BlitSurface(tSurface, NULL, gScreenSurface, &tRect);	

	tRect.x = 815; //Change rect pos x
	tRect.y = 260; //Change rect pos y
	//Cleans Surface
	SDL_FreeSurface(tSurface);
	tSurface = TTF_RenderText_Solid(tFont, "Mapa Anterior:", tColor);
	SDL_BlitSurface(tSurface, NULL, gScreenSurface, &tRect);
	tRect.x = 860; //Change rect pos x
	tRect.y = 290; //Change rect pos y
	//Cleans Surface
	SDL_FreeSurface(tSurface);
	tSurface = TTF_RenderText_Solid(tFont, "Tecla 4", tColor);
	SDL_BlitSurface(tSurface, NULL, gScreenSurface, &tRect);

	tRect.x = 815; //Change rect pos x
	tRect.y = 340; //Change rect pos y
	//Cleans Surface
	SDL_FreeSurface(tSurface);
	tSurface = TTF_RenderText_Solid(tFont, "Proximo Mapa:", tColor);
	SDL_BlitSurface(tSurface, NULL, gScreenSurface, &tRect);
	tRect.x = 860; //Change rect pos x
	tRect.y = 370; //Change rect pos y
	//Cleans Surface
	SDL_FreeSurface(tSurface);
	tSurface = TTF_RenderText_Solid(tFont, "Tecla 6", tColor);
	SDL_BlitSurface(tSurface, NULL, gScreenSurface, &tRect);

	tRect.x = 825; //Change rect pos x
	tRect.y = 420; //Change rect pos y
	//Cleans Surface
	SDL_FreeSurface(tSurface);
	tSurface = TTF_RenderText_Solid(tFont, "Mapa Atual:", tColor);
	SDL_BlitSurface(tSurface, NULL, gScreenSurface, &tRect);
	tRect.x = 960; //Change rect pos x	
	//Cleans Surface
	SDL_FreeSurface(tSurface);
	tSurface = TTF_RenderText_Solid(tFont, to_string(currentMap + 1).c_str(), tColor);
	SDL_BlitSurface(tSurface, NULL, gScreenSurface, &tRect);

	tRect.x = 850; //Change rect pos x
	tRect.y = 500; //Change rect pos y
	//Cleans Surface
	SDL_FreeSurface(tSurface);
	tSurface = TTF_RenderText_Solid(tFont, "Morreu?", tColor);
	SDL_BlitSurface(tSurface, NULL, gScreenSurface, &tRect);
	tRect.x = 840; //Change rect pos x
	tRect.y = 530; //Change rect pos y
	//Cleans Surface
	SDL_FreeSurface(tSurface);
	tSurface = TTF_RenderText_Solid(tFont, "Tecla Enter", tColor);
	SDL_BlitSurface(tSurface, NULL, gScreenSurface, &tRect);

}

SDL_Rect FoodRandomizer(SDL_Rect f, position player[], int size) {

	isPosFree = false;

	while (!isPosFree) {

		isPosFree = true;

		f.x = rand() % 780 + 1;
		f.y = rand() % 580 + 1;

		f.x -= (f.x % 40);
		f.y -= (f.y % 40);

		//Checks if there is a player on next position
		for (int i = 0; i < size; i++) {

			if ((f.x == player[i].x && f.y == player[i].y)) {
				isPosFree = false;			
			}
		}
		//Check if there is a wall on the next position		
		if (Map[currentMap][f.y / 20][f.x /20] == 1) {
			isPosFree = false;
		}
	}

	return f;
}

void EndAll() {

	SDL_DestroyWindow(gWindow);

	Mix_CloseAudio();

	SDL_Quit();
	TTF_Quit();
	IMG_Quit();

}

int main(int argc, char* agrs[]) {

    Initialize();

    LoadAssets();

	//Define Color Rects
	blackRect.x = 0;
	blackRect.y = 0;
	blackRect.w = 800;
	blackRect.h = 600;
	whiteRect.x = 800;
	whiteRect.y = 0;
	whiteRect.w = WINDOW_SIZE_X - 800;
	whiteRect.h = 600;
	//Define Player Rect
	playerRect.w = 20;
	playerRect.h = 20;
	//Define Wall Rect
	wallRect.w = 20;
	wallRect.h = 20;

    //Snake Size
    int pSize = 3, inFront = 0, nextFront, nextToSave;

    //Event Handler
	SDL_Event e;
	//Check if player wants to quit from game
	bool quit = false, getInput = true;

	//Player initial speed		
	speed pSpeed;
	pSpeed.x = 20;
	pSpeed.y = 0;

	//Get the position of where the player will move to
	position newPos;
	//Rearange player positions
	position orderedPos[maxSize];
	//Player positions
	position playerPos[maxSize];
	//First piece of player pos
	playerPos[0].x = 400;
	playerPos[0].y = 300;
	playerPos[1].x = 400;
	playerPos[1].y = 300;
	playerPos[2].x = 400;
	playerPos[2].y = 300;

	//Zero all other pieces position
	for (int i = 3; i < maxSize; i++)	{

		playerPos[i].x = 0;
		playerPos[i].y = 0;

	}

	//Where food will appear
	SDL_Rect foodPos;
	foodPos.x = 80;
	foodPos.y = 0;
	foodPos.w = 20;
	foodPos.h = 20;

	//Ramdomize food position concerning walls and player positions
	foodPos = FoodRandomizer(foodPos, playerPos, pSize);

	//Time Handler  --  SDL_GetTicks() gets the miliseconds passed since Init
	int startTime = SDL_GetTicks(), endTime;
	
	UpdateGameScreen(playerPos, foodPos, pSize);
	WriteText();

	//First value for reset Time
	resetTime = SDL_GetTicks();

	while (!quit) {
		while (SDL_PollEvent(&e)) {

			//Checks if player clicked on X or pushed Esc
			if ((e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) || e.type == SDL_QUIT) {
				quit = true;

			} else if (getInput) {

				if (e.key.keysym.sym == SDLK_RIGHT && pSpeed.x == 0 && e.type == SDL_KEYDOWN) {

					pSpeed.x = 20;
					pSpeed.y = 0;
					getInput = false;

				} else if (e.key.keysym.sym == SDLK_LEFT && pSpeed.x == 0 && e.type == SDL_KEYDOWN) {

					pSpeed.x = -20;
					pSpeed.y = 0;
					getInput = false;

				} else if (e.key.keysym.sym == SDLK_UP && pSpeed.y == 0 && e.type == SDL_KEYDOWN) {

					pSpeed.x = 0;
					pSpeed.y = -20;
					getInput = false;

				} else if (e.key.keysym.sym == SDLK_DOWN && pSpeed.y == 0 && e.type == SDL_KEYDOWN) {

					pSpeed.x = 0;
					pSpeed.y = 20;
					getInput = false;

				} else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_6) {

					currentMap++;

					if (currentMap == numberOfMaps) {
						currentMap = 0;
					}

					pSize = 3;					

			 		playerPos[0].x = 400;
					playerPos[0].y = 300;
					playerPos[1].x = 400;
					playerPos[1].y = 300;
					playerPos[2].x = 400;
					playerPos[2].y = 300;

					for (int i = 3; i < maxSize; i++) {
						playerPos[i].x = 0;
						playerPos[i].y = 0;
				 	}

				 	//Ramdomize food position concerning walls and player positions
					foodPos = FoodRandomizer(foodPos, playerPos, pSize);

					pSpeed.x = 20;
					pSpeed.y = 0;

					inFront = 0;

					resetTime = SDL_GetTicks();
					score = 0;

				} else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_4) {

					currentMap--;

					if (currentMap == -1) {
						currentMap = numberOfMaps - 1;
					}

					pSize = 3;					

			 		playerPos[0].x = 400;
					playerPos[0].y = 300;
					playerPos[1].x = 400;
					playerPos[1].y = 300;
					playerPos[2].x = 400;
					playerPos[2].y = 300;

					for (int i = 3; i < maxSize; i++) {
						playerPos[i].x = 0;
						playerPos[i].y = 0;
				 	}

				 	//Ramdomize food position concerning walls and player positions
					foodPos = FoodRandomizer(foodPos, playerPos, pSize);

					pSpeed.x = 20;
					pSpeed.y = 0;

					inFront = 0;

					resetTime = SDL_GetTicks();
					score = 0;
				} 
			}			
		}

		endTime = SDL_GetTicks();

		if (endTime - startTime >= upTime - (pSize)) {

			nextFront = inFront - 1;			

			if (nextFront == -1) {
				nextFront = pSize - 1;
			}

			newPos.x = playerPos[inFront].x + pSpeed.x;
			newPos.y = playerPos[inFront].y + pSpeed.y;

			if (newPos.x == -20) {
				newPos.x = 780;
			}
			else if (newPos.x == 800) {
				newPos.x = 0;
			}
			else if (newPos.y == -20) {
				newPos.y = 580;
			}
			else if (newPos.y == 600) {
 				newPos.y = 0;
			}


			//If food is in the next place that snake will go...
			if (newPos.x == foodPos.x && newPos.y == foodPos.y) {

				score++;

				Mix_PlayChannel(-1, AudioItem, 0);

				foodPos.x = -60;
				foodPos.y = 0;	

				int changePos = inFront;

				for (int i = 0; i < pSize + 1; i++) {

					orderedPos[i] = playerPos[changePos];

					changePos++;

					if (changePos == pSize) {
						changePos = 0;
					}
				}

				//New tail becomes old tail
				playerPos[pSize] = playerPos[nextFront];

				for (int i = 0; i < pSize + 1; i++) {
					playerPos[i] = orderedPos[i];
				}

				pSize++;

				inFront = 0;

				//Ramdomize food position concerning walls and player positions
				foodPos = FoodRandomizer(foodPos, playerPos, pSize);				

			} else {

				//Checks for snake part on next position
				for (int i = 0; i < pSize; i++) {

					if (i != nextFront) {
						if (playerPos[i].x == newPos.x && playerPos[i].y == newPos.y) {
							willCrash = true;
							Mix_PlayChannel(-1, AudioDeath, 0);
						}
					}
				}

				if (!willCrash) {
					
					//Checks for block in next position
					if (Map[currentMap][newPos.y / 20][newPos.x / 20] == 1) {

						willCrash = true;
						Mix_PlayChannel(-1, AudioDeath, 0);
				
					} else {

						playerPos[nextFront].x = newPos.x;
						playerPos[nextFront].y = newPos.y;
						
						inFront = nextFront;
						
						startTime = SDL_GetTicks();

						getInput = true;

					}
				}
			}			
		}	

		while (willCrash && !quit) {

			while (SDL_PollEvent(&e)) {

				if ((e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) || e.type == SDL_QUIT) {

					quit = true;

				} else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) {
					
					pSize = 3;					

			 		playerPos[0].x = 400;
					playerPos[0].y = 300;
					playerPos[1].x = 400;
					playerPos[1].y = 300;
					playerPos[2].x = 400;
					playerPos[2].y = 300;

					for (int i = 3; i < maxSize; i++) {
						playerPos[i].x = 0;
						playerPos[i].y = 0;
				 	}

				 	//Ramdomize food position concerning walls and player positions
					foodPos = FoodRandomizer(foodPos, playerPos, pSize);

					pSpeed.x = 20;
					pSpeed.y = 0;

					inFront = 0;

				 	//startTime = SDL_GetTicks();
					willCrash = false;		

					//Resets score
					score = 0;	
					//Puts reset time
					resetTime = SDL_GetTicks();	

				} else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_6) {

					currentMap++;

					if (currentMap == numberOfMaps) {
						currentMap = 0;
					}

					pSize = 3;					

			 		playerPos[0].x = 400;
					playerPos[0].y = 300;
					playerPos[1].x = 400;
					playerPos[1].y = 300;
					playerPos[2].x = 400;
					playerPos[2].y = 300;

					for (int i = 3; i < maxSize; i++) {
						playerPos[i].x = 0;
						playerPos[i].y = 0;
				 	}

				 	//Ramdomize food position concerning walls and player positions
					foodPos = FoodRandomizer(foodPos, playerPos, pSize);

					pSpeed.x = 20;
					pSpeed.y = 0;

					inFront = 0;

					resetTime = SDL_GetTicks();
					score = 0;

					willCrash = false;

				} else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_4) {

					currentMap--;

					if (currentMap == -1) {
						currentMap = numberOfMaps - 1;
					}

					pSize = 3;					

			 		playerPos[0].x = 400;
					playerPos[0].y = 300;
					playerPos[1].x = 400;
					playerPos[1].y = 300;
					playerPos[2].x = 400;
					playerPos[2].y = 300;

					for (int i = 3; i < maxSize; i++) {
						playerPos[i].x = 0;
						playerPos[i].y = 0;
				 	}

				 	//Ramdomize food position concerning walls and player positions
					foodPos = FoodRandomizer(foodPos, playerPos, pSize);

					pSpeed.x = 20;
					pSpeed.y = 0;

					inFront = 0;

					resetTime = SDL_GetTicks();
					score = 0;

					willCrash = false;
				}
			}

			getInput = false;
		}		

		totalTime = (SDL_GetTicks() - resetTime) / 1000;
		UpdateGameScreen(playerPos, foodPos, pSize);
		WriteText();
		//Updates Screen
		SDL_UpdateWindowSurface(gWindow);	

	}

    EndAll();        
    return 0;
}