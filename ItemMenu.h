#pragma once
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

using namespace std;

class ItemMenu
{
private:
	SDL_Texture* generateTextTexture(TTF_Font* font, SDL_Color colour, string text);

public:
	SDL_Renderer* renderer;
	int* items;//items array

	SDL_Texture* noItem, * lifeRegen, * bomb, * attackBoost, * defenceBoost, * cancel;

	int x, y;
	int selectedItemIndex;

	bool visible = false;


	~ItemMenu();
	void setup(SDL_Renderer* renderer, int* items, int x, int y);
	void moveUp();
	void moveDown();
	void draw();
};

