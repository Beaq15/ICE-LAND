#pragma once
#include "AnimationManager.h"

using namespace std;

class BattleEffects
{
public:
	int x, y;
	SDL_Renderer* renderer;
	Animation hit, heal, explode, atkBoost, defBoost;
	AnimationManager animationManager;

	//set true while effect is animating
	bool doAction;

	void setup(SDL_Renderer* renderer, int x, int y);
	void setXY(int x, int y);
	void doHit();
	void doHeal();
	void doExplode();
	void doAtkBoost();
	void doDefBoost();

	void update(float dt);
	void draw();
};

