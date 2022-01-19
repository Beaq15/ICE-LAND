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

using namespace std;

class BattleScreen
{
public:
	SDL_Renderer* renderer;
	SDL_Texture* backgroundTexture;

	SnowQueen* snowQueen;
	int* items;//pointer for our items array

	Character* enemy;

	bool battleFinished;
	bool quit;
	bool heroesTurn = true;

	SDL_Texture* nameTexture;
	SDL_Rect nameRect;

	CharacterAnimationSet heroAnimationSet;
	CharacterAnimationSet enemyAnimationSet;

	HPBar heroHP;
	HPBar enemyHP;

	Button fightButton;
	Button itemButton;

	int heroDmg = 0, enemyDmg = 0;

	BattleEffects battleEffects;

	ItemMenu itemMenu;
	InfoBox infoBox;

	BattleScreen(SDL_Renderer* renderer, SnowQueen* snowQueen, int* items, CharacterType enemyType);
	~BattleScreen();
	bool animationsPlaying();
	void useItem();
	void update();
	void draw();
};

