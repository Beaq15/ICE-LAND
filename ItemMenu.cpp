#include "ItemMenu.h"

SDL_Texture* ItemMenu::generateTextTexture(TTF_Font* font, SDL_Color colour, string text)
{
	SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.c_str(), colour);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);

	return textTexture;
}

ItemMenu::~ItemMenu()
{
	SDL_DestroyTexture(noItem);
	SDL_DestroyTexture(lifeRegen);
	SDL_DestroyTexture(bomb);
	SDL_DestroyTexture(attackBoost);
	SDL_DestroyTexture(defenceBoost);
	SDL_DestroyTexture(cancel);
}

void ItemMenu::setup(SDL_Renderer* renderer, int* items, int x, int y)
{
	this->renderer = renderer;
	this->items = items;
	this->x = x;
	this->y = y;

	TTF_Font* font = TTF_OpenFont("assets/openSans_BoldItalic.ttf", 16);
	SDL_Color textColor = { 0,0,0,0 };

	//generate all text textures
	noItem = generateTextTexture(font, textColor, "--");
	lifeRegen = generateTextTexture(font, textColor, "Life regen");
	bomb = generateTextTexture(font, textColor, "Bomb");
	attackBoost = generateTextTexture(font, textColor, "Attack Boost");
	defenceBoost = generateTextTexture(font, textColor, "Defence Boost");
	cancel = generateTextTexture(font, textColor, "Cancel");

	TTF_CloseFont(font);

}

void ItemMenu::moveUp()
{
	selectedItemIndex--;
	//smallest index is 0 in items array, so lets not go negative
	if (selectedItemIndex < 0)
		selectedItemIndex = 0;
}

void ItemMenu::moveDown()
{
	selectedItemIndex++;
	//items array index 0-9, but also we have cancel button as slot 10 in our menu
	if (selectedItemIndex > 10)
		selectedItemIndex = 10;
}

void ItemMenu::draw()
{
	if (!visible)
		return; //skips rest of this function

	SDL_Rect itemButton = { x, y, 100, 20 };

	//loop through 10 items for drawing to screen
	for (int i = 0; i < 10; i++)
	{
		//put button beneath previous button
		itemButton.y = y + (i * itemButton.h);

		//set item buttons background colour based on if its selected or not
		if (selectedItemIndex == i)
			SDL_SetRenderDrawColor(renderer, 217, 43, 90, 255);
		else
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		//render button back colour
		SDL_RenderFillRect(renderer, &itemButton);

		//setup Texture pointer and work out which text texture we need for this item we are rendering
		SDL_Texture* tmpTexture = noItem;
		if (items[i] == 1)
			tmpTexture = lifeRegen;
		else if (items[i] == 2)
			tmpTexture = bomb;
		else if (items[i] == 3)
			tmpTexture = attackBoost;
		else if (items[i] == 4)
			tmpTexture = defenceBoost;

		SDL_Rect textRect;
		textRect.x = itemButton.x + 2;
		textRect.y = itemButton.y + 2;
		//get width of this text texture we are pointing at
		SDL_QueryTexture(tmpTexture, NULL, NULL, &textRect.w, &textRect.h);
		//draw
		SDL_RenderCopy(renderer, tmpTexture, NULL, &textRect);

	}

	//and also do cancel button too
	if (selectedItemIndex == 10)
		SDL_SetRenderDrawColor(renderer, 217, 43, 90, 255);
	else
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	//put button beneath previous button
	itemButton.y = y + (10 * itemButton.h);
	SDL_RenderFillRect(renderer, &itemButton);

	SDL_Rect textRect;
	textRect.x = itemButton.x + 2;
	textRect.y = itemButton.y + 2;
	//get width of this text texture we are pointing at
	SDL_QueryTexture(cancel, NULL, NULL, &textRect.w, &textRect.h);
	//draw
	SDL_RenderCopy(renderer, cancel, NULL, &textRect);
}
