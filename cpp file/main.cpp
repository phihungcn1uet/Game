
#include "LibFile.h"
// cac class duoc su dung
static SDL_Window* gWindow = NULL;
static SDL_Renderer* gRenderer = NULL;
BaseObject background;
BaseObject pausebuttom;
Figure figure;
Enemy enemy;
Rocket rocket;
Boom boom;
Special special;
Life life;
Menu menu;
TTF_Font* font_time = NULL;
TTF_Font* font_playorexit = NULL;
long long timewhenplay = 0;

// khoi tao
bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO ) < 0)
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
			if (TTF_Init() == -1) {
				success = false;
			}
			font_time = TTF_OpenFont("font/OpenSans-Semibold.ttf", 20);
			font_playorexit = TTF_OpenFont("font/OpenSans-Semibold.ttf", 60);
			if (font_time != NULL) {
				success = true;
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
	//quit TTF
	TTF_CloseFont(font_time);
	TTF_CloseFont(font_playorexit);
	TTF_Quit();
	//quit mixer
	soundnormalbullet = NULL;
	Mix_FreeChunk(soundrocket);
	Mix_FreeChunk(soundboom);
	Mix_FreeChunk(soundspecial);
}
// khi chet va reset game ve ban dau
void ResetGame() {
	timewhenplay = int(SDL_GetTicks64()) ;
	enemy.enemys.clear();
	enemy.boss1.clear();
	rocket.sRocket1.clear();
	boom.sBoom1.clear();
	enemy.score = 0;
	figure.bullets.clear();
	enemy.boss1.clear();
	enemy.skill1.clear();
	special.specialpos1.clear();
	life.animationlife1.push_back(animationlife(0, 0));
	life.animationlife1.push_back(animationlife(32, 0));
	life.animationlife1.push_back(animationlife(64, 0));
	life.animationlife1.push_back(animationlife(96, 0));
}
// load cac hinh anh
bool loadbackground() {
	bool res = background.loadFromFile("img/background.png",gRenderer);
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
bool loadboss() {
	bool res = enemy.loadFromFileBoss("img/boss.png", gRenderer);
	return res;
}
bool loadbossskill() {
	bool res = enemy.loadFromFileBossSkill("img/bossskill.png", gRenderer);
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
	bool res = life.loadFromFileLife("img/heart.png", gRenderer);
	return res;
}
bool loadmenu() {
	bool res = menu.loadFromFile("img/menu.png", gRenderer);
	return res;
}
bool loadpausebuttom() {
	bool res = pausebuttom.loadFromFile("img/pausegamebuttom.png", gRenderer);
	return res;
}
int main(int argc, char* args[])
{
	// fps va random
	ImpTimer fps_timer;
	srand(time(0));
	fps_timer.start();
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//load cac hinh anh
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
		if (!loadboss()) {
			std::cout << "Can't load boss" << std::endl;
		}
		if (!loadbossskill()) {
			std::cout << "Can't load bossskill" << std::endl;
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
		if (!loadpausebuttom()) {
			std::cout << "Can't load pause buttom" << std::endl;
		}
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
			std::cout << " Can't load audio" << std::endl;
		}
		int scrollingOffset =0 ;
			//cac gia tri bool duoc su dung
		    //bool thoat
			bool quit = false;
			// bool va cham
			bool collision = true;
			//bool kieu dan: dan thuong(true), dan dac biet(false)
			bool bullettype = true;
			// bool nhan vat chet hay chua
			bool death = false;
			// bool co dang choi game hay khong
			bool playgame = false;
			//bool co dang dung game hay khong
			bool pausegame = false;
			// bool co phai luot choi thu 2 tro di hay khong
			bool secondplay = false;
			
			//Time and score text
			TextObject time_game;
			time_game.SetColor(TextObject::WHITE_TEXT);
			//Event handler
			SDL_Event e;
			while (!quit)
			{
				
				while (SDL_PollEvent(&e) != 0)
				{
					//neu quit game
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					// nut dung tro choi
					else if (playgame == true && e.type == SDL_MOUSEBUTTONDOWN ) {
						int x, y;
						SDL_GetMouseState(&x, &y);
						if (x > 1216 && x < 1280 && y>0 && y < 64) {
							playgame = false;
							pausegame = true;
						}
					}
					if (playgame == true && pausegame == false) {
						figure.handleEvent(e, gRenderer);
					}
					//khi lan dau vao game
					if (playgame == false && secondplay == false && pausegame==false ) {
						menu.startmenu(e, playgame, quit, secondplay,timewhenplay,font_playorexit, gRenderer, ResetGame);
						
					}
					// khi da chet het 3 mang va luot choi tiep theo
					else if (playgame == false &&secondplay == true && pausegame==false) {
						 menu.startmenu(e, playgame,quit, secondplay, timewhenplay, font_playorexit, gRenderer, ResetGame);
					}
					// khi tam dung game
					else if (playgame == false && pausegame == true) {
						menu.pausemenu(e, playgame,pausegame, quit,  font_playorexit, gRenderer,figure);
					}
				}
				//khi lan dau vao game
				if (playgame == false && secondplay == false && pausegame == false) {
					menu.render(gRenderer, NULL, 0, 0);
					menu.startmenu(e, playgame, quit, secondplay, timewhenplay, font_playorexit, gRenderer, ResetGame);
				}
				// khi da chet het 3 mang va luot choi tiep theo
				else if (playgame == false && secondplay == true && pausegame == false) {
						menu.render(gRenderer, NULL, 0, 0);
						menu.startmenu(e,playgame, quit, secondplay, timewhenplay, font_playorexit, gRenderer, ResetGame);
				}
				// khi tam dung game
				else if (playgame == false && pausegame == true) {
					menu.render(gRenderer, NULL, 0, 0);
					menu.pausemenu(e,playgame,pausegame, quit, font_playorexit, gRenderer,figure);
				}	
				else if (playgame == true && pausegame == false) {
					// scrolling map
					--scrollingOffset;
					if (scrollingOffset < -1280)
					{
						scrollingOffset = 0;
					}
					// gia tri thoi gian moi lan choi game
				    int time = int(SDL_GetTicks64());
					time -= timewhenplay;
					//load background
					background.render(gRenderer, NULL, scrollingOffset, 0);
					background.render(gRenderer, NULL, scrollingOffset + 1280, 0);
					pausebuttom.render(gRenderer, NULL, 1216, 0);
					// di chuyen
					life.loadlifeani(gRenderer, death,secondplay, figure.character, special.specialnumlife, time, collision,playgame, figure);
					figure.move(gRenderer);
					// xu ly dan va nv dich
					enemy.random();
					enemy.enemymove(gRenderer, figure.bullets, death, figure.character, collision);
					enemy.SetScore(font_time, gRenderer);
					// xu ly boss
					enemy.timerandomboss(time);
					enemy.bossmove(gRenderer, figure.bullets, death,bullettype, figure.character, collision,time,font_time);
					// xu ly loai dan
					if (bullettype)figure.movebullet(gRenderer);
					else if (!bullettype) figure.moveball(gRenderer);
					
					// xu ly ten lua
					rocket.random(time);
					rocket.rocketmove(gRenderer, figure.character, death, collision, bullettype, figure.bullets);
					//xu ly bom
					boom.random(time);
					boom.boommove(gRenderer, figure.character, death, collision, bullettype, figure.bullets);
					//hieu ung dac biet
					special.randomspecial(time);
					special.specialappearance(gRenderer, figure.character, collision, bullettype, time, figure);
					//Show game time
					std::string str_time = "Time: ";
					int timebysecond = time / 1000;
					std::string str_val = std::to_string(timebysecond);
					str_time += str_val;
					time_game.SetText(str_time);
					time_game.loadFromRenderText(font_time, gRenderer);
					time_game.RenderText(gRenderer, SCREEN_WIDTH - 200, 15);
				}
				    // show len man hinh
					SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
					SDL_RenderPresent(gRenderer);
					// game FPS
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

