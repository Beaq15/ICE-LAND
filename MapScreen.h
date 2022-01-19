#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "SnowQueen.h"
#include "MapObject.h"
#include <list>//is a container that can shrink and grow (others vector, map, queue, stack)

#include <fstream>//file stream
#include "InfoBox.h"

#include <stdlib.h>//useful functions including rand and srand
#include <time.h>//time in seconds since start of year

#include "BattleScreen.h"
#include "MainMenu.h"

using namespace std;

class MapScreen
{
public:
	SnowQueen* snowQueen;//reference hero built inside main.cpp
	int* items; //going to use this to reference items[10] from main.cpp

	SDL_Renderer* renderer;

	//2d array representing the map. 0 values = walls, 1 values = can walk/ground
	int map[14][14];
	MapObject heroObj;
	MapObject door;
	list<MapObject> mapObjects;

	SDL_Texture* snowQueenTexture, * doorTexture, * snowmanTexture, * chestTexture, * bigfootTexture, * snowTexture, * skyTexture, * cornerLDownTexture, * cornerLUPTexture, * cornerRDownTexture, * cornerRUPTexture, * icestoneBigLeftTexture, * icestoneBigRightTexture, * icestoneSmallTexture, * mountainBigDownTexture, * mountainBigUPTexture, * mountainSmallDownTexture, * mountainSmallUpTexture, * seaTexture;

	bool quit = false;
	bool escaped = false;
	bool doorLocked = true;

	InfoBox infoBox;

	MapScreen(SDL_Renderer* renderer, SnowQueen* snowQueen, int* items);
	~MapScreen();
	void itemFound();

	void update();
	void draw();
};

