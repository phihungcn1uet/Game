
#include "LibFile.h"
static SDL_Window* gWindow = NULL;
static SDL_Renderer* gRenderer = NULL;
BaseObject background;
Figure figure;
Enemy enemy;
Rocket rocket;
Boom boom;
Special special;
Life life;
Menu menu;
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
	bool res = background.loadFromFile("img/hello01.png",gRenderer);
	return res;
}

bool loadfigure() {
	bool res = figure.loadFromFile("img/plane.png", gRenderer);
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
bool loadfireball() {
	bool res = figure.loadFromFileFireBall("img/fireball.png", gRenderer);
	return res;
}
bool loadheart() {
	bool res = life.loadFromFile("img/heart.png", gRenderer);
	return res;
}
bool loadmenu() {
	bool res = menu.loadFromFile("img/menu.png", gRenderer);
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
		if (!loadfireball()) {
			std::cout << "Can't load fire ball" << std::endl;
		}
		if (!loadspecial()) {
			std::cout << "Can't load special" << std::endl;
		}
		if (!loadheart()) {
			std::cout << "can't load heart" << std::endl;
		}
		if (!loadmenu()) {
			std::cout << "can't load menu" << std::endl;
		}
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
			std::cout << " Can't load audio" << std::endl;
		}
		int scrollingOffset =0 ;
			//Main loop flag
			bool quit = false;
			bool collision = true;
			bool bullettype = true;
			bool death = false;
			bool playgame = false;
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
					if(playgame == true) figure.handleEvent(e,gRenderer);
					else if (playgame==false) menu.startmenu(e, playgame);
				}
					//load background
				if (playgame == false) {
					menu.render(gRenderer, NULL, 0, 0);
					//menu.startmenu(e, playgame);
				}
				else if (playgame == true) {
					--scrollingOffset;
					if (scrollingOffset < -1280)
					{
						scrollingOffset = 0;
					}
					int x = SDL_GetTicks64();
					//load background
					background.render(gRenderer, NULL, scrollingOffset, 0);
					background.render(gRenderer, NULL, scrollingOffset + 1280, 0);
					// di chuyen
					life.loadlifeani(gRenderer, death, figure.character, special.specialnumlife, x, collision,playgame, figure);
					figure.move(gRenderer, death);
					// xu ly dan
					enemy.random();
					enemy.enemymove(gRenderer, figure.bullets, death, figure.character, collision);
					if (bullettype)figure.movebullet(gRenderer);
					else if (!bullettype) {
						figure.moveball(gRenderer);
					}
					special.randomspecial(x);
					rocket.random(x);
					rocket.rocketmove(gRenderer, figure.character, death, collision, bullettype, figure.bullets);
					boom.random(x);
					boom.boommove(gRenderer, figure.character, death, collision, bullettype, figure.bullets);
					special.specialappearance(gRenderer, figure.character, collision, bullettype, x, figure);
				}
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
	//}
	return 0;
}

