//extra library includes
#include <iostream> //input output stream
#include <string> 
#include "Character.h"
#include "SnowQueen.h"
#include "Snowman.h"
#include "BigFoot.h"
#include "MapScreen.h"
#include "MainMenu.h"
#include "Button.h"
#include "GameStates.h"
#include "BattleScreen.h"
//SDL Libraries
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

using namespace std;


int main(int argc, char** argv)
{
	string name;
	name = "Snow Queen";

	//hero stats
	int hp = 100, str = 4, def = 5, agi = 1;
	SnowQueen snowQueen;
	snowQueen.setName(name);
	snowQueen.setupStats(hp, str, def, agi);

	//Initialise SDL2
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		//if init not return 0, then initialisation failed
		cout << "SDL Init Error: " << SDL_GetError() << endl;
		system("pause");
		return 1;

	}
	//initialise subsystems we need e.g sdl image, mixer, ttf
	//TODO: look up C++ bitwise logic
	//image- being able to deal with other image types other then bmp. Also lets you play with surface pixel data
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		cout << "SDL IMG Init Error: " << IMG_GetError() << endl;
		system("pause");
		return 1;
	}
	//ttf - text to font, for rendering text to screen
	if (TTF_Init() != 0)
	{
		cout << "SDL TTF Init Error: " << TTF_GetError() << endl;
		system("pause");
		return 1;
	}
	//mixer- sound and music
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		cout << "SDL Mixer Init Error: " << Mix_GetError() << endl;
		system("pause");
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow("ICE LAND", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 768, 768, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		cout << "SDL window Error: " << SDL_GetError() << endl;
		SDL_Quit();
		system("pause");
		return 1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
	{
		cout << "SDL renderer Error: " << SDL_GetError() << endl;
		SDL_Quit();
		system("pause");
		return 1;
	}

	//the size gfx are at min, but then scale up to actual window size
	SDL_RenderSetLogicalSize(renderer, 384, 384);

	//ITEMS(using arrays...)
	//items as ints. 0 = no item, 1 = chocolate, 2 = grenade, 3 = atk up, 4 = def up
	//integer array holding 10 int variables
	int items[10];
	//loop through array using for loop and set each slot to = 0 (no item)
	for (int i = 0; i <= 9; i++)
	{
		//reference index using variable
		items[i] = 0;
	}

	GameStates currentGameState = GameStates::MainMenu;

	//setup mainmenu object
	MapScreen mapScreen(renderer, &snowQueen, items);
	MainMenu mainMenu(renderer);

	bool keepLooping = true;
	//Game Loop
	while (keepLooping)
	{
		switch (currentGameState)
		{
		case GameStates::MainMenu:
			mainMenu.update();
			mainMenu.draw();
			if (mainMenu.quit)
				keepLooping = false;
			if (mainMenu.playButtonPressed)
			{
				currentGameState = GameStates::MapScreen;
				mainMenu.playButtonPressed = false;
			}
			break;
		case GameStates::MapScreen:
			mapScreen.update();
			mapScreen.draw();
			if (mapScreen.quit)
				keepLooping = false;
			break;

		}
		//swaps drawing buffer
		SDL_RenderPresent(renderer);
	}
	//CLEANUP
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	//lets user interact by pressing anykey
	system("pause");
	return 0;
}