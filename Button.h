#pragma once
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

using namespace std;

class Button
{
public:
	SDL_Renderer* renderer;
	SDL_Rect buttonRect;
	SDL_Texture* textTexture;
	SDL_Rect textRect;

	bool selected;

	~Button();

	void setup(SDL_Renderer* renderer, SDL_Rect buttonRect, string text);
	void draw();
	void drawInactive();//what the buttons look like when the user cannot choose options
};

