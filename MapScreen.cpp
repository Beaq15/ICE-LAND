#include "MapScreen.h"



MapScreen::MapScreen(SDL_Renderer* renderer, SnowQueen* snowQueen, int* items)
{
	//NOTE:computer code random is pseudorandom (fake random)
	//setting a seed value for the random algorithm will generate a set of numbers which appear random
	//if we use the same seed value each time then we'll get the exact same 'random' outcomes
	//THEREFORE we will set the seed as a changing value, the seconds since start of the year
	//so that the seed value is different each time we run the game
	//srand(time(NULL));

	this->renderer = renderer;
	this->snowQueen = snowQueen;
	this->items = items;

	//loop through map using nested loop and clear all values out to be zero(walls)
	for (int x = 0; x < 12; x++)
	{
		for (int y = 0; y < 12; y++)
		{
			map[x][y] = 6;
		}
	}
	//Open map text file
	fstream mapFile("assets/mapbea.txt");
	if (mapFile.is_open())
	{
		for (int y = 0; y < 12; y++)
		{
			for (int x = 0; x < 12; x++)
			{
				char grid;//read in a single character from where we are up to in the file
				mapFile >> grid;
				if (grid == 's')
				{
					map[x][y] = 1; 	//sky			
				}
				else if (grid == 'm')
				{
					map[x][y] = 5; 	//smallMountainUp			
				}
				else if (grid == 'd')
				{
					map[x][y] = 4; 	//smallMountainDown			
				}
				else if (grid == 'M')
				{
					map[x][y] = 2; 	//bigMountainUp			
				}
				else if (grid == 'D')
				{
					map[x][y] = 3; 	//biglMountainDown		
				}
				else if (grid == 'i')
				{
					map[x][y] = 11; //iceStoneBigLeft	
				}
				else if (grid == 'I')
				{
					map[x][y] = 12; //iceStoneBigRight	
				}
				else if (grid == 'L')
				{
					map[x][y] = 8; //cornerLUp
				}
				else if (grid == 'l')
				{
					map[x][y] = 7; //cornerLDown
				}
				else if (grid == 'R')
				{
					map[x][y] = 9; //cornerRUP
				}
				else if (grid == 'r')
				{
					map[x][y] = 0; //cornerRDown
				}
				else if (grid == 'S')
				{
					map[x][y] = 10; //sea
				}
				else if (grid == 'p')
				{
					map[x][y] = 13; //icestoneSmall
				}
				else
				{
					map[x][y] = 6; //snow

					if (grid == 'h')
					{
						heroObj.type = 1;
						heroObj.x = x;
						heroObj.y = y;
					}
					else if (grid == 'u')
					{
						door.type = 2;
						door.x = x;
						door.y = y;
					}
					else if (grid == 'c')
					{
						MapObject chest;
						chest.type = 5;
						chest.x = x;
						chest.y = y;

						mapObjects.push_back(chest);
					}
					else if (grid == 'g')
					{
						MapObject glob;
						glob.type = 3;
						glob.x = x;
						glob.y = y;

						mapObjects.push_back(glob);
					}
					else if (grid == 'C')
					{
						MapObject mimic;
						mimic.type = 4;
						mimic.x = x;
						mimic.y = y;

						mapObjects.push_back(mimic);
					}
				}
			}
		}
	}
	//close file
	mapFile.close();

	//LOAD UP TILE TEXTURES
	snowQueenTexture = IMG_LoadTexture(renderer, "assets/elsaTile.png");
	doorTexture = IMG_LoadTexture(renderer, "assets/doorTile.png");
	snowmanTexture = IMG_LoadTexture(renderer, "assets/snowmanTile.png");
	chestTexture = IMG_LoadTexture(renderer, "assets/chestTile.png");
	bigfootTexture = IMG_LoadTexture(renderer, "assets/bigfootTile.png");
	snowTexture = IMG_LoadTexture(renderer, "assets/snow.png");
	skyTexture = IMG_LoadTexture(renderer, "assets/sky.png");
	seaTexture = IMG_LoadTexture(renderer, "assets/sea.png");
	cornerLDownTexture = IMG_LoadTexture(renderer, "assets/cornerLDown.png");
	cornerLUPTexture = IMG_LoadTexture(renderer, "assets/cornerLUP.png");
	cornerRDownTexture = IMG_LoadTexture(renderer, "assets/cornerRDown.png");
	cornerRUPTexture = IMG_LoadTexture(renderer, "assets/cornerRUP.png");
	icestoneBigLeftTexture = IMG_LoadTexture(renderer, "assets/icestoneBigLeft.png");
	icestoneBigRightTexture = IMG_LoadTexture(renderer, "assets/icestoneBigRight.png");
	icestoneSmallTexture = IMG_LoadTexture(renderer, "assets/icestoneSmall.png");
	mountainBigDownTexture = IMG_LoadTexture(renderer, "assets/mountainBigDown.png");
	mountainBigUPTexture = IMG_LoadTexture(renderer, "assets/mountainBigUP.png");
	mountainSmallDownTexture = IMG_LoadTexture(renderer, "assets/mountainSmallDown.png");
	mountainSmallUpTexture = IMG_LoadTexture(renderer, "assets/mountainSmallUp.png");

	//setup info box
	infoBox.setup(renderer);
	infoBox.setText("Welcome to the Ice Land!");
}

MapScreen::~MapScreen()
{
	//CLEANUP TEXTURE MEMORY
	SDL_DestroyTexture(snowQueenTexture);
	SDL_DestroyTexture(doorTexture);
	SDL_DestroyTexture(snowmanTexture);
	SDL_DestroyTexture(bigfootTexture);
	SDL_DestroyTexture(chestTexture);
	SDL_DestroyTexture(seaTexture);
	SDL_DestroyTexture(skyTexture);
	SDL_DestroyTexture(snowTexture);
	SDL_DestroyTexture(mountainSmallUpTexture);
	SDL_DestroyTexture(mountainSmallDownTexture);
	SDL_DestroyTexture(mountainBigUPTexture);
	SDL_DestroyTexture(mountainBigDownTexture);
	SDL_DestroyTexture(icestoneBigLeftTexture);
	SDL_DestroyTexture(icestoneBigRightTexture);
	SDL_DestroyTexture(icestoneSmallTexture);
	SDL_DestroyTexture(cornerLUPTexture);
	SDL_DestroyTexture(cornerLDownTexture);
	SDL_DestroyTexture(cornerRUPTexture);
	SDL_DestroyTexture(cornerRDownTexture);
}

void MapScreen::itemFound()
{
	//randomly pick an item (between 1-4)
	int item = rand() % 4 + 1;//rand gets next number out of random number set (value between 0-2147483647)
	//try find a free slot for this item!
	bool freeSlotFound = false;
	for (int i = 0; i < 10; i++)
	{
		//once find free slot, set it to the item and exit the loop
		if (items[i] == 0)
		{
			freeSlotFound = true;
			items[i] = item;
			break;//exits the loop
		}
	}

	if (freeSlotFound)
	{
		if (item == 1)
			infoBox.setText("Found life regen!");
		else if (item == 2)
			infoBox.setText("Found bomb!");
		else if (item == 3)
			infoBox.setText("Found Attack Boost!");
		else if (item == 4)
			infoBox.setText("Found Defence Boost!");
	}
	else
	{
		infoBox.setText("Your bag is full!");
	}
	infoBox.visible = true;
}

void MapScreen::update()
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
		//if a button was pressed
		if (sdlEvent.type == SDL_KEYDOWN)
		{
			//then check which button
			//did they press ESC key?
			if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			{
				quit = true;
			}
			//hide infobox when enter is pressed
			if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_RETURN)
			{
				infoBox.visible = false;
			}
			if (infoBox.visible == false && snowQueen->getHP() > 0)
			{
				//player movement
				int hx = heroObj.x;
				int hy = heroObj.y;
				//right dpad on keyboard
				if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_RIGHT)
				{
					hx++;
				}
				//left
				if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_LEFT)
				{
					hx--;
				}
				//down dpad on keyboard
				if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_DOWN)
				{
					hy++;
				}
				//left
				if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_UP)
				{
					hy--;
				}
				//if hx and hy are within the grid
				//AND is land we can walk on (map value of 6)
				if (hx >= 0 && hx < 12 && hy >= 0 && hy < 12 && (map[hx][hy] == 6 || map[hx][hy] == 8 || map[hx][hy] == 7 || map[hx][hy] == 9 || map[hx][hy] == 0))
				{
					//set heroObj.x and y to hx and hy
					heroObj.x = hx;
					heroObj.y = hy;



					//can we escape the dungeon?
					if (!doorLocked && !escaped && heroObj.x == door.x && heroObj.y == door.y)
					{
						infoBox.setText("You escaped!");
						infoBox.visible = true;
						escaped = true;
					}
					else if (doorLocked && !escaped && heroObj.x == door.x && heroObj.y == door.y)
					{
						infoBox.setText("Kill all monsters before escaping!");
						infoBox.visible = true;
						if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_RETURN)
						{
							infoBox.visible = false;
						}
					}

					//see if we walked onto a map object
					//for(int i = 1; i <= 10; i++)
					for (list<MapObject>::iterator mo = mapObjects.begin(); mo != mapObjects.end(); mo++)
					{
						//iterator is a special pointer pointing to a position in a list
						//dereferencing(*) iterator gives you access to the item at that point in the list

						//only interact with active map objects
						if ((*mo).active)
						{
							//is hero's x,y overlapping this mapobjects x,y
							if (heroObj.x == mo->x && heroObj.y == mo->y)
							{
								mo->active = false;

								//check map objects type and deal with accordingly
								if (mo->type == 3)
								{
									BattleScreen battle(renderer, snowQueen, items, snowmanType);
									battle.update();
									if (battle.quit)
										quit = true;
									else if (snowQueen->getHP() <= 0)
									{
										infoBox.setText("You died!");
										infoBox.visible = true;
									}
								}
								else if (mo->type == 4)
								{
									BattleScreen battle(renderer, snowQueen, items, bigFootType);
									battle.update();

									if (battle.quit)
										quit = true;
									else if (snowQueen->getHP() <= 0)
									{
										infoBox.setText("You died!");
										infoBox.visible = true;
									}
								}
								else if (mo->type == 5)
								{
									//open chest get item :D
									itemFound();
								}
							}
						}
					}
				}
			}
		}

	}

	//check to see if map objects all inactive and if we should unlock the door
	if (!infoBox.visible && doorLocked)
	{
		bool monstersAlive = false;
		for (MapObject mo : mapObjects)
		{
			//if is a monster(glob or mimic)
			if (mo.type == 3 || mo.type == 4)
			{
				//if is active monster?
				if (mo.active)
				{
					monstersAlive = true;
					break;
				}
			}
		}
		//if all monsters are dead, unlock the door
		if (!monstersAlive)
		{
			doorLocked = false;
			infoBox.setText("The door is unlocked!");
			infoBox.visible = true;
		}
	}

	//has user closed infobox after escaping
	if (!infoBox.visible && (escaped || snowQueen->getHP() <= 0))
	{
		quit = true;
	}
}

void MapScreen::draw() {
	//MAP DRAWING
	//tile representing size of 1 grid thing from map
	SDL_Rect tileRect = { 0,0,32,32 };
	//loop through and draw each grid value from map array
	for (int x = 0; x < 12; x++)
	{
		for (int y = 0; y < 12; y++)
		{
			//MOVE rectangle to grid position with regards to tile width/height
			tileRect.x = x * tileRect.w;
			tileRect.y = y * tileRect.h;
			//SDL_RenderFillRect(renderer, &tileRect);
			//IF is ground, set draw colour to ground colour
			//ELSE set to wall colour
			if (map[x][y] == 1)
			{
				SDL_RenderCopy(renderer, skyTexture, NULL, &tileRect);
			}
			else if (map[x][y] == 6)
			{
				SDL_RenderCopy(renderer, snowTexture, NULL, &tileRect);
			}
			else if (map[x][y] == 5)
			{
				SDL_RenderCopy(renderer, mountainSmallUpTexture, NULL, &tileRect);
			}
			else if (map[x][y] == 4)
			{
				SDL_RenderCopy(renderer, mountainSmallDownTexture, NULL, &tileRect);
			}
			else if (map[x][y] == 2)
			{
				SDL_RenderCopy(renderer, mountainBigUPTexture, NULL, &tileRect);
			}
			else if (map[x][y] == 3)
			{
				SDL_RenderCopy(renderer, mountainBigDownTexture, NULL, &tileRect);
			}
			else if (map[x][y] == 11)
			{
				SDL_RenderCopy(renderer, icestoneBigLeftTexture, NULL, &tileRect);
			}
			else if (map[x][y] == 12)
			{
				SDL_RenderCopy(renderer, icestoneBigRightTexture, NULL, &tileRect);
			}
			else if (map[x][y] == 8)
			{
				SDL_RenderCopy(renderer, cornerLUPTexture, NULL, &tileRect);
			}
			else if (map[x][y] == 7)
			{
				SDL_RenderCopy(renderer, cornerLDownTexture, NULL, &tileRect);
			}
			else if (map[x][y] == 9)
			{
				SDL_RenderCopy(renderer, cornerRUPTexture, NULL, &tileRect);
			}
			else if (map[x][y] == 0)
			{
				SDL_RenderCopy(renderer, cornerRDownTexture, NULL, &tileRect);
			}
			else if (map[x][y] == 10)
			{
				SDL_RenderCopy(renderer, seaTexture, NULL, &tileRect);
			}
			else if (map[x][y] == 13)
			{
				SDL_RenderCopy(renderer, icestoneSmallTexture, NULL, &tileRect);
			}

		}
	}
	//DRAW MAP OBJECTS
	//draw hero
	tileRect.x = heroObj.x * tileRect.w; //e.g hero x = 4, y = 6. tile w = 32 h = 32
	tileRect.y = heroObj.y * tileRect.h;
	SDL_RenderCopy(renderer, snowQueenTexture, NULL, &tileRect);
	//draw door
	tileRect.x = door.x * tileRect.w;
	tileRect.y = door.y * tileRect.h;
	SDL_RenderCopy(renderer, doorTexture, NULL, &tileRect);
	//DRAW MAP OBJECTS IN LIST
	//loop through list and draw each object
	for (MapObject mo : mapObjects)
	{
		//NOTE: mo is a mapObject copy from mapObjects and is not a direct reference to the mapObject in the list
		if (mo.active)
		{
			tileRect.x = mo.x * tileRect.w;
			tileRect.y = mo.y * tileRect.h;
			if (mo.type == 3)//glob
			{
				SDL_RenderCopy(renderer, snowmanTexture, NULL, &tileRect);
			}
			else if (mo.type == 5)
			{
				SDL_RenderCopy(renderer, chestTexture, NULL, &tileRect);
			}
			else
			{
				SDL_RenderCopy(renderer, bigfootTexture, NULL, &tileRect);
			}
		}
	}
	//draw info box on top
	infoBox.draw();

	//present frame to screen
	SDL_RenderPresent(renderer);
}