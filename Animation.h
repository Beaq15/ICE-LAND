#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

class Animation
{
public:
	//basic info
	int numberOfFrames;
	int frameWidth, frameHeight;
	int offsetX, offsetY; //frame pivot point
	float frameDuration; //how long single frame shows on screen 1 = 1 second, 0.5 = 500ms
	SDL_Texture* spriteSheet; //reference to existing texture
	SDL_Renderer* renderer;

	void setup(string spriteSheetFile, SDL_Renderer* renderer, int numberOfFrames, float frameDuration, int offsetX, int offsetY);
	~Animation();
	void draw(int frame, int x, int y);
};

