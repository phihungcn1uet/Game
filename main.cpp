
#include "LibFile.h"
static SDL_Window* gWindow = NULL;
static SDL_Renderer* gRenderer = NULL;
BaseObject background;
Figure figure;
Enemy enemy;
Rocket rocket;
Boom boom;
Special special;
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
	bool res = background.loadFromFile("img/hello01.jpg",gRenderer);
	return res;
}

bool loadfigure() {
	bool res = figure.loadFromFile("img/maybay.png", gRenderer);
	return res;
}

bool loadbullet() {
	bool res = figure.loadFromFileBullet("img/bullet1.png", gRenderer);
	return res;
}

bool loadenemy() {
	bool res = enemy.loadFromFileEnemy("img/nv.png", gRenderer);
	return res;
}
bool loadrocket() {
	bool res = rocket.loadFromFileRocket("img/rocket.png", gRenderer);
	return res;
}
bool loadboom() {
	bool res =boom.loadFromFileBoom("img/boom.png", gRenderer);
	return res;
}
bool loadspecial() {
	bool res = special.loadFromFile("img/luckybox.png", gRenderer);
	return res;
}
int main(int argc, char* args[])
{
	ImpTimer fps_timer;
	srand(time(0));
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		if (!loadbackground()) {
			std::cout << "Can't load background" << std::endl;
		}
		if (!loadfigure()) {
			std::cout << "Can't load figure" << SDL_GetError() << std::endl;
		}
		if (!loadbullet()) {
			std::cout << "Can't load bullet" << std::endl;
		}
		if (!loadenemy()) {
			std::cout << "Can't load enemy" << std::endl;
		}
		if (!loadrocket()) {
			std::cout << "Can't load rocket" << std::endl;
		}
		if (!loadboom()) {
		std::cout << "Can't load boom" << std::endl;
	    }
		if (!loadspecial()) {
			std::cout << "Can't load special" << std::endl;
		}
		int scrollingOffset =0 ;
			//Main loop flag
			bool quit = false;
			bool check = true;
			//Event handler
			SDL_Event e;
			//While application is running
			
			while (!quit)
			{
				fps_timer.start();
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					figure.handleEvent(e,gRenderer);
				}
				//load background
				--scrollingOffset;
				if (scrollingOffset < -1280)
				{
					scrollingOffset = 0;
				}
				//load background
				background.render(gRenderer, NULL, scrollingOffset,0);
				background.render(gRenderer, NULL, scrollingOffset+1280, 0);
				// di chuyen
				figure.move(gRenderer,quit);
				// xu ly dan
				enemy.random();
				enemy.enemymove(gRenderer,figure.bullets,quit,figure.character,check);
				figure.movebullet(gRenderer);
				int x = SDL_GetTicks64();
				rocket.random(x);
				rocket.rocketmove(x, gRenderer,figure.character,quit,check);
				boom.random(x);
				boom.boommove(x, gRenderer, figure.character, quit,check);
				special.randomspecial(x);
				special.specialappearance(gRenderer, figure.character,check,x);
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderPresent(gRenderer);
				int real_imp_time = fps_timer.get_ticks();
				int time_one_frame = 1000 / FRAME_PER_SECOND; // tinh theo mili giay

				if (real_imp_time < time_one_frame) {
					int delay_time = time_one_frame - real_imp_time;
					if (delay_time >= 0) {
						SDL_Delay(delay_time);
					}
				}
				SDL_RenderClear(gRenderer);
			}
		}
		//Free resources and close SDL
		close();

	return 0;
}

