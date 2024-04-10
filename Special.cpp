#include "LibFile.h"

Special::Special() {
	special = NULL;
	sBox = { 0,0,0,0 };
	time1 = 0;
}

Special::~Special() {
	free();
}


bool Special::loadFromFile(std::string path, SDL_Renderer* screen) {
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
			sBox.w = loadedSurface->w;
			sBox.h = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}
	special = newTexture;
	return special != NULL;
}


void Special::free() {
	if (special != NULL)
	{
		SDL_DestroyTexture(special);
		special = NULL;
		sBox.x = 0;
		sBox.y = 0;
	}
}
void Special::randomspecial(const int &a) {
	int time = a / 1000;
	if (time % 10 == 0 && time != 0) {
		int x_pos = 640;
		int y_pos = rand()%640;
		specialpos1.push_back(specialpos(x_pos, y_pos));
    }
	if (specialpos1.size() > 1) specialpos1.erase(specialpos1.begin() + 1);
}
void Special::specialappearance(SDL_Renderer* screen,character &chacracter, bool& check, const int&a) {
	for (int i = 0; i < specialpos1.size(); i++) {
		sBox.x = specialpos1[i].x;
		sBox.y = specialpos1[i].y;
		SDL_RenderCopy(screen, special, NULL, &sBox);
		if (checkCollision(chacracter.mBox, sBox)) {
			check = false;
			specialpos1.erase(specialpos1.begin() + i);
			time1 = a/1000;
			std::cout << time1 << std::endl;
		}
	}
	if (a/1000 - time1 == 5) {
		check = true;
	}
}