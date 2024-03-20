
#include "LibFile.h"

BaseObject background;
Figure figure;

SDL_Rect wall0 = {0,576,1280,64};
SDL_Rect wall1 = {128,512,128,64};
bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

void close()
{
	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}
bool loadbackground() {
	bool res = background.loadFromFile("img/hello1.jpg",gRenderer);
	return res;
}

bool loadfigure() {
	bool res = figure.loadFromFile("img/nv.png", gRenderer);
	return res;
}


int main(int argc, char* args[])
{
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		if (loadbackground()==false) {
			std::cout << "Can't load background" << std::endl;
		}
		if (loadfigure() == false) {
			std::cout << "Can't load figure" << std::endl;
		}
		//Map
		GameMap Map;
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;
			SDL_Rect camera = { 0, 0, SCREEN_WIDTH/2, SCREEN_HEIGHT/2 };
			//While application is running
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					figure.handleEvent(e);
				}
				
				//load background
				background.render(gRenderer, NULL, 0, 0);
				//load figure
				Map.loadFileMap("map/newmap.txt");
				Map.DrawMap(gRenderer);
				figure.move(gRenderer);
				//Clear screen
				//figure.ColliisonWall(wall0);
				//figure.ColliisonWall(wall1);
				figure.Gravity();
				figure.checkarround();
					//figure.setCamera(camera);
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				//Update screen
				SDL_RenderPresent(gRenderer);
				SDL_RenderClear(gRenderer);
			}
		}
		//Free resources and close SDL
		close();

	return 0;
}

