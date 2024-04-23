#include "LibFile.h"

Rocket::Rocket() {
	rTexture=NULL;
	rBox = { 0,0,0,0 };
	x_pos=0;
	y_pos=0;
}
Rocket :: ~Rocket() {
	free();
}
bool Rocket::loadFromFileRocket(std::string path, SDL_Renderer* screen) {
		free();
		SDL_Texture* newTexture = NULL;

		SDL_Surface* loadedSurface = IMG_Load(path.c_str());
		if (loadedSurface == NULL)
		{
			printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
		}
		else
		{
			SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

			newTexture = SDL_CreateTextureFromSurface(screen, loadedSurface);
			if (newTexture == NULL)
			{
				printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
			}
			else
			{
				rBox.w = loadedSurface->w;
				rBox.h = loadedSurface->h;
			}

			SDL_FreeSurface(loadedSurface);
		}
		rTexture = newTexture;
		return rTexture != NULL;
}
void Rocket::free() {
	if (rTexture != NULL)
	{
		SDL_DestroyTexture(rTexture);
		rTexture = NULL;
		rBox.x = 0;
		rBox.y = 0;
	}
}
void Rocket :: rocketmove(SDL_Renderer *screen,character &character,bool & death,const bool& collision,const bool&bullettype, std::vector <Bullet>& bullets) {
		for (int i = 0; i < sRocket1.size(); i++) {
			sRocket1[i].x -= Rocketvel;
			rBox.x = sRocket1[i].x;
			rBox.y = sRocket1[i].y;
			SDL_RenderCopy(screen, rTexture, NULL, &rBox);
			soundrocket = Mix_LoadWAV("sound/soundrocket.wav");
			Mix_PlayChannel(-1, soundrocket, 0);
			if (sRocket1[i].x < 0) {
				sRocket1.erase(sRocket1.begin() + i);
			}
			if (collision) {
				if (checkCollision(character.mBox, rBox)) {
					death = true;
				}
			}
			if (!bullettype) {
				for (int j = 0; j < bullets.size(); j++) {
					//std :: cout << bullets.size() << std::endl;
					SDL_Rect a = { bullets[j].x,bullets[j].y,128,64 };
					if (checkCollision(a, rBox)) {
						sRocket1.erase(sRocket1.begin() + i);
						bullets.erase(bullets.begin() + j);
					}
				}
			}
		}
}

void Rocket::random(const int& a) {
	//std::cout << a/1000 << std::endl;
	int time = a / 1000;
	int du = a % 1000;
	if (du < 30) {
		if (time % 7 == 0 && time != 0) {
			x_pos = 1280;
			y_pos = rand() % 640;
			sRocket1.push_back(sRocket(x_pos, y_pos));
			if (sRocket1.size() > 1) sRocket1.erase(sRocket1.begin() + 1);
		}
	}
}

