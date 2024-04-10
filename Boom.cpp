#include "LibFile.h"

Boom :: Boom() {
	bTexture = NULL;
	bBox = { 0,0,0,0 };
	x_pos = 0;
	y_pos = 0;
}
Boom :: ~Boom() {
	free();
}
bool Boom::loadFromFileBoom(std::string path, SDL_Renderer* screen) {
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
			bBox.w = loadedSurface->w;
			bBox.h = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}
	bTexture = newTexture;
	return bTexture != NULL;
}
void Boom::free() {
	if (bTexture != NULL)
	{
		SDL_DestroyTexture(bTexture);
		bTexture = NULL;
		bBox.x = 0;
		bBox.y = 0;
	}
}
void Boom::boommove(int& a, SDL_Renderer* screen, character& character, bool& quit, const bool& check) {
	for (int i = 0; i < sBoom1.size(); i++) {
		sBoom1[i].y += 10;
		bBox.x = sBoom1[i].x;
		bBox.y = sBoom1[i].y;
		SDL_RenderCopy(screen, bTexture, NULL, &bBox);
		if (sBoom1[i].y > SCREEN_HEIGHT) {
			sBoom1.erase(sBoom1.begin() + i);
		}
		if (check) {
			if (checkCollision(character.mBox, bBox)) {
				quit = true;
			}
		}
	}
}

void Boom::random(const int& a) {
	int time = a / 1000;
	if (time % 5 == 0 && time != 0) {
		x_pos = rand()% 1280;
		y_pos = 0;
		sBoom1.push_back(sBoom(x_pos, y_pos));
		if (sBoom1.size() > 1) sBoom1.erase(sBoom1.begin() + 1);
	}
}

