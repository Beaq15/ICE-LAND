#include "MainMenu.h"

MainMenu::MainMenu(SDL_Renderer* renderer)
{
	this->renderer = renderer;
	//load background texture
	backgroundTexture = IMG_LoadTexture(renderer, "assets/mainmenuBG.jpeg");

	//setup button
	playButton.setup(renderer, { 60,270,80,30 }, "PLAY");
	playButton.selected = false;
	quitButton.setup(renderer, { 240,270,80,30 }, "QUIT");
	quitButton.selected = false;
}

MainMenu::~MainMenu()
{
	SDL_DestroyTexture(backgroundTexture);
}

void MainMenu::update()
{
	//read user inputs including keyboard, mouse, gamepads, screen resize/close, touchscreens etc
	SDL_Event sdlEvent;
	//loop through input events and copy their details one by one into our sdlEvent variable
	while (SDL_PollEvent(&sdlEvent))
	{
		//event when user clicks close window button
		if (sdlEvent.type == SDL_QUIT)
		{
			quit = true;
		}
		if (sdlEvent.type == SDL_KEYDOWN)
		{
			if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				quit = true;
			else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_DOWN)
			{
				playButton.selected = true;
			}
			if (playButton.selected && sdlEvent.key.keysym.scancode == SDL_SCANCODE_RIGHT)
			{
				quitButton.selected = true;
				playButton.selected = false;
			}
			if (quitButton.selected && sdlEvent.key.keysym.scancode == SDL_SCANCODE_LEFT)
			{
				quitButton.selected = false;
				playButton.selected = right;
			}
			if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_RETURN && playButton.selected)
			{
				playButtonPressed = true;
			}
			if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_RETURN && quitButton.selected)
			{
				quit = true;
			}
		}
	}
}

void MainMenu::draw()
{
	//clear the screen
	SDL_SetRenderDrawColor(renderer, 21, 209, 249, 255);
	SDL_RenderClear(renderer);

	//draw bg
	SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

	//draw button
	playButton.draw();
	quitButton.draw();

	//present frame to screen
	SDL_RenderPresent(renderer);
}