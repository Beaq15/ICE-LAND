#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <list>
#include "SnowQueen.h"
#include "Snowman.h"
#include "BigFoot.h"
#include "CharacterType.h"
#include "CharacterAnimationSet.h"
#include "HPBar.h"
#include "Button.h"
#include "BattleEffects.h"
#include "ItemMenu.h"
#include "InfoBox.h"
#include "MapScreen.h"

using namespace std;

class MainMenu
{
public:
	SnowQueen snowQueen;
	int* items;

	SDL_Renderer* renderer;
	SDL_Texture* backgroundTexture;

	Button playButton;
	Button quitButton;

	bool quit = false;
	bool playButtonPressed = false;

	MainMenu(SDL_Renderer* renderer);
	~MainMenu();

	void update();
	void draw();
};

